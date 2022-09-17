#pragma once

#include "condition.h"
#include "stdint.h"

__host void _h_sleepmilli(long long milli);
__host long long _h_nowmilli();

__host int _h_system(const char *cmd);
