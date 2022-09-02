#include "fileop.h"
#include "environ.h"
#include "dataproc.h"
#include "dirent.h"
#include "libgen.h"
#include "string.h"
#include "sys/stat.h"
#include "unistd.h"

#if OS_MAC
    #include <mach-o/dyld.h>
#endif

size_t getworkd(char *buf, size_t bufsz) {
    char *dir = getcwd(buf, bufsz);
    if (dir) {
        return strlen(buf);
    } else {
        *buf = '\0';
        return 0;
    }
}

size_t getexed(char *buf, size_t bufsz) {
#if OS_MAC
    int  err = _NSGetExecutablePath(buf, (uint32_t *)&bufsz);
    bool ok  = !err;
#else
    ssize_t sz = readlink("/proc/self/exe", buf, bufsz);
    bool    ok = sz > 0;
#endif

    if (ok) {
        char  *dir = dirname(buf);
        size_t len = strlen(dir);
        memmove(buf, dir, len + 1);
        return len;
    } else {
        *buf = '\0';
        return 0;
    }
}

size_t gettmpd(char *buf, size_t bufsz) {
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

bool fexists(const char *path, bool *isdir) {
    struct stat info;
    int  err = stat(path, &info);
    bool dir = !err && S_ISDIR(info.st_mode);

    if (isdir) {
        *isdir = dir;
    }
    return err;
}

bool dmake(const char *path) {
    int err = mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO);
    return !err;
}

bool denter(const char *path) {
    int err = chdir(path);
    return !err;
}

DIRECT *dopen(const char *path) {
    return (DIRECT *)opendir(path);
}

size_t dread(DIRECT *dir, char *sub, size_t subsz) {
    struct dirent *ent = readdir((DIR *)dir);
    if (!ent) {
        *sub = '\0';
        return 0;
    }

    size_t actlen = strlen(ent->d_name);
    size_t cpylen = minv(actlen, subsz - 1);
    strncpy(sub, ent->d_name, cpylen);
    sub[cpylen] = '\0';

    return actlen;
}

void dclose(DIRECT *dir) {
    closedir((DIR *)dir);
}
