#include "mem.h"
#include "stdlib.h"

void *_h_realloc(void *ptr, size_t size) {
    return realloc(ptr, size);
}

void _h_free(void *ptr) {
    free(ptr);
}
