#include "libmx.h"

int mx_tolower(int c);

unsigned long mx_hex_to_nbr(const char *hex) {
    if(!hex) {
        return 0;
    }
    int size = mx_strlen(hex);
    int pow = 0;
    unsigned long result = 0;
    for (int i = size - 1; i >= 0; i--) {
        if (!((mx_tolower(hex[i]) >= 48 && mx_tolower(hex[i]) <= 57) || 
        (mx_tolower(hex[i]) >= 97 && mx_tolower(hex[i]) <= 102))) {
            return 0;
        }
        else {
            if (mx_tolower(hex[i]) >= 48 && mx_tolower(hex[i]) <= 57) {
                if ((result + (mx_tolower(hex[i]) - 48) * mx_pow(16, pow)) < result) {
                    return 0;
                }
                result += (mx_tolower(hex[i]) - 48) * mx_pow(16, pow);
                pow++;
            }
            else {
                if ((result + (mx_tolower(hex[i]) - 48) * mx_pow(16, pow)) < result) {
                    return 0;
                }
                result += (mx_tolower(hex[i]) - 87) * mx_pow(16, pow);
                pow++;
            }
        }
    }
    return result;
}

int mx_tolower(int c) {
    if (c >= 65 && c <= 90) {
        return c+32;
    }
    else {
        return c;
    }
}
