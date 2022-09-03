#pragma once

#include "stdbool.h"

#if __cplusplus
extern "C" {
#endif

//NOTE: only '?' and '*' are supported.

bool iswcpat(const char *pat);
bool wcmatch(const char *pat, const char *str);

#if __cplusplus
}
#endif
