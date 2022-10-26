#pragma once

#include "condition.h"
#include "stdint.h"

__host void    _h_sleepmilli(int64_t milli);
__host int64_t _h_nowmilli  (void);

__host int   _h_system(const char *command);
__host char *_h_getenv(const char *name);
__host int   _h_atexit(void (*func)(void));
__host void  _h_exit  (int code);
