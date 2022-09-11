#include "os.h"
#include "stdlib.h"
#include "sys/timeb.h"
#include "unistd.h"

void _h_sleepmilli(int64_t milli) {
    useconds_t micro = (useconds_t)milli * 1000;
    usleep(micro);
}

int64_t _h_nowmilli() {
    struct timeb tm;
    ftime(&tm);

    return (int64_t)tm.time * 1000 + (int64_t)tm.millitm;
}

int _h_system(const char *cmd) {
    return system(cmd);
}
