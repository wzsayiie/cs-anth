#pragma once

#include "stdbool.h"

#if __cplusplus
extern "C" {
#endif

bool hasprefix(const char *str, const char *pre);
bool hassuffix(const char *str, const char *suf);

#if __cplusplus
}
#endif
