#pragma once

#include "memory.h"
#include "os.h"

#if __cplusplus
extern "C" {
#endif

//memory management:

#define realloc _h_realloc
#define free    _h_free

void *calloc(size_t inum, size_t isz);
void *malloc(size_t size);

//program utilities:

#define system _h_system

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#if __cplusplus
}
#endif
