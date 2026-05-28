/**
 * @file os_port_config.h
 * @brief RTOS port configuration file
 *
 * @section License
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Copyright (C) 2010-2019 Oryx Embedded SARL. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * @author Oryx Embedded SARL (www.oryx-embedded.com)
 * @version 1.9.6
 **/

#include "trace_config.h"
#include "config.h"

#ifndef _OS_PORT_CONFIG_H
#define _OS_PORT_CONFIG_H

//Select underlying RTOS
#define USE_FREERTOS

#define GPL_LICENSE_TERMS_ACCEPTED

//extern void *	 _memcpy (void * dest, const void *str, size_t size);
//
//#define osMemcpy(dest, src, length) do { memcpy(dest, src, (length + 3UL) & ~3UL); } while(0)
//#define osMemmove(dest, src, length) do { __DSB(); memmove(dest, src, (length + 3UL) & ~3UL);  } while(0)
//#define osMemset(p, value, length) do { __DSB(); memset(p, value, (length + 3UL) & ~3UL); } while(0)

//#define osMemcpy(dest, src, length) do { __DSB(); memcpy(dest, src, length);  __DSB();} while(0)
//#define osMemmove(dest, src, length) do { __DSB(); memmove(dest, src, length);  __DSB();} while(0)
//#define osMemset(p, value, length) do { __DSB(); memset(p, value, length);  __DSB();} while(0)

//#include <string.h>
//#include "cache.h"
//#define osMemset(p, value, length) do {SCB_CLEANDCACHE(p, length); memset(p, value, length); SCB_INVALIDATEDCACHE(p, length);} while (0)
//#define osMemcpy(dest, src, length) do {SCB_CLEANDCACHE((void*)dest, length); SCB_CLEANDCACHE((void*)src, length); memcpy(dest, src, length); SCB_INVALIDATEDCACHE((void*)dest, length); SCB_INVALIDATEDCACHE((void*)src, length); } while (0)
//#define osMemmove(dest, src, length) do {SCB_CLEANDCACHE(dest, length); SCB_CLEANDCACHE(src, length); memmove(dest, src, length); SCB_INVALIDATEDCACHE(dest, length); SCB_INVALIDATEDCACHE(src, length);} while (0)

#endif
