#pragma once

#include "stdbool.h"
#include "xlist.h"

//NOTE: only '?' and '*' are supported.

__libf bool iswcpat(const char *pat);
__libf bool wcmatch(const char *pat, const char *str);

__libf XLIST *wccopyfiles(const char *pat);
