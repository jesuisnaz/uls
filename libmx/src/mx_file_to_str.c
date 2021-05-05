#include "libmx.h"

char *mx_file_to_str(const char *file) {
    int fp;
    char *dst_str = NULL;
    char buff;
    int count = 0;
    fp = open(file, O_RDONLY);
    if (fp > 0) {
        for ( ; read(fp, &buff, 1); count++);
        close(fp);
        if(count > 0) {
            dst_str = mx_strnew(count);
            fp = open(file, O_RDONLY);
            for (int i = 0; read(fp, &buff, 1); i++) {
                dst_str[i] = buff;
            }
            close(fp);
            return dst_str;
        }
    }
    return NULL;
}
