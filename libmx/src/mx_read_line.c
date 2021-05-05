#include "libmx.h"

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
    if (fd == -1 || buf_size <= 0) {
        return -2;
    }
    static char *str = NULL;
    if(str == NULL) {
        str = mx_strdup("");
    }
    char tmp[buf_size + 1];
    for (size_t i = 0; i <= buf_size; i++) {
        tmp[i] = '\0';
    }
    char *str2 = NULL;
    int len = 0;
    int res = 0;
    int r;
    while (!mx_contains(tmp, delim) && !mx_contains(str, delim)) {
        if ((r = read(fd, tmp, buf_size)) < 0) {
            return -2;
        }
        if(r == 0 && mx_strlen(str) == 0) {
            return -1;
        }
        str2 = mx_strjoin(str, tmp);
        mx_strdel(&str);
        str = mx_strdup(str2);
        mx_strdel(&str2);
        for (size_t i = 0; i <= buf_size; i++) {
            tmp[i] = '\0';
        }
    }
    for(int i = 0; str[i] != delim; ++i, len++);
    *lineptr = mx_strndup(str, len);
    str2 = str;
    str = mx_strdup(&str[len + 1]);
    free(str2);
    res = mx_strlen(*lineptr);
    return res;
}
