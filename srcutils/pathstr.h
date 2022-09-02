#pragma once

#include "stdbool.h"

#if __cplusplus
extern "C" {
#endif

bool ispathsep(char ch);

char *pathcat(char *dir, const char *base);
char *pathtid(char *path);

#if __cplusplus
}
#endif
