#include "debug_log.h"

#include <stdio.h>
#include "main.h"

volatile int32_t ITM_RxBuffer = ITM_RXBUFFER_EMPTY;

void debugLogInit(void)
{
}

static void debugLogItmPutChar(char c)
{
  uint32_t timeout = 10000U;

  if ((CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk) == 0U)
  {
    return;
  }

  if ((ITM->TCR & ITM_TCR_ITMENA_Msk) == 0U)
  {
    return;
  }

  if ((ITM->TER & 1UL) == 0U)
  {
    return;
  }

  while ((ITM->PORT[0U].u32 == 0UL) && (timeout > 0U))
  {
    timeout--;
  }

  if (timeout > 0U)
  {
    ITM->PORT[0U].u8 = (uint8_t) c;
  }
}

static void debugLogItmWrite(const char *s)
{
  if (s != NULL)
  {
    while (*s != '\0')
    {
      debugLogItmPutChar(*s++);
    }
  }
}

__attribute__((weak)) void debugLogTcpWrite(const char *s)
{
  (void) s;
}

__attribute__((weak)) void debugLogTracealyzerWrite(const char *s)
{
  (void) s;
}

void debugLogBackendWrite(const char *s)
{
#if (DEBUG_LOG_ENABLE != 0)
  #if (DEBUG_LOG_BACKEND == DEBUG_LOG_BACKEND_ITM)
    debugLogItmWrite(s);
  #elif (DEBUG_LOG_BACKEND == DEBUG_LOG_BACKEND_TCP)
    debugLogTcpWrite(s);
  #elif (DEBUG_LOG_BACKEND == DEBUG_LOG_BACKEND_TRACEALYZER)
    debugLogTracealyzerWrite(s);
  #else
    (void) s;
  #endif
#else
  (void) s;
#endif
}

void debugLogPutChar(char c)
{
  char s[2];

  s[0] = c;
  s[1] = '\0';
  debugLogBackendWrite(s);
}

void debugLogWrite(const char *s)
{
  debugLogBackendWrite(s);
}

void debugLogVPrintf(const char *format, va_list args)
{
#if (DEBUG_LOG_ENABLE != 0)
  char buffer[DEBUG_LOG_LINE_BUFFER_SIZE];
  int length;

  length = vsnprintf(buffer, sizeof(buffer), format, args);

  if (length < 0)
  {
    return;
  }

  if (length >= (int) sizeof(buffer))
  {
    length = (int) sizeof(buffer) - 1;
  }

  buffer[length] = '\0';
  debugLogBackendWrite(buffer);
#else
  (void) format;
  (void) args;
#endif
}

void debugLogPrintf(const char *format, ...)
{
#if (DEBUG_LOG_ENABLE != 0)
  va_list args;

  va_start(args, format);
  debugLogVPrintf(format, args);
  va_end(args);
#else
  (void) format;
#endif
}

int32_t __io_putchar(int32_t ch)
{
  debugLogPutChar((char) ch);
  return ch;
}

int32_t __io_getchar(void)
{
#if (DEBUG_LOG_BACKEND == DEBUG_LOG_BACKEND_ITM)
  return ITM_ReceiveChar();
#else
  return -1;
#endif
}
