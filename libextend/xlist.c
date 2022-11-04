#include "xlist.h"
#include "stdlib.h"
#include "string.h"

//assist:

static XITEM *xistore(XITEM item) {
    static XITEM cache = { NULL };

    cache = item;
    return &cache;
}

static void xlgrow(XLIST *list, int diff) {
    list->count += diff;
    list->items = realloc(list->items, sizeof(XITEM) * (size_t)(list->count));
}

static void xlmove(XLIST *list, int dst, int src, int count) {
    void  *d = list->items + dst;
    void  *s = list->items + src;
    size_t c = sizeof(XITEM) * (size_t)count;

    memmove(d, s, c);
}

//list:

XLIST *xlalloc(void) {
    return calloc(1, sizeof(XLIST));
}

void xlfree(XLIST *list, xifree ifree) {
    //IMPORTANT: passing null is allowed.
    if (!list) {
        return;
    }

    if (ifree) {
        for (int i = 0; i < list->count; ++i) {
            ifree(list->items[i].ptr);
        }
    }
    free(list->items);
    free(list);
}

void xlset(XLIST *list, int index, xifree ifree, XITEM item) {
    if (ifree) {
        ifree(list->items[index].ptr);
    }
    list->items[index] = item;
}

void xlsetp(XLIST *l, int n, xifree f, void  *i) { xlset(l, n, f, (XITEM){ .ptr = i }); }
void xlsetd(XLIST *l, int n, xifree f, double i) { xlset(l, n, f, (XITEM){ .dbl = i }); }
void xlseti(XLIST *l, int n, xifree f, int    i) { xlset(l, n, f, (XITEM){ .num = i }); }

XITEM *xlget(XLIST *list, int index) {
    return xistore(list->items[index]);
}

void xlinsert(XLIST *list, int index, XITEM item) {
    xlgrow(list, 1);
    xlmove(list, index + 1, index, list->count - index - 1);

    list->items[index] = item;
}

void xlinsertp(XLIST *l, int n, void  *i) { xlinsert(l, n, (XITEM){ .ptr = i }); }
void xlinsertd(XLIST *l, int n, double i) { xlinsert(l, n, (XITEM){ .dbl = i }); }
void xlinserti(XLIST *l, int n, int    i) { xlinsert(l, n, (XITEM){ .num = i }); }

XITEM *xlremove(XLIST *list, int index, xifree ifree) {
    XITEM item = list->items[index];
    if (ifree) {
        ifree(item.ptr);
    }

    xlmove(list, index, index + 1, list->count - index - 1);
    xlgrow(list, -1);

    //NOTE: if the item was freed, return value is garbage.
    return xistore(item);
}

void xlpush(XLIST *list, XITEM item) {
    xlinsert(list, list->count, item);
}

void xlpushp(XLIST *l, void  *i) { xlpush(l, (XITEM){ .ptr = i }); }
void xlpushd(XLIST *l, double i) { xlpush(l, (XITEM){ .dbl = i }); }
void xlpushi(XLIST *l, int    i) { xlpush(l, (XITEM){ .num = i }); }

XITEM *xlpop(XLIST *list, xifree ifree) {
    return xlremove(list, list->count - 1, ifree);
}

XITEM *xlback(XLIST *list) {
    return xlget(list, list->count - 1);
}
