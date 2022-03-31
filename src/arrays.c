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

/* [X] Implement a array (mutable array with automatic resizing) */

typedef struct {
	size_t size;
	size_t fill;
	size_t *buffer;
} array;

array *make_array(size_t size) {
	DEBUG_PRINT(("[INFO] make_array				 size: %d fill: %d\n",
							 size, 0));
	array *result = calloc(size , sizeof(array));
	result->size = size;
	result->fill = 0;
	result->buffer = calloc(size, sizeof(size_t));
	for(int i = 0; i <= size; i++)
		result->buffer[i] = NULL;
	return result;
}

array *resize(array *arr, size_t size) {
	DEBUG_PRINT(("[INFO] resize					 fill: %d size: %d\n", arr->fill, size));
	array *result = arr;
	if(size == arr->size) {
		return arr;
	} else if (size == 0) {
		destroy_array(arr);
		return make_array(0);
	} else {
		result->size = size;
		result->buffer = realloc(arr->buffer, result->size * sizeof(size_t));
	}
	return arr;
}

size_t at(array *arr, size_t index) {
	DEBUG_PRINT(("[INFO] at							 index: %d fill: %d\n", index, arr->fill));
	return arr->buffer[index];
}

size_t size(array *arr) {
	DEBUG_PRINT(("[INFO] size						 fill: %d\n", arr->fill));
	return arr->fill;
}

size_t capacity(array *arr) {
	DEBUG_PRINT(("[INFO] is_empty				 %d\n", arr->size - arr->fill));
	return arr->size - arr->fill;
}

bool is_empty(array *arr) {
	bool result = (0 == size(arr));
	DEBUG_PRINT(("[INFO] is_empty				 %d\n", result));
	return result;
}

void print_array(array *arr) {
	DEBUG_PRINT(("[INFO] print_array				 "));
	for(int i = 0; i <= arr->fill; i++) {
		DEBUG_PRINT(("buffer[%d]: %d ", i, arr->buffer[i]));
	}
	DEBUG_PRINT(("size: %d fill: %d\n",
							 arr->size, arr->fill));
}

array *prepend(array *arr, size_t element) {
	array *result = arr;
	size_t temp;
	DEBUG_PRINT(("[INFO] prepend				 "));
	for(int i = 0; i < arr->fill; ++i) {
		DEBUG_PRINT(("buffer[%d]: %d ", i, arr->buffer[i]));
	}
	//	DEBUG_PRINT(("buffer[%d]: %d ", arr->fill + 1, element));
	DEBUG_PRINT(("\n"));

	if(arr->fill == arr->size) {
		result = resize(arr, 2*arr->fill);
	} else {
		result->fill = arr->fill + 1;
		result->size = arr->size;
		result->buffer = arr->buffer;
	}

	for(int i = result->fill; i >= 1; i--) {
		result->buffer[i] = result->buffer[i - 1];
	}
	result->buffer[0] = element;

	return result;
}

array *append(array *arr, size_t element) {
	array *result = arr;
	DEBUG_PRINT(("[INFO] append					 "));
	for(int i = 0; i <= arr->fill; i++) {
		DEBUG_PRINT(("buffer[%d]: %d ", i, arr->buffer[i]));
	}
	DEBUG_PRINT(("\n"));

	if(arr->fill == arr->size) {
		result = resize(arr, 2*arr->fill);
	} else {
		result->size = arr->size;
		result->buffer = arr->buffer;
	}
	result->fill = arr->fill + 1;
	result->buffer[result->fill - 1] = element;

	return result;
}

array *pop(array *arr) {
	size_t element = arr->buffer[arr->fill - 1];
	DEBUG_PRINT(("[INFO] pop						 "));

	if(0 == arr->fill) {
		DEBUG_PRINT(("head: NULL fill: %d, size: %d\n", element, arr->fill, arr->size));
		return arr->buffer[arr->fill] = NULL;;
	} else if (arr->fill * 4 <= arr->size) {
		arr = resize(arr, arr->fill / 2);
	} else if(1 <= arr->fill) {
		DEBUG_PRINT(("head: %d fill: %d, size: %d\n", element, arr->fill, arr->size));
		arr->buffer[arr->fill] = NULL;
		arr->fill = arr->fill - 1;
	} else {
		DEBUG_PRINT(("head: NULL fill: %d, size: %d\n", element, arr->fill, arr->size));
		return NULL;
	}
	return element;
}

void *shift(array *arr) {
	size_t element = arr->buffer[0];
	size_t *temp_buffer = arr->buffer;
	DEBUG_PRINT(("[INFO] shift					 "));
	for(int i = arr->fill; (i - 1) >= 0; i--) {
		int index = arr->fill - i;
		DEBUG_PRINT(("buffer[%d]: %d ", index, arr->buffer[index]));
	}
	DEBUG_PRINT(("\n"));

	if(1 <= arr->fill) {
		if (arr->fill * 4 <= arr->size) {
			arr = resize(arr, arr->fill / 2);
		}
		arr->fill = arr->fill - 1;
		arr->buffer[0] = arr->buffer[1];
		for(int i = 0; i <= arr->fill; i += 1) {
			arr->buffer[i] = arr->buffer[i + 1];
		}
	}

	return element;
}

array *insert(array *arr, size_t index, size_t element) {
	if(arr->fill + 1 >= arr->size) {
		arr = resize(arr, 2*arr->fill);
	}

	arr->fill += 1;
	for(int i = arr->fill; i >= index; i--) {
		arr->buffer[i] = arr->buffer[i - 1];
	}
	arr->buffer[index] = element;
	DEBUG_PRINT(("[INFO] insert					 element: %d size: %d fill: %d\n",
							 element, arr->size, arr->fill));

	return arr;
}

array *delete(array *arr, size_t index) {
	DEBUG_PRINT(("[INFO] delete					 "));
	for(int i = 0; i <= arr->fill; i++) {
		DEBUG_PRINT(("buffer[%d]: %d ", i, arr->buffer[i]));
	}
	DEBUG_PRINT(("\n"));
	if(index < 0 || index > arr->fill)
		return arr;


	arr->buffer[index] = NULL;
	for(int i = index; i > arr->fill; i++) {
		arr->buffer[i - 1] = arr->buffer[i];
	}
	arr->fill -= 1;

	if (arr->fill * 4 <= arr->size) {
		arr = resize(arr, arr->fill / 2);
	}

	return arr;
}

void destroy_array(array *arr) {
	DEBUG_PRINT(("[INFO] destroy_array				 size: %d fill: %d\n",
							 arr->size, arr->fill));
	free(arr->buffer);
	free(arr);
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
