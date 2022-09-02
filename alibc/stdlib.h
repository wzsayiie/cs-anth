#pragma once

#include "stdalloc.h"
#include "stdsystem.h"

#if __cplusplus
extern "C" {
#endif

void *calloc(size_t inum, size_t isz);
void *malloc(size_t size);

#if __cplusplus
}
#endif
