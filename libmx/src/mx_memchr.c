#include "libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
    if (!s) {
        return NULL;
    }
    else {
        size_t i = 0;
        char *res = (char*) s;
        for ( ; res[i] && i < n; i++) {
            if (res[i] == c) {
                return (void*) &res[i];
            }
        }
    }
    return NULL;
}
