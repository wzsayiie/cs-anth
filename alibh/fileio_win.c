#include "fileio.h"
#include "direct.h"
#include "string.h"
#include "sys/stat.h"
#include "windows.h"

//files management:

bool _h_fexists(const char *path, bool *isdir) {
    struct stat info;
    int  err = stat(path, &info);
    bool dir = !err && (info.st_mode & S_IFMT == S_IFDIR);

    if (isdir) {
        *isdir = dir;
    }
    return !err;
}

//directories management:

size_t _h_getexepath(char *buf, size_t bufsz) {
    return (size_t)GetModuleFileNameA(NULL, buf, (DWORD)bufsz);
}

size_t _h_getworkdir(char *buf, size_t bufsz) {
    char *dir = getcwd(buf, (int)bufsz);
    if (dir) {
        return strlen(buf);
    } else {
        *buf = '\0';
        return 0;
    }
}

size_t _h_gettmpdir(char *buf, size_t bufsz) {
    char path[MAX_PATH + 1];
    DWORD slen = GetTempPathA((DWORD)sizeof(path), path);
    if (slen == 0) {
        *buf = '\0';
        return 0;
    }

    size_t llen = (size_t)GetLongPathNameA(path, buf, (DWORD)bufsz);
    if (llen == 0) {
        *buf = '\0';
        return 0;
    }

    if (buf[llen - 1] == '\\') {
        buf[llen - 1] = '\0';
        llen -= 1;
    }
    return llen;
}

//directories read & write:

bool _h_dmake(const char *path) {
    int err = _mkdir(path);
    return !err;
}

bool _h_denter(const char *path) {
    int err = _chdir(path);
    return !err;
}

ADIR *_h_dopen(const char *path) {
    return NULL;
}

char *_h_dcopy(ADIR *dir) {
    return NULL;
}

void _h_dclose(ADIR *dir) {
}
