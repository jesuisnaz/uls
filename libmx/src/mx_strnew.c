#include "libmx.h"

char *mx_strnew(const int size) {
    char *new_str;
    if (size <= 0) {
        new_str = NULL;
    }
    else {
        new_str = malloc(size+1);
        if (!new_str) {
            new_str = NULL;
        }
        else {
            for (int i = 0; i <= size; i++) {
                new_str[i] = '\0';
            }
        }
    }
    return new_str;
}
