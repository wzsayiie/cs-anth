#include "conapi.h"
#include "Windows.h"
#include "ctype.h"
#include "stdio.h"

//window information:

void _h_getwinsize(int *width, int *height) {
    HANDLE outh = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(outh, &info);

    if (width ) { *width  = info.srWindow.Right  - info.srWindow.Left + 1; }
    if (height) { *height = info.srWindow.Bottom - info.srWindow.Top  + 1; }
}

void _h_stepcursor(int stepx, int stepy) {
    HANDLE outh = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(outh, &info);

    info.dwCursorPosition.X += (SHORT)stepx;
    info.dwCursorPosition.Y += (SHORT)stepy;
    SetConsoleCursorPosition(outh, info.dwCursorPosition);
}

void _h_showcursor(bool show) {
    HANDLE outh = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(outh, &info);

    info.bVisible = (BOOL)show;
    SetConsoleCursorInfo(outh, &info);
}

//stdin:

static bool  _iscanon  = true;
static DWORD _canondat = 0;

void _h_beginrawin(void) {
    HANDLE inh = GetStdHandle(STD_INPUT_HANDLE);

    //record data of canonical input mode.
    GetConsoleMode(inh, &_canondat);
    _iscanon = false;

    //set flags for raw input mode.
    SetConsoleMode(inh, ENABLE_WINDOW_INPUT);
}

void _h_endrawin(void) {
    HANDLE inh = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(inh, _canondat);

    _iscanon = true;
}

int _h_readkey(void) {
    //in canonical input mode.
    if (_iscanon) {
        return getchar();
    }

    //in raw input model:
    if (!_kbhit()) {
        return K_NUL;
    }

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

    DWORD state = key.dwControlKeyState;
    bool  ctrl  = (state & LEFT_CTRL_PRESSED) || (state & RIGHT_CTRL_PRESSED);
    bool  shift = state & SHIFT_PRESSED;
    WORD  code  = key.wVirtualKeyCode;
    char  ascii = key.uChar.AsciiChar;

    //ctrl+a ~ ctrl+z.
    if (ctrl && !shift && 'A' <= code && code <= 'Z') {
        return code - 'A' + 1;
    }

    //controls.
    if (!ctrl && !shift) {
        if (code == VK_RETURN) { return K_ENTER; }
        if (code == VK_TAB   ) { return K_TAB  ; }
        if (code == VK_ESCAPE) { return K_ESC  ; }
        if (code == VK_SPACE ) { return K_SPACE; }
        if (code == VK_BACK  ) { return K_BACK ; }
    }

    //shift+tab.
    if (!ctrl && shift && code == VK_TAB) {
        return K_SHIFT_TAB;
    }

    //arrows.
    if (!ctrl) {
        if (code == VK_LEFT ) { return shift ? K_SHIFT_LEFT  : K_LEFT ; }
        if (code == VK_UP   ) { return shift ? K_SHIFT_UP    : K_UP   ; }
        if (code == VK_RIGHT) { return shift ? K_SHIFT_RIGHT : K_RIGHT; }
        if (code == VK_DOWN ) { return shift ? K_SHIFT_DOWN  : K_DOWN ; }
    }

    //printables.
    if (isprint(ascii)) {
        return ascii;
    }

    return K_NUL;
}

//stduot & stderr:

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

void _h_setforecolor(ccolor color) {
    recordprtattr();

    static WORD code[C_DEFCOLOR];
    static bool first = true;
    if (first) {
        first = false;

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

void _h_setbackcolor(ccolor color) {
    recordprtattr();

    static WORD code[C_DEFCOLOR];
    static bool first = true;
    if (first) {
        first = false;

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

void _h_writeout(const char *str, int num) {
    HANDLE outh = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD  writ = 0;
    WriteConsole(outh, str, (DWORD)num, &writ, NULL);
}

void _h_flushout(void) {
    HANDLE outh = GetStdHandle(STD_OUTPUT_HANDLE);
    FlushFileBuffers(outh);
}

void _h_writeerr(const char *str, int num) {
    HANDLE errh = GetStdHandle(STD_ERROR_HANDLE);
    DWORD  writ = 0;
    WriteConsole(errh, str, (DWORD)num, &writ, NULL);
}

void _h_flusherr(void) {
    HANDLE errh = GetStdHandle(STD_ERROR_HANDLE);
    FlushFileBuffers(errh);
}
