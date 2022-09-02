#include "pathstr.h"
#include "environ.h"
#include "string.h"

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
