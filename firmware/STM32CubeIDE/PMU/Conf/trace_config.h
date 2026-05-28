/*
 * trace_config.h
 *
 *  Created on: 14 груд. 2020 р.
 *      Author: timohin
 */

#ifndef TRACE_CONFIG_H_
#define TRACE_CONFIG_H_

/* ************************** <Trace Section> ****************************************************************** */

//#ifdef DEBUG

#define EXT4_TRACE_ENABLE		1
#define CYCLONE_TRACE_ENABLE	1
#define GPS_TRACE_ENABLE		0
#define ADC_TRACE_ENABLE		0
#define ONE_SEC_TRACE_ENABLE	0
#define TICK_TRACE_ENABLE		0
#define CALC_TRACE_ENABLE		0
#define C37118_TRACE_ENABLE		0
#define USB_TRACE_ENABLE		0
#define GUI_TRACE_ENABLE		0
#define IEC61850_TRACE_ENABLE	0

//#endif

#if EXT4_TRACE_ENABLE == 1 //Ext4 section
#define EXT4_TRACE(...) {vTaskSuspendAll(); fprintf(stderr, __VA_ARGS__); xTaskResumeAll();}
#else
#define EXT4_TRACE(...)
#endif

#if CYCLONE_TRACE_ENABLE == 1 //Cyclone section
#define TRACE_PRINTF(...) {vTaskSuspendAll(); fprintf(stderr, __VA_ARGS__); xTaskResumeAll();}
#else
#define TRACE_PRINTF(...)
#endif

#if GPS_TRACE_ENABLE == 1 //GPS section
extern traceString gps_channel;
#define GPS_TRACE_PRINTF(...) vTracePrintF(gps_channel, __VA_ARGS__)
#else
#define GPS_TRACE_PRINTF(...)
#endif

#if ADC_TRACE_ENABLE == 1 //ADC trace section
extern traceHandle ADCHandle;
#define ADC_TRACE_BEGIN_INT(...) vTraceStoreISRBegin(ADCHandle)
#define ADC_TRACE_PRINTF(...) vTracePrintF(ADCHandle, __VA_ARGS__)
#define ADC_TRACE_END_INT(...) vTraceStoreISREnd(0)
#else
#define ADC_TRACE_BEGIN_INT(...)
#define ADC_TRACE_PRINTF(...)
#define ADC_TRACE_END_INT(...)
#endif

#if (ONE_SEC_TRACE_ENABLE) //One second timer section
extern traceHandle TIM2Handle;
extern traceString one_sec_channel;
#define ONE_SEC_TRACE_BEGIN_INT(...) vTraceStoreISRBegin(TIM2Handle)
#define ONE_SEC_TRACE_PRINTF(...) vTracePrintF(one_sec_channel, __VA_ARGS__)
#define ONE_SEC_TRACE_END_INT(...) vTraceStoreISREnd(0)
#else
#define ONE_SEC_TRACE_BEGIN_INT(...)
#define ONE_SEC_TRACE_PRINTF(...)
#define ONE_SEC_TRACE_END_INT(...)
#endif

#if TICK_TRACE_ENABLE == 1 //One tick timer section
extern traceHandle TIM4Handle;
#define TICK_BEGIN_INT(...) vTraceStoreISRBegin(TIM4Handle)
#define TICK_TRACE_PRINTF(...) vTracePrintF(TIM4Handle, __VA_ARGS__)
#define TICK_END_INT(...) vTraceStoreISREnd(0)
#else
#define TICK_BEGIN_INT(...)
#define TICK_TRACE_PRINTF(...)
#define TICK_END_INT(...)
#endif

#if CALC_TRACE_ENABLE == 1 //Calc section
extern traceString calc_channel;
#define CALC_TRACE_PRINTF(...) vTracePrintF(calc_channel, __VA_ARGS__)
#else
#define CALC_TRACE_PRINTF(...)
#endif

#if C37118_TRACE_ENABLE == 1 //C37118 section
extern traceString c37118_channel;
#define C37118_TRACE_PRINTF(...) vTracePrintF(c37118_channel, __VA_ARGS__)
#else
#define C37118_TRACE_PRINTF(...)
#endif

#if USB_TRACE_ENABLE == 1 //C37118 section
extern traceString usb_channel;
#define USB_TRACE_PRINTF(...) vTracePrintF(usb_channel, __VA_ARGS__)
#else
#define USB_TRACE_PRINTF(...)
#endif

#if GUI_TRACE_ENABLE == 1 //GUI section
extern traceString gui_channel;
#define GUI_TRACE(...) vTracePrintF(gui_channel, __VA_ARGS__)
#else
#define GUI_TRACE(...)
#endif

#if IEC61850_TRACE_ENABLE == 1 //C37118 section
extern traceString usb_channel;
#define IEC61850_TRACE_PRINTF(...) vTracePrintF(usb_channel, __VA_ARGS__)
#else
#define IEC61850_TRACE_PRINTF(...)
#endif

/* ************************** </Trace Section> *************************************************************** */

#endif /* TRACE_CONFIG_H_ */
