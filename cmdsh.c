#include "fileop.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define BUF_SIZE 128
#define BAT_FILE "cmdsh.bat"

int main() {
    //get the bat file.
    char path[BUF_SIZE];
    getexed(path, BUF_SIZE);
    pathcat(path, BAT_FILE);

    //check if the bat file exists.
    if (!fexists(path, NULL)) {
        printf("not found bat file '%s'\n", BAT_FILE);
        return 1;
    }

    //execute.
    char cmdln[BUF_SIZE] = "cmd /k ";
    strcat(cmdln, path);
    system(cmdln);

    return 0;
}
