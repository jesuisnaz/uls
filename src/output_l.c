#include "uls.h"

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
    char *month_day = get_file_month_and_day(p_stat);
    char *f_hour_year = get_hour_or_year(p_stat, ls);

    mx_printchar(get_filetype_char(p_stat));
    mx_printstr(permissions(p_stat));
    print_spacing(ls->link_len, mx_intlen(l));
    mx_printint(l);
    print_spacing(ls->usr_len, mx_strlen(pw));
    mx_printstr(pw);
    print_spacing(ls->grp_len, mx_strlen(gr));
    mx_printstr(gr);
    print_spacing(ls->size_len, mx_intlen(f_s));
    mx_printint(f_s);
    mx_printchar(' ');
    mx_printstr(month_day);
    print_spacing(ls->hour_year_len, mx_strlen(f_hour_year));
    mx_printstr(f_hour_year);
    mx_printchar(' ');
    mx_printstr(entry);
    mx_printchar('\n');
    mx_strdel(&month_day);
    mx_strdel(&f_hour_year);
}

void print_entries_l(DIR *dirp, t_ls *ls) {
    t_dirent *dirent_p = NULL;
    t_list *entry_names = NULL;
    t_stat *p_stat = (t_stat *) malloc(sizeof(t_stat));
    char *file_path = NULL;

    while ((dirent_p = readdir(dirp)) != NULL) {
        mx_push_back(&entry_names, mx_strdup(dirent_p->d_name));
    }
    mx_sort_list(entry_names, ls->cmp_p);
    set_field_lens(entry_names, ls, p_stat);
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
        file_path = prepare_path(ls->curr_dir_name, entry_names->data);
        stat(file_path, p_stat);
        print_l_format(p_stat, entry_names->data, ls);
        mx_pop_front(&entry_names);
        mx_strdel(&file_path);
    }
    closedir(dirp);
}
