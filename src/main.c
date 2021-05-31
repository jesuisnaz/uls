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
    return ls;
}

int main(int argc, char **argv) {
    t_list *files = NULL;
    t_ls *ls = init_ls();

    parse_args(argc, argv, &files, ls);
    output_files(&files, ls);
    cleanup(&files);
}
