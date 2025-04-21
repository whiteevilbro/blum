#include "memmgnt.h"

#include <stdlib.h>

void* check(void* p) {
  if (p == NULL)
    exit(42);
  return p;
}

void* smalloc(size_t size) {
  return check(malloc(size));
}

void* srealloc(void* ptr, size_t size) {
  return check(realloc(ptr, size));
}

void* scalloc(size_t count, size_t size) {
  return check(calloc(count, size));
}