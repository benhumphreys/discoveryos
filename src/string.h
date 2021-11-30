#ifndef STRING_H
#define STRING_H

#include "types.h"

void *memmove(void *dest, const void *src, size_t n);

void *memset(void *s, int c, size_t n);

void reverse(char *s);

size_t strlen(const char *s);

#endif
