#pragma once

#include "environ.h"

#if __cplusplus
    #define __extern_c  extern "C"
#else
    #define __extern_c
#endif

#if CMPL_MSC
    #define __dllvisible __declspec(dllexport)
#else
    #define __dllvisible
#endif

#define __export  __extern_c __dllvisible
