#include "libmx.h"

void *mx_memmem(const void *big, 
                size_t big_len, 
                const void *little, 
                size_t little_len) {
    if (!big || !little || big_len < little_len || big_len <= 0 || little_len <= 0) {
        return NULL;
    }

    const char *big_cpy = (const char *)big;
    const char *little_cpy = (const char *)little;
    if (little_len == 1) {
        return mx_memchr(big_cpy, *(int*)little_cpy, big_len);
    }
    size_t i = 0;
    for (char *current = (char*)big_cpy ; i <= big_len-little_len; i++, current++) {
        if(!mx_memcmp(current, little_cpy, little_len)) {
            return current;
        }
    }
    return NULL;
}
