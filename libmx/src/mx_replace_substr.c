#include "libmx.h"

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
    if (!str || !sub || !replace) {
        return NULL;
    }
    else if(mx_strlen(str) == 0 && mx_strlen(sub) == 0) {
        char *new_str = mx_strdup(replace);
        return (char*)new_str;
    }
    else if(mx_strlen(sub) == 0 || mx_get_substr_index(str, sub) == -1) {
        char *new_str = mx_strdup(str);
        return (char*)new_str;
    }
    else {
        char *new_str = mx_strnew(mx_strlen(str) - 
                                 (mx_count_substr(str, sub) * mx_strlen(sub)) + 
                                 (mx_count_substr(str, sub) * mx_strlen(replace)));
        int i = 0;
        while(str+i) {
            if (mx_get_substr_index(str+i, sub) == 0) {
                mx_strcat(new_str, replace);
                i += mx_strlen(sub);
            }
            else if(mx_get_substr_index(str+i, sub) > 0) {
                mx_strncat(new_str, str+i, mx_get_substr_index(str+i, sub));
                i += mx_get_substr_index(str+i, sub);
            }
            else if(mx_get_substr_index(str+i, sub) == -1 && mx_strlen(str+i) > 0) {
                mx_strcat(new_str, str + i);
                break;
            }
            else {
                break;
            }
        }
        return (char*)new_str;
    }
}
