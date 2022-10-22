#pragma once

#include "condition.h"
#include "stdbool.h"

//NOTE: only '?' and '*' are supported.

__libf bool iswcpat(const char *pat);
__libf bool wcmatch(const char *pat, const char *str);

__libf char **wccopyfiles(const char *pat, int *num);
__libf void   wcfreefiles(char    **files, int  num);
