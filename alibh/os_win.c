#include "os.h"
#include "environ.h"
#include "stdlib.h"

#if OS_WIN

void _h_sleepmilli(int64_t milli) {
}

int64_t _h_nowmilli() {
    return 0;
}

int _h_system(const char *cmd) {
    return system(cmd);
}

#endif //OS_WIN.
