#pragma once

#include "condition.h"
#include "stdint.h"

__host void    _h_sleepmilli(int64_t milli);
__host int64_t _h_nowmilli();

__host int _h_system(const char *cmd);
