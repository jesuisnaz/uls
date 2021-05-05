#include "libmx.h"

char *mx_str_tolower(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = mx_tolower(str[i]);
    }
    return str;
}
