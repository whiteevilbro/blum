#ifndef MEMMGNT_INCLUDED
#define MEMMGNT_INCLUDED

#define __need_NULL
#define __need_size_t
#include <stddef.h>

void* check(void* p);
void* smalloc(size_t size);
void* srealloc(void* ptr, size_t size);
void* scalloc(size_t count, size_t size);

#endif
