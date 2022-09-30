#include "osapi.h"
#include "sys/timeb.h"
#include "windows.h"

void _h_sleepmilli(long long milli) {
    Sleep((DWORD)milli);
}

long long _h_nowmilli(void) {
    struct _timeb tm;
    _ftime(&tm);

    return (
        (long long)tm.time * 1000 +
        (long long)tm.millitm
    );
}
