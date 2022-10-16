#pragma once

#include "math.h"
#include "stddef.h"

//compare:

#define _DEF_INT_CMP(max, min, tp)                                  \
/**/    static inline tp max(tp x, tp y) { return x > y ? x : y; }  \
/**/    static inline tp min(tp x, tp y) { return x < y ? x : y; }

_DEF_INT_CMP(imax  , imin  , int               )
_DEF_INT_CMP(imaxll, iminll, long long         )
_DEF_INT_CMP(imaxp , iminp , ptrdiff_t         )
_DEF_INT_CMP(umax  , umin  , unsigned int      )
_DEF_INT_CMP(umaxll, uminll, unsigned long long)
_DEF_INT_CMP(umaxz , uminz , size_t            )

//vector:

#define _DEF_VEC(v2, v3, v4, m2, m3, m4, tp)            \
/**/    typedef union _union_##v2 {                     \
/**/        struct {                                    \
/**/            union { tp x; tp w; };                  \
/**/            union { tp y; tp h; };                  \
/**/        };                                          \
/**/        tp i[2];                                    \
/**/    } v2;                                           \
/**/                                                    \
/**/    static inline v2 m2(tp x, tp y) {               \
/**/        v2 v; {                                     \
/**/            v.x = x;                                \
/**/            v.y = y;                                \
/**/        }                                           \
/**/        return v;                                   \
/**/    }                                               \
/**/                                                    \
/**/    typedef union _union_##v3 {                     \
/**/        struct {                                    \
/**/            union { tp x; tp r; };                  \
/**/            union { tp y; tp g; };                  \
/**/            union { tp z; tp b; };                  \
/**/        };                                          \
/**/        tp i[3];                                    \
/**/    } v3;                                           \
/**/                                                    \
/**/    static inline v3 m3(tp x, tp y, tp z) {         \
/**/        v3 v; {                                     \
/**/            v.x = x;                                \
/**/            v.y = y;                                \
/**/            v.z = z;                                \
/**/        }                                           \
/**/        return v;                                   \
/**/    }                                               \
/**/                                                    \
/**/    typedef union _union_##v4 {                     \
/**/        struct {                                    \
/**/            union { tp x;       tp r; };            \
/**/            union { tp y;       tp g; };            \
/**/            union { tp z; tp h; tp b; };            \
/**/            union { tp w;       tp a; };            \
/**/        };                                          \
/**/        tp i[4];                                    \
/**/    } v4;                                           \
/**/                                                    \
/**/    static inline v4 m4(tp x, tp y, tp z, tp w) {   \
/**/        v4 v; {                                     \
/**/            v.x = x;                                \
/**/            v.y = y;                                \
/**/            v.z = z;                                \
/**/            v.w = w;                                \
/**/        }                                           \
/**/        return v;                                   \
/**/    }

_DEF_VEC(CFLT2, CFLT3, CFLT4, mkflt2, mkflt3, mkflt4, float)
_DEF_VEC(CINT2, CINT3, CINT4, mkint2, mkint3, mkint4, int  )
