#pragma once

#if _WIN64 || __LLP64__
    typedef unsigned long long  size_t   ;
    typedef long long           ptrdiff_t;
#elif __ILP64__ || __LP64__
    typedef unsigned long       size_t   ;
    typedef long                ptrdiff_t;
#else
    typedef unsigned int        size_t   ;
    typedef int                 ptrdiff_t;
#endif

#if __cplusplus
    #define NULL nullptr
#else
    #define NULL ((void *)0)
#endif
