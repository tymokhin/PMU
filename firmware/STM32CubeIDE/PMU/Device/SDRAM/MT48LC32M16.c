/*
 * MT48LC32M16.c
 *
 *  Created on: May 9, 2020
 *      Author: timohin
 */

#include "MT48LC32M16.h"

#include "main.h"

/*  SDRAM refresh period = 64 mc
    Number of rows = 8192
    SDRAM clock frequency = 108 MHz (216/2 MHz)
    COUNT = (SDRAM refresh period / Number of rows )*(SDRAM clock frequency) - 20
    Refresh rate = 0.064 / (8192rows) ) * 108000000 - 20 = 823
*/
//#define REFRESH_COUNT       ((uint32_t)823)
/* Typical value used only on Auto-Refresh command.
   I think that is "AUTO REFRESH period" parameter in SDRAM datasheet
   AUTO_REFRESH_NUMBER = (AUTO REFRESH period [ms])/(SDRAM clock frequency [MHz]) rounded in high
   AUTO_REFRESH_NUMBER = (0.066 ms)*( 108 MHz) = 7.128 -> 8 */
#define AUTO_REFRESH_NUMBER (8)

void MT48LC32M16_Init(SDRAM_HandleTypeDef *hsdram, uint32_t fmc_sdram_cmd_target_bank);

void MT48LC32M16_Init(SDRAM_HandleTypeDef *hsdram, uint32_t fmc_sdram_cmd_target_bank)
{
	FMC_SDRAM_CommandTypeDef command;

	__IO uint32_t tmpmrd =0;
	command.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
	command.CommandTarget = fmc_sdram_cmd_target_bank;
	command.AutoRefreshNumber = 1;
	command.ModeRegisterDefinition = 0;
	if (HAL_SDRAM_SendCommand(hsdram, &command, SDRAM_TIMEOUT) != HAL_OK)
	{
		Error_Handler();
	}
	HAL_Delay(1);
	command.CommandMode = FMC_SDRAM_CMD_PALL;
	command.CommandTarget = fmc_sdram_cmd_target_bank;
	command.AutoRefreshNumber = 1;
	command.ModeRegisterDefinition = 0;
	if (HAL_SDRAM_SendCommand(hsdram, &command, SDRAM_TIMEOUT) != HAL_OK)
	{
		Error_Handler();
	}
	command.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
	command.CommandTarget = fmc_sdram_cmd_target_bank;
	command.AutoRefreshNumber = AUTO_REFRESH_NUMBER;
	command.ModeRegisterDefinition = 0;
	if (HAL_SDRAM_SendCommand(hsdram, &command, SDRAM_TIMEOUT) != HAL_OK)
	{
		Error_Handler();
	}
	tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1          |
					   SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
					   MT48LC32M16_READ_CAS_LATENCY          |
					   SDRAM_MODEREG_OPERATING_MODE_STANDARD |
					   MT48LC32M16_WRITE_BURST_MODE;
	tmpmrd &= ~((uint32_t)0x0007U);
	tmpmrd |= MT48LC32M16_READ_BURST_LENGTH;
	command.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
	command.CommandTarget = fmc_sdram_cmd_target_bank;
	command.AutoRefreshNumber = 1;
	command.ModeRegisterDefinition = tmpmrd;
	if (HAL_SDRAM_SendCommand(hsdram, &command, SDRAM_TIMEOUT) != HAL_OK)
	{
		Error_Handler();
	}

	PLL1_ClocksTypeDef pll1_clocks;
	PLL2_ClocksTypeDef pll2_clocks;

	uint32_t freq = 0;
	switch (__HAL_RCC_GET_FMC_SOURCE()){
	case RCC_FMCCLKSOURCE_D1HCLK: // Domain1 HCLK Clock selected as FMC clock
		freq = SystemD2Clock;
		break;
	case RCC_FMCCLKSOURCE_PLL: //PLL1_Q Clock selected as FMC clock
		HAL_RCCEx_GetPLL1ClockFreq(&pll1_clocks);
		freq = pll1_clocks.PLL1_Q_Frequency;
		break;
	case RCC_FMCCLKSOURCE_PLL2:// PLL2_R Clock selected as FMC clock
		HAL_RCCEx_GetPLL2ClockFreq(&pll2_clocks);
		freq = pll2_clocks.PLL2_R_Frequency;
		break;
	}
	/* SDRAM is clocked at FMC kernel clock divided by SDClockPeriod (2). */
	freq /= 2U;
	if (freq > 0){
		HAL_SDRAM_ProgramRefreshRate(hsdram, (uint32_t)(MT48LC32M16_REFRESH_TIMEOUT / MT48LC32M16_ROW_COUNT * freq - 20));
	}
}



