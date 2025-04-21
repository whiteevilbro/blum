#ifndef VECTOR_INCLUDED
#define VECTOR_INCLUDED

#include "memmgnt.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef int (*comparator_fn)(const void*, const void*);
typedef int (*eq_fn)(const void*, const void*);

#define GEN_VECTOR(T, NAME, DEFAULT_CAP) \
  GEN_VECTOR_TYPE(T, NAME)               \
  GEN_VECTOR_PROTOTYPES(T, NAME)         \
  GEN_METHODS(T, NAME, DEFAULT_CAP)

#define GEN_METHODS(T, NAME, DEFAULT_CAP) \
  GEN_VECTOR_INIT(T, NAME, DEFAULT_CAP)   \
  GEN_VECTOR_DEINIT(T, NAME)              \
  GEN_NEW_VECTOR(T, NAME)                 \
  GEN_DELETE_VECTOR(T, NAME)              \
  GEN_VECTOR_ENSURE_CAPACITY(T, NAME)     \
  GEN_VECTOR_ADD_TAIL(T, NAME)            \
  GEN_VECTOR_FILL(T, NAME)                \
  GEN_VECTOR_DEL_TAIL(T, NAME)            \
  GEN_VECTOR_GET(T, NAME)                 \
  GEN_VECTOR_GET_OR(T, NAME)              \
  GEN_VECTOR_SET(T, NAME)                 \
  GEN_VECTOR_DEL(T, NAME)                 \
  GEN_VECTOR_GET_LENGTH(T, NAME)          \
  GEN_VECTOR_SORT(T, NAME)                \
  GEN_VECTOR_MAP(T, NAME)                 \
  GEN_VECTOR_FIND(T, NAME)

#define GEN_VECTOR_TYPE(T, NAME) \
  typedef struct {               \
    T* storage;                  \
    size_t size;                 \
    size_t capacity;             \
  } NAME;

#define GEN_VECTOR_PROTOTYPES(T, NAME)  \
  GEN_VECTOR_INIT_P(T, NAME)            \
  GEN_VECTOR_DEINIT_P(T, NAME)          \
  GEN_NEW_VECTOR_P(T, NAME)             \
  GEN_DELETE_VECTOR_P(T, NAME)          \
  GEN_VECTOR_ENSURE_CAPACITY_P(T, NAME) \
  GEN_VECTOR_ADD_TAIL_P(T, NAME)        \
  GEN_VECTOR_FILL_P(T, NAME)            \
  GEN_VECTOR_DEL_TAIL_P(T, NAME)        \
  GEN_VECTOR_GET_P(T, NAME)             \
  GEN_VECTOR_GET_OR_P(T, NAME)          \
  GEN_VECTOR_SET_P(T, NAME)             \
  GEN_VECTOR_DEL_P(T, NAME)             \
  GEN_VECTOR_GET_LENGTH_P(T, NAME)      \
  GEN_VECTOR_SORT_P(T, NAME)            \
  GEN_VECTOR_MAP_P(T, NAME)             \
  GEN_VECTOR_FIND_P(T, NAME)


#define GEN_VECTOR_INIT_P(T, NAME) \
  void NAME##_init(NAME* NAME##_vector);

#define GEN_VECTOR_INIT(T, NAME, DEFAULT_CAP)                       \
  void NAME##_init(NAME* NAME##_vector) {                           \
    NAME##_vector->storage = (T*) smalloc(DEFAULT_CAP * sizeof(T)); \
    NAME##_vector->size = 0;                                        \
    NAME##_vector->capacity = DEFAULT_CAP;                          \
  }

#define GEN_VECTOR_DEINIT_P(T, NAME) \
  void NAME##_deinit(NAME* NAME##_vector);

#define GEN_VECTOR_DEINIT(T, NAME)          \
  void NAME##_deinit(NAME* NAME##_vector) { \
    free(NAME##_vector->storage);           \
  }

#define GEN_NEW_VECTOR_P(T, NAME) \
  NAME* new_##NAME();

#define GEN_NEW_VECTOR(T, NAME)                          \
  NAME* new_##NAME() {                                   \
    NAME* NAME##_vector = (NAME*) smalloc(sizeof(NAME)); \
    NAME##_init(NAME##_vector);                          \
    return NAME##_vector;                                \
  }

#define GEN_DELETE_VECTOR_P(T, NAME) \
  void delete_##NAME(NAME* NAME##_vector);

#define GEN_DELETE_VECTOR(T, NAME)          \
  void delete_##NAME(NAME* NAME##_vector) { \
    NAME##_deinit(NAME##_vector);           \
    free(NAME##_vector);                    \
  }

#define GEN_VECTOR_ENSURE_CAPACITY_P(T, NAME) \
  void NAME##_ensure_capacity(NAME* NAME##_vector, size_t required_cap);

#define GEN_VECTOR_ENSURE_CAPACITY(T, NAME)                                                                 \
  void NAME##_ensure_capacity(NAME* NAME##_vector, size_t required_cap) {                                   \
    if (NAME##_vector->capacity >= required_cap)                                                            \
      return;                                                                                               \
    NAME##_vector->capacity = (((--required_cap) / NAME##_vector->capacity) + 1) * NAME##_vector->capacity; \
    NAME##_vector->storage = srealloc(NAME##_vector->storage, NAME##_vector->capacity * sizeof(T));         \
  }

#define GEN_VECTOR_ADD_TAIL_P(T, NAME) \
  void NAME##_add_tail(NAME* NAME##_vector, T item);

#define GEN_VECTOR_ADD_TAIL(T, NAME)                                \
  void NAME##_add_tail(NAME* NAME##_vector, T item) {               \
    NAME##_ensure_capacity(NAME##_vector, NAME##_vector->size + 1); \
    NAME##_vector->storage[NAME##_vector->size++] = item;           \
  }

#define GEN_VECTOR_FILL_P(T, NAME) \
  void NAME##_fill(NAME* NAME##_vector, size_t count, T item);

#define GEN_VECTOR_FILL(T, NAME)                                \
  void NAME##_fill(NAME* NAME##_vector, size_t count, T item) { \
    size_t n = NAME##_vector->size + count;                     \
    NAME##_ensure_capacity(NAME##_vector, n);                   \
    for (size_t i = NAME##_vector->size; i < n; i++) {          \
      NAME##_vector->storage[i] = item;                         \
    }                                                           \
    NAME##_vector->size = n;                                    \
  }

#define GEN_VECTOR_DEL_TAIL_P(T, NAME) \
  T NAME##_del_tail(NAME* NAME##_vector);

#define GEN_VECTOR_DEL_TAIL(T, NAME)                                                                       \
  T NAME##_del_tail(NAME* NAME##_vector) {                                                                 \
    assert(NAME##_vector->size != 0);                                                                      \
    T ret = NAME##_vector->storage[--NAME##_vector->size];                                                 \
    if (NAME##_vector->size * 4 <= NAME##_vector->capacity) {                                              \
      NAME##_vector->capacity /= 2;                                                                        \
      NAME##_vector->storage = (T*) srealloc(NAME##_vector->storage, NAME##_vector->capacity * sizeof(T)); \
    }                                                                                                      \
    return ret;                                                                                            \
  }

#define GEN_VECTOR_GET_P(T, NAME) \
  T NAME##_get(NAME* NAME##_vector, size_t index);

#define GEN_VECTOR_GET(T, NAME)                     \
  T NAME##_get(NAME* NAME##_vector, size_t index) { \
    assert(index < NAME##_vector->size);            \
    return NAME##_vector->storage[index];           \
  }

#define GEN_VECTOR_GET_OR_P(T, NAME) \
  T NAME##_get_or(NAME* NAME##_vector, size_t index, T _default);

#define GEN_VECTOR_GET_OR(T, NAME)                                 \
  T NAME##_get_or(NAME* NAME##_vector, size_t index, T _default) { \
    if (index >= NAME##_vector->size) {                            \
      return _default;                                             \
    }                                                              \
    return NAME##_get(NAME##_vector, index);                       \
  }

#define GEN_VECTOR_SET_P(T, NAME) \
  void NAME##_set(NAME* NAME##_vector, size_t index, T elem);

#define GEN_VECTOR_SET(T, NAME)                                \
  void NAME##_set(NAME* NAME##_vector, size_t index, T elem) { \
    assert(index < NAME##_vector->size);                       \
    NAME##_vector->storage[index] = elem;                      \
  }

#define GEN_VECTOR_DEL_P(T, NAME) \
  T NAME##_del(NAME* NAME##_vector, size_t index);

#define GEN_VECTOR_DEL(T, NAME)                                               \
  T NAME##_del(NAME* NAME##_vector, size_t index) {                           \
    assert(index < NAME##_vector->size);                                      \
    T* deletion_ptr = NAME##_vector->storage + index;                         \
    T deletion = *deletion_ptr;                                               \
    memmove(deletion_ptr, deletion_ptr + 1, NAME##_vector->size - index - 1); \
    return deletion;                                                          \
  }

#define GEN_VECTOR_GET_LENGTH_P(T, NAME) \
  size_t NAME##_get_length(NAME* NAME##_vector);

#define GEN_VECTOR_GET_LENGTH(T, NAME)            \
  size_t NAME##_get_length(NAME* NAME##_vector) { \
    return NAME##_vector->size;                   \
  }

#define GEN_VECTOR_SORT_P(T, NAME) \
  void NAME##_sort(NAME* NAME##_vector, comparator_fn cmp);

#define GEN_VECTOR_SORT(T, NAME)                                        \
  void NAME##_sort(NAME* NAME##_vector, comparator_fn cmp) {            \
    qsort(NAME##_vector->storage, NAME##_vector->size, sizeof(T), cmp); \
  }

#define GEN_VECTOR_MAP_P(T, NAME) \
  void NAME##_map(NAME* NAME##_vector, T (*func)(T item));

#define GEN_VECTOR_MAP(T, NAME)                                         \
  void NAME##_map(NAME* NAME##_vector, T (*func)(T item)) {             \
    size_t size = NAME##_vector->size;                                  \
    for (size_t i = 0; i < size; i++) {                                 \
      NAME##_set(NAME##_vector, i, func(NAME##_get(NAME##_vector, i))); \
    }                                                                   \
  }

#define GEN_VECTOR_FIND_P(T, NAME) \
  T* NAME##_find(NAME* NAME##_vector, T item, eq_fn eq, size_t entry);

#define GEN_VECTOR_FIND(T, NAME)                                       \
  T* NAME##_find(NAME* NAME##_vector, T item, eq_fn eq, size_t from) { \
    size_t size = NAME##_vector->size;                                 \
    for (size_t i = from; i < size; i++) {                             \
      if (eq(&(NAME##_vector->storage[i]), &item)) {                   \
        return &(NAME##_vector->storage[i]);                           \
      }                                                                \
    }                                                                  \
    return NULL;                                                       \
  }


#endif