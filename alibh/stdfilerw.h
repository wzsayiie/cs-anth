#pragma once

#include "stddef.h"

#if __cplusplus
extern "C" {
#endif

typedef struct __FILE FILE;

FILE *fopen (const char *path, const char *mode);
int   fclose(FILE *file);

size_t fread (void       *buf, size_t isz, size_t inum, FILE *file);
size_t fwrite(const void *ptr, size_t isz, size_t inum, FILE *file);

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

int  fseek(FILE *file, long offset, int seekbase);
long ftell(FILE *file);

#if __cplusplus
}
#endif
