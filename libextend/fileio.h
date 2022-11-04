#pragma once

#include "fioapi.h"
#include "xlist.h"

static bool   (*const fexists   )(const char *, bool *) = _h_fexists   ;
static size_t (*const getexepath)(char *, size_t)       = _h_getexepath;
static size_t (*const getworkdir)(char *, size_t)       = _h_getworkdir;
static size_t (*const gettmpdir )(char *, size_t)       = _h_gettmpdir ;
static bool   (*const dmake     )(const char *)         = _h_dmake     ;
static bool   (*const denter    )(const char *)         = _h_denter    ;
static CDIR  *(*const dopen     )(const char *)         = _h_dopen     ;
static char  *(*const dcopy     )(CDIR *)               = _h_dcopy     ;
static void   (*const dclose    )(CDIR *)               = _h_dclose    ;

//return value need to free.
__libf char *fcopyall(const char *path, size_t *size);

__libf void fwriteall(const char *path, const void *dat, size_t datsz);
__libf void dmakeall (const char *path);

//get sub-items of a directory.
__libf XLIST *dcopyitems(const char *path);
