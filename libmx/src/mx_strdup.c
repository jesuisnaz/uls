#include "libmx.h"

char *mx_strdup(const char *s1) {
    int size = mx_strlen(s1);
    
    if (size > 0) {
        char *str_new = mx_strnew(size);
        if(!str_new) {
            return NULL;
        }
        mx_strcpy(str_new, s1);
        return str_new;
    }
    else {
        return NULL;
    }
}
