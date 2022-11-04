#pragma once

#include "condition.h"
#include "stdbool.h"

//window information.
__host void _h_getwinsize(int *width, int *height);
__host void _h_stepcursor(int  stepx, int  stepy );
__host void _h_showcursor(bool show);

//stdin:

__host void _h_beginrawin(void);
__host void _h_endrawin  (void);

//in canonical input mode, this function does not return until an enter key pressed.
//in raw input mode, this function is non-blocking. if no data in stdin, it will return 0.
__host int _h_readkey(void);

//in raw input mode,
//"readkey()" possibly returns control characters followed.
typedef enum _e_ckey {
    K_NUL    =  0,

    K_CTRL_A =  1,
    K_CTRL_B =  2,
    K_CTRL_C =  3,
    K_CTRL_D =  4,
    K_CTRL_E =  5,
    K_CTRL_F =  6,
    K_CTRL_G =  7,
    K_CTRL_H =  8,
    K_CTRL_I =  9,
    K_CTRL_J = 10,
    K_CTRL_K = 11,
    K_CTRL_L = 12,
    K_CTRL_M = 13,
    K_CTRL_N = 14,
    K_CTRL_O = 15,
    K_CTRL_P = 16,
    K_CTRL_Q = 17,
    K_CTRL_R = 18,
    K_CTRL_S = 19,
    K_CTRL_T = 20,
    K_CTRL_U = 21,
    K_CTRL_V = 22,
    K_CTRL_W = 23,
    K_CTRL_X = 24,
    K_CTRL_Y = 25,
    K_CTRL_Z = 26,

    K_ENTER  = K_CTRL_H,
    K_TAB    = K_CTRL_I,
    K_ESC    = 27,
    K_SPACE  = 32,
    K_BACK   =127,

    //extension control character.
    K_SHIFT_TAB   = 224,
    K_SHIFT_LEFT  = 225,
    K_SHIFT_UP    = 226,
    K_SHIFT_RIGHT = 227,
    K_SHIFT_DOWN  = 228,
    K_LEFT        = 229,
    K_UP          = 230,
    K_RIGHT       = 231,
    K_DOWN        = 232,

} ckey;

//stduot & stderr:

typedef enum _e_ccolor {
    C_BLACK       =  0,
    C_RED         =  1,
    C_GREEN       =  2,
    C_YELLOW      =  3,
    C_BLUE        =  4,
    C_PURPLE      =  5,
    C_CYAN        =  6,
    C_WHITE       =  7,
    C_LIGHTBLACK  =  8,
    C_LIGHTRED    =  9,
    C_LIGHTGREEN  = 10,
    C_LIGHTYELLOW = 11,
    C_LIGHTBLUE   = 12,
    C_LIGHTPURPLE = 13,
    C_LIGHTCYAN   = 14,
    C_LIGHTWHITE  = 15,
    C_DEFCOLOR    = 16,
} ccolor;

__host void _h_setforecolor(ccolor color);
__host void _h_setbackcolor(ccolor color);
__host void _h_setunderline(bool   under);
__host void _h_resetprtattr(void);

__host void _h_writeout(const char *str, int num);
__host void _h_flushout(void);

__host void _h_writeerr(const char *str, int num);
__host void _h_flusherr(void);
