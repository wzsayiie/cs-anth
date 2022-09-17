#pragma once

#include "environ.h"

#if __cplusplus
    #define __extern_c  extern "C"
#else
    #define __extern_c
#endif

#if CMPL_MSC
    #define __dllexport __declspec(dllexport)
#else
    #define __dllexport
#endif

#define __host  __extern_c __dllexport
#define __libf  __extern_c
