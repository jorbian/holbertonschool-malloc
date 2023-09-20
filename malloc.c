#include <stdio.h>
#include <stdlib.h>

#include "malloc.h"

/**
* _malloc - reimplementation of malloc
* @size: number of bytes requested
*/
void *_malloc(size_t size)
{
	(void *)size;

	return (size);
}
