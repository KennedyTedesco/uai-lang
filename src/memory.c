#include "memory.h"
#include <stdlib.h>

void *uai_malloc(const size_t size) {
  void *ptr = malloc(size);
  if (ptr == NULL) {
	fprintf(stderr, "Fatal: failed to allocate %zu bytes.\n", size);
	exit(EXIT_FAILURE);
  }
  return ptr;
}

void uai_free(void *ptr) {
  free(ptr);
}
