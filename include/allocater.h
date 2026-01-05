#ifndef ALLOCATER_H
#define ALLOCATER_H

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MALLOC_SIZE 1024 * 1024

typedef struct allocaterHeader_t {
    size_t blockSize;
    struct allocaterHeader_t *nextHdr;
    bool isFree;
} allocaterHeader_t;


// typedef struct allocaterHeader_t {
//     size_t blockSize;
//     void *nextHdr;
// } allocaterHeader_t;
//
void *allocater(size_t size);

#endif
