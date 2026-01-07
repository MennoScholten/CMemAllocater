#include "allocater.h"
#include <stdio.h>

#define DEBUG
static bool isInitialized = false;
static unsigned char *mem = NULL;
static size_t allocatedMem = 0;

void *allocater(size_t size) {
    if (size <= 0) {
        #ifdef DEBUG
            printf("Incorrect size given: %ld\n", size);
        #endif
        return NULL;
    }
    if (!isInitialized) {
        mem = calloc(MALLOC_SIZE, sizeof(unsigned char));

        if (mem == NULL) {
            #ifdef DEBUG
                printf("Allocation failed\n");
            #endif
            return NULL;
        }
        allocaterHeader_t* hdr = (allocaterHeader_t*) mem;

        if (sizeof(allocaterHeader_t) + size <= MALLOC_SIZE) {
            hdr->nextHdr = NULL;
            hdr->blockSize = size;
            hdr->isFree = false;

            allocatedMem += sizeof(allocaterHeader_t) + size;
            unsigned char *retPointer = (unsigned char*) hdr + sizeof(allocaterHeader_t);

            isInitialized = true;


            #ifdef DEBUG
                printf("Size of Allocation %lu\n", size);
                printf("Total Allocation %lu\n", allocatedMem);
                printf("Size of Header %lu\n", sizeof(allocaterHeader_t));
                printf("Header %p\n", (unsigned char *) hdr);
                printf("Header BlockSize %lu\n", hdr->blockSize);
                printf("Return pointer %p\n", retPointer);
            #endif

            return retPointer;
        }

        #ifdef DEBUG
            printf("Allocation failed\n");
        #endif
        free(mem);
        return NULL;
    }

    if (allocatedMem + sizeof(allocaterHeader_t) + size <= MALLOC_SIZE) {
        allocaterHeader_t *hdr = (allocaterHeader_t*) mem;

        while ((unsigned char*) hdr <= mem + MALLOC_SIZE) {
            if (hdr->isFree && hdr->blockSize >= size) {
                #ifdef DEBUG
                    printf("Header is free\n");
                #endif
                unsigned char *retPointer = (unsigned char*) hdr + sizeof(allocaterHeader_t);

                #ifdef DEBUG
                    printf("Size of Allocation %lu\n", size);
                    printf("Size of Header %lu\n", sizeof(allocaterHeader_t));
                    printf("Return pointer %p\n", retPointer);
                #endif

                return retPointer;
            }
            else if (hdr->nextHdr != NULL) {
                #ifdef DEBUG
                    printf("Going to nextHdr\n");
                #endif
                hdr = hdr->nextHdr;
            }
            else if (hdr->nextHdr == NULL) {
                #ifdef DEBUG
                    printf("NextHdr empty -> creating new header\n");
                #endif
                allocaterHeader_t *nHdr = (allocaterHeader_t*) ((unsigned char*) hdr + sizeof(allocaterHeader_t) + hdr->blockSize);

                nHdr->nextHdr = NULL;
                nHdr->blockSize = size;
                nHdr->isFree = false;

                hdr->nextHdr = nHdr;
                unsigned char *retPointer = (unsigned char*) nHdr + sizeof(allocaterHeader_t);

                allocatedMem += sizeof(allocaterHeader_t) + size;

                #ifdef DEBUG
                    printf("Size of Allocation %lu\n", size);
                    printf("Total Allocation %lu\n", allocatedMem);
                    printf("Size of Header %lu\n", sizeof(allocaterHeader_t));
                    printf("Header %p\n", (unsigned char *) hdr);
                    printf("Header BlockSize %lu\n", hdr->blockSize);
                    printf("Next Header ptr %p\n", (unsigned char *) nHdr);
                    printf("Next Header BlockSize %lu\n", nHdr->blockSize);
                    printf("Return pointer %p\n", retPointer);
                    // printf("Return pointer size %ld\n",retPointer - (unsigned char*) hdr);
                #endif

                return retPointer;
            }

        }
    }

    #ifdef DEBUG
        printf("Out of memory\n");
    #endif
    return NULL;
}
