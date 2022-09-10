#pragma once

#include "condition.h"
#include "stdint.h"

__export void    _h_sleepmilli(int64_t milli);
__export int64_t _h_nowmilli();

__export int _h_system(const char *cmd);
