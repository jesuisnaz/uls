#include "uls.h"
#include "libmx.h"

void print_entries(DIR *dirp, t_ls *ls) {
    t_dirent *dirent_p = NULL;
    t_list *entry_names = NULL;
    bool first = true;
    char *separator = isatty(1) ? "  " : "\n";

    if ((ls->flags & FLAG_1) != 0) separator = "\n";
    while ((dirent_p = readdir(dirp)) != NULL) {
        mx_push_back(&entry_names, mx_strdup(dirent_p->d_name));
    }
    mx_sort_list(entry_names, ls->cmp_p);
    while (entry_names) {
        if (is_curr_or_prev_dir(entry_names->data)) {
            if ((ls->flags & FLAG_A) != 0 || (ls->flags & FLAG_a) == 0) {
                mx_pop_front(&entry_names);
                continue;
            }
        } else if (((char *)entry_names->data)[0] == '.' &&
        ((ls->flags & (FLAG_A | FLAG_a)) == 0)) {
            mx_pop_front(&entry_names);
            continue;
        }
        if (!first) mx_printstr(separator);
        mx_printstr(entry_names->data);
        first = false;
        mx_pop_front(&entry_names);
    }
    if (mx_is_empty(entry_names)) {
        mx_printchar('\n');
    }
    closedir(dirp);
}

void output_files(t_list **files, t_ls *ls) {
    bool print_dir_names = mx_list_size(*files) > 1;
    for (int i = 0; !mx_is_empty(*files); i++) {
        if (print_dir_names) {
            mx_printstr((*files)->data);
            mx_printstr(":\n");
        }
        if ((ls->flags & FLAG_l) != 0) {
            mx_printstr("total ");
            mx_printint(get_block_size((*files)->data, ls));
            mx_printchar('\n');
        }
        ls->curr_dir_name = (*files)->data;
        if (!(ls->flags & FLAG_l))
            print_entries(opendir((*files)->data), ls);
        else
            print_entries_l(opendir((*files)->data), ls);
        mx_pop_front(files);
        if (print_dir_names && !mx_is_empty(*files)) mx_printchar('\n');
    }
}
