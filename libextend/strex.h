#pragma once

#include "condition.h"
#include "stdbool.h"
#include "string.h"

//string:

__libf bool startswith(const char *str, const char *pre);
__libf bool endswith  (const char *str, const char *suf);

//path:

__libf bool ispathsep(char ch);

//"dirname()" and "basename()" have different behaviours on different systems.
__libf char *pathbase(const char *path);
__libf char *pathdir (char       *path);

__libf char *pathcat(char *dir , const char *base);
__libf char *pathtid(char *path);
