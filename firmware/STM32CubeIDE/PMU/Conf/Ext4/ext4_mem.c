/*
 * ext4_mem.c
 *
 *  Created on: Jan 2, 2024
 *      Author: Александр
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void * ext4_user_malloc(size_t b){
	void* ptr = NULL;
	if (b>0){
		ptr = malloc(b);
	}
	return ptr;
}

void* ext4_user_calloc(size_t nmemb, size_t size)
{
	return ext4_user_malloc(nmemb*size);
}


void* ext4_user_realloc(void *ptr, size_t size)
{
	void* new_data = NULL;
	if(size)
	{
		if(!ptr)
			return ext4_user_malloc(size);

		new_data = ext4_user_malloc(size);
		if(new_data)
		{
			memcpy(new_data, ptr, size); // TODO: unsafe copy...
			free(ptr); // we always move the data. free.
		}
	}
	return new_data;
}
