#include "conapi.h"
#include "ctype.h"
#include "stdio.h"
#include "string.h"
#include "sys/ioctl.h"
#include "termios.h"
#include "unistd.h"

//console window:

void _h_getwinsize(int *width, int *height) {
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

    if (width ) { *width  = size.ws_col; }
    if (height) { *height = size.ws_row; }
}

void _h_stepcur(int stepx, int stepy) {
    if (stepx < 0) { fprintf(stdout, "\e[%dD", -stepx); }
    if (stepx > 0) { fprintf(stdout, "\e[%dC",  stepx); }

    if (stepy < 0) { fprintf(stdout, "\e[%dA", -stepy); }
    if (stepy > 0) { fprintf(stdout, "\e[%dB",  stepy); }
}

void _h_showcur(bool show) {
    fprintf(stdout, show ? "\e[?25h" : "\e[?25l");
}

//stdin:

static bool           _israw = false;
static struct termios _canon ;

void _h_beginrawmode(void) {
    //record flags in canonical mode.
    tcgetattr(STDIN_FILENO, &_canon);

    //set flags for raw mode:
    _israw = true;

    struct termios raw = _canon;
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

void _h_endrawmode(void) {
    _israw = false;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &_canon);
}

typedef struct _struct_KEYITEM {
    int         dst;
    const char *seq;
} KEYITEM;

static KEYITEM _keylist[] = {
    //IMPORTANT: data need to sort.
    { C_ESC        , "\e"      },
    { C_SHIFT_UP   , "\e[1;2A" },
    { C_SHIFT_DOWN , "\e[1;2B" },
    { C_SHIFT_RIGHT, "\e[1;2C" },
    { C_SHIFT_LEFT , "\e[1;2D" },
    { C_UP         , "\e[A"    },
    { C_DOWN       , "\e[B"    },
    { C_RIGHT      , "\e[C"    },
    { C_LEFT       , "\e[D"    },
    { C_SHIFT_TAB  , "\e[Z"    },
};

typedef struct _struct_KEYRANGE {
    KEYITEM *head;
    KEYITEM *tail;
    int      idx ;
} KEYRANGE;

static bool clipkeyrange(KEYRANGE *range, char aim) {
    while (range->head < range->tail && range->head->seq[range->idx] < aim) {
        range->head += 1;
    }
    while (range->tail > range->head && range->tail->seq[range->idx] > aim) {
        range->tail -= 1;
    }

    return range->head->seq[range->idx] == aim;
}

int _h_readchar(void) {
    //in canonical mode.
    if (!_israw) {
        return getchar();
    }

    //in raw mode:
    KEYRANGE range;
    memset(&range, 0, sizeof(range));

    while (true) {
        char    chr = 0;
        ssize_t num = read(STDIN_FILENO, &chr, 1);

        //no more data.
        if (num != 1) {
            if (range.head) {
                bool found = clipkeyrange(&range, '\0');
                if (found) {
                    //the sequence end.
                    return range.head->dst;
                }
            }

            return C_NUL;
        }

        //step the escape sequence.
        if (range.head) {
            bool found = clipkeyrange(&range, chr);
            if (found) {
                range.idx += 1;
                continue;
            } else {
                //the sequence exception.
                return C_NUL;
            }
        }

        //ready for escape sequences.
        if (chr == '\e') {
            range.head = _keylist;
            range.tail = _keylist + sizeof(_keylist) / sizeof(KEYITEM) - 1;
            range.idx  = 1;

            continue;
        }

        //ctrl+a ~ ctrl+z.
        if (1 <= chr && chr <= 26) {
            return chr;
        }

        //controls.
        if (chr == C_ENTER) { return C_ENTER; }
        if (chr == C_TAB  ) { return C_TAB  ; }
        if (chr == C_SPACE) { return C_SPACE; }
        if (chr == C_BACK ) { return C_BACK ; }

        //printables.
        if (isprint(chr)) {
            return chr;
        }

        //unsupports.
        return C_NUL;
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
