#include "libgen.h"
#include "string.h"
#include "pathstr.h"

static char *posslastsep(char *path) {
    char *it = path + strlen(path) - 2;

    for (; it >= path + 1; --it) {
        if (ispathsep(*it)) {
            break;
        }
    }

    return it;
}

char *basename(char *path) {
    char *it = posslastsep(path);

    if (it > path && ispathsep(*it)) {
        return it + 1;
    } else {
        return path;
    }
}

char *dirname(char *path) {
    char *it = posslastsep(path);

    if (it > path && ispathsep(*it)) {
        *it = '\0';
    } else if (*path) {
        strcpy(path, ".");
    }
    return path;
}
