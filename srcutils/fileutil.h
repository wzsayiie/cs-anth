#pragma once

#include "stdbool.h"
#include "stddef.h"

#if __cplusplus
extern "C" {
#endif

size_t freadall (const char *path, char       *buf, size_t bufsz);
void   fwriteall(const char *path, const void *dat, size_t datsz);
void   dmakeall (const char *path);

//get sub-items of a directory.
char **dcopyitems(const char *path , int *num);
void   dfreeitems(char      **items, int  num);

#if __cplusplus
}
#endif
