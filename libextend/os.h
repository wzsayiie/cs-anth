#pragma once

#include "osapi.h"

static void    (*const sleepmilli)(int64_t) = _h_sleepmilli;
static int64_t (*const nowmilli  )(void   ) = _h_nowmilli  ;
