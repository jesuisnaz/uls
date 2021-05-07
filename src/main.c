#include "uls.h"
#include "libmx.h"

// TODO fix this
static void cleanup(t_list **files) {
    while (*files != NULL) {
        mx_pop_front(files);
    }
}

int main(int argc, char **argv) {
    t_list *files = NULL;
    t_ls *ls = (t_ls *)malloc(sizeof(t_ls));

    parse_args(argc, argv, &files, ls);
    output_files(&files, ls);
    cleanup(&files);
}
