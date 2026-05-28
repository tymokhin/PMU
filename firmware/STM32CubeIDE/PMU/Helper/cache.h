/*
 * cache.h
 *
 *  Created on: Jan 8, 2024
 *      Author: Александр
 */

#include "main.h"

#ifndef CACHE_H_
#define CACHE_H_

#define ALIGN_BOUND				  ((uint32_t)(__SCB_DCACHE_LINE_SIZE - 1))

/*#define SCB_CLEANDCACHE(BUF, SIZE) SCB_CleanDCache_by_Addr( \
//		(uint32_t*)((uint32_t)(BUF) & ~ALIGN_BOUND),  \
//		((uint32_t)((BUF) + (SIZE) + ALIGN_BOUND) & ~ALIGN_BOUND)-((uint32_t)(BUF) & ~ALIGN_BOUND))

//#define SCB_INVALIDATEDCACHE(BUF, SIZE) SCB_InvalidateDCache_by_Addr( \
//		(uint32_t*)((uint32_t)(BUF) & ~ALIGN_BOUND),  \
//		((uint32_t)((BUF) + (SIZE) + ALIGN_BOUND) & ~ALIGN_BOUND)-((uint32_t)(BUF) & ~ALIGN_BOUND))
 */


__STATIC_FORCEINLINE void SCB_CLEANDCACHE(void *addr, int32_t dsize){
#if defined (__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
  if ( dsize > 0 ) {
	  uint32_t ptr = (uint32_t)addr & ~((uint32_t)(__SCB_DCACHE_LINE_SIZE - 1U));
	  uint32_t end = (uint32_t)addr + dsize;
    __DSB();

    do {
      SCB->DCCMVAC = ptr;             /* register accepts only 32byte aligned values, only bits 31..5 are valid */
      ptr += __SCB_DCACHE_LINE_SIZE;
    } while ( ptr <= end );

    __DSB();
    __ISB();
  }
#endif
}

/*
\brief   D-Cache Invalidate by address
\details Invalidates D-Cache for the given address.
         D-Cache is invalidated starting from a 32 byte aligned address in 32 byte granularity.
         D-Cache memory blocks which are part of given address + given size are invalidated.
\param[in]   addr    address
\param[in]   dsize   size of memory block (in number of bytes)
*/
__STATIC_FORCEINLINE void SCB_INVALIDATEDCACHE (void *addr, int32_t dsize)
{
#if defined (__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
  if ( dsize > 0 ) {
	  uint32_t ptr = (uint32_t)addr & ~((uint32_t)(__SCB_DCACHE_LINE_SIZE - 1U));
	  uint32_t end = (uint32_t)addr + dsize;

    __DSB();

    do {
      SCB->DCIMVAC = ptr;             /* register accepts only 32byte aligned values, only bits 31..5 are valid */
      ptr += __SCB_DCACHE_LINE_SIZE;
    } while ( ptr <= end );

    __DSB();
    __ISB();
  }
#endif
}

#endif /* CACHE_H_ */
