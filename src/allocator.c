#include "allocater.h"

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

        #ifdef DEBUG
            printf("Mem First pointer %p\n", mem);
            printf("Hdr First pointer %p\n", (unsigned char*) hdr);
        #endif

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
                printf("Size of Header %ld\n", sizeof(allocaterHeader_t));
                printf("Return pointer %p\n", retPointer);
            #endif

            return retPointer;
        }

        #ifdef DEBUG
            printf("Allocation failed\n");
        #endif
        return NULL;
    }

    if (allocatedMem + sizeof(allocaterHeader_t) + size <= MALLOC_SIZE) {
        allocaterHeader_t *hdr = (allocaterHeader_t*) mem;

        while ((size_t)((unsigned char*) hdr - (unsigned char*) mem) <= allocatedMem) {
            if (hdr->isFree && hdr->blockSize >= size) {
                unsigned char *retPointer = (unsigned char*) hdr + sizeof(allocaterHeader_t);

                #ifdef DEBUG
                    printf("Size of Allocation %lu\n", size);
                    printf("Size of Header %lu\n", sizeof(allocaterHeader_t));
                    printf("Return pointer %p\n", retPointer);
                #endif

                return retPointer;
            }
            else if (hdr->nextHdr != NULL) {
                hdr = hdr->nextHdr;
            }
            else if (hdr->nextHdr == NULL) {
                allocaterHeader_t *nHdr = (allocaterHeader_t*) ((unsigned char*) hdr + hdr->blockSize);

                nHdr->nextHdr = NULL;
                nHdr->blockSize = size;
                nHdr->isFree = false;

                hdr->nextHdr = nHdr;
                unsigned char *retPointer = (unsigned char*) hdr + sizeof(allocaterHeader_t);

                allocatedMem += sizeof(allocaterHeader_t) + size;

                #ifdef DEBUG
                    printf("Size of Allocation %lu\n", size);
                    printf("Total Allocation %lu\n", allocatedMem);
                    printf("Size of Header %ld\n", sizeof(allocaterHeader_t));
                    printf("Return pointer %p\n", retPointer);
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
