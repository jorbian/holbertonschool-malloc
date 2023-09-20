#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "malloc.h"

#define MALIGN(x) ((8 - 1 + x) & ~(8 - 1))
#define MALLOCD_PAGE sysconf(_SC_PAGESIZE)

/**
* _memcpy - reimplenatation of memcpy
* @v_destination: place we're copying to
* @v_source: place we're copying from
* @num_bytes: how much we're copying
*
* Return: memory address newly allocated, or NULL on error
*/
static void *_memcpy(void *v_destination, const void *v_source, size_t num_bytes)
{
  char *dst;
  const char *src;

  dst = v_destination;
  src = v_source;

  while(num_bytes-- > 0)
    *dst++ = *src++;

  return (v_destination);
}

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
	_memcpy(pointer, &chunk_header, sizeof(chunk_header));
	heap_pointer = (void *)((char *)(pointer) + chunk_header);

	return (
		(void *)(
			(char *)(pointer) + MALIGN(
				sizeof(size_t)
			)
		)
	);
}
