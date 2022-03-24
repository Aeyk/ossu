#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <sys/types.h>
/* [ ] Implement a vector (mutable array with automatic resizing) */

typedef struct {
  size_t size;  
  size_t *buffer;
} vector;

vector *make_vector(size_t size) {
  vector *result = malloc(sizeof(vector));
  result->size = size;
  result->buffer = malloc(size * sizeof(size_t));
  for(size_t i = 0; i <= size; i++) {
    result->buffer[i] = 0;
  }
  return result;
}

vector *push(vector *vec, size_t element) {
  vec->size = vec->size + 1;
  vec->buffer = realloc(vec->buffer, vec->size * sizeof(size_t));

  if(NULL == vec->buffer) {
    vec->size = vec->size - 1;   
    return -1;
  }
  vec->buffer[vec->size - 1] = element;
  return vec;
}

vector *pop(vector *vec) {
  size_t element = vec->buffer[vec->size - 2];

  vec->size = vec->size - 1;
  vec->buffer = realloc(vec->buffer, vec->size * sizeof(size_t));

  if(NULL == vec->buffer) {
    vec->size = vec->size + 1;   
    return -1;
  }

  return element;
}

void destroy_vector(vector *vector) {
  free(vector);
}

int main(int argc, char** argv) {
  assert(argc >= 1);
  assert(argv != NULL);

  vector *A = make_vector(10);  
  for(int i = 0; i <= 10; i++ ) {
    printf("%d\n", A->buffer[i]);
    A = push(A, 128);
  }
  for(int i = 0; i <= 10; i++ ) {
    printf("%d\n", pop(A));    
  }

  destroy_vector(A);

  int _errno = errno;
  if(errno >= 0)
    return EXIT_SUCCESS;
  else
    return _errno;
}
