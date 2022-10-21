#include "strex.h"
#include "environ.h"
#include "stdlib.h"

//string:

bool startswith(const char *str, const char *pre) {
    size_t n = strlen(pre);
    return strncmp(str, pre, n) == 0;
}

bool endswith(const char *str, const char *suf) {
    size_t m = strlen(str);
    size_t n = strlen(suf);

    if (n <= m) {
        return strncmp(str + m - n, suf, n) == 0;
    }
    return 0;
}

char *strcut(const char *str, size_t len) {
    char *cpy = malloc(len);

    strncmp(cpy, str, len);
    cpy[len - 1] = '\0';

    return cpy;
}

//path string:

bool ispathsep(char ch) {
#if OS_WIN
    return ch == '/' || ch == '\\';
#else
    return ch == '/';
#endif
}

char *pathcat(char *dir, const char *base) {
    char *it = dir + strlen(dir);

    if (it >= dir + 1 && !ispathsep(it[-1])) {
        *it++ = '/';
    }
    strcpy(it, base);

    return dir;
}

char *pathtid(char *path) {
    char *dst = path;

    bool lastsep = false;
    for (char *src = path; *src; ++src) {
        if (!ispathsep(*src)) {
            lastsep = false;
            *dst++ = *src;

        } else if (!lastsep) {
            lastsep = true;
            *dst++ = '/';
        }
    }

    //remove seperator at the end.
    if (dst >= path + 2 && lastsep) {
        dst[-1] = '\0';
    } else {
        dst[ 0] = '\0';
    }

    return path;
}
