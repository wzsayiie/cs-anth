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

char **wccopyfiles(const char *pat, int *num) {
    //the pattern does not contain wildcards.
    if (!iswcpat(pat)) {
        char **files = malloc(sizeof(char *));

        *files = strdup(pat);
        *num   = 1;

        return files;
    }

    char *dir = strdup(pat);
    pathdir(dir);

    //wildcards in directory path is unsupported.
    if (iswcpat(dir)) {
        free(dir);

        *num = 0;
        return NULL;
    }

    int    candnum = 0;
    char **candids = dcopyitems(dir, &candnum);

    if (candnum == 0) {
        free(dir);

        *num = 0;
        return NULL;
    }

    //filter out suiable files:
    char **files = NULL;
    *num = 0;

    const char *base = pathbase(pat);
    size_t      dlen = strlen(dir);

    for (int i = 0; i < candnum; ++i) {
        char *cand = candids[i];
        if (!wcmatch(base, cand)) {
            continue;
        }

        size_t clen = strlen(cand);
        char  *file = malloc(dlen + 1 + clen + 1);
        strcpy (file, dir);
        pathcat(file, candids[i]);

        files = realloc(files, sizeof(char *) * (*num + 1));
        files[*num] = file;
        *num += 1;
    }

    dfreeitems(candids, candnum);
    free(dir);

    return files;
}

void wcfreefiles(char **files, int num) {
    for (int i = 0; i < num; ++i) {
        free(files[i]);
    }
    free(files);
}
