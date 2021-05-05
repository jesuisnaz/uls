#include "libmx.h"

void *mx_realloc(void *ptr, size_t size) {
    if(!ptr) {
        return mx_strnew(size);
    }
    else if((int)size < 1) {
        mx_strdel(ptr);
        return ptr;
    }
    else {
        char *new = malloc(size);
        if(!new) {
            return NULL;
        }
        else {
            mx_memcpy(new, ptr, size);
            free(ptr);
            return new;
        }
    }
    // return NULL;
}
