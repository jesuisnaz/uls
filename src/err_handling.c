#include "uls.h"

void print_error_no_file(char *filename, t_ls *ls) {
    char *filename_in_brackets = mx_strjoin(filename, "'");
    char *msg_tmpl = errno == EACCES ? mx_strjoin(ls->uls_path, CANNOT_OPEN_TMPL)
            : mx_strjoin(ls->uls_path, NO_ACCESS_TMPL);
    char *result = mx_strjoin(msg_tmpl, filename_in_brackets);

    perror(result);
    mx_strdel(&filename_in_brackets);
    mx_strdel(&msg_tmpl);
    mx_strdel(&result);
}

void print_error_no_flag(char flag, t_ls *ls) {
    char *msg_tmpl = mx_strjoin(ls->uls_path, INV_OPTION_TMPL);

    mx_printstr(msg_tmpl);
    mx_printchar(flag);
    mx_printchar('\'');
    mx_printchar('\n');
    mx_strdel(&msg_tmpl);
}

void invalid_flag(char flag, t_ls *ls) {
    print_error_no_flag(flag, ls);
    exit(0);
}
