#pragma once

#include "condition.h"
#include "stdbool.h"
#include "string.h"

//string:

__libf bool startswith(const char *str, const char *pre);
__libf bool endswith  (const char *str, const char *suf);

//the function is the same as "strndup()" from c23.
//now ms-cl does not support the latter.
__libf char *stridup(const char *str, size_t len);

//path:

__libf bool ispathsep(char ch);

__libf char *pathcat(char *dir, const char *base);
__libf char *pathtid(char *path);
