#pragma once

#include "condition.h"

//item:

typedef union _u_XITEM {
    void  *ptr;
    double dbl;
    int    num;
} XITEM;

//cast a "XITEM *" to "char *", "double" and "int".
#define __xistr  *(char * *)
#define __xidbl  *(double *)
#define __xiint  *(int    *)

//list:

typedef struct _s_XLIST {
    int    count;
    XITEM *items;
} XLIST;

static inline int xlcount(XLIST *list) {
    return list->count;
}

typedef void (*xifree)(void *);

__libf XLIST *xlalloc  (void);
__libf void   xlfree   (XLIST *list, xifree ifree);

__libf void   xlset    (XLIST *list, int index, xifree ifree, XITEM  item);
__libf void   xlsetp   (XLIST *list, int index, xifree ifree, void  *item);
__libf void   xlsetd   (XLIST *list, int index, xifree ifree, double item);
__libf void   xlseti   (XLIST *list, int index, xifree ifree, int    item);
__libf XITEM *xlget    (XLIST *list, int index);

__libf void   xlinsert (XLIST *list, int index, XITEM  item );
__libf void   xlinsertp(XLIST *list, int index, void  *item );
__libf void   xlinsertd(XLIST *list, int index, double item );
__libf void   xlinserti(XLIST *list, int index, int    item );
__libf XITEM *xlremove (XLIST *list, int index, xifree ifree);

__libf void   xlpush   (XLIST *list, XITEM  item );
__libf void   xlpushp  (XLIST *list, void  *item );
__libf void   xlpushd  (XLIST *list, double item );
__libf void   xlpushi  (XLIST *list, int    item );
__libf XITEM *xlpop    (XLIST *list, xifree ifree);
__libf XITEM *xlback   (XLIST *list);
