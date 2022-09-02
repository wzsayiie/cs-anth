#pragma once

#include "stdbool.h"
#include "stddef.h"

#if __cplusplus
extern "C" {
#endif

size_t getworkd(char *buf, size_t bufsz);
size_t getexed (char *buf, size_t bufsz);
size_t gettmpd (char *buf, size_t bufsz);

bool fexists(const char *path, bool *isdir);
bool dmake  (const char *path);
bool denter (const char *path);

typedef struct direct DIRECT;

DIRECT *dopen (const char *path);
size_t  dread (DIRECT *dir, char *sub, size_t subsz);
void    dclose(DIRECT *dir);

#if __cplusplus
}
#endif
