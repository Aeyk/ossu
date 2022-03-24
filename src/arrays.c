#define DEBUG

#ifdef DEBUG
# define DEBUG_PRINT(x) printf x
#else
# define DEBUG_PRINT(x) do {} while (0)
#endif


#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <sys/types.h>
/* [ ] Implement a vector (mutable array with automatic resizing) */

typedef struct {
  size_t size;
  size_t fill;
  size_t *buffer;
} vector;

vector *make_vector(size_t size) {
  vector *result = malloc(sizeof(vector));
  result->size = size;
  result->fill = 0;
  result->buffer = malloc(size * sizeof(size_t));
  DEBUG_PRINT(("[INFO] make_vector	size: %d	fill: %d\n",
               result->size, result->fill));
  return result;
}

vector *push(vector *vec, size_t element) {
  vector *result = malloc(sizeof(vec));
  memcpy(result, vec, sizeof(vec));
  if(vec->fill == vec->size) {
    result->fill = vec->fill + 1;
    result->size = vec->size * 2;
    result->buffer = realloc(vec->buffer, result->size * sizeof(size_t));    
  } else if(vec->fill <= vec->size - 1) {
    result->fill = vec->fill + 1;
    result->size = vec->size;
    result->buffer = vec->buffer;
  } else {
  } 
  result->buffer[result->fill] = element;
  DEBUG_PRINT(("[INFO] push		size: %d	fill: %d	buffer[fill]: %d\n",
               result->size, result->fill, result->buffer[result->fill]));
  return result;
}

vector *pop(vector *vec) {
  size_t element = vec->buffer[vec->fill];
  if(0 <= vec->fill - 1) {
    vec->fill = vec->fill - 1;
    vec->buffer[vec->fill] = NULL;
  }
  DEBUG_PRINT(("[INFO] pop		size: %d	fill: %d	buffer[fill]: %d\n",
               vec->size, vec->fill, element));
  return element;
}

void destroy_vector(vector *vec) {
  DEBUG_PRINT(("[INFO] destroy_vector	size: %d	fill: %d\n",
               vec->size, vec->fill));
  free(vec->buffer);
  free(vec);
}

int main(int argc, char** argv) {
  assert(argc >= 1);
  assert(argv != NULL);

  vector *A = make_vector(2);  
  for(int i = 0; i <= 10; ++i ) {
    A = push(A, 128);
    pop(A);
  }

  for(int i = 0; i <= 8; ++i ) {
    A = push(A, 255);
  }
  
  for(int i = 0; i <= 8; ++i ) {
    pop(A);
  }

  
  destroy_vector(A);

  int _errno = errno;
  if(errno >= 0)
    return EXIT_SUCCESS;
  else
    return _errno;
}
