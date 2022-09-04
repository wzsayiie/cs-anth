#pragma once

#include "stdint.h"

#if __cplusplus
extern "C" {
#endif

void    _h_sleepmilli(int64_t milli);
int64_t _h_nowmilli();

int _h_system(const char *cmd);

#if __cplusplus
}
#endif
