#ifndef _MALLOC_H
#define _MALLOC_H

#define MALLOCD_PAGE sysconf(_SC_PAGESIZE)

void *naive_malloc(size_t size);
void *_malloc(size_t size);
void _free(void *ptr);

#endif
