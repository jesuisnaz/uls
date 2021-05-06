#include "uls.h"

int get_link_len(t_list *files, t_stat *p_stat) {
    t_list *node = files;

    int result = 0;
    int curr_len = 0;
    while (node) {
        stat(node->data, p_stat);
        curr_len = mx_intlen(nlink(p_stat));
        if (result < curr_len) result = curr_len;
        node = node->next;
    }
    return result;
}

int get_usr_len(t_list *files, t_stat *p_stat) {
    t_list *node = files;

    int result = 0;
    int curr_len = 0;
    while (node) {
        stat(node->data, p_stat);
        curr_len = mx_strlen(get_pw_name(p_stat));
        if (result < curr_len) result = curr_len;
        node = node->next;
    }
    return result;
}

int get_grp_len(t_list *files, t_stat *p_stat) {
    t_list *node = files;

    int result = 0;
    int curr_len = 0;
    while (node) {
        stat(node->data, p_stat);
        curr_len = mx_strlen(get_gr_name(p_stat));
        if (result < curr_len) result = curr_len;
        node = node->next;
    }
    return result;
}

int get_size_len(t_list *files, t_stat *p_stat) {
    t_list *node = files;

    int result = 0;
    int curr_len = 0;
    while (node) {
        stat(node->data, p_stat);
        curr_len = mx_intlen(get_file_size(p_stat));
        if (result < curr_len) result = curr_len;
        node = node->next;
    }
    return result;
}

int get_day_len(t_list *files, t_stat *p_stat) {
    (void) files;
    (void) p_stat;
    return 2;
}
