#include "osapi.h"
#include "sys/time.h"
#include "unistd.h"

void _h_sleepmilli(int64_t milli) {
    useconds_t micro = (useconds_t)milli * 1000;
    usleep(micro);
}

int64_t _h_nowmilli(void) {
    struct timeval time;
    gettimeofday(&time, NULL);

    return (
        (int64_t)time.tv_sec  * 1000 +
        (int64_t)time.tv_usec / 1000
    );
}
