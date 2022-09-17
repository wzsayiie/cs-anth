#pragma once

#include "condition.h"
#include "stdbool.h"

//string:

__libf bool startswith(const char *str, const char *pre);
__libf bool endswith  (const char *str, const char *suf);

//path string:

__libf bool ispathsep(char ch);

__libf char *pathcat(char *dir, const char *base);
__libf char *pathtid(char *path);
