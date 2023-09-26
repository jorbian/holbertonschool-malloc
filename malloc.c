#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "malloc.h"

/**
* _malloc - reimplementation of malloc
* @size: number of bytes requested
*
* Return: Pointer to the start of allocated memory.
*/
void *_malloc(size_t size)
{
	void *pointer;

	static void *heap_start, *chunk_start;
	static size_t unused;

	if (!heap_start)
		heap_start = sbrk(0);

	if (!unused)
	{
		unused = MALLOCD_PAGE;
		sbrk(MALLOCD_PAGE);
	}
	if (!chunk_start)
		chunk_start = heap_start;

	while (size % 8 != 0)
		size++;

	while (unused < (size + sizeof(size_t)))
	{
		sbrk(MALLOCD_PAGE);
		unused += MALLOCD_PAGE;
	}
	pointer = chunk_start;
	chunk_start = (char *)chunk_start + size + sizeof(size_t);
	unused -= (size + sizeof(size_t));
	*((size_t *)pointer) = size;
	pointer = (char *)pointer + sizeof(size_t);

	return (pointer);
}
