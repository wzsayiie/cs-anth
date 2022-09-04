#pragma once

#include "stdbool.h"

#if __cplusplus
extern "C" {
#endif

//string:

bool startswith(const char *str, const char *pre);
bool endswith  (const char *str, const char *suf);

//path string:

bool ispathsep(char ch);

char *pathcat(char *dir, const char *base);
char *pathtid(char *path);

#if __cplusplus
}
#endif
