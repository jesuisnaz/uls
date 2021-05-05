#include "libmx.h"

void *mx_memset(void *b, int c, size_t len) {
    if (!b) {
        return NULL;
    }
    else {
        for(size_t i = 0; i < len; i++) {
           ((unsigned char*)b)[i] = c;
        }
        return b;
    }
}
