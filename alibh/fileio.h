#pragma once

#include "stdbool.h"
#include "stddef.h"

#if __cplusplus
extern "C" {
#endif

//files management:

bool _h_fexists(const char *path, bool *isdir);
bool _h_rename (const char *oldn, const char *newn);
bool _h_remove (const char *path);

//files read & write:

typedef struct _hfile HFILE;

HFILE *_h_fopen (const char *path, const char *mode);
bool   _h_fclose(HFILE *file);

size_t _h_fread (void       *buf, size_t isz, size_t inum, HFILE *file);
size_t _h_fwrite(const void *ptr, size_t isz, size_t inum, HFILE *file);

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

bool _h_fseek(HFILE *file, long offset, int seekbase);
long _h_ftell(HFILE *file);

//directories management:

size_t _h_getexepath(char *buf, size_t bufsz);
size_t _h_getworkdir(char *buf, size_t bufsz);
size_t _h_gettmpdir (char *buf, size_t bufsz);

//directories read & write:

bool _h_dmake (const char *path);
bool _h_denter(const char *path);

typedef struct _hdir HDIR;

HDIR *_h_dopen (const char *path);
char *_h_dcopy (HDIR *dir); //return value need to free.
void  _h_dclose(HDIR *dir);

#if __cplusplus
}
#endif
