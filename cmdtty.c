#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[]) {
    //get directory:
    char  *dir  = strdup(argv[0]);
    size_t dlen = strlen(dir);

    while (true) {
        if (dlen == 0 || dir[dlen - 1] == '\\') {
            dir[dlen] = '\0';
            break;
        }
        dlen -= 1;
    }

    //execute command.
    char  f[] = "cmd /k \"%scmdtty.bat\"";
    char *cmd = malloc(dlen + sizeof(f));
    sprintf(cmd, f, dir);

    system(cmd);

    //clear.
    free(dir);
    free(cmd);
}
