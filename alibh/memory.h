#pragma once

#include "condition.h"
#include "stddef.h"

__host void *_h_realloc(void *ptr, size_t size);
__host void  _h_free   (void *ptr);
