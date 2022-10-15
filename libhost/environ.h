#pragma once

//which compiler.
#if __acc__
    #define CMPL_ACC   1
#elif __clang__
    #define CMPL_CLANG 1
#elif __GNUC__
    #define CMPL_GCC   1
#elif _MSC_VER
    #define CMPL_MSC   1
#else
    #error "unknown compiler."
#endif

//word size.
#if _WIN64 || (__ILP64__ || __LP64__ || __LLP64__)
    #define PTR_64 1
#elif _WIN32 || (__ILP32__ || __LP32__)
    #define PTR_32 1
#else
    #error "unknown word size."
#endif

//which os:
#if __linux__
    #define OS_LINUX 1
#elif __MACH__
    #define OS_MAC   1
#elif _WIN32
    #define OS_WIN   1
#else
    #error "unknown os."
#endif

#define OS_POSIX (OS_LINUX || OS_MAC)
