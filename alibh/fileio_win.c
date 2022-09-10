#include "fileio.h"
#include "environ.h"
#include "stdio.h"

#if OS_WIN

//files management:

bool _h_fexists(const char *path, bool *isdir) {
    return false;
}

bool _h_rename(const char *oldn, const char *newn) {
    int err = rename(oldn, newn);
    return !err;
}

bool _h_remove(const char *path) {
    int err = remove(path);
    return !err;
}

//files read & write:

HFILE *_h_fopen(const char *path, const char *mode) {
    return (HFILE *)fopen(path, mode);
}

bool _h_fclose(HFILE *file) {
    int err = fclose((FILE *)file);
    return !err;
}

size_t _h_fread(void *buf, size_t isz, size_t inum, HFILE *file) {
    return fread(buf, isz, inum, (FILE *)file);
}

size_t _h_fwrite(const void *ptr, size_t isz, size_t inum, HFILE *file) {
    return fwrite(ptr, isz, inum, (FILE *)file);
}

bool _h_fseek(HFILE *file, long offset, int seekbase) {
    int err = fseek((FILE *)file, offset, seekbase);
    return !err;
}

long _h_ftell(HFILE *file) {
    return ftell((FILE *)file);
}

//directories management:

size_t _h_getexepath(char *buf, size_t bufsz) {
    return 0;
}

size_t _h_getworkdir(char *buf, size_t bufsz) {
    return 0;
}

size_t _h_gettmpdir(char *buf, size_t bufsz) {
    return 0;
}

//directories read & write:

bool _h_dmake(const char *path) {
    return false;
}

bool _h_denter(const char *path) {
    return false;
}

HDIR *_h_dopen(const char *path) {
    return NULL;
}

char *_h_dcopy(HDIR *dir) {
    return NULL;
}

void _h_dclose(HDIR *dir) {
}

#endif //OS_WIN.
