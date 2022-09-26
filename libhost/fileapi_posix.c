#include "fileapi.h"
#include "dirent.h"
#include "string.h"
#include "sys/stat.h"
#include "unistd.h"

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

//directories management:

size_t _h_getexepath(char *buf, size_t bufsz) {
#if OS_MAC
    int  err  = _NSGetExecutablePath(buf, (uint32_t *)&bufsz);
    bool okay = !err;
#else
    ssize_t size = readlink("/proc/self/exe", buf, bufsz - 1);
    bool    okay = size > 0;

    //NOTE: "readlink" does not append a terminating '\0'.
    buf[size] = '\0';
#endif

    if (okay) {
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

ADIR *_h_dopen(const char *path) {
    return (ADIR *)opendir(path);
}

char *_h_dcopy(ADIR *dir) {
    struct dirent *ent = readdir((DIR *)dir);
    if (ent) {
        return strdup(ent->d_name);
    }
    return NULL;
}

void _h_dclose(ADIR *dir) {
    closedir((DIR *)dir);
}
