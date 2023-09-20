#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "malloc.h"

#define MALIGN(x) ((8 - 1 + x) & ~(8 - 1))
#define MALLOCD_PAGE sysconf(_SC_PAGESIZE)

/**
* naive_malloc - naive version of malloc: dynnamically allocate using sb
* @size: number of bytes to allocate
*
* Return: memory address newly allocated, or NULL on error
*/
void *naive_malloc(size_t size)
{
	size_t chunk_header = MALIGN(size + sizeof(size_t));
	static size_t block;
	void *pointer;
	static void *heap_pointer;

	if (!size)
		return (NULL);

	while (block < chunk_header)
	{
		if (heap_pointer)
			sbrk(0);
		else
			MALLOCD_PAGE, heap_pointer = sbrk(MALLOCD_PAGE);

		block = block + MALLOCD_PAGE;
	}
	pointer = heap_pointer;
	memcpy(pointer, &chunk_header, sizeof(chunk_header));
	heap_pointer = (void *)((char *)(pointer) + chunk_header);

	return (
		(void *)(
			(char *)(pointer) + MALIGN(
				sizeof(size_t)
			)
		)
	);
}
