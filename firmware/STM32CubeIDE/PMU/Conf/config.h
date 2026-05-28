/*
 * config.h
 *
 *  Created on: Oct 31, 2020
 *      Author: timohin
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include "FreeRTOS.h"
#include "trace_config.h"

#ifndef APP_TRACE_ERROR
#define APP_TRACE_ERROR(...) TRACE_PRINTF(__VA_ARGS__)
#endif

#if defined(configSUPPORT_STATIC_ALLOCATION) && (configSUPPORT_STATIC_ALLOCATION == 1)
#define OS_STATIC_TASK_SUPPORT ENABLED
#else
#define OS_STATIC_TASK_SUPPORT DISABLED
#endif

/* **************************** <One second capture timer from GPS> ******************************************** */
extern TIM_HandleTypeDef 			htim2;
#define ONE_SEC_TIMER				&htim2
#define ONE_SEC_TIMER_HANDLER		TIM2_IRQHandler
#define ONE_SEC_TIMER_IRQ			TIM2_IRQn
#define ONE_SEC_TIMER_INT_PRIORITY	(configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 2)
#define ONE_SEC_CAPTURE_CHANNEL		TIM_CHANNEL_1
#define ONE_SEC_CAPTURE_FLAG		TIM_FLAG_CC1
#define ONE_SEC_TIMER_OVERFLOW_VAL	300000000
/* **************************** </One second capture timer from GPS> ******************************************* */

/* **************************** <Tick generate timer> ********************************************************** */
extern TIM_HandleTypeDef 			htim4;
#define TICK_TIMER					&htim4
#define TICK_TIMER_HANDLER			TIM4_IRQHandler
#define TICK_TIMER_IRQ				TIM4_IRQn
#define TICK_CHANNEL				TIM_CHANNEL_1
#define TICK_TIMER_INT_PRIORITY		(configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 1)
/* **************************** </Tick generate timer> ********************************************************* */

/* **************************** <ADC Externan Interrupt> ******************************************************* */
#define ADC_BUSY_IRQHandler			EXTI0_IRQHandler
#define ADC_BUSY_IRQn				EXTI0_IRQn
#define ADC_BUSY_INT_PRIORITY		(configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 4)
#define ADC_FIRSTDATA_IRQn 			EXTI1_IRQn
#define ADC_FIRSTDATA_INT_PRIORITY	(configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 3)

#define ADC_DATA_PORT				ADC_DB0_GPIO_Port
#define ADC_DATA_SHIFT				8
#define ADC_DATA_MASK				0x0000FF00
/* **************************** </ADC Externan Interrupt> ****************************************************** */

/* **************************** <SD Card Controller Interrupt priority> **************************************** */
#define SD_INT_PRIORITY 			(configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 1)
//#define SD_RX_DMA_INT_PRIORITY 		(configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 5)
//#define SD_TX_DMA_INT_PRIORITY 		(configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 5)
/* **************************** </SD Card Controller Interrupt priority> *************************************** */

/* **************************** <USART1 Interrupt priority> **************************************************** */
#define USART_IRQ_PRIORITY 			(configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 5)
#define USART_TX_DMA_IRQ_PRIORITY 	(configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 5)
#define USART_RX_DMA_IRQ_PRIORITY 	(configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 5)
/* **************************** </USART1 Interrupt priority> *************************************************** */

/* **************************** <Ext Interrupt for SD Card Detect priority> ************************************ */
#define SD_DETECT_INT_PRIORITY 		(configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 5)
/* **************************** </Ext Interrupt for SD Card Detect priority> *********************************** */

/* **************************** <GPS Section> ****************************************************************** */
#define GPS_FILE_NAME 	"/tty/tty1"
#define GPS_DELAY		100
/* **************************** </GPS Section> ***************************************************************** */

//#define TCP	0
//#define UDP	1

#define STATIC_FS
#define STATIC_FS_SIZE 5
#define STATIC_MOUNT_NAME_MAX_LEN 16

#define CONSOLE_TASK_STACK_SIZE (1024/sizeof(StackType_t))
#define CONSOLE_TASK_RIPRITY (configMAX_PRIORITIES-3)

#define CONSOLE_LISTENER_TASK_STACK_SIZE (configMINIMAL_STACK_SIZE*5)
#define CONSOLE_LISTENER_TASK_RIPRITY (configMAX_PRIORITIES-1)


#endif /* CONFIG_H_ */
