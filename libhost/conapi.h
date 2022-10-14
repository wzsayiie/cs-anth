#pragma once

#include "condition.h"
#include "stdbool.h"

//console window:
__host void _h_getwinsize(int *width, int *height);
__host void _h_stepcur   (int  stepx, int  stepy );
__host void _h_showcur   (bool show);

#define C_BLACK        0
#define C_RED          1
#define C_GREEN        2
#define C_YELLOW       3
#define C_BLUE         4
#define C_PURPLE       5
#define C_CYAN         6
#define C_WHITE        7
#define C_LIGHTBLACK   8
#define C_LIGHTRED     9
#define C_LIGHTGREEN  10
#define C_LIGHTYELLOW 11
#define C_LIGHTBLUE   12
#define C_LIGHTPURPLE 13
#define C_LIGHTCYAN   14
#define C_LIGHTWHITE  15
#define C_DEFCOLOR    16

__host void _h_setforecolor(int  color);
__host void _h_setbackcolor(int  color);
__host void _h_setunderline(bool under);
__host void _h_resetprtattr(void);

//stdin:

__host void _h_beginrawmode(void);
__host void _h_endrawmode  (void);

//in canonical mode, this function do not return until the user pressed the enter key.
//in raw mode, this function is non-blocking. if no data in stdin, it will return 0.
__host int _h_readchar(void);

//in raw mode,
//"readchar" possibly returns control characters followed:

#define K_NUL         ((int)0x00)

#define K_CTRL_A      ((int)0x01)
#define K_CTRL_B      ((int)0x02)
#define K_CTRL_C      ((int)0x03)
#define K_CTRL_D      ((int)0x04)
#define K_CTRL_E      ((int)0x05)
#define K_CTRL_F      ((int)0x06)
#define K_CTRL_G      ((int)0x07)
#define K_CTRL_H      ((int)0x08)
#define K_CTRL_I      ((int)0x09)
#define K_CTRL_J      ((int)0x0A)
#define K_CTRL_K      ((int)0x0B)
#define K_CTRL_L      ((int)0x0C)
#define K_CTRL_M      ((int)0x0D)
#define K_CTRL_N      ((int)0x0E)
#define K_CTRL_O      ((int)0x0F)
#define K_CTRL_P      ((int)0x10)
#define K_CTRL_Q      ((int)0x11)
#define K_CTRL_R      ((int)0x12)
#define K_CTRL_S      ((int)0x13)
#define K_CTRL_T      ((int)0x14)
#define K_CTRL_U      ((int)0x15)
#define K_CTRL_V      ((int)0x16)
#define K_CTRL_W      ((int)0x17)
#define K_CTRL_X      ((int)0x18)
#define K_CTRL_Y      ((int)0x19)
#define K_CTRL_Z      ((int)0x1A)

#define K_ENTER       K_CTRL_H
#define K_TAB         K_CTRL_I
#define K_ESC         ((int)0x1B)
#define K_SPACE       ((int)0x20)
#define K_BACK        ((int)0x7F)

//custom control character.
#define K_SHIFT_TAB   ((int)0xD0)
#define K_SHIFT_LEFT  ((int)0xD1)
#define K_SHIFT_UP    ((int)0xD2)
#define K_SHIFT_RIGHT ((int)0xD3)
#define K_SHIFT_DOWN  ((int)0xD4)
#define K_LEFT        ((int)0xD5)
#define K_UP          ((int)0xD6)
#define K_RIGHT       ((int)0xD7)
#define K_DOWN        ((int)0xD8)

//stduot & stderr.
__host void _h_writeout(const char *str);
__host void _h_writeerr(const char *str);
