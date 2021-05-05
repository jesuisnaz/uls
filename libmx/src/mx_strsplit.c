#include "libmx.h"

char **mx_strsplit(const char *s, char c) {
    if(!s) {
        return NULL;
    }
    else {
        char **arr = (char**) malloc(sizeof(char*) * mx_count_words(s, c) + 1);
        int word = 0;
        int len = 0;
        for(int i = 0; word < mx_count_words(s, c); word++) {
            while(s[i] == c) {
                i++;
            }
            while(s[i] != c && s[i] != '\0') {
                len++;
                i++;
            }
            arr[word] = mx_strndup(&s[i-len], len);
            len = 0;
        }
        return arr;
    }
}
