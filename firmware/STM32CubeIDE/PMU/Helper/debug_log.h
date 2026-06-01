#ifndef DEBUG_LOG_H_
#define DEBUG_LOG_H_

#include <stdarg.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DEBUG_LOG_ENABLE
#define DEBUG_LOG_ENABLE 1
#endif

#ifndef DEBUG_LOG_LINE_BUFFER_SIZE
#define DEBUG_LOG_LINE_BUFFER_SIZE 192
#endif

#define DEBUG_LOG_BACKEND_NONE       0
#define DEBUG_LOG_BACKEND_ITM        1
#define DEBUG_LOG_BACKEND_TCP        2
#define DEBUG_LOG_BACKEND_TRACEALYZER 3

#ifndef DEBUG_LOG_BACKEND
#define DEBUG_LOG_BACKEND DEBUG_LOG_BACKEND_ITM
#endif

void debugLogInit(void);
void debugLogPutChar(char c);
void debugLogWrite(const char *s);
void debugLogVPrintf(const char *format, va_list args);
void debugLogPrintf(const char *format, ...);
void debugLogBackendWrite(const char *s);

void debugLogTcpWrite(const char *s);
void debugLogTracealyzerWrite(const char *s);

#if (DEBUG_LOG_ENABLE != 0)
#define DEBUG_LOG_PRINTF(...) debugLogPrintf(__VA_ARGS__)
#define DBG_FATAL(...)        DEBUG_LOG_PRINTF("[F] " __VA_ARGS__)
#define DBG_ERROR(...)        DEBUG_LOG_PRINTF("[E] " __VA_ARGS__)
#define DBG_WARNING(...)      DEBUG_LOG_PRINTF("[W] " __VA_ARGS__)
#define DBG_INFO(...)         DEBUG_LOG_PRINTF("[I] " __VA_ARGS__)
#define DBG_DEBUG(...)        DEBUG_LOG_PRINTF("[D] " __VA_ARGS__)
#else
#define DEBUG_LOG_PRINTF(...)
#define DBG_FATAL(...)
#define DBG_ERROR(...)
#define DBG_WARNING(...)
#define DBG_INFO(...)
#define DBG_DEBUG(...)
#endif

#ifdef __cplusplus
}
#endif

#endif /* DEBUG_LOG_H_ */
