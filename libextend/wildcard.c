#include "wildcard.h"

bool iswcpat(const char *pat) {
    while (*pat) {
        if (*pat == '*' || *pat == '?') {
            return true;
        } else {
            pat += 1;
        }
    }

    return false;
}

bool wcmatch(const char *pat, const char *str) {
    while (*pat && *str) {
        if (*pat == '*') {
            //the "*" appears at the end.
            if (!pat[1]) {
                return true;
            }

            bool m = false;
            int  s = 0;
            for (; str[s]; ++s) {
                if (wcmatch(pat + 1, str + s)) {
                    m = true;
                    break;
                }
            }

            if (m) {
                pat += 1;
                str += s;
            } else {
                break;
            }

        } else if (*pat == '?') {
            pat += 1;
            str += 1;

        } else if (*pat == *str) {
            pat += 1;
            str += 1;

        } else {
            break;
        }
    }

    return !*pat && !*str;
}
