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

//stdin:

static bool  _israw = false;
static DWORD _canon = 0;

void _h_beginrawmode(void) {
    HANDLE inh = GetStdHandle(STD_INPUT_HANDLE);

    //record flags in canonical mode.
    _israw = true;
    GetConsoleMode(inh, &_canon);

    //enable raw key input.
    SetConsoleMode(inh, ENABLE_WINDOW_INPUT);
}

void _h_endrawmode(void) {
    HANDLE inh = GetStdHandle(STD_INPUT_HANDLE);

    _israw = false;
    SetConsoleMode(inh, _canon);
}

int _h_readchar(void) {
    if (!_kbhit()) {
        return C_NUL;
    }

    //in canonical mode.
    if (!_israw) {
        return getchar();
    }

    //in raw model:

    HANDLE       inh = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD rec ;
    DWORD        num = 0;

    ReadConsoleInput(inh, &rec, 1, &num);
    if (rec.EventType != KEY_EVENT) {
        return C_NUL;
    }

    KEY_EVENT_RECORD key = rec.Event.KeyEvent;
    if (!key.bKeyDown) {
        return C_NUL;
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
        if (code == VK_RETURN) { return C_ENTER; }
        if (code == VK_TAB   ) { return C_TAB  ; }
        if (code == VK_ESCAPE) { return C_ESC  ; }
        if (code == VK_SPACE ) { return C_SPACE; }
        if (code == VK_BACK  ) { return C_BACK ; }
    }

    //shift+tab.
    if (!ctrl && shft && code == VK_TAB) {
        return C_SHIFT_TAB;
    }

    //arrows.
    if (!ctrl) {
        if (code == VK_LEFT ) { return shft ? C_SHIFT_LEFT  : C_LEFT ; }
        if (code == VK_UP   ) { return shft ? C_SHIFT_UP    : C_UP   ; }
        if (code == VK_RIGHT) { return shft ? C_SHIFT_RIGHT : C_RIGHT; }
        if (code == VK_DOWN ) { return shft ? C_SHIFT_DOWN  : C_DOWN ; }
    }

    //printables.
    if (isprint(asci)) {
        return asci;
    }

    return C_NUL;
}

//stduot & stderr:

void _h_writeout(const char *str) {
    fprintf(stdout, "%s", str);
}

void _h_writeerr(const char *str) {
    fprintf(stderr, "%s", str);
}
