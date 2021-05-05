#include "libmx.h"

void mx_print_strarr_br(char **arr) {
    if (!arr) {
        mx_printstrn("(null)");
    }
    else {
        mx_printchar('[');
        for (int i = 0; arr[i]; i++) {
            mx_printchar('\"');
            mx_printstr(arr[i]);
            mx_printchar('\"');
            if (arr[i+1]) {
                mx_printstr(", ");
            }
        }
        mx_printchar(']');
        mx_printchar(10);
    }
}
