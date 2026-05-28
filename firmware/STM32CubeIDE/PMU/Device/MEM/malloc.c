#include <stdio.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "malloc.h"

void * malloc(size_t b){
	void* ptr = NULL;
	if (b>0)
		ptr = pvPortMalloc(b);
	return ptr;
}

void free(void * ptr){
	if (ptr)
		vPortFree(ptr);

}

void* calloc(size_t nmemb, size_t size)
{
	return malloc(nmemb * size);
}

void* realloc(void *ptr, size_t size)
{
	if(ptr == NULL)
		return pvPortMalloc(size);

	if(size == 0) {
		vPortFree(ptr);
		return NULL;
	}

	void* new_ptr = pvPortMalloc(size);
	if(new_ptr)
	{
#ifdef malloc_usable_size
		memcpy(new_ptr, ptr, malloc_usable_size(ptr));
#else
		memcpy(new_ptr, ptr, size);
#endif
		free(ptr);
	}
	return new_ptr;
}
