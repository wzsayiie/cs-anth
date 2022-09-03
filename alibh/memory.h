#pragma once

#include "stddef.h"

#if __cplusplus
extern "C" {
#endif

void *_h_realloc(void *ptr, size_t size);
void  _h_free   (void *ptr);

#if __cplusplus
}
#endif
