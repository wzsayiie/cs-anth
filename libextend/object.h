#pragma once

#include "condition.h"
#include "stddef.h"

typedef struct _struct_OBJECT {
    void (*deinitchain)(void *);
} OBJECT;

__libf void OBJECT_init  (OBJECT *obj);
__libf void OBJECT_deinit(OBJECT *obj);

static inline void OBJECT_initchain  (void *obj) { OBJECT_init  (obj); }
static inline void OBJECT_deinitchain(void *obj) { OBJECT_deinit(obj); }

__libf void *newobject   (size_t size, void *initchain, void *deinitchain);
__libf void  deleteobject(void *obj);

#define defclass(name, supr, body)                          \
/**/    typedef struct _struct_##name name;                 \
/**/                                                        \
/**/    void name##_init  (name *);                         \
/**/    void name##_deinit(name *);                         \
/**/                                                        \
/**/    static inline void name##_initchain(void *obj) {    \
/**/        supr##_initchain(obj);                          \
/**/        name##_init(obj);                               \
/**/    }                                                   \
/**/    static inline void name##_deinitchain(void *obj) {  \
/**/        name##_deinit(obj);                             \
/**/        supr##_deinitchain(obj);                        \
/**/    }                                                   \
/**/                                                        \
/**/    struct _struct_##name {                             \
/**/        supr   base;                                    \
/**/        struct body;                                    \
/**/    }

#define cnew(cls)    newobject(sizeof(cls), cls##_initchain, cls##_deinitchain)
#define cdelete(obj) deleteobject(obj)
