#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "config.h"

void vApplicationStackOverflowHook( TaskHandle_t xTask, char * pcTaskName ){
	APP_TRACE_ERROR("Stack overflow: task=%s handle=%08lX\n", pcTaskName, (uint32_t)xTask);
	for(;;) ;
}

void vAssertCalled( uint32_t ulLine, const char *pcFile ){
	APP_TRACE_ERROR("Assert Called at line: %lu in file: %s\n", ulLine, pcFile);
	for(;;) ;
}

#if (configUSE_MALLOC_FAILED_HOOK == 1)

void vApplicationMallocFailedHook (void){
	APP_TRACE_ERROR("Malloc failed hook\n");
	for(;;) ;
}

#endif
