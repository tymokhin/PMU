/*
 * ext4_conf.h
 *
 *  Created on: Oct 5, 2020
 *      Author: timohin
 */

#include "FreeRTOS.h"
#include "task.h"

#ifndef EXT4_CONF_H_
#define EXT4_CONF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "config.h"
#include "sysfs.h"

#include <stm32h7_sd_blockdev.h>

#define FS_TASK_STACK_SIZE (8*1024/sizeof(StackType_t))

#define CONFIG_HAVE_OWN_OFLAGS 0

//#define CONFIG_USE_USER_MALLOC

void * ext4_user_malloc(size_t b);
void* ext4_user_calloc(size_t nmemb, size_t size);
void* ext4_user_realloc(void *ptr, size_t size);
#define ext4_user_free free

#ifndef EXT4_TRACE
	#define EXT4_TRACE(...)
#endif

#ifdef __cplusplus
}
#endif

#endif /* EXT4_CONF_H_ */
