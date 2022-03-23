#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>

int main(int argc, char** argv) {
  assert(argc >= 1);
  assert(argv != NULL);

  int _errno = errno;
  if(errno >= 0)
    return EXIT_SUCCESS;
  else
    return _errno;
}
