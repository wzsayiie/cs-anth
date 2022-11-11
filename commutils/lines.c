//count the number of lines of source files.

#include "fileio.h"
#include "stdio.h"
#include "stdlib.h"
#include "strex.h"
#include "wildcard.h"

typedef struct _s_COUNTINF {
    int files; //the number of counted files.
    int valid; //the number of non-blank lines.
    int blank; //the number of blank lines.
} COUNTINF;

bool support(const char *path) {
    const char *types[] = {
        ".h"   , ".hh", ".hpp",
        ".c"   , ".cc", ".cpp", ".cxx",
        ".m"   , ".mm",
        ".js"  , ".ts",
        ".java",
        ".cs"  ,
        ".py"  ,
        NULL
    };

    for (const char **t = types; *t; ++t) {
        if (endswith(path, *t)) {
            return true;
        }
    }
    return false;
}

char *copydir(const char *path) {
    char *dir = strdup(path);
    return pathdir(dir);
}

char *copybase(const char *path) {
    char *base = pathbase(path);
    return strdup(base);
}

char *copypath(const char *dir, const char *base) {
    size_t size = strlen(dir) + strlen(base) + 2;
    char  *path = malloc(size);

    strcpy (path, dir );
    pathcat(path, base);

    return path;
}

void scan(const char *text, size_t size, COUNTINF *inf) {
    inf->files += 1;

    bool valid = false;
    for (size_t i = 0; i < size; ) {
        char ch = text[i];
        if (ch == '\r' && i + 1 < size && text[i + 1] == '\n') {
            //"\r\n" is treated as one newline.
            i += 2;
        } else {
            i += 1;
        }

        if (ch == '\r' || ch == '\n') {
            if (valid) {
                inf->valid += 1;
            } else {
                inf->blank += 1;
            }
            valid = false;

        } else if (ch != ' ' && ch != '\t') {
            valid = true;
        }
    }

    //count the last line.
    if (valid) {
        inf->valid += 1;
    }
}

void accfil(COUNTINF *inf, const char *path) {
    if (support(path)) {
        printf("count  %s\n", path);
    } else {
        printf("ignore %s\n", path);
        return;
    }

    size_t size = 0;
    char  *text = fcopyall(path, &size);
    if (!text) {
        return;
    }

    scan(text, size, inf);
    free(text);
}

void accdir(COUNTINF *inf, const char *dir) {
    XLIST *list = dcopyitems(dir);
    if (!list) {
        return;
    }

    for (int i = 0; i < xlcount(list); ++i) {
        char *base = __xistr xlget(list, i);
        char *path = copypath(dir, base);
        
        bool isdir = false;
        bool exist = fexists(path, &isdir);
        if (isdir) {
            accdir(inf, path);
        } else if (exist) {
            accfil(inf, path);
        }
        
        free(path);
    }

    xldestroy(list, free);
}

void accpat(COUNTINF *inf, const char *pat) {
    XLIST *list = wccopyfiles(pat);
    if (!list) {
        return;
    }

    for (int i = 0; i < xlcount(list); ++i) {
        char *path = __xistr xlget(list, i);

        bool isdir = false;
        bool exist = fexists(path, &isdir);
        if (isdir) {
            accdir(inf, path);
        } else if (exist) {
            accfil(inf, path);
        }
    }

    xldestroy(list, free);
}

int main(int argc, const char *argv[]) {
    if (argc == 1) {
        printf("no input files\n");
        return EXIT_FAILURE;
    }

    COUNTINF inf;
    memset(&inf, 0, sizeof(inf));

    for (int i = 1; i < argc; ++i) {
        const char *item = argv[i];

        //NOTE: on unix-like systems, filenames can contain '?' and '*'.
        //check if the file exists firstly.
        bool isdir = false;
        bool exist = fexists(item, &isdir);
        if (isdir) {
            accdir(&inf, item);

        } else if (exist) {
            accfil(&inf, item);

        } else if (iswcpat(item)) {
            accpat(&inf, item);

        } else {
            printf("unknown %s\n", item);
        }
    }

    int   files = inf.files;
    int   total = inf.valid + inf.blank;
    float vperc = total > 0 ? inf.valid / (float)total : 0;
    float bperc = total > 0 ? inf.blank / (float)total : 0;
    printf("\n");
    printf("total files:%8d\n", files);
    printf("total lines:%8d\n", total);
    printf("valid lines:%8d (%4.2f%%)\n", inf.valid, vperc);
    printf("blank lines:%8d (%4.2f%%)\n", inf.blank, bperc);
    printf("\n");

    return EXIT_SUCCESS;
}
