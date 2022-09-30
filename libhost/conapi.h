#pragma once

#include "condition.h"
#include "stdbool.h"

//console window.
__host void _h_getwinsize(int *width, int *height);
__host void _h_stepcur   (int  stepx, int  stepy );
__host void _h_showcur   (bool show);

//stdin:

__host void _h_beginrawmode(void);
__host void _h_endrawmode  (void);

//in canonical mode, this function do not return until the user pressed the enter key.
//in raw mode, this function is non-blocking. if no data in stdin, it will return 0.
__host int _h_readchar(void);

//in raw mode,
//"readchar" possibly returns control characters followed:

#define C_NUL        ((int)0x00)

#define C_CTRL_A     ((int)0x01)
#define C_CTRL_B     ((int)0x02)
#define C_CTRL_C     ((int)0x03)
#define C_CTRL_D     ((int)0x04)
#define C_CTRL_E     ((int)0x05)
#define C_CTRL_F     ((int)0x06)
#define C_CTRL_G     ((int)0x07)
#define C_CTRL_H     ((int)0x08)
#define C_CTRL_I     ((int)0x09)
#define C_CTRL_J     ((int)0x0A)
#define C_CTRL_K     ((int)0x0B)
#define C_CTRL_L     ((int)0x0C)
#define C_CTRL_M     ((int)0x0D)
#define C_CTRL_N     ((int)0x0E)
#define C_CTRL_O     ((int)0x0F)
#define C_CTRL_P     ((int)0x10)
#define C_CTRL_Q     ((int)0x11)
#define C_CTRL_R     ((int)0x12)
#define C_CTRL_S     ((int)0x13)
#define C_CTRL_T     ((int)0x14)
#define C_CTRL_U     ((int)0x15)
#define C_CTRL_V     ((int)0x16)
#define C_CTRL_W     ((int)0x17)
#define C_CTRL_X     ((int)0x18)
#define C_CTRL_Y     ((int)0x19)
#define C_CTRL_Z     ((int)0x1A)

#define C_ENTER      C_CTRL_H
#define C_TAB        C_CTRL_I
#define C_ESC        ((int)0x1B)
#define C_SPACE      ((int)0x20)
#define C_BACK       ((int)0x7F)

//custom control character.
#define C_SHIFT_TAB  ((int)0xD0)
#define C_CTRL_LEFT  ((int)0xD1)
#define C_CTRL_UP    ((int)0xD2)
#define C_CTRL_RIGHT ((int)0xD3)
#define C_CTRL_DOWN  ((int)0xD4)
#define C_LEFT       ((int)0xD5)
#define C_UP         ((int)0xD6)
#define C_RIGHT      ((int)0xD7)
#define C_DOWN       ((int)0xD8)

//stduot & stderr.
__host void _h_writeout(const char *str);
__host void _h_writeerr(const char *str);
