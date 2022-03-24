#define DEBUG
#ifdef DEBUG
# define DEBUG_PRINT(x) printf x
#else
# define DEBUG_PRINT(x) do {} while (0)
#endif

#include <math.h>
#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <sys/types.h>

/* [X] Implement a vector (mutable array with automatic resizing) */

typedef struct {
  size_t size;
  size_t fill;
  size_t *buffer;
} vector;

vector *make_vector(size_t size) {
  vector *result = calloc(size , sizeof(vector));
  result->size = size;
  result->fill = 0;
  result->buffer = calloc(size, sizeof(size_t));
  for(int i = 0; i <= size; i++)
    result->buffer[i] = NULL;
  DEBUG_PRINT(("[INFO] make_vector	 	size: %d	fill: %d\n",
               result->size, result->fill));
  return result;
}

vector *push(vector *vec, size_t element) {
  vector *result = vec;
  if(vec->fill == vec->size) {
    result->fill = vec->fill + 1;
    result->size = vec->size * 2;
    result->buffer = realloc(vec->buffer, result->size * sizeof(size_t));    
  } else {
    result->fill = vec->fill + 1;
    result->size = vec->size;
    result->buffer = vec->buffer;
  }
  result->buffer[result->fill] = element;
  DEBUG_PRINT(("[INFO] push			size: %d	fill: %d	buffer[fill]: %d", 
               result->size, result->fill, result->buffer[result->fill] ));
  for(int i = 0; i <= vec->fill; i++) {
    DEBUG_PRINT((" buffer[%d]: %d ", i, result->buffer[i]));
  }
  DEBUG_PRINT(("\n"));
  return result;
}

vector *pop(vector *vec) {
  size_t element = vec->buffer[vec->fill];
  if(0 <= vec->fill - 1) {
    vec->buffer[vec->fill] = NULL;
    vec->fill = vec->fill - 1;
  }
  DEBUG_PRINT(("[INFO] pop			element: %d", element));
  DEBUG_PRINT(("\n"));
  return element;
}

void *pop_head(vector *vec) {
  size_t past;
  size_t element = vec->buffer[0];
  size_t *temp_buffer = vec->buffer;
  if(0 <= vec->fill) {
    vec->fill = vec->fill - 1;
    temp_buffer[0] = vec->buffer[1];
    for(int i = 1; i <= vec->fill; i += 1) {
      temp_buffer[i - 1] = vec->buffer[i];
    }
  }
  // memcpy(vec->fill, temp_buffer, vec->size);
  DEBUG_PRINT(("[INFO] pop_head 	 	"/* size: %d	fill: %d	buffer[fill]: %d", */
               /* vec->size, vec->fill, element */));
  for(int i = vec->fill; i >= 0; i--) {
    int index = vec->fill - i;
    DEBUG_PRINT(("buffer[%d]: %d ", index, vec->buffer[index]));
  }
  DEBUG_PRINT(("\n"));


  return element;
}

void destroy_vector(vector *vec) {
  DEBUG_PRINT(("[INFO] destroy_vector		size: %d	fill: %d\n",
               vec->size, vec->fill));
  free(vec->buffer);
  free(vec);
}

int main(int argc, char** argv) {
  assert(argc >= 1);
  assert(argv != NULL);

  /* vector *A = make_vector(2); */
  /* for(int i = 0; i <= 10; ++i ) { */
  /*   A = push(A, 128); */
  /*   pop(A); */
  /* } */

  /* for(int i = 0; i <= 8; ++i ) { */
  /*   A = push(A, 255); */
  /* } */
  
  /* for(int i = 0; i <= 8; ++i ) { */
  /*   pop(A); */
  /* } */
  /* destroy_vector(A); */

  vector *B = make_vector(1);
  for(int i = 0; i <= 4; i++) {
    B = push(B, pow(2, i));
  }
  for(int i = 0; i <= 4; i++ ) {
    pop_head(B);
  }
  destroy_vector(B);

  vector *C = make_vector(2);
  for(int i = 0; i <= 4; i++) {
    C = push(C, i*2);
  }
  for(int i = 0; i <= 4; i++) {
    pop(C);
  }
  destroy_vector(C);
  
  int _errno = errno;
  if(errno >= 0)
    return EXIT_SUCCESS;
  else
    return _errno;
}
