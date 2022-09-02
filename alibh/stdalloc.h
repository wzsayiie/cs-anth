#pragma once

#include "stddef.h"

#if __cplusplus
extern "C" {
#endif

void *realloc(void *ptr, size_t size);
void  free   (void *ptr);

#if __cplusplus
}
#endif
