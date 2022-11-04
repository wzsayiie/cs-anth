#include "wildcard.h"
#include "fileio.h"
#include "stdlib.h"
#include "strex.h"

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

XLIST *wccopyfiles(const char *pat) {
    //the pattern does not contain wildcards.
    if (!iswcpat(pat)) {
        XLIST *list = xlalloc();

        char *file = strdup(pat);
        xlpushp(list, file);

        return list;
    }

    char *dir = strdup(pat);
    pathdir(dir);

    //wildcards in directory path is unsupported.
    if (iswcpat(dir)) {
        free(dir);
        return NULL;
    }

    XLIST *bases = dcopyitems(dir);
    if (!bases) {
        free(dir);
        return NULL;
    }

    //filter out suiable files:
    XLIST *list = NULL;
    char  *bpat = pathbase(pat);
    size_t dlen = strlen(dir);

    for (int i = 0; i < xlcount(bases); ++i) {
        char *base = __xistr xlget(bases, i);
        if (!wcmatch(bpat, base)) {
            continue;
        }

        //NOTE: splice a full path.
        size_t blen = strlen(base);
        char  *item = malloc(dlen + 1 + blen + 1);
        strcpy (item, dir );
        pathcat(item, base);

        //IMPORTANT: allocate when the list is needed.
        //do not return a list with 0 length.
        if (!list) {
            list = xlalloc();
        }
        xlpushp(list, item);
    }

    xlfree(bases, free);
    free(dir);

    return list;
}
