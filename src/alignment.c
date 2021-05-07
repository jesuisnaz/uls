#include "uls.h"

int get_link_len(t_list *files, char *dir, t_stat *p_stat) {
    t_list *node = files;
    int result = 0;
    int curr_len = 0;
    char *path = NULL;

    while (node) {
        path = prepare_path(dir, node->data);
        stat(path, p_stat);
        curr_len = mx_intlen(nlink(p_stat));
        if (result < curr_len) result = curr_len;
        node = node->next;
    }
    mx_strdel(&path);
    return result;
}

int get_usr_len(t_list *files, char *dir, t_stat *p_stat) {
    t_list *node = files;
    int result = 0;
    int curr_len = 0;
    char *path = NULL;

    while (node) {
        path = prepare_path(dir, node->data);
        stat(path, p_stat);
        curr_len = mx_strlen(get_pw_name(p_stat));
        if (result < curr_len) result = curr_len;
        node = node->next;
    }
    mx_strdel(&path);
    return result;
}

int get_grp_len(t_list *files, char *dir, t_stat *p_stat) {
    t_list *node = files;
    int result = 0;
    int curr_len = 0;
    char *path = NULL;

    while (node) {
        path = prepare_path(dir, node->data);
        stat(path, p_stat);
        curr_len = mx_strlen(get_gr_name(p_stat));
        if (result < curr_len) result = curr_len;
        node = node->next;
    }
    mx_strdel(&path);
    return result;
}

int get_size_len(t_list *files, char *dir, t_stat *p_stat) {
    t_list *node = files;
    int result = 0;
    int curr_len;
    char *path = NULL;

    while (node) {
        path = prepare_path(dir, node->data);
        stat(path, p_stat);
        curr_len = mx_intlen(get_file_size(p_stat));
        if (result < curr_len) result = curr_len;
        node = node->next;
    }
    mx_strdel(&path);
    return result;
}
