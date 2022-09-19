#pragma once

#include "mathex.h"
#include "stddef.h"

#define _DEF_INT_CMP(max, min, tp)                                  \
/**/    static inline tp max(tp x, tp y) { return x > y ? x : y; }  \
/**/    static inline tp min(tp x, tp y) { return x < y ? x : y; }

_DEF_INT_CMP(imaxh , iminh , short             )
_DEF_INT_CMP(imax  , imin  , int               )
_DEF_INT_CMP(imaxl , iminl , long              )
_DEF_INT_CMP(imaxll, iminll, long long         )
_DEF_INT_CMP(imaxp , iminp , ptrdiff_t         )
_DEF_INT_CMP(umaxh , uminh , unsigned short    )
_DEF_INT_CMP(umax  , umin  , unsigned int      )
_DEF_INT_CMP(umaxl , uminl , unsigned long     )
_DEF_INT_CMP(umaxll, uminll, unsigned long long)
_DEF_INT_CMP(umaxz , uminz , size_t            )
