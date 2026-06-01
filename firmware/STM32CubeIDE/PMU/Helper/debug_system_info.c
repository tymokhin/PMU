#include "debug_system_info.h"

#include "debug_log.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"

static void debugSystemInfoPrintRcc(void)
{
  RCC_ClkInitTypeDef clocks;
  uint32_t flashLatency;

  HAL_RCC_GetClockConfig(&clocks, &flashLatency);

  DEBUG_LOG_PRINTF("[SYS] Core clock      : %lu Hz\r\n",
      (unsigned long) SystemCoreClock);
  DEBUG_LOG_PRINTF("[SYS] HCLK            : %lu Hz\r\n",
      (unsigned long) HAL_RCC_GetHCLKFreq());
  DEBUG_LOG_PRINTF("[SYS] PCLK1           : %lu Hz\r\n",
      (unsigned long) HAL_RCC_GetPCLK1Freq());
  DEBUG_LOG_PRINTF("[SYS] PCLK2           : %lu Hz\r\n",
      (unsigned long) HAL_RCC_GetPCLK2Freq());
  DEBUG_LOG_PRINTF("[SYS] SysClk source   : 0x%08lX\r\n",
      (unsigned long) clocks.SYSCLKSource);
  DEBUG_LOG_PRINTF("[SYS] Flash latency   : %lu WS\r\n",
      (unsigned long) flashLatency);
}

static void debugSystemInfoPrintCacheMpu(void)
{
  DEBUG_LOG_PRINTF("[SYS] I-Cache         : %s\r\n",
      ((SCB->CCR & SCB_CCR_IC_Msk) != 0U) ? "ON" : "OFF");
  DEBUG_LOG_PRINTF("[SYS] D-Cache         : %s\r\n",
      ((SCB->CCR & SCB_CCR_DC_Msk) != 0U) ? "ON" : "OFF");
  DEBUG_LOG_PRINTF("[SYS] MPU             : %s\r\n",
      ((MPU->CTRL & MPU_CTRL_ENABLE_Msk) != 0U) ? "ON" : "OFF");
}

static void debugSystemInfoPrintRtos(void)
{
  DEBUG_LOG_PRINTF("[SYS] FreeRTOS kernel : %s\r\n",
      tskKERNEL_VERSION_NUMBER);
  DEBUG_LOG_PRINTF("[SYS] Tick rate       : %lu Hz\r\n",
      (unsigned long) configTICK_RATE_HZ);
  DEBUG_LOG_PRINTF("[SYS] Max priorities  : %lu\r\n",
      (unsigned long) configMAX_PRIORITIES);
  DEBUG_LOG_PRINTF("[SYS] Heap size       : %lu bytes\r\n",
      (unsigned long) configTOTAL_HEAP_SIZE);
  DEBUG_LOG_PRINTF("[SYS] Free heap       : %lu bytes\r\n",
      (unsigned long) xPortGetFreeHeapSize());
  DEBUG_LOG_PRINTF("[SYS] Tasks created   : %lu\r\n",
      (unsigned long) uxTaskGetNumberOfTasks());
}

void debugSystemInfoPrint(void)
{
  DEBUG_LOG_PRINTF("\r\n");
  DEBUG_LOG_PRINTF("[SYS] ===== PMU startup info =====\r\n");
  DEBUG_LOG_PRINTF("[SYS] Build           : %s %s\r\n", __DATE__, __TIME__);
  DEBUG_LOG_PRINTF("[SYS] Compiler        : GCC %s\r\n", __VERSION__);
  DEBUG_LOG_PRINTF("[SYS] Device ID       : 0x%08lX\r\n",
      (unsigned long) HAL_GetDEVID());
  DEBUG_LOG_PRINTF("[SYS] Revision ID     : 0x%08lX\r\n",
      (unsigned long) HAL_GetREVID());
  DEBUG_LOG_PRINTF("[SYS] HAL version     : 0x%08lX\r\n",
      (unsigned long) HAL_GetHalVersion());
  debugSystemInfoPrintRcc();
  debugSystemInfoPrintCacheMpu();
  debugSystemInfoPrintRtos();
  DEBUG_LOG_PRINTF("[SYS] ============================\r\n");
  DEBUG_LOG_PRINTF("\r\n");
}
