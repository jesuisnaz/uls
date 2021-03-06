#include "uls.h"

static void cleanup(t_list **files, t_ls **ls) {
    mx_del_list_and_data(files);
    (*ls)->curr_dir_name = NULL;
    mx_strdel(&(*ls)->uls_path);
    mx_strdel(&(*ls)->curr_year);
    free(*ls);
}

static t_ls *init_ls() {
    t_ls *ls = (t_ls *) malloc(sizeof(t_ls));
    ls->flags = 0;
    ls->cmp_p = NULL;
    ls->curr_dir_name = NULL;
    ls->uls_path = NULL;
    ls->curr_year = NULL;
    ls->link_len = 0;
    ls->usr_len = 0;
    ls->grp_len = 0;
    ls->size_len = 0;
    ls->hour_year_len = 4;
    return ls;
}

int main(int argc, char **argv) {
    t_list *dirs = NULL;
    t_ls *ls = init_ls();
    mx_parse_args(argc, argv, &dirs, ls);
    mx_output_files(&dirs, ls);
    cleanup(&dirs, &ls);
}
