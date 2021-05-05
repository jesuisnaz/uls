#include "libmx.h"

int mx_get_substr_index(const char *str, const char *sub) {
    if (!str || !sub) {
        return -2;
    }
    else if (mx_strlen(sub) > mx_strlen(str)) {
        return -1;
    }
    else {
        int sub_index = -1;
        for (int i = 0 ; str[i]; i++) {
            if(mx_strncmp(&str[i], sub, mx_strlen(sub)) == 0) {
                sub_index = i;
                break;
            }
        }
        return sub_index;
    }
}
