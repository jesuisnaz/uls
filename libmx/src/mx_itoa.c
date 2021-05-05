#include "libmx.h"

char *mx_itoa(int number) {
    if (number == INT_MIN) {
        return mx_strdup("-2147483648");
    }
    else if (number == 0) {
        return mx_strdup("0");
    }
    else {
        int number_cpy = mx_abs(number);
        int len = 1;
        bool negative = 0;
        for ( ; number_cpy /= 10; len++);
        if (number < 0) {
            len++;
            negative = 1;
        }
        number = mx_abs(number);
        char *result = mx_strnew(len);
        int i = 0;
        for ( ; number; i++) {
            result[i] = (number%10)+48;
            number /= 10;
        }
        if (negative) {
            result[i] = '-';
        }
        mx_str_reverse(result);
        return result;
    }
}
