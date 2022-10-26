#include "osapi.h"
#include "stdlib.h"

int _h_system(const char *cmd) {
    return system(cmd);
}

char *_h_getenv(const char *name) {
    return getenv(name);
}

int _h_atexit(void (*func)(void)) {
    return atexit(func);
}

void _h_exit(int code) {
    exit(code);
}
