#include "libmx.h"

int mx_count_words(const char *str, char delimeter) {
    int counter = 0;
    int i = 0;
    bool plus = 0;

    if (!str) {
        return -1;
    }
    else {
        while(str[i] != '\0') {        
            while(str[i] == delimeter && str[i] != '\0') {
                i++;
            }
            while(str[i] != delimeter && str[i] != '\0') {
                i++;
                plus = 1;
            }
            if(plus == 1) {
                counter++;
                plus = 0;
            }
        }
        return counter;
    }
}
