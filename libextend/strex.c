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

char *stridup(const char *str, size_t len) {
    char *cpy = malloc(len + 1);

    strncpy(cpy, str, len);
    cpy[len] = '\0';

    return cpy;
}

//path:

static const char SEP = '/';

bool ispathsep(char ch) {
#if OS_WIN
    return ch == '/' || ch == '\\';
#else
    return ch == '/';
#endif
}

char *pathbase(const char *path) {
    //skip separators at the end.
    const char *it = path + strlen(path) - 1;
    while (it >= path && ispathsep(*it)) {
        it -= 1;
    }

    //"\0" or all characters are separators.
    if (it == path - 1) {
        return (char *)path;
    }

    while (it > path && !ispathsep(it[-1])) {
        it -= 1;
    }
    return (char *)it;
}

char *pathdir(char *path) {
    char *it = path + strlen(path) - 1;

    //path is "\0".
    if (it == path - 1) {
        return path;
    }

    //skip all separators at the end.
    while (it >= path && ispathsep(*it)) {
        it -= 1;
    }
    //if all characters are separators. return "/".
    if (it == path - 1) {
        strcpy(path, "/");
        return path;
    }

    while (it >= path && !ispathsep(*it)) {
        it -= 1;
    }
    
    if (it == path -1) {
        //only base. return ".".
        strcpy(path, ".");
    } else if (it == path) {
        //like "/x". return "/".
        strcpy(path, "/");
    } else {
        *it = '\0';
    }
    return path;
}

char *pathcat(char *dir, const char *base) {
    char *it = dir + strlen(dir);

    if (it >= dir + 1 && !ispathsep(it[-1])) {
        *it++ = SEP;
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
            *dst++  = *src ;

        } else if (!lastsep) {
            lastsep = true;
            *dst++  = SEP ;
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
