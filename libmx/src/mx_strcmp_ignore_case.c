#include "libmx.h"

int mx_strcmp_ignore_case(const char *s1, const char *s2) {
    int i = 0;
    for ( ; s1[i] != '\0' && s2[i] != '\0'; i++) {
        if (mx_tolower(s1[i]) != mx_tolower(s2[i])) {
            break;
        }
    }
    return mx_tolower(s1[i]) - mx_tolower(s2[i]);
}
