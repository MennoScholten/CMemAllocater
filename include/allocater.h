#ifndef ALLOCATER_H
#define ALLOCATER_H

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MALLOC_SIZE 1024 * 1024

typedef struct {
    size_t blockSize;
    struct allocaterHeader_t *nextHdr;
} allocaterHeader_t;

void *allocater(size_t size);

#endif
