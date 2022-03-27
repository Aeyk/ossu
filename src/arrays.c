#define DEBUG
#ifdef DEBUG
# define DEBUG_PRINT(x) printf x
#else
# define DEBUG_PRINT(x) do {} while (0)
#endif

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h> 
#include <assert.h>
#include <math.h>
#include <errno.h>
#include <sys/types.h>

/* [X] Implement a vector (mutable array with automatic resizing) */

typedef struct {
  size_t size;
  size_t fill;
  size_t *buffer;
} vector;

vector *make_vector(size_t size) {
  DEBUG_PRINT(("[INFO] make_vector 	 	 size: %d	fill: %d\n",
               size, 0));
  vector *result = calloc(size , sizeof(vector));
  result->size = size;
  result->fill = 0;
  result->buffer = calloc(size, sizeof(size_t));
  for(int i = 0; i <= size; i++)
    result->buffer[i] = NULL;
  return result;
}

size_t at(vector *vec, size_t index) {
  DEBUG_PRINT(("[INFO] at		  			 	 index: %d fill: %d\n", index, vec->fill));
  return vec->buffer[index];
}

size_t size(vector *vec) {
  DEBUG_PRINT(("[INFO] size 			 %d\n", vec->fill));
  return vec->fill;
}

size_t capacity(vector *vec) {
  DEBUG_PRINT(("[INFO] is_empty 			 %d\n", vec->size - vec->fill));
  return vec->size - vec->fill;
}

bool is_empty(vector *vec) {
  bool result = (0 == size(vec));
  DEBUG_PRINT(("[INFO] is_empty 			 %d\n", result));
  return result;
}


vector *prepend(vector *vec, size_t element) {
  vector *result = vec;
	size_t temp;
	DEBUG_PRINT(("[INFO] prepend	 			 "));
  for(int i = 0; i <= vec->fill; i++) {
    DEBUG_PRINT(("buffer[%d]: %d ", i, vec->buffer[i]));
  }
  //	DEBUG_PRINT(("buffer[%d]: %d ", vec->fill + 1, element));
  DEBUG_PRINT(("\n"));

  if(vec->fill == vec->size) {
    result->fill = vec->fill + 1;
    result->size = vec->size * 2;
    result->buffer = realloc(vec->buffer, result->size * sizeof(size_t));    
  } else {
    result->fill = vec->fill + 1;
    result->size = vec->size;
    result->buffer = vec->buffer;
  }
	
	for(int i = result->fill; i >= 1; i--) {
		result->buffer[i] = result->buffer[i - 1];
	}
	result->buffer[0] = element;
	
  return result;
}

vector *append(vector *vec, size_t element) {
  vector *result = vec;  
  DEBUG_PRINT(("[INFO] append					 "));
  for(int i = 0; i <= vec->fill; i++) {
    DEBUG_PRINT(("buffer[%d]: %d ", i, vec->buffer[i]));
  }
	DEBUG_PRINT(("\n"));
	
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
  return result;
}

vector *pop(vector *vec) {
  size_t element = NULL || vec->buffer[vec->fill];
	DEBUG_PRINT(("[INFO] pop		 	 			 "));

  if(1 <= vec->size) {
		DEBUG_PRINT(("head: %d fill: %d, size: %d\n", element, vec->fill, vec->size));
    vec->buffer[vec->fill] = NULL;
    vec->fill = vec->fill - 1;
  } else {
		DEBUG_PRINT(("head: NULL fill: %d, size: %d\n", element, vec->fill, vec->size));
		return NULL;
	}
  return element;
}

void *shift(vector *vec) {
  size_t element = vec->buffer[0];
  size_t *temp_buffer = vec->buffer;
  DEBUG_PRINT(("[INFO] shift			 	 	 "));
  for(int i = vec->fill; (i - 1) >= 0; i--) {
    int index = vec->fill - i;
    DEBUG_PRINT(("buffer[%d]: %d ", index, vec->buffer[index]));
  }
  DEBUG_PRINT(("\n"));

  if(1 <= vec->fill) {
    vec->fill = vec->fill - 1;
		vec->buffer[0] = vec->buffer[1];				
    for(int i = 0; i <= vec->fill; i += 1) {
      vec->buffer[i] = vec->buffer[i + 1];
    }
  }
  
  return element;
}

vector *insert(vector *vec, size_t index, size_t element) {
  vector *result = vec;
  DEBUG_PRINT(("[INFO] insert	 	 	 	 	 element: %d size: %d\n",
               vec->size, element));
  if(index == vec->fill) {
    result = prepend(result, element);
  } else if (index == 0) {
    result = append(result, element);
  } else {
    result->fill += 1;
    for(int i = result->fill; i <= index; i--) {
      result->buffer[i] = result->buffer[i - 1];
    }
    result->buffer[index] = element;
  }
  return result;
}

vector *delete(vector *vec, size_t index) {
  vector *result = vec;
  if(index == vec->fill) {
    result = pop(result);
  } else if (index == 0) {
    result = shift(result);
  } else {
    result->fill -= 1; 
    for(int i = index; i <= result->fill; i++) {
      result->buffer[i] = result->buffer[i + 1];
    }
    result->buffer[index] = NULL;
  }
  DEBUG_PRINT(("[INFO] delete 	 		 "));
  for(int i = vec->fill; i >= 0; i--) {
    int index = vec->fill - i;
    DEBUG_PRINT(("buffer[%d]: %d ", index, result->buffer[index]));
  }
  DEBUG_PRINT(("\n"));
}

void destroy_vector(vector *vec) {
  DEBUG_PRINT(("[INFO] destroy_vector	 size: %d	fill: %d\n",
               vec->size, vec->fill));
  free(vec->buffer);
  free(vec);
}

int main(int argc, char** argv) {
  assert(argc >= 1);
  assert(argv != NULL);
  
  int _errno = errno;
  if(errno >= 0)
    return EXIT_SUCCESS;
  else
    return _errno;
}
