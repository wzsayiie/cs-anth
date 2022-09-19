#include "os.h"
#include "sys/time.h"
#include "unistd.h"

void _h_sleepmilli(long long milli) {
    useconds_t micro = (useconds_t)milli * 1000;
    usleep(micro);
}

long long _h_nowmilli() {
    struct timeval time;
    gettimeofday(&time, NULL);

    return (
        (long long)time.tv_sec  * 1000 +
        (long long)time.tv_usec / 1000
    );
}
