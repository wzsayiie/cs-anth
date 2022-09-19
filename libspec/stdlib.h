#pragma once

#include "memory.h"
#include "os.h"

//memory management:

#define realloc _h_realloc
#define free    _h_free

__libf void *calloc(size_t inum, size_t isz);
__libf void *malloc(size_t size);

//program utilities:

#define system _h_system

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
