#include "uls.h"

bool is_curr_or_prev_dir(char *dir) {
    return !mx_strcmp(dir, ".") || !mx_strcmp(dir, "..");
}

char *prepare_path(char *dir, char* file) {
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
