#include "libmx.h"

void mx_printstr(const char *s) {
    if (s == NULL) {
        write(1, "(null)", 6);
    }
    else {
        // int strlen = 0;
        // for ( ; s[strlen] != '\0'; strlen++);
        write(1, s, mx_strlen(s));
    }
}
