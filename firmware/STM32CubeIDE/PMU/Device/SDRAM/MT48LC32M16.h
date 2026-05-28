/*
 * MT48LC32M16.h
 *
 *  Created on: May 9, 2020
 *      Author: timohin
 */

#ifndef MT48LC32M16_H_
#define MT48LC32M16_H_

#include "main.h"

#define SDRAM_BANK_SIZE							 ((uint32_t)0x04000000)

#define SDRAM_TIMEOUT     						 ((uint32_t)0xFFFF)
#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)

#define MT48LC32M16_REFRESH_TIMEOUT		(0.064) //s
#define MT48LC32M16_ROW_COUNT			(8192)

/*
 * External SDRAM used as cacheable Cortex-M7 data memory should not be left in
 * BL=1 / CL=2 mode at 120MHz-class FMC clocks. Burst reads are what make cache
 * linefills viable, and many MT48LC32M16 speed grades require CL=3 above 100MHz.
 */
#define MT48LC32M16_READ_BURST_LENGTH   SDRAM_MODEREG_BURST_LENGTH_8
#define MT48LC32M16_READ_CAS_LATENCY    SDRAM_MODEREG_CAS_LATENCY_3
#define MT48LC32M16_WRITE_BURST_MODE    SDRAM_MODEREG_WRITEBURST_MODE_SINGLE

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

void MT48LC32M16_Init(SDRAM_HandleTypeDef *hsdram, uint32_t fmc_sdram_cmd_target_bank);

#ifdef __cplusplus
}
#endif

#endif /* MT48LC32M16_H_ */
