#include "fileio.h"
#include "environ.h"
#include "dirent.h"
#include "stdio.h"
#include "string.h"
#include "sys/stat.h"
#include "unistd.h"

#if OS_POSIX

#if OS_MAC
    #include "mach-o/dyld.h"
#endif

//files management:

bool _h_fexists(const char *path, bool *isdir) {
    struct stat info;
    int  err = stat(path, &info);
    bool dir = !err && S_ISDIR(info.st_mode);

    if (isdir) {
        *isdir = dir;
    }
    return !err;
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
#if OS_MAC
    int  err = _NSGetExecutablePath(buf, (uint32_t *)&bufsz);
    bool ok  = !err;
#else
    ssize_t sz = readlink("/proc/self/exe", buf, bufsz);
    bool    ok = sz > 0;
#endif

    if (ok) {
        return strlen(buf);
    } else {
        *buf = '\0';
        return 0;
    }
}

size_t _h_getworkdir(char *buf, size_t bufsz) {
    char *dir = getcwd(buf, bufsz);
    if (dir) {
        return strlen(buf);
    } else {
        *buf = '\0';
        return 0;
    }
}

size_t _h_gettmpdir(char *buf, size_t bufsz) {
    const char *dir = "/tmp";
    size_t len = strlen(dir);

    if (bufsz >= len + 1) {
        strcpy(buf, dir);
        return len;
    } else {
        *buf = '\0';
        return 0;
    }
}

//directories read & write:

bool _h_dmake(const char *path) {
    int err = mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO);
    return !err;
}

bool _h_denter(const char *path) {
    int err = chdir(path);
    return !err;
}

HDIR *_h_dopen(const char *path) {
    return (HDIR *)opendir(path);
}

char *_h_dcopy(HDIR *dir) {
    struct dirent *ent = readdir((DIR *)dir);
    if (ent) {
        return strdup(ent->d_name);
    }
    return NULL;
}

void _h_dclose(HDIR *dir) {
    closedir((DIR *)dir);
}

#endif //OS_POSIX.
