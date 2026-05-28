/*
 * sd_blockdev.h
 *
 *  Created on: Jun 8, 2020
 *      Author: timohin
 */

#include <stdint.h>
#include <stdbool.h>

#include <main.h>

#include "ext4_config.h"
#include "ext4_blockdev.h"
#include "FreeRTOS.h"
#include "semphr.h"

#ifndef SD_BLOCKDEV_H_
#define SD_BLOCKDEV_H_

#ifdef __cplusplus
extern "C" {
#endif

struct sd_ext4_blockdev {
	struct ext4_blockdev blockdev;
	struct ext4_blockdev_iface block_dev_iface;
	uint8_t* blockdev_buf;
	SD_HandleTypeDef* hsd;
	void (*init)(void);
	xSemaphoreHandle mutex;
	xSemaphoreHandle smphr;
};

#if defined(configSUPPORT_STATIC_ALLOCATION) && (configSUPPORT_STATIC_ALLOCATION == 1)
struct sd_ext4_blockdev_static {
	struct sd_ext4_blockdev dev;
	StaticSemaphore_t sd_mutex_buff;
	StaticSemaphore_t tx_smphr_buff;
	StaticSemaphore_t rx_smphr_buff;
};
#endif

struct ext4_blockdev * create_sd_ext4_blockdev(SD_HandleTypeDef* hsd, void (*init)(void));
char* entry_to_str(uint8_t type);

#ifdef __cplusplus
}
#endif

#endif
