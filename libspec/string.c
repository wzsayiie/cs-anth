#include "string.h"
#include "stdlib.h"

//string manipulation:

char *strncat(char *dst, const char *src, size_t len) {
    char *ins = dst + strlen(dst);
    memcpy(ins, src, len);
    ins[len] = '\0';

    return dst;
}

char *strcat(char *dst, const char *src) {
    char *ins = dst + strlen(dst);
    strcpy(ins, src);

    return dst;
}

char *strncpy(char *dst, const char *src, size_t len) {
    //NOTE: do not put '\0' to the end.
    memcpy(dst, src, len);
    return dst;
}

char *strcpy(char *dst, const char *src) {
    char *ins = dst;
    while (*src) {
        *ins++ = *src++;
    }
    *ins = '\0';

    return dst;
}

char *strndup(const char *str, size_t len) {
    char *cpy = malloc(len + 1);

    memcpy(cpy, str, len);
    cpy[len] = '\0';

    return cpy;
}

char *strdup(const char *str) {
    size_t siz = strlen(str) + 1;
    char  *cpy = malloc(siz);

    memcpy(cpy, str, siz);

    return cpy;
}

//string test:

int strncmp(const char *a, const char *b, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        if (a[i] != b[i]) {
            return a[i] < b[i] ? -1 : 1;
        }
    }
    return 0;
}

int strcmp(const char *a, const char *b) {
    while  (*a || *b) {
        if (*a != *b) {
            return *a < *b ? -1 : 1;
        }

        a += 1;
        b += 1;
    }
    return 0;
}

size_t strlen(const char *str) {
    const char *end = str;
    while (*end) {
        end += 1;
    }

    return (size_t)(end - str);
}

//memory manipulation:

void *memcpy(void *dst, const void *src, size_t num) {
    for (size_t i = 0; i < num; ++i) {
        ((char *)dst)[i] = ((char *)src)[i];
    }
    return dst;
}

void *memmove(void *dst, const void *src, size_t num) {
    if (dst <= src) {
        return memcpy(dst, src, num);
    }

    //copy from back to front.
    for (int i = (int)num - 1; i >= 0; --i) {
        ((char *)dst)[i] = ((char *)src)[i];
    }
    return dst;
}

void *memset(void *dst, int ch, size_t num) {
    for (size_t i = 0; i < num; ++i) {
        ((char *)dst)[i] = (char)ch;
    }
    return dst;
}
