#include <debug.h>

#ifndef _FAULT_HOOK_H
#define _FAULT_HOOK_H

#define _Error_Handler(msg, file, line) \
{ if (*msg!='\0') APP_TRACE_ERROR("%s\n\r", msg);\
  APP_TRACE_ERROR("Error in file: '%s' line: %d\n\r", file, line);\
  while(1);}

#define _Warning_Handler(msg, file, line) \
{ if (*msg!='\0') APP_TRACE_ERROR("%s\n\r", msg);\
  APP_TRACE_ERROR("Error in file: '%s' line: %d\n\r", file, line);}

#endif
