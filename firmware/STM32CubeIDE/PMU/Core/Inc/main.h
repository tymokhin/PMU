/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
void MX_ETH_Init(void);
void MX_SDMMC2_SD_Init(void);
void MX_USB_OTG_HS_USB_Init(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ADC_BUSY_Pin GPIO_PIN_4
#define ADC_BUSY_GPIO_Port GPIOE
#define ADC_IN1_Pin GPIO_PIN_2
#define ADC_IN1_GPIO_Port GPIOE
#define ADC_MODE2_Pin GPIO_PIN_14
#define ADC_MODE2_GPIO_Port GPIOH
#define ADC_IN2_Pin GPIO_PIN_3
#define ADC_IN2_GPIO_Port GPIOE
#define RI_Pin GPIO_PIN_8
#define RI_GPIO_Port GPIOB
#define ADC_MODE1_Pin GPIO_PIN_13
#define ADC_MODE1_GPIO_Port GPIOH
#define ADC_IN4_Pin GPIO_PIN_6
#define ADC_IN4_GPIO_Port GPIOE
#define ADC_IN3_Pin GPIO_PIN_5
#define ADC_IN3_GPIO_Port GPIOE
#define GPS_RESET_Pin GPIO_PIN_13
#define GPS_RESET_GPIO_Port GPIOC
#define DCD_Pin GPIO_PIN_7
#define DCD_GPIO_Port GPIOB
#define SDIO_DET_Pin GPIO_PIN_3
#define SDIO_DET_GPIO_Port GPIOD
#define ANT_PWR_ON_Pin GPIO_PIN_9
#define ANT_PWR_ON_GPIO_Port GPIOA
#define ADC_IN7_Pin GPIO_PIN_7
#define ADC_IN7_GPIO_Port GPIOF
#define GPS_PWR_ON_Pin GPIO_PIN_6
#define GPS_PWR_ON_GPIO_Port GPIOC
#define LED_ON_Pin GPIO_PIN_7
#define LED_ON_GPIO_Port GPIOC
#define ADC_IN6_Pin GPIO_PIN_6
#define ADC_IN6_GPIO_Port GPIOF
#define ADC_RESET_Pin GPIO_PIN_9
#define ADC_RESET_GPIO_Port GPIOF
#define SIM_PRESENT_Pin GPIO_PIN_6
#define SIM_PRESENT_GPIO_Port GPIOG
#define USB_VBUS_FAULT_Pin GPIO_PIN_7
#define USB_VBUS_FAULT_GPIO_Port GPIOG
#define ADC_RANGE_Pin GPIO_PIN_10
#define ADC_RANGE_GPIO_Port GPIOF
#define ADC_IN8_Pin GPIO_PIN_8
#define ADC_IN8_GPIO_Port GPIOF
#define LED_REST_Pin GPIO_PIN_4
#define LED_REST_GPIO_Port GPIOA
#define ETH_RST_IN_Pin GPIO_PIN_13
#define ETH_RST_IN_GPIO_Port GPIOD
#define JOYSTICK_Y_Pin GPIO_PIN_0
#define JOYSTICK_Y_GPIO_Port GPIOA
#define GPS_SYNC_Pin GPIO_PIN_6
#define GPS_SYNC_GPIO_Port GPIOA
#define PPS_Pin GPIO_PIN_10
#define PPS_GPIO_Port GPIOH
#define ADC_MODE0_Pin GPIO_PIN_12
#define ADC_MODE0_GPIO_Port GPIOH
#define ADC_CONVERT_Pin GPIO_PIN_12
#define ADC_CONVERT_GPIO_Port GPIOD
#define JOYSTICK_X_Pin GPIO_PIN_1
#define JOYSTICK_X_GPIO_Port GPIOA
#define DTR_Pin GPIO_PIN_1
#define DTR_GPIO_Port GPIOB
#define DSR_Pin GPIO_PIN_2
#define DSR_GPIO_Port GPIOB
#define ADC_IN5_Pin GPIO_PIN_12
#define ADC_IN5_GPIO_Port GPIOE
#define ADC_PAR_SER_BYTE_Pin GPIO_PIN_3
#define ADC_PAR_SER_BYTE_GPIO_Port GPIOH
#define ADC_FIRSTDATA_Pin GPIO_PIN_0
#define ADC_FIRSTDATA_GPIO_Port GPIOB
#define USB_VBUS_EN_Pin GPIO_PIN_15
#define USB_VBUS_EN_GPIO_Port GPIOB
#define JOYSTICK_SW_Pin GPIO_PIN_3
#define JOYSTICK_SW_GPIO_Port GPIOA
#define NET_ACT_Pin GPIO_PIN_12
#define NET_ACT_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
