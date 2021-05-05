#include "libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count) {
    int start = 0;
    int end = size - 1;
    int mid;
    
    if(!arr || !s || !count || size < 1) {
        return -1;
    }

    while (1){
        mid = start + (end - start) / 2;
        
        if(mx_strcmp(arr[start], arr[end]) > 0) {
            (*count) = 0;
            return -1;
        }
        else if(mx_strcmp(arr[mid], s) < 0) {
            (*count)++;
            start = mid + 1;
        }
        else if(mx_strcmp(arr[mid], s) > 0) {
            (*count)++;
            end = mid - 1;
        }
        else if (mx_strcmp(arr[mid], s) == 0) {
            (*count)++;
            return mid;
        }
    }
}
