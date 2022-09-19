#include "fileex.h"
#include "stdio.h"
#include "stdlib.h"
#include "strex.h"

char *fcopyall(const char *path, size_t *size) {
    FILE *file = fopen(path, "rb");
    if (!file) {
        *size = 0;
        return 0;
    }

    fseek(file, 0, SEEK_END);
    *size = (size_t)ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buf = malloc(*size);
    fread(buf, sizeof(char), *size, file);
    fclose(file);
    return buf;
}

void fwriteall(const char *path, const void *dat, size_t datsz) {
    FILE *file = fopen(path, "wb");
    if (!file) {
        return;
    }

    fwrite(dat, sizeof(char), datsz, file);
    fclose(file);
}

void dmakeall(const char *path) {
    char *bgn = strdup(path);
    char *end = bgn;

    while (*end) {
        while (ispathsep(*end)) {
            end += 1;
        }
        while (*end && !ispathsep(*end)) {
            end += 1;
        }

        char sep = *end;
        *end = '\0';
        if (!fexists(bgn, NULL)) {
            dmake(bgn);
        }
        *end = sep;
    }

    free(bgn);
}

char **dcopyitems(const char *path, int *num) {
    //allocate number at a time.
    const size_t ONCE_ALLOC_N = 16;

    ADIR *dir = dopen(path);
    if (!dir) {
        *num = 0;
        return NULL;
    }

    char **items = NULL;
    int    alln  = 0;
    int    usedn = 0;

    while (true) {
        char *it = dcopy(dir);
        if (!it) {
            break;
        }

        if (strcmp(it, "..") == 0 ||
            strcmp(it, "." ) == 0 )
        {
            free(it);
            continue;
        }

        if (usedn == alln) {
            alln += ONCE_ALLOC_N;
            items = realloc(items, alln * sizeof(char *));
        }

        items[usedn] = it;
        usedn += 1;
    }
    dclose(dir);

    *num = usedn;
    return items;
}

void dfreeitems(char **items, int num) {
    for (int i = 0; i < num; ++i) {
        free(items[i]);
    }
    free(items);
}
