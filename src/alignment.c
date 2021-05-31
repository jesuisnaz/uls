#include "uls.h"

void set_field_lens(t_list *entry_names, t_ls *ls, t_stat *p_stat) {
    t_list *node = entry_names;
    int lnk_l = 0, usr_l = 0, grp_l = 0, size_l = 0, hour_year_l = 0;
    char *path = NULL;

    while (node) {
        path = prepare_path(ls->curr_dir_name, node->data);
        stat(path, p_stat);
        lnk_l = mx_intlen(nlink(p_stat));
        usr_l = mx_strlen(get_pw_name(p_stat));
        grp_l = mx_strlen(get_gr_name(p_stat));
        size_l = mx_intlen(get_file_size(p_stat));
        hour_year_l = mx_strlen(get_hour_or_year(p_stat, ls));
        ls->link_len = ls->link_len < lnk_l ? lnk_l : ls->link_len;
        ls->usr_len = ls->usr_len < usr_l ? usr_l : ls->usr_len;
        ls->grp_len = ls->grp_len < grp_l ? grp_l : ls->grp_len;
        ls->size_len = ls->size_len < size_l ? size_l : ls->size_len;
        ls->hour_year_len = ls->hour_year_len < hour_year_l ? hour_year_l : ls->hour_year_len;
        node = node->next;
    }
}
