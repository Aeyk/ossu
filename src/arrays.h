#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <errno.h>
#include <sys/types.h>

typedef struct {
  size_t size;
  size_t fill;
  size_t *buffer;
} array;

extern array *make_array(size_t size);
extern size_t at(array *vec, size_t index);
extern size_t size(array *vec);
extern size_t capacity(array *vec);
extern bool is_empty(array *vec);
extern array *remove_item(array *arr, size_t needle);
extern array *push(array *vec, size_t element);
extern array *push_tail(array *vec, size_t element);
extern array *pop(array *vec);
extern void *pop_head(array *vec);
extern array *insert(array *vec, size_t index, size_t element);
extern array *delete(array *vec, size_t index);
extern void destroy_array(array *vec);
