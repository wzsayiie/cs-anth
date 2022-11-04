#include "conapi.h"
#include "ctype.h"
#include "stdio.h"
#include "string.h"
#include "sys/ioctl.h"
#include "termios.h"
#include "unistd.h"

//window information:

void _h_getwinsize(int *width, int *height) {
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

    if (width ) { *width  = size.ws_col; }
    if (height) { *height = size.ws_row; }
}

void _h_stepcursor(int stepx, int stepy) {
    if (stepx < 0) { printf("\e[%dD", -stepx); }
    if (stepx > 0) { printf("\e[%dC",  stepx); }

    if (stepy < 0) { printf("\e[%dA", -stepy); }
    if (stepy > 0) { printf("\e[%dB",  stepy); }
}

void _h_showcursor(bool show) {
    printf(show ? "\e[?25h" : "\e[?25l");
}

//stdin:

static bool           _iscanon = false;
static struct termios _canondat;

void _h_beginrawin(void) {
    //record flags of canonical input mode.
    tcgetattr(STDIN_FILENO, &_canondat);
    _iscanon = false;

    //set flags for raw input mode:
    struct termios raw = _canondat;
    raw.c_lflag &= ~ICANON; //disable canonical.
    raw.c_lflag &= ~ECHO  ; //disable echo.
    raw.c_lflag &= ~ISIG  ; //disable interrupt(ctrl+c) and stop(ctrl+z) signals.
    raw.c_lflag &= ~IEXTEN; //disable escape(ctrl+v) and discard(ctrl+o) signals.
    raw.c_iflag &= ~IXON  ; //disable pause(ctrl+s) and resume(ctrl+q) signals.
    raw.c_iflag &= ~ICRNL ; //disable carriage-translating(ctrl+m).

    raw.c_cc[VMIN ] = 0;
    raw.c_cc[VTIME] = 1; //read waiting time. one unit is 100 milliseconds.

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void _h_endrawin(void) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &_canondat);
    _iscanon = true;
}

typedef struct _s_KEYITEM {
    ckey        val;
    const char *seq;
} KEYITEM;

static KEYITEM _keylist[] = {
    //IMPORTANT: data need to sort.
    { K_ESC        , "\e"      },
    { K_SHIFT_UP   , "\e[1;2A" },
    { K_SHIFT_DOWN , "\e[1;2B" },
    { K_SHIFT_RIGHT, "\e[1;2C" },
    { K_SHIFT_LEFT , "\e[1;2D" },
    { K_UP         , "\e[A"    },
    { K_DOWN       , "\e[B"    },
    { K_RIGHT      , "\e[C"    },
    { K_LEFT       , "\e[D"    },
    { K_SHIFT_TAB  , "\e[Z"    },
};

typedef struct _s_KEYRANGE {
    KEYITEM *head;
    KEYITEM *tail;
    int      idx ;
} KEYRANGE;

static bool clipkeyrange(KEYRANGE *range, char val) {
    while (range->head < range->tail && range->head->seq[range->idx] < val) {
        range->head += 1;
    }
    while (range->tail > range->head && range->tail->seq[range->idx] > val) {
        range->tail -= 1;
    }

    return range->head->seq[range->idx] == val;
}

static int readkeyseq() {
    KEYRANGE range;
    range.head = _keylist;
    range.tail = _keylist + sizeof(_keylist) / sizeof(KEYITEM) - 1;
    range.idx  = 1;

    while (true) {
        //only one left.
        if (range.head == range.tail) {
            return range.head->val;
        }

        char    chr = 0;
        ssize_t num = read(STDIN_FILENO, &chr, 1);

        //no more data.
        if (num != 1) {
            bool found = clipkeyrange(&range, '\0');
            if (found) {
                return range.head->val;
            } else {
                return K_NUL;
            }
        }

        //step one.
        bool found = clipkeyrange(&range, chr);
        if (found) {
            range.idx += 1;
        } else {
            return K_NUL;
        }
    }
    return K_NUL;
}

int _h_readkey(void) {
    //in canonical input mode.
    if (_iscanon) {
        return getchar();
    }

    //in raw input mode:

    char    chr = 0;
    ssize_t num = read(STDIN_FILENO, &chr, 1);

    //no more data.
    if (num != 1) {
        return K_NUL;
    }

    //read a escape sequence.
    if (chr == '\e') {
        return readkeyseq();
    }

    //ctrl+a ~ ctrl+z.
    if (1 <= chr && chr <= 26) {
        return chr;
    }

    //controls.
    if (chr == K_ENTER) { return K_ENTER; }
    if (chr == K_TAB  ) { return K_TAB  ; }
    if (chr == K_SPACE) { return K_SPACE; }
    if (chr == K_BACK ) { return K_BACK ; }

    //printables.
    if (isprint(chr)) {
        return chr;
    }

    return K_NUL;
}

//stduot & stderr:

void _h_setforecolor(ccolor color) {
    static const int code[C_DEFCOLOR + 1] = {
        [C_BLACK      ] = 30,
        [C_RED        ] = 31,
        [C_GREEN      ] = 32,
        [C_YELLOW     ] = 33,
        [C_BLUE       ] = 34,
        [C_PURPLE     ] = 35,
        [C_CYAN       ] = 36,
        [C_WHITE      ] = 37,

        [C_LIGHTBLACK ] = 90,
        [C_LIGHTRED   ] = 91,
        [C_LIGHTGREEN ] = 92,
        [C_LIGHTYELLOW] = 93,
        [C_LIGHTBLUE  ] = 94,
        [C_LIGHTPURPLE] = 95,
        [C_LIGHTCYAN  ] = 96,
        [C_LIGHTWHITE ] = 97,

        [C_DEFCOLOR   ] = 39,
    };

    if (0 <= color && color <= C_DEFCOLOR) {
        printf("\e[%dm", code[color]);
    }
}

void _h_setbackcolor(ccolor color) {
    static const int code[C_DEFCOLOR + 1] = {
        [C_BLACK      ] =  40,
        [C_RED        ] =  41,
        [C_GREEN      ] =  42,
        [C_YELLOW     ] =  43,
        [C_BLUE       ] =  44,
        [C_PURPLE     ] =  45,
        [C_CYAN       ] =  46,
        [C_WHITE      ] =  47,

        [C_LIGHTBLACK ] = 100,
        [C_LIGHTRED   ] = 101,
        [C_LIGHTGREEN ] = 102,
        [C_LIGHTYELLOW] = 103,
        [C_LIGHTBLUE  ] = 104,
        [C_LIGHTPURPLE] = 105,
        [C_LIGHTCYAN  ] = 106,
        [C_LIGHTWHITE ] = 107,

        [C_DEFCOLOR   ] =  49,
    };

    if (0 <= color && color <= C_DEFCOLOR) {
        printf("\e[%dm", code[color]);
    }
}

void _h_setunderline(bool under) {
    printf(under ? "\e[4m" : "\e[24m");
}

void _h_resetprtattr(void) {
    printf("\e[0m");
}

void _h_writeout(const char *str, int num) {
    write(STDOUT_FILENO, str, (size_t)num);
}

void _h_flushout(void) {
    fflush(stdout);
}

void _h_writeerr(const char *str, int num) {
    write(STDERR_FILENO, str, (size_t)num);
}

void _h_flusherr(void) {
    fflush(stderr);
}
