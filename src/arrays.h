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
} vector;

extern vector *make_vector(size_t size);
extern size_t at(vector *vec, size_t index);
extern size_t size(vector *vec);
extern size_t capacity(vector *vec);
extern bool is_empty(vector *vec);
extern vector *push(vector *vec, size_t element);
extern vector *push_tail(vector *vec, size_t element);
extern vector *pop(vector *vec);
extern void *pop_head(vector *vec);
extern vector *insert(vector *vec, size_t index, size_t element);
extern vector *delete(vector *vec, size_t index);
extern void destroy_vector(vector *vec);
