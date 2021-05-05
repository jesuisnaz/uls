#include "libmx.h"

int mx_strncmp(const char *s1, const char *s2, int n) {
    if(n == 0) {
        return 0;
    }
    else {
        int i = 0;
        for ( ; s1[i] != '\0' && s2[i] != '\0' && i < n - 1; i++) {
            if (s1[i] != s2[i]) {
                break;
            }
        }
        return s1[i] - s2[i];
    }
}
