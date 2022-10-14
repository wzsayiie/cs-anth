#include "conapi.h"
#include "ctype.h"
#include "stdio.h"
#include "windows.h"

//console window:

void _h_getwinsize(int *width, int *height) {
    HANDLE outh = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(outh, &info);

    if (width ) { *width  = info.srWindow.Right  - info.srWindow.Left + 1; }
    if (height) { *height = info.srWindow.Bottom - info.srWindow.Top  + 1; }
}

void _h_stepcur(int stepx, int stepy) {
    HANDLE outh = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(outh, &info);

    info.dwCursorPosition.X += (SHORT)stepx;
    info.dwCursorPosition.Y += (SHORT)stepy;
    SetConsoleCursorPosition(outh, info.dwCursorPosition);
}

void _h_showcur(bool show) {
    HANDLE outh = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(outh, &info);

    info.bVisible = (BOOL)show;
    SetConsoleCursorInfo(outh, &info);
}

#define FORE_MASK (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define BACK_MASK (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY)

static bool _attrrec = false;
static WORD _defattr = 0;
static WORD _deffore = 0;
static WORD _defback = 0;

static void recordprtattr(void) {
    if (_attrrec) {
        return;
    }

    HANDLE outh = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(outh, &info);

    _attrrec = true;
    _defattr = info.wAttributes;
    _deffore = info.wAttributes & FORE_MASK;
    _defback = info.wAttributes & BACK_MASK;
}

static void setprtattr(WORD mask, WORD value) {
    HANDLE outh = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(outh, &info);

    WORD attr = (info.wAttributes & ~mask) | (value & mask);
    SetConsoleTextAttribute(outh, attr);
}

void _h_setforecolor(int color) {
    recordprtattr();

    static WORD code[C_DEFCOLOR] = {0};
    if (!code[C_DEFCOLOR - 1]) {

        code[C_BLACK      ] =  0;
        code[C_RED        ] =  FOREGROUND_RED   ;
        code[C_GREEN      ] =  FOREGROUND_GREEN ;
        code[C_YELLOW     ] =  FOREGROUND_RED   | FOREGROUND_GREEN ;
        code[C_BLUE       ] =  FOREGROUND_BLUE  ;
        code[C_PURPLE     ] =  FOREGROUND_RED   | FOREGROUND_BLUE  ;
        code[C_CYAN       ] =  FOREGROUND_GREEN | FOREGROUND_BLUE  ;
        code[C_WHITE      ] =  FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE ;

        code[C_LIGHTBLACK ] = code[C_BLACK ] | FOREGROUND_INTENSITY;
        code[C_LIGHTRED   ] = code[C_RED   ] | FOREGROUND_INTENSITY;
        code[C_LIGHTGREEN ] = code[C_GREEN ] | FOREGROUND_INTENSITY;
        code[C_LIGHTYELLOW] = code[C_YELLOW] | FOREGROUND_INTENSITY;
        code[C_LIGHTBLUE  ] = code[C_BLUE  ] | FOREGROUND_INTENSITY;
        code[C_LIGHTPURPLE] = code[C_PURPLE] | FOREGROUND_INTENSITY;
        code[C_LIGHTCYAN  ] = code[C_CYAN  ] | FOREGROUND_INTENSITY;
        code[C_LIGHTWHITE ] = code[C_WHITE ] | FOREGROUND_INTENSITY;
    }

    if (0 <= color && color < C_DEFCOLOR) {
        setprtattr(FORE_MASK, code[color]);

    } else if (color == C_DEFCOLOR) {
        setprtattr(FORE_MASK, _deffore);
    }
}

void _h_setbackcolor(int color) {
    recordprtattr();

    static WORD code[C_DEFCOLOR] = {0};
    if (!code[C_DEFCOLOR - 1]) {

        code[C_BLACK      ] =  0;
        code[C_RED        ] =  BACKGROUND_RED   ;
        code[C_GREEN      ] =  BACKGROUND_GREEN ;
        code[C_YELLOW     ] =  BACKGROUND_RED   | BACKGROUND_GREEN ;
        code[C_BLUE       ] =  BACKGROUND_BLUE  ;
        code[C_PURPLE     ] =  BACKGROUND_RED   | BACKGROUND_BLUE  ;
        code[C_CYAN       ] =  BACKGROUND_GREEN | BACKGROUND_BLUE  ;
        code[C_WHITE      ] =  BACKGROUND_RED   | BACKGROUND_GREEN | BACKGROUND_BLUE ;

        code[C_LIGHTBLACK ] = code[C_BLACK ] | BACKGROUND_INTENSITY;
        code[C_LIGHTRED   ] = code[C_RED   ] | BACKGROUND_INTENSITY;
        code[C_LIGHTGREEN ] = code[C_GREEN ] | BACKGROUND_INTENSITY;
        code[C_LIGHTYELLOW] = code[C_YELLOW] | BACKGROUND_INTENSITY;
        code[C_LIGHTBLUE  ] = code[C_BLUE  ] | BACKGROUND_INTENSITY;
        code[C_LIGHTPURPLE] = code[C_PURPLE] | BACKGROUND_INTENSITY;
        code[C_LIGHTCYAN  ] = code[C_CYAN  ] | BACKGROUND_INTENSITY;
        code[C_LIGHTWHITE ] = code[C_WHITE ] | BACKGROUND_INTENSITY;
    }

    if (0 <= color && color < C_DEFCOLOR) {
        setprtattr(BACK_MASK, code[color]);

    } else if (color == C_DEFCOLOR) {
        setprtattr(BACK_MASK, _defback);
    }
}

void _h_setunderline(bool under) {
    recordprtattr();

    if (under) {
        setprtattr(COMMON_LVB_UNDERSCORE, COMMON_LVB_UNDERSCORE);
    } else {
        setprtattr(COMMON_LVB_UNDERSCORE, 0);
    }
}

void _h_resetprtattr(void) {
    if (!_attrrec) {
        return;
    }

    HANDLE outh = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(outh, _defattr);

    _attrrec = false;
}

//stdin:

static bool  _israwmode = false;
static DWORD _canonmode = 0;

void _h_beginrawmode(void) {
    HANDLE inh = GetStdHandle(STD_INPUT_HANDLE);

    //record flags in canonical mode.
    _israwmode = true;
    GetConsoleMode(inh, &_canonmode);

    //enable raw key input.
    SetConsoleMode(inh, ENABLE_WINDOW_INPUT);
}

void _h_endrawmode(void) {
    HANDLE inh = GetStdHandle(STD_INPUT_HANDLE);

    _israwmode = false;
    SetConsoleMode(inh, _canonmode);
}

int _h_readchar(void) {
    if (!_kbhit()) {
        return K_NUL;
    }

    //in canonical mode.
    if (!_israwmode) {
        return getchar();
    }

    //in raw model:

    HANDLE       inh = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD rec ;
    DWORD        num = 0;

    ReadConsoleInput(inh, &rec, 1, &num);
    if (rec.EventType != KEY_EVENT) {
        return K_NUL;
    }

    KEY_EVENT_RECORD key = rec.Event.KeyEvent;
    if (!key.bKeyDown) {
        return K_NUL;
    }

    DWORD modi = key.dwControlKeyState;
    bool  ctrl = (modi & LEFT_CTRL_PRESSED) || (modi & RIGHT_CTRL_PRESSED);
    bool  shft = modi & SHIFT_PRESSED;
    WORD  code = key.wVirtualKeyCode;
    char  asci = key.uChar.AsciiChar;

    //ctrl+a ~ ctrl+z.
    if (ctrl && !shft && 'A' <= code && code <= 'Z') {
        return code - 'A' + 1;
    }

    //controls.
    if (!ctrl && !shft) {
        if (code == VK_RETURN) { return K_ENTER; }
        if (code == VK_TAB   ) { return K_TAB  ; }
        if (code == VK_ESCAPE) { return K_ESC  ; }
        if (code == VK_SPACE ) { return K_SPACE; }
        if (code == VK_BACK  ) { return K_BACK ; }
    }

    //shift+tab.
    if (!ctrl && shft && code == VK_TAB) {
        return K_SHIFT_TAB;
    }

    //arrows.
    if (!ctrl) {
        if (code == VK_LEFT ) { return shft ? K_SHIFT_LEFT  : K_LEFT ; }
        if (code == VK_UP   ) { return shft ? K_SHIFT_UP    : K_UP   ; }
        if (code == VK_RIGHT) { return shft ? K_SHIFT_RIGHT : K_RIGHT; }
        if (code == VK_DOWN ) { return shft ? K_SHIFT_DOWN  : K_DOWN ; }
    }

    //printables.
    if (isprint(asci)) {
        return asci;
    }

    return K_NUL;
}

//stduot & stderr:

void _h_writeout(const char *str) {
    fprintf(stdout, "%s", str);
}

void _h_writeerr(const char *str) {
    fprintf(stderr, "%s", str);
}
