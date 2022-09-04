#include "os.h"
#include "environ.h"
#include "stdlib.h"
#include "sys/time.h"
#include "unistd.h"

#if OS_POSIX

void _h_sleepmilli(int64_t milli) {
    useconds_t micro = (useconds_t)milli * 1000;
    usleep(micro);
}

int64_t _h_nowmilli() {
    struct timeval val;
    gettimeofday(&val, NULL);

    return (
        (int64_t)val.tv_sec  * 1000 +
        (int64_t)val.tv_usec / 1000
    );
}

int _h_system(const char *cmd) {
    return system(cmd);
}

#endif //OS_POSIX.
