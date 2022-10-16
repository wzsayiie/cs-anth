#include "fioapi.h"
#include "stdio.h"

//files management:

bool _h_rename(const char *oldn, const char *newn) {
    int err = rename(oldn, newn);
    return !err;
}

bool _h_remove(const char *path) {
    int err = remove(path);
    return !err;
}

//files read & write:

CFILE *_h_fopen(const char *path, const char *mode) {
    return (CFILE *)fopen(path, mode);
}

bool _h_fclose(CFILE *file) {
    int err = fclose((FILE *)file);
    return !err;
}

size_t _h_fread(void *buf, size_t isz, size_t inum, CFILE *file) {
    return fread(buf, isz, inum, (FILE *)file);
}

size_t _h_fwrite(const void *ptr, size_t isz, size_t inum, CFILE *file) {
    return fwrite(ptr, isz, inum, (FILE *)file);
}

bool _h_fseek(CFILE *file, long offset, int seekbase) {
    int err = fseek((FILE *)file, offset, seekbase);
    return !err;
}

long _h_ftell(CFILE *file) {
    return ftell((FILE *)file);
}
