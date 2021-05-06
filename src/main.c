#include "uls.h"
#include "libmx.h"

static void print_error_no_file(char *filename) {
    char *result = mx_strjoin("Error: ", filename);
    perror(result);
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

static void add_flag(s_ls *ls, char flag) {
    switch (flag) {
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
            invalid_flag(flag);
    }
}

static void parse_args(int argc, char **args, t_list **files, s_ls *ls) {
    for (int i = 1; i < argc; i++) {
        if (mx_get_char_index(args[i], '-') == 0)
            add_flag(ls, *(args[i] + 1));
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

static void print_entries(DIR *dirp, s_ls *ls) {
    s_dirent *direntp = NULL;
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

static void output_files(t_list **files, s_ls *ls) {
    bool print_dir_names = mx_list_size(*files) > 1;
    for (int i = 0; !mx_is_empty(*files); i++) {
        if (print_dir_names) {
            mx_printstr((*files)->data);
            mx_printstr(":\n");
        }
        print_entries(opendir((*files)->data), ls);
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
    s_ls *ls = (s_ls *)malloc(sizeof(s_ls));

    parse_args(argc, argv, &files, ls);
    output_files(&files, ls);
    cleanup(&files);
}
