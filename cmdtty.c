#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMD_TL "cmd /k \"%scmdtty.bat\""

int main(int argc, const char *argv[]) {
    char  *dir  = strdup(argv[0]);
    size_t dlen = strlen(dir);
    while (dlen > 0 && dir[dlen - 1] != '\\') {
        dlen -= 1;
    }
    dir[dlen] = '\0';

    char *cmd = malloc(dlen + sizeof(CMD_TL) - 2);
    sprintf(cmd, CMD_TL, dir);
    free(dir);

    //execute the command.
    system(cmd);

    free(cmd);
}
