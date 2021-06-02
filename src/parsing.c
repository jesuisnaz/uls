#include "uls.h"

static void find_nonexistent(t_list **files, t_ls *ls) {
    DIR *dirp = NULL;
    t_list *node = *files;
    t_list *prev = NULL;

    while (node) {
        dirp = opendir(node->data);
        if (!dirp) {
            print_error_no_file(node->data, ls);
            if (node == *files) {
                mx_pop_front(files);
                node = *files;
                continue;
            } else {
                prev->next = node->next;
                free(node);
                node = prev;
                continue;
            }
        }
        closedir(dirp);
        prev = node;
        node = node->next;
    }
}

void add_flag(t_ls *ls, char *flag) {
    for (int i = 1; flag[i]; i++) {
        switch (flag[i]) {
            case 'a':
                ls->flags &= ~FLAG_A;
                ls->flags |= FLAG_a;
                break;
            case 'A':
                ls->flags &= ~FLAG_a;
                ls->flags |= FLAG_A;
                break;
            case 'l':
                ls->flags |= FLAG_l;
                break;
            case 'R':
                ls->flags |= FLAG_R;
                break;
            case 'r':
                ls->flags |= FLAG_r;
                break;
            case '1':
                ls->flags |= FLAG_1;
                break;
            case 'd':
                ls->flags |= FLAG_d;
                break;
            case 'h':
                ls->flags |= FLAG_h;
                break;
            case '@':
                ls->flags |= FLAG_at;
                break;
            default:
                invalid_flag(flag[i], ls);
        }
    }
}


void parse_args(int argc, char **args, t_list **dirs, t_ls *ls) {
    ls->uls_path = get_uls_path(args[0]);
    ls->curr_year = get_curr_year();
    for (int i = 1; i < argc; i++) {
        if (mx_get_char_index(args[i], '-') == 0 && mx_strlen(args[i]) > 1)
            add_flag(ls, args[i]);
        else
            mx_push_back(dirs, mx_strdup(args[i]));
    }
    ls->cmp_p = (ls->flags & FLAG_r) == 0 ? &cmp : &cmp_r;
    if (mx_is_empty(*dirs)) {
        mx_push_back(dirs, mx_strdup("./"));
    } else {
        find_nonexistent(dirs, ls);
        mx_sort_list(*dirs, ls->cmp_p);
    }
}
