#include "libmx.h"

int mx_count_substr(const char *str, const char *sub) {
    if (!str || !sub) {
        return -1;
    }
    else if (mx_strlen(sub) == 0) {
        return 0;
    }
    else {    
        int counter = 0;
        int i = 0;
        while(mx_strstr(str + i, sub) != 0) {
            if(mx_strstr(str + i, sub) != 0) {
                i = (char*)mx_strstr(str + i, sub) - str + 1;
                counter++;
            }
            else {
                return counter;
            }
        }
        return counter;
    }
}
