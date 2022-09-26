#pragma once

#include "fileapi.h"

#define fexists    _h_fexists
#define getexepath _h_getexepath
#define getworkdir _h_getworkdir
#define gettmpdir  _h_gettmpdir
#define dmake      _h_dmake
#define denter     _h_denter
#define dopen      _h_dopen
#define dcopy      _h_dcopy
#define dclose     _h_dclose

//return value need to free.
__libf char *fcopyall(const char *path, size_t *size);

__libf void fwriteall(const char *path, const void *dat, size_t datsz);
__libf void dmakeall (const char *path);

//get sub-items of a directory.
__libf char **dcopyitems(const char *path , int *num);
__libf void   dfreeitems(char      **items, int  num);
