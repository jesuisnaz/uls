#include "libmx.h"

char *mx_strtrim(const char *str) {
    if(!str) {
        return NULL;
    }
    else {
        int start_trim = 0;
        int end_trim = 0;
        for( ; mx_isspace(str[start_trim]); start_trim++);
        for( ; mx_isspace(str[mx_strlen(str) - 1 - end_trim]); end_trim++);

        char *str_new = mx_strndup(str + start_trim, mx_strlen(str) - start_trim - end_trim);
        return str_new;
    }
}
