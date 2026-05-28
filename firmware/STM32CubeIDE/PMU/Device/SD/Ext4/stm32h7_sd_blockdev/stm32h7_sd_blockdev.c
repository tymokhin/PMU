/*
 * sd_blockdev.c
 *
 *  Created on: Sep 29, 2019
 *      Author: Александр
 */

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stm32h7_sd_blockdev.h>
#include "ext4.h"
#include "ext4_mbr.h"
#include "ext4_blockdev.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "cache.h"

#ifndef SD_TIMEOUT
#	define SD_TIMEOUT (portMAX_DELAY) // pdMS_TO_TICKS(5000)  /*ms*/
#endif

#define IS_IRQ_MASKED()           (__get_PRIMASK() != 0U)
#define IS_IRQ_MODE()             (__get_IPSR() != 0U)
#define IS_IRQ()                  (IS_IRQ_MODE() || IS_IRQ_MASKED())

/**********************BLOCKDEV INTERFACE**************************************/
static int blockdev_open(struct ext4_blockdev *bdev);
static int blockdev_bread(struct ext4_blockdev *bdev, void *buf, uint64_t blk_id, uint32_t blk_cnt);
static int blockdev_bwrite(struct ext4_blockdev *bdev, const void *buf, uint64_t blk_id, uint32_t blk_cnt);
static int blockdev_close(struct ext4_blockdev *bdev);
static int blockdev_lock(struct ext4_blockdev *bdev);
static int blockdev_unlock(struct ext4_blockdev *bdev);

struct _sd_device_node{
	struct sd_ext4_blockdev* dev;
	struct _sd_device_node* next;
};

static struct _sd_device_node * _sd_devices = NULL;

struct ext4_blockdev * create_sd_ext4_blockdev(SD_HandleTypeDef* hsd, void (*init)(void))
{
	if (init != NULL) init();

	struct sd_ext4_blockdev* dev = (struct sd_ext4_blockdev*)ext4_malloc(sizeof(struct sd_ext4_blockdev));
	if (dev){
		struct _sd_device_node * node = {NULL};

		dev->hsd = hsd;
		dev->mutex = xSemaphoreCreateMutex();
		if (dev->mutex)
			vQueueAddToRegistry(dev->mutex, "Ext4 Mutex");
		else
			goto error;

		dev->smphr = xSemaphoreCreateBinary();
		if (dev->smphr)
			vQueueAddToRegistry(dev->mutex, "Ext4 Semphr");
		else
			goto error;

		dev->blockdev_buf = (uint8_t*) ext4_malloc(hsd->SdCard.LogBlockSize*32);
		if (dev->blockdev_buf)
			memset(dev->blockdev_buf, 0, hsd->SdCard.LogBlockSize*32);
		else
			goto error;

		dev->init = NULL;
		memset(&dev->block_dev_iface, 0, sizeof(struct ext4_blockdev_iface));
		dev->block_dev_iface.open = blockdev_open;
		dev->block_dev_iface.close = blockdev_close;
		dev->block_dev_iface.bread = blockdev_bread;
		dev->block_dev_iface.bwrite = blockdev_bwrite;
		dev->block_dev_iface.lock = blockdev_lock;
		dev->block_dev_iface.unlock = blockdev_unlock;
		dev->block_dev_iface.ph_bsize = hsd->SdCard.LogBlockSize;
		dev->block_dev_iface.ph_bcnt = hsd->SdCard.LogBlockNbr;
		dev->block_dev_iface.ph_bbuf = dev->blockdev_buf;

		dev->blockdev.bdif = &dev->block_dev_iface;
		dev->blockdev.part_offset = 0;
		dev->blockdev.part_size = (uint64_t)(hsd->SdCard.LogBlockNbr) * (uint64_t)(hsd->SdCard.LogBlockSize);
		dev->blockdev.lg_bcnt = hsd->SdCard.LogBlockNbr;
		dev->blockdev.lg_bsize  = hsd->SdCard.LogBlockSize;

		node = (struct _sd_device_node *)ext4_malloc(sizeof(struct _sd_device_node));
		if (node)
			memset(node, 0, sizeof(struct _sd_device_node));
		else
			goto error;

		node->dev = dev;
		node->next = NULL;

		struct _sd_device_node ** last = &_sd_devices;
		while (*last != NULL){
			if ((*last)->dev->hsd == hsd)
				goto error;
			last = &((*last)->next);
		}
		*last = node;

		return &dev->blockdev;
		error:
		if (dev->mutex)
			vSemaphoreDelete(dev->mutex);
		if (dev->smphr)
			vSemaphoreDelete(dev->smphr);
		if (dev->blockdev_buf)
			free(dev->blockdev_buf);
		if (node)
			free(node);
		free(dev);
	}
	return NULL;
}

static int blockdev_lock(struct ext4_blockdev *bdev){
	if (bdev){
		struct sd_ext4_blockdev * dev =(struct sd_ext4_blockdev *)bdev;
		if (!IS_IRQ()){
			if (xSemaphoreTake(dev->mutex, portMAX_DELAY) == pdPASS)
				return EOK;
		} else {
			BaseType_t xTaskWoken = pdFALSE;
			portBASE_TYPE state = xSemaphoreTakeFromISR(dev->mutex, &xTaskWoken);
			portYIELD_FROM_ISR(xTaskWoken);
			if (state == pdPASS)
				return EOK;
		}
	}
	return EIO;
}

static int blockdev_unlock(struct ext4_blockdev *bdev){
	if (bdev){
		struct sd_ext4_blockdev * dev =(struct sd_ext4_blockdev *)bdev;
		if (!IS_IRQ()){
			if (xSemaphoreGive(dev->mutex) == pdPASS)
				return EOK;
		} else {
			BaseType_t xTaskWoken = pdFALSE;
			if (xSemaphoreGiveFromISR(dev->mutex, &xTaskWoken) == pdPASS){
				portYIELD_FROM_ISR(xTaskWoken);
				return EOK;
			}
		}
	}
	return EIO;
}

/******************************************************************************/
static int blockdev_open(struct ext4_blockdev *bdev)
{
	struct sd_ext4_blockdev * dev =(struct sd_ext4_blockdev *)bdev;
	if (dev->hsd->State==HAL_SD_STATE_RESET)
		if (dev->init)
			dev->init();
	if (dev->hsd->State!=HAL_SD_STATE_READY)
		return EIO;
	xSemaphoreGive(dev->smphr);
	return EOK;
}

static int blockdev_close(struct ext4_blockdev *bdev)
{
	struct sd_ext4_blockdev * dev =(struct sd_ext4_blockdev *)bdev;
	if (xSemaphoreTake(dev->smphr, SD_TIMEOUT) != pdPASS)
		return ETIME;
	return EOK;
}

/******************************************************************************/

static int blockdev_bread(struct ext4_blockdev *bdev, void *buf, uint64_t blk_id,
			 uint32_t blk_cnt)
{
	struct sd_ext4_blockdev * dev =(struct sd_ext4_blockdev *)bdev;

	TickType_t time;
	TickType_t is_timeout;

	//Check SD card controller is ready
	time = xTaskGetTickCount();
	HAL_SD_StateTypeDef state_return;
	do
	{
		state_return = HAL_SD_GetState(dev->hsd);
		is_timeout = xTaskGetTickCount() - time < SD_TIMEOUT;
	} while ((state_return != HAL_SD_STATE_READY) && is_timeout);

	if (!is_timeout){
		xSemaphoreGive(dev->smphr);
		return ETIME;
	}

	//Check SD card is ready
	HAL_SD_CardStateTypeDef sd_card_state_return;
	time = xTaskGetTickCount();
	do
	{
		sd_card_state_return = HAL_SD_GetCardState(dev->hsd);
		is_timeout = xTaskGetTickCount()-time < SD_TIMEOUT;
	} while((sd_card_state_return != HAL_SD_CARD_TRANSFER) && is_timeout);

	if (!is_timeout)
	{
		xSemaphoreGive(dev->smphr);
		return EIO;
	}

	//Drop buffer begin and end for prevent damage data before and after buffer
	SCB_CLEANDCACHE((uint32_t*)buf, 1);
	SCB_CLEANDCACHE((uint32_t*)(buf + bdev->bdif->ph_bsize * blk_cnt), 1);

	//Take an RX semaphore
	if (xSemaphoreTake(dev->smphr, SD_TIMEOUT ) != pdPASS)
		return ETIME;
	//Start read SDCard by DMA
	if (HAL_SD_ReadBlocks_DMA(dev->hsd, buf, blk_id, blk_cnt) != HAL_OK){
		xSemaphoreGive(dev->smphr);
		return EIO;
	}

	//Take an RX semaphore again for waiting end of DMA receive
	if (xSemaphoreTake(dev->smphr, SD_TIMEOUT) != pdPASS){
		xSemaphoreGive(dev->smphr);
		return ETIME;
	}

	//Invalidate chach for buffer address
	SCB_INVALIDATEDCACHE((uint32_t*)buf, bdev->bdif->ph_bsize * blk_cnt);

	//Release an RX semaphore for future use
	xSemaphoreGive(dev->smphr);

	return EOK;
}


/******************************************************************************/
static int blockdev_bwrite(struct ext4_blockdev *bdev, const void *buf,
			  uint64_t blk_id, uint32_t blk_cnt)
{
	struct sd_ext4_blockdev * dev =(struct sd_ext4_blockdev *)bdev;

	TickType_t time;
	TickType_t is_timeout;

	//Check SD card controller is ready
	time = xTaskGetTickCount();
	HAL_SD_StateTypeDef state_return;
	do
	{
		state_return = HAL_SD_GetState(dev->hsd);
		is_timeout = xTaskGetTickCount() - time < SD_TIMEOUT;
	} while ((state_return != HAL_SD_STATE_READY) && is_timeout);

	if (!is_timeout){
		xSemaphoreGive(dev->smphr);
		return ETIME;
	}

	//Check SD card is ready
	HAL_SD_CardStateTypeDef sd_card_state_return;
	time = xTaskGetTickCount();
	do
	{
		sd_card_state_return = HAL_SD_GetCardState(dev->hsd);
		is_timeout = xTaskGetTickCount()-time < SD_TIMEOUT;
	} while((sd_card_state_return != HAL_SD_CARD_TRANSFER) && is_timeout);

	if (!is_timeout)
	{
		xSemaphoreGive(dev->smphr);
		return EIO;
	}


	//Drop data from cache to memory for DMA use
	SCB_CLEANDCACHE((uint32_t*)buf, bdev->bdif->ph_bsize * blk_cnt);

	//Take a semaphore
	if (xSemaphoreTake(dev->smphr, SD_TIMEOUT )!=pdPASS)
		return ETIME;

	//Start write SDCard by DMA
	if (HAL_SD_WriteBlocks_DMA(dev->hsd, (void*)buf, blk_id, blk_cnt) != HAL_OK){
		xSemaphoreGive(dev->smphr);
		return EIO;
	}

	//Take an TX semaphore again for waiting end of DMA receive
	if (xSemaphoreTake(dev->smphr, SD_TIMEOUT)!=pdPASS){
		xSemaphoreGive(dev->smphr);
		return ETIME;
	}

	//Release an TX semaphore for future use
	xSemaphoreGive(dev->smphr);

	return EOK;
}

/*********************** SD Callback Function ****************************/

static struct sd_ext4_blockdev * get_ext4_blockdev_by_hsd(SD_HandleTypeDef *hsd){
	struct _sd_device_node * last = _sd_devices;
	while (last != NULL){
		if (last->dev->hsd == hsd)
			return last->dev;
		last = last->next;
	}
	return NULL;
}

void HAL_SD_RxCpltCallback(SD_HandleTypeDef *hsd) {
	BaseType_t xTaskWoken = pdFALSE;
	struct sd_ext4_blockdev * block_device = get_ext4_blockdev_by_hsd(hsd);
	if (!block_device) return;
	if (hsd->State == HAL_SD_STATE_READY)
		xSemaphoreGiveFromISR(block_device->smphr, &xTaskWoken);
	portYIELD_FROM_ISR(xTaskWoken);
}

void HAL_SD_TxCpltCallback(SD_HandleTypeDef *hsd) __attribute__(( alias("HAL_SD_RxCpltCallback")));


void HAL_SD_ErrorCallback(SD_HandleTypeDef *hsd){
	EXT4_TRACE("sd error\n\r");
	Error_Handler();
}

void HAL_SD_AbortCallback(SD_HandleTypeDef *hsd){
	EXT4_TRACE("sd abort\n");
}

char *entry_to_str(uint8_t type)
{
	switch (type) {
	case EXT4_DE_UNKNOWN:
		return "[unk] ";
	case EXT4_DE_REG_FILE:
		return "[fil] ";
	case EXT4_DE_DIR:
		return "[dir] ";
	case EXT4_DE_CHRDEV:
		return "[cha] ";
	case EXT4_DE_BLKDEV:
		return "[blk] ";
	case EXT4_DE_FIFO:
		return "[fif] ";
	case EXT4_DE_SOCK:
		return "[soc] ";
	case EXT4_DE_SYMLINK:
		return "[sym] ";
	default:
		break;
	}
	return "[???]";
}
