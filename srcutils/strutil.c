#include "strutil.h"
#include "string.h"

bool hasprefix(const char *str, const char *pre) {
    size_t n = strlen(pre);
    return strncmp(str, pre, n) == 0;
}

bool hassuffix(const char *str, const char *suf) {
    size_t m = strlen(str);
    size_t n = strlen(suf);

    if (n <= m) {
        return strncmp(str + m - n, suf) == 0;
    }
    return 0;
}
