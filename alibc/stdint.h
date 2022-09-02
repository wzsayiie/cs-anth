#pragma once

#include "environ.h"

typedef signed char         int8_t  ;
typedef short               int16_t ;
typedef int                 int32_t ;
typedef long long           int64_t ;

typedef unsigned char       uint8_t ;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long long  uint64_t;

#define INT8_MAX    ~(1   <<  7)    //.. ... ... ... ... ... 127
#define INT16_MAX   ~(1   << 15)    //.. ... ... ... ... .32'767
#define INT32_MAX   ~(1   << 31)    //.. ... ... ..2'147'483'647
#define INT64_MAX   ~(1LL << 63)    //.9'223'372'036'854'775'807

#define INT8_MIN     (1   <<  7)    //.. ... ... ... ... ...-128
#define INT16_MIN    (1   << 15)    //.. ... ... ... ... -32'768
#define INT32_MIN    (1   << 31)    //.. ... ... .-2'147'483'648
#define INT64_MIN    (1LL << 63)    //-9'223'372'036'854'775'808

#define UINT8_MAX   ~0              //.. ... ... ... ... ... 255
#define UINT16_MAX  ~0              //.. ... ... ... ... .65'535
#define UINT32_MAX  ~0              //.. ... ... ..4'294'967'295
#define UINT64_MAX  ~0LL            //18'446'744'073'709'551'615

#if _WIN64 || __LLP64__
    typedef long long           intptr_t ;
    typedef unsigned long long  uintptr_t;
#elif __ILP64__ || __LP64__
    typedef long                intptr_t ;
    typedef unsigned long       uintptr_t;
#else
    typedef int                 intptr_t ;
    typedef unsigned int        uintptr_t;
#endif
