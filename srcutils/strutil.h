#pragma once

#include "stdbool.h"

#if __cplusplus
extern "C" {
#endif

//string:

bool hasprefix(const char *str, const char *pre);
bool hassuffix(const char *str, const char *suf);

//path string:

bool ispathsep(char ch);

char *pathcat(char *dir, const char *base);
char *pathtid(char *path);

#if __cplusplus
}
#endif
