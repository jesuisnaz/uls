#include "libmx.h"

char *mx_strncpy(char *dst, const char *src, int len) {
    if (!dst || !src) {
        return NULL;
    }
    else {
        for (int i = 0; src[i] && i < len; i++) {
            dst[i] = src[i];
        }
        return dst;
    }
}
