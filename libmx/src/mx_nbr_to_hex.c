#include "libmx.h"

char *mx_nbr_to_hex(unsigned long nbr) {
    short hex_len = 1;
    unsigned long nbr_cpy = nbr;
    for ( ; nbr_cpy /= 16 ; hex_len++);
    char *hex = (char*)malloc((sizeof(char)) * hex_len);
    if (!hex) {
        exit(-1);
    }
    for (int i = hex_len-1; i >= 0; i--) {
        if (nbr % 16 < 10) {
            hex[i] = (nbr % 16) + 48;
        }
        else {
            hex[i] = (nbr % 16) + 87;
        }
        nbr /= 16;
    }
    return hex;
}
