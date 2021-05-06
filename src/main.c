#include "uls.h"
#include "libmx.h"

static void print_error_no_file(char *filename) {
    char *t = mx_strjoin("'", filename);
    char *filename_in_brackets = mx_strjoin(t, "'");
    char *result = mx_strjoin("uls: cannot access ", filename_in_brackets);
    perror(result);
    mx_strdel(&t);
    mx_strdel(&filename_in_brackets);
    mx_strdel(&result);
}

static void print_error_no_flag(char flag) {
    char *result = "uls: invalid option -- '";

    mx_printstr(result);
    mx_printchar(flag);
    mx_printchar('\'');
    mx_printchar('\n');
}

static void invalid_flag(char flag) {
    print_error_no_flag(flag);
    exit(0);
}

static void find_nonexistent(t_list **files) {
    DIR *dirp = NULL;
    t_list *node = *files;
    t_list *prev = NULL;

    while (node) {
        dirp = opendir(node->data);
        if (dirp == NULL) {
            print_error_no_file(node->data);
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

bool cmp(void *data1, void *data2) {
    char *d1 = mx_strdup(data1);
    char *d2 = mx_strdup(data2);
    int after_dot1;
    int after_dot2;
    for (after_dot1 = 0; d1[after_dot1] == '.'; after_dot1++);
    for (after_dot2 = 0; d2[after_dot2] == '.'; after_dot2++);
    int result = mx_strcmp_ignore_case(d1 + after_dot1, d2 + after_dot2);
    if (result == 0) return mx_strlen(data1) > mx_strlen(data2);
    mx_strdel(&d1);
    mx_strdel(&d2);
    return result > 0;
}

bool cmp_r(void *data1, void *data2) {
    char *d1 = mx_strdup(data1);
    char *d2 = mx_strdup(data2);
    int after_dot1;
    int after_dot2;
    for (after_dot1 = 0; d1[after_dot1] == '.'; after_dot1++);
    for (after_dot2 = 0; d2[after_dot2] == '.'; after_dot2++);
    int result = mx_strcmp_ignore_case(d1 + after_dot1, d2 + after_dot2);
    if (result == 0) return mx_strlen(data1) <= mx_strlen(data2);
    mx_strdel(&d1);
    mx_strdel(&d2);
    return result <= 0;
}

static void add_flag(t_ls *ls, char *flag) {
    for (int i = 1; flag[i]; i++) {
        switch (flag[i]) {
            case 'l':
                ls->flags |= FLAG_l;
                break;
            case 'a':
                ls->flags |= FLAG_a;
                break;
            case 'r':
                ls->flags |= FLAG_r;
                break;
            case '1':
                ls->flags |= FLAG_1;
                break;
            case 'A':
                ls->flags |= FLAG_A;
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
                invalid_flag(flag[i]);
        }
    }
}

static void parse_args(int argc, char **args, t_list **files, t_ls *ls) {
    for (int i = 1; i < argc; i++) {
        if (mx_get_char_index(args[i], '-') == 0 && mx_strlen(args[i]) > 1)
            add_flag(ls, args[i]);
        else
            mx_push_back(files, mx_strdup(args[i]));
    }
    ls->cmp_p = (ls->flags & FLAG_r) == 0 ? &cmp : &cmp_r;
    if (mx_is_empty(*files)) {
        mx_push_back(files, mx_strdup("./"));
    } else {
        find_nonexistent(files);
        mx_sort_list(*files, ls->cmp_p);
    }
}

static void print_entries(DIR *dirp, t_ls *ls) {
    t_dirent *direntp = NULL;
    t_list *entry_names = NULL;
    bool first = true;
    char *separator = isatty(1) ? "  " : "\n";

    if ((ls->flags & FLAG_1) != 0) separator = "\n";
    while ((direntp = readdir(dirp)) != NULL) {
        mx_push_back(&entry_names, mx_strdup(direntp->d_name));
    }
    mx_sort_list(entry_names, ls->cmp_p);
    while (entry_names) {
        if (mx_strcmp(entry_names->data, ".") == 0 ||
         mx_strcmp(entry_names->data, "..") == 0) {
            if ((ls->flags & FLAG_A) != 0 || (ls->flags & FLAG_a) == 0) {
                mx_pop_front(&entry_names);
            } else {
                if (!first) mx_printstr(separator);
                first = false;
                mx_printstr(entry_names->data);
                mx_pop_front(&entry_names);
            }
        } else if (((char *)entry_names->data)[0] == '.' &&
        ((ls->flags & (FLAG_A | FLAG_a)) == 0)) {
            mx_pop_front(&entry_names);
        } else {
            if (!first) mx_printstr(separator);
            mx_printstr(entry_names->data);
            first = false;
            mx_pop_front(&entry_names);
        }
        if (mx_is_empty(entry_names)) {
            mx_printchar('\n');
        }
    }
    closedir(dirp);
}

static void print_spacing(int col_len, int word_len) {
    mx_printchar(' ');
    for (int i = 0; i < col_len - word_len; i++) {
        mx_printchar(' ');
    }
}

static void print_l_format(t_stat *p_stat, char *entry, t_ls *ls) {
    int l = nlink(p_stat);
    char *pw = get_pw_name(p_stat);
    char *gr = get_gr_name(p_stat);
    int f_s = get_file_size(p_stat);
    char *mt = mtime(p_stat);

    mx_printchar(get_filetype_char(p_stat));
    mx_printstr(permissions(p_stat));
    print_spacing(ls->link_len, mx_intlen(l));
    mx_printint(nlink(p_stat));
    print_spacing(ls->usr_len, mx_strlen(pw));
    mx_printstr(get_pw_name(p_stat));
    print_spacing(ls->grp_len, mx_strlen(gr));
    mx_printstr(get_gr_name(p_stat));
    print_spacing(ls->size_len, mx_intlen(f_s));
    mx_printint(get_file_size(p_stat));

    mx_printchar(' ');
    mx_printstr(mt);
    mx_printchar(' ');
    mx_printstr(entry);
}

static void print_entries_l(DIR *dirp, t_ls *ls) {
    t_dirent *direntp = NULL;
    t_list *entry_names = NULL;
    t_stat *p_stat = (t_stat *) malloc(sizeof(t_stat));

    while ((direntp = readdir(dirp)) != NULL) {
        mx_push_back(&entry_names, mx_strdup(direntp->d_name));
    }
    mx_sort_list(entry_names, ls->cmp_p);
    ls->link_len = get_link_len(entry_names, p_stat);
    ls->usr_len = get_usr_len(entry_names, p_stat);
    ls->grp_len = get_grp_len(entry_names, p_stat);
    ls->size_len = get_size_len(entry_names, p_stat);
    ls->day_len = get_day_len(entry_names, p_stat);
    while (entry_names) {
        stat(entry_names->data, p_stat);
        if (mx_strcmp(entry_names->data, ".") == 0 ||
            mx_strcmp(entry_names->data, "..") == 0) {
            if ((ls->flags & FLAG_A) != 0 || (ls->flags & FLAG_a) == 0) {
                mx_pop_front(&entry_names);
                continue;
            } else {
                print_l_format(p_stat, entry_names->data, ls);
                mx_pop_front(&entry_names);
            }
        } else if (((char *)entry_names->data)[0] == '.' &&
                   ((ls->flags & (FLAG_A | FLAG_a)) == 0)) {
            mx_pop_front(&entry_names);
            continue;
        } else {
            print_l_format(p_stat, entry_names->data, ls);
            mx_pop_front(&entry_names);
        }
        mx_printchar('\n');
//        free(p_stat);
    }
    closedir(dirp);
}

static void output_files(t_list **files, t_ls *ls) {
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
        if ((ls->flags & FLAG_l) == 0)
            print_entries(opendir((*files)->data), ls);
        else
            print_entries_l(opendir((*files)->data), ls);
        mx_pop_front(files);
        if (print_dir_names && !mx_is_empty(*files)) mx_printchar('\n');
    }
}

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
