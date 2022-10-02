#ifndef KMALLOC_H
#define KMALLOC_H

#include "types.h"

void *kmalloc(size_t size);
void kmalloc_init(void *ptr, size_t size);
void kfree(void *ptr);

#endif
