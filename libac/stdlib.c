#include "stdlib.h"
#include "string.h"

void *calloc(size_t inum, size_t isz) {
    size_t size = inum * isz;

    void *ptr = realloc(NULL, size);
    memset(ptr, 0, size);
    
    return ptr;
}

void *malloc(size_t size) {
    return realloc(NULL, size);
}
