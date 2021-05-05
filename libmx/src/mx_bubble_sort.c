#include "libmx.h"
// #include "../inc/libmx.h"

int mx_bubble_sort(int *arr, int size) {
    int tmp;
    int swap = 0;
    for(int i = 0; i < size-1; i++) {
        for(int j = 0; j < size-i-1; j++) {
            if(arr[j] > arr[j + 1]) {
                tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
                swap++;
            }
        }
    }
    return swap;
}

// #include <stdio.h>
// int main() {
//     int arr1[9] = {68, -20, 2, -6, 8, 53, 79, -30, -25};
//     int arr2[2] = {-7, -23};
//     int arr3[13] = {33,19,39,47,10,63,69,48,26,25,67,-4,2};
//     int arr4[15] = {-11,79,69,-9,-23,2,43,66,-25,35,38,61,84,7,11};
//     int arr5[7] = {-2,20,54,86,60,73,52};
//     printf("%i\n", mx_bubble_sort(arr1, 9));
//     printf("%i\n", mx_bubble_sort(arr2, 2));
//     printf("%i\n", mx_bubble_sort(arr3, 13));
//     printf("%i\n", mx_bubble_sort(arr4, 15));
//     printf("%i\n", mx_bubble_sort(arr5, 7));
// }
