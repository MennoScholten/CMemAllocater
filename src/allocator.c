#include "allocater.h"
#include <stdio.h>
static bool isInitialized = false;
static unsigned char *mem = NULL;
static size_t allocatedMem = 0;

void *allocater(size_t size) {
    if (!isInitialized) {
        mem = malloc(MALLOC_SIZE);
        if (mem == NULL) {
            #ifdef DEBUG
                printf("Allocation failed\n");
            #endif
            return NULL;
        }

        isInitialized = true;
    }

    if (allocatedMem + size <= MALLOC_SIZE) {
        #ifdef DEBUG
            printf("Allocating %ld bytes\n", size);
        #endif

    }
    else {
        #ifdef DEBUG
            printf("Out of memory\n");
        #endif
        return NULL;
    }



    return NULL;
}
