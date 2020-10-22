#include "memory.h"
#include <stdlib.h>
#include <string.h>

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

char *dup_string(const char *ch) {
  char *literal = uai_malloc(sizeof(*ch) * (strlen(ch) + 1));
  strcpy(literal, ch);
  return literal;
}
