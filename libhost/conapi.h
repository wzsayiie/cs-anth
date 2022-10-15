#pragma once

#include "condition.h"
#include "stdbool.h"

//console window:
__host void _h_getwinsize(int *width, int *height);
__host void _h_stepcur   (int  stepx, int  stepy );
__host void _h_showcur   (bool show);

#define C_BLACK       ((int)  0)
#define C_RED         ((int)  1)
#define C_GREEN       ((int)  2)
#define C_YELLOW      ((int)  3)
#define C_BLUE        ((int)  4)
#define C_PURPLE      ((int)  5)
#define C_CYAN        ((int)  6)
#define C_WHITE       ((int)  7)
#define C_LIGHTBLACK  ((int)  8)
#define C_LIGHTRED    ((int)  9)
#define C_LIGHTGREEN  ((int) 10)
#define C_LIGHTYELLOW ((int) 11)
#define C_LIGHTBLUE   ((int) 12)
#define C_LIGHTPURPLE ((int) 13)
#define C_LIGHTCYAN   ((int) 14)
#define C_LIGHTWHITE  ((int) 15)
#define C_DEFCOLOR    ((int) 16)

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

#define K_NUL         ((int)  0)

#define K_CTRL_A      ((int)  1)
#define K_CTRL_B      ((int)  2)
#define K_CTRL_C      ((int)  3)
#define K_CTRL_D      ((int)  4)
#define K_CTRL_E      ((int)  5)
#define K_CTRL_F      ((int)  6)
#define K_CTRL_G      ((int)  7)
#define K_CTRL_H      ((int)  8)
#define K_CTRL_I      ((int)  9)
#define K_CTRL_J      ((int) 10)
#define K_CTRL_K      ((int) 11)
#define K_CTRL_L      ((int) 12)
#define K_CTRL_M      ((int) 13)
#define K_CTRL_N      ((int) 14)
#define K_CTRL_O      ((int) 15)
#define K_CTRL_P      ((int) 16)
#define K_CTRL_Q      ((int) 17)
#define K_CTRL_R      ((int) 18)
#define K_CTRL_S      ((int) 19)
#define K_CTRL_T      ((int) 20)
#define K_CTRL_U      ((int) 21)
#define K_CTRL_V      ((int) 22)
#define K_CTRL_W      ((int) 23)
#define K_CTRL_X      ((int) 24)
#define K_CTRL_Y      ((int) 25)
#define K_CTRL_Z      ((int) 26)

#define K_ENTER       K_CTRL_H
#define K_TAB         K_CTRL_I
#define K_ESC         ((int) 27)
#define K_SPACE       ((int) 32)
#define K_BACK        ((int)127)

//custom control character.
#define K_SHIFT_TAB   ((int)224)
#define K_SHIFT_LEFT  ((int)225)
#define K_SHIFT_UP    ((int)226)
#define K_SHIFT_RIGHT ((int)227)
#define K_SHIFT_DOWN  ((int)228)
#define K_LEFT        ((int)229)
#define K_UP          ((int)230)
#define K_RIGHT       ((int)231)
#define K_DOWN        ((int)232)

//stduot & stderr.
__host void _h_writeout(const char *str);
__host void _h_writeerr(const char *str);
