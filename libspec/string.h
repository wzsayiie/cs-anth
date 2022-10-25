#pragma once

#include "stddef.h"

//string manipulation:

char *strncat(char *dst, const char *src, size_t len);
char *strcat (char *dst, const char *src);

char *strncpy(char *dst, const char *src, size_t len);
char *strcpy (char *dst, const char *src);

char *strndup(const char *str, size_t len);
char *strdup (const char *str);

//string test:

int strncmp(const char *a, const char *b, size_t len);
int strcmp (const char *a, const char *b);

size_t strlen(const char *str);

//memory manipulation:

void *memcpy (void *dst, const void *src, size_t num);
void *memmove(void *dst, const void *src, size_t num);

void *memset(void *dst, int ch, size_t num);
