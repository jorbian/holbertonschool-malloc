#include <stdlib.h>
#include <unistd.h>

#include "malloc.h"

/**
* naive_malloc - naive version of malloc: dynnamically allocate using sb
* @size: number of bytes to allocate
*
* Return: memory address newly allocated, or NULL on error
*/
void *naive_malloc(size_t size)
{
	void *prev_break;

	prev_break = sbrk(size);

	if (prev_break == (void *)-1)
		return (NULL);

	return (prev_break);
}

