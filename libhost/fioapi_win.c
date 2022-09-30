#include "fioapi.h"
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

struct _struct_ADIR {
    HANDLE           handle;
    WIN32_FIND_DATAA dat   ;
    bool             first ;
};

ADIR *_h_dopen(const char *path) {
    size_t plen = strlen(path);
    char  *name = malloc(plen + 3);
    strcpy(name, path);
    if (name[plen - 1] != '\\' && name[plen - 1] != '/') {
        strcpy(name + plen, "\\*");
    } else {
        strcpy(name + plen, "*");
    }

    ADIR *dir   = calloc(1, sizeof(ADIR));
    dir->handle = FindFirstFileA(name, &dir->dat);
    dir->first  = true;

    free(name);

    if (dir->handle == INVALID_HANDLE_VALUE) {
        free(dir);
        return NULL;
    }
    return dir;
}

char *_h_dcopy(ADIR *dir) {
    if (dir->first) {
        dir->first = false;
        return strdup(dir->dat.cFileName);
    }

    BOOL success = FindNextFileA(dir->handle, &dir->dat);
    if (success) {
        return strdup(dir->dat.cFileName);
    }

    return NULL;
}

void _h_dclose(ADIR *dir) {
    FindClose(dir->handle);
    free(dir);
}
