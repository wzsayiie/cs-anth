#pragma once

#include "fileio.h"

#if __cplusplus
extern "C" {
#endif

#define fexists    _h_fexists
#define getexepath _h_getexepath
#define getworkdir _h_getworkdir
#define gettmpdir  _h_gettmpdir
#define dmake      _h_dmake
#define denter     _h_denter
#define dopen      _h_dopen
#define dcopy      _h_dcopy
#define dclose     _h_dclose

char *fcopyall (const char *path, size_t *size); //return value need to free.
void  fwriteall(const char *path, const void *dat, size_t datsz);
void  dmakeall (const char *path);

//get sub-items of a directory.
char **dcopyitems(const char *path , int *num);
void   dfreeitems(char      **items, int  num);

#if __cplusplus
}
#endif
