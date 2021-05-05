#include "uls.h"
#include "libmx.h"

static void print_error_no_file(char *filename) {
    char *result = mx_strjoin("Error: ", filename);
    perror(result);
    mx_strdel(&result);
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


static void parse_args(int argc, char **args, t_list **files) {
    if (argc < 2) {
        mx_push_back(files, mx_strdup("./"));
    } else {
        for (int i = 1; args[i]; i++) {
            mx_push_back(files, mx_strdup(args[i]));
        }
    }
}

bool cmp(void *data1, void *data2) {
    char *d1 = mx_strdup(data1);
    char *d2 = mx_strdup(data2);
    int after_dot1;
    int after_dot2;
    for (after_dot1 = 0; d1[after_dot1] == '.'; after_dot1++);
    for (after_dot2 = 0; d2[after_dot2] == '.'; after_dot2++);
    bool result = mx_strcmp_ignore_case(d1 + after_dot1, d2 + after_dot2) > 0;
    mx_strdel(&d1);
    mx_strdel(&d2);
    return result;
}

static void print_entries(DIR *dirp) {
    struct dirent* direntp = NULL;
    t_list *entry_names = NULL;
    bool (*cmp_p)(void *, void *) = &cmp;

    while ((direntp = readdir(dirp)) != NULL) {
        mx_push_back(&entry_names, mx_strdup(direntp->d_name));
    }
    mx_sort_list(entry_names, cmp_p);
    while (entry_names) {
        mx_printstr(entry_names->data);
        mx_pop_front(&entry_names);
        mx_is_empty(entry_names) ? mx_printchar('\n') : mx_printstr("  ");
    }
    closedir(dirp);
}

static void output_files(t_list **files) {
    bool print_dir_names = mx_list_size(*files) > 1;
    for (int i = 0; !mx_is_empty(*files); i++) {
        if (print_dir_names) {
            mx_printstr((*files)->data);
            mx_printstr(":\n");
        }
        print_entries(opendir((*files)->data));
        mx_pop_front(files);
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
    bool (*cmp_p)(void *, void *) = &cmp;

    parse_args(argc, argv, &files);
    find_nonexistent(&files);
    mx_sort_list(files, cmp_p);
    output_files(&files);
    cleanup(&files);
}
