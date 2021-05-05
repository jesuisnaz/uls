#include "libmx.h"

char *mx_del_extra_spaces(const char *str) {
    if (!str) {
        return NULL;
    }
    else {
        char *str_trim = mx_strtrim(str);
        for(int i = 0; str_trim[i]; i++) {
            if (mx_isspace(str_trim[i])) {
                str_trim[i] = ' ';
                if(mx_isspace(str_trim[i+1])) {
                    str_trim[i+1] = '\0';
                    for (int j = i+1; str_trim[j+1] != '\0'; j++) {
                        mx_swap_char(&str_trim[j], &str_trim[j+1]);
                    }
                    i--;
                }
            }
        }
        char *clean_str = mx_strdup(str_trim);
        mx_strdel(&str_trim);
        return clean_str;
    }
}
