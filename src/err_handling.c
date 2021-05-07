#include "uls.h"

void print_error_no_file(char *filename) {
    char *t = mx_strjoin("'", filename);
    char *filename_in_brackets = mx_strjoin(t, "'");
    char *result = mx_strjoin("uls: cannot access ", filename_in_brackets);
    perror(result);
    mx_strdel(&t);
    mx_strdel(&filename_in_brackets);
    mx_strdel(&result);
}

void print_error_no_flag(char flag) {
    char *result = "uls: invalid option -- '";

    mx_printstr(result);
    mx_printchar(flag);
    mx_printchar('\'');
    mx_printchar('\n');
}

void invalid_flag(char flag) {
    print_error_no_flag(flag);
    exit(0);
}
