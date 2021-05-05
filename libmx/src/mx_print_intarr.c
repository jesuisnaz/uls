#include "libmx.h"

void mx_print_intarr(int *arr, int n) {
    if (!arr) {
        mx_printstrn("(null)");
    }
    else {
        int i = 0;
        while (i<n) {
            mx_printint(arr[i]);
            mx_printchar(' ');
            i++;
        }
        mx_printchar(10);
    }
}
