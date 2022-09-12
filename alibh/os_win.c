#include "os.h"
#include "sys/timeb.h"
#include "windows.h"

void _h_sleepmilli(int64_t milli) {
    Sleep((DWORD)milli);
}

int64_t _h_nowmilli() {
    struct _timeb tm;
    _ftime(&tm);

    return (int64_t)tm.time * 1000 + (int64_t)tm.millitm;
}
