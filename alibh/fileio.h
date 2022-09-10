#pragma once

#include "condition.h"
#include "stdbool.h"
#include "stddef.h"

//files management:

__export bool _h_fexists(const char *path, bool *isdir);
__export bool _h_rename (const char *oldn, const char *newn);
__export bool _h_remove (const char *path);

//files read & write:

typedef struct _hfile HFILE;

__export HFILE *_h_fopen (const char *path, const char *mode);
__export bool   _h_fclose(HFILE *file);

__export size_t _h_fread (void       *buf, size_t isz, size_t inum, HFILE *file);
__export size_t _h_fwrite(const void *ptr, size_t isz, size_t inum, HFILE *file);

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

__export bool _h_fseek(HFILE *file, long offset, int seekbase);
__export long _h_ftell(HFILE *file);

//directories management:

__export size_t _h_getexepath(char *buf, size_t bufsz);
__export size_t _h_getworkdir(char *buf, size_t bufsz);
__export size_t _h_gettmpdir (char *buf, size_t bufsz);

//directories read & write:

__export bool _h_dmake (const char *path);
__export bool _h_denter(const char *path);

__export typedef struct _hdir HDIR;

__export HDIR *_h_dopen (const char *path);
__export char *_h_dcopy (HDIR *dir); //return value need to free.
__export void  _h_dclose(HDIR *dir);
