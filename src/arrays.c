#define DEBUG
#include <stdio.h>
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
  #ifdef DEBUG
  printf("result->size %d\nresult->fill %d\n", result->size, result->fill);
  #endif

  return result;
}

vector *push(vector *vec, size_t element) {
  #ifdef DEBUG
  printf("vec->size %d\nvec->fill %d\n", vec->size, vec->fill);
  #endif
  vector *result;
  if(vec->fill <= vec->size - 1) {
    result->fill = vec->fill + 1;
    result->size = vec->size;
    result->buffer = vec->buffer;
  } else {
    result->fill = vec->fill + 1;
    result->size = vec->size * 2;
    result->buffer = realloc(vec->buffer, vec->size * sizeof(size_t));
 } 
  vec->buffer[vec->fill] = element;
  return result ;
}


vector *pop(vector *vec) {
  if(0 < vec->fill) {
    vec->fill = vec->fill - 1;
    vec->buffer[vec->fill] = 0;
    return vec->buffer[vec->fill];
  } else {
    return vec->buffer[vec->fill];
  }
}

void destroy_vector(vector *vec) {
  free(vec->buffer);
  free(vec);
}

int main(int argc, char** argv) {
  assert(argc >= 1);
  assert(argv != NULL);

  vector *A = make_vector(2);  
  for(int i = 0; i <= 10; ++i ) {
    A = push(A, 128);
    printf("A->buffer[A->fill] %d\n", A->buffer[A->fill]);
  }

  /* for(int i = 0; i <= 10; ++i ) { */
  /*   size_t temp = pop(A); */
  /*   printf("%d\n", temp); */
  /* } */

  destroy_vector(A);

  int _errno = errno;
  if(errno >= 0)
    return EXIT_SUCCESS;
  else
    return _errno;
}
