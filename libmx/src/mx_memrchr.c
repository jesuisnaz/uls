#include "libmx.h"

void *mx_memrchr(const void *s, int c, size_t n) {
    if (!s) {
        return NULL;
    }
    else {
        char *result = (char *) s;
        for( ; n > 0; n--) {
            if(result[n-1] == c) {
                return (void*) &result[n-1];
            }
        }
    }
    return NULL;
}
