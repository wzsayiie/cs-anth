#include "os.h"
#include "stdlib.h"

void _h_sleepmilli(int64_t milli) {
}

int64_t _h_nowmilli() {
    return 0;
}

int _h_system(const char *cmd) {
    return system(cmd);
}
