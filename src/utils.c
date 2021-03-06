#include "uls.h"

bool mx_is_curr_or_prev_dir(char *dir) {
    if (!dir) return false;
    return !mx_strcmp(dir, ".") || !mx_strcmp(dir, "..");
}

char *mx_prepare_path(char *dir, char* file) {
    char *path = mx_strdup(dir);
    char *result = NULL;
    if (dir[mx_strlen(dir) - 1] != '/') {
        mx_strdel(&path);
        path = mx_strjoin(dir, "/");
    }
    result = mx_strjoin(path, file);
    mx_strdel(&path);
    return result;
}

bool mx_cmp(void *data1, void *data2) {
    char *d1 = mx_strdup(data1);
    char *d2 = mx_strdup(data2);
    int after_dot1;
    int after_dot2;
    int result;

    for (after_dot1 = 0; d1[after_dot1] == '.'; after_dot1++);
    for (after_dot2 = 0; d2[after_dot2] == '.'; after_dot2++);
    result = mx_strcmp_ignore_case(d1 + after_dot1, d2 + after_dot2);
    mx_strdel(&d1);
    mx_strdel(&d2);
    if (result == 0) return mx_strlen(data1) > mx_strlen(data2);
    return result > 0;
}

bool mx_cmp_r(void *data1, void *data2) {
    char *d1 = mx_strdup(data1);
    char *d2 = mx_strdup(data2);
    int after_dot1;
    int after_dot2;
    int result;

    for (after_dot1 = 0; d1[after_dot1] == '.'; after_dot1++);
    for (after_dot2 = 0; d2[after_dot2] == '.'; after_dot2++);
    result = mx_strcmp_ignore_case(d1 + after_dot1, d2 + after_dot2);
    if (result == 0) return mx_strlen(data1) <= mx_strlen(data2);
    mx_strdel(&d1);
    mx_strdel(&d2);
    return result <= 0;
}

char *get_curr_year() {
    time_t curr_time = time(&curr_time);
    return mx_strndup(ctime(&curr_time) + CAL_YEAR_OFFSET, 4);
}

char *get_uls_path(char *path) {
    char *result = NULL;
    int offset;

    if (path[0] == '/') {
        result = mx_strnew(100);
        readlink("/proc/self/exe", result, 100);
    } else {
        offset = path[0] == '.' && path[1] != '.' ? 2 : 0;
        result = mx_strdup(path + offset);
    }
    return result;
}
