#include "object.h"
#include "stdlib.h"

void OBJECT_init  (OBJECT *obj) {}
void OBJECT_deinit(OBJECT *obj) {}

void *newobject(size_t size, void *initchain, void *deinitchain) {
    OBJECT *obj = calloc(1, size);

    obj->deinitchain = (void (*)(void *))deinitchain;
    ((void (*)(void *))initchain)(obj);

    return obj;
}

void deleteobject(void *obj) {
    ((OBJECT *)obj)->deinitchain(obj);
    free(obj);
}
