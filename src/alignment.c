#include "uls.h"

static int get_link_len(t_list *files, char *dir, t_stat *p_stat) {
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

static int get_usr_len(t_list *files, char *dir, t_stat *p_stat) {
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

static int get_grp_len(t_list *files, char *dir, t_stat *p_stat) {
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

static int get_size_len(t_list *files, char *dir, t_stat *p_stat) {
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

void set_field_lens(t_list *entry_names, t_ls *ls, t_stat *p_stat) {
    ls->link_len = get_link_len(entry_names, ls->curr_dir_name, p_stat);
    ls->usr_len = get_usr_len(entry_names, ls->curr_dir_name, p_stat);
    ls->grp_len = get_grp_len(entry_names, ls->curr_dir_name, p_stat);
    ls->size_len = get_size_len(entry_names, ls->curr_dir_name, p_stat);
}
