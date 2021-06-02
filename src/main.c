#include "uls.h"
#include "libmx.h"

// TODO fix this
static void cleanup(t_list **files) {
    while (*files != NULL) {
        mx_pop_front(files);
    }
}

static t_ls *init_ls() {
    t_ls *ls = (t_ls *) malloc(sizeof(t_ls));
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

    parse_args(argc, argv, &dirs, ls);
    output_files(&dirs, ls);
    cleanup(&dirs);
}
