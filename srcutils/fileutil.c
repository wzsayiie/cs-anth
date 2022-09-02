#include "fileutil.h"
#include "fileop.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

size_t freadall(const char *path, char *buf, size_t bufsz) {
    FILE *file = fopen(path, "rb");
    if (!file) {
        *buf = '\0';
        return 0;
    }

    size_t actsz = fread(buf, sizeof(char), bufsz, file);
    fclose(file);
    return actsz;
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
}

char **dcopyitems(const char *path, int *num) {
    //allocate number at a time.
    const size_t ONCE_ALLOC_N = 16;

    DIRECT *dir = dopen(path);
    if (!dir) {
        *num = 0;
        return NULL;
    }

    char **items = NULL;
    int    alln  = 0;
    int    usedn = 0;

    char buf[256];
    while (true) {
        size_t len = dread(dir, buf, sizeof(buf));
        if (!len) {
            break;
        }

        if (strcmp(buf, "..") == 0 ||
            strcmp(buf, "." ) == 0 )
        {
            continue;
        }

        if (usedn == alln) {
            alln += ONCE_ALLOC_N;
            items = realloc(items, alln * sizeof(char *));
        }

        items[usedn] = strdup(buf);
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
