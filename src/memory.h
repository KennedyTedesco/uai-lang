#ifndef UAI_MEMORY_H
#define UAI_MEMORY_H

#include <stdio.h>

void uai_free(void *ptr);
void *uai_malloc(size_t size);
char *dup_string(const char *ch);

#endif
