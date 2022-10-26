#pragma once

#include "mem.h"
#include "osapi.h"

//memory management:

static void *(*const realloc)(void *, size_t) = _h_realloc;
static void  (*const free   )(void *)         = _h_free   ;

__libf void *calloc(size_t inum, size_t isz);
__libf void *malloc(size_t size);

//program utilities:

static int   (*const system)(const char *)   = _h_system;
static char *(*const getenv)(const char *)   = _h_getenv;
static int   (*const atexit)(void (*)(void)) = _h_atexit;
static void  (*const exit  )(int)            = _h_exit  ;

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
