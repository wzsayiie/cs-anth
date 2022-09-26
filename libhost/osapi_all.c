#include "osapi.h"
#include "stdlib.h"

int _h_system(const char *cmd) {
    return system(cmd);
}
