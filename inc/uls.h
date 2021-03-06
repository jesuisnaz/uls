#pragma once

#include "libmx.h"

#include <stdlib.h>

#define __USE_MISC
#define __USE_XOPEN

#define NTIME_LEN 25
#define PATH_MAX 255

#define FLAG_l 0x1
#define FLAG_a 0x2
#define FLAG_r 0x4
#define FLAG_1 0x8
#define FLAG_A 0x10
#define FLAG_d 0x20
#define FLAG_h 0x30
#define FLAG_at 0x40
#define FLAG_R 0x50

#define NO_ACCESS_TMPL ": cannot access '"
#define INV_OPTION_TMPL ": invalid option -- '"
#define CANNOT_OPEN_TMPL ": cannot open directory '"

#define CAL_YEAR_OFFSET 20
#define CAL_HOUR_OFFSET 11
#define CAL_MONTH_DAY_OFFSET 4

#define YEAR_LEN 4
#define HOUR_LEN 5
#define MONTH_DAY_LEN 6


#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <grp.h>
#include <time.h>

typedef struct dirent t_dirent;

typedef struct stat t_stat;

typedef struct s_ls {
    char flags;
    bool (*cmp_p)(void *, void *);
    char *curr_dir_name;
    char *uls_path;
    char *curr_year;
    int link_len;
    int usr_len;
    int grp_len;
    int size_len;
    int hour_year_len;
} t_ls;

// Err Handling
void mx_print_error_no_file(char *filename, t_ls *ls);
void mx_print_error_no_flag(char flag, t_ls *ls);
void mx_invalid_flag(char flag, t_ls *ls);

// Parsing
void mx_parse_args(int argc, char **args, t_list **files, t_ls *ls);
void mx_add_flag(t_ls *ls, char *flag);

// Printing
void mx_output_files(t_list **files, t_ls *ls);
void mx_print_entries_l(DIR *dirp, t_ls *ls);
void mx_print_entries(DIR *dirp, t_ls *ls);

// Utils
char *get_uls_path(char *path);
char *get_curr_year();
bool mx_is_curr_or_prev_dir(char *dir);
char *mx_prepare_path(char *dir, char* file);
bool mx_cmp(void *data1, void *data2);
bool mx_cmp_r(void *data1, void *data2);

// File stats
char *mx_permissions(t_stat *p_stat);
__nlink_t mx_nlink(t_stat *p_stat);
char *mx_get_pw_name(t_stat *p_stat);
char *mx_get_gr_name(t_stat *p_stat);
char *mx_mtime(t_stat *p_stat);
char mx_get_filetype_char(t_stat *p_stat);
int mx_get_block_size(char* directory, t_ls *ls);
int mx_get_file_size(t_stat *p_stat);
char *mx_get_file_month_and_day(t_stat *p_stat);
char *mx_get_hour_or_year(t_stat *p_stat, t_ls *uls);

// Output alignment
void mx_set_field_lens(t_list *entry_names, t_ls *ls, t_stat *p_stat);

extern ssize_t readlink (const char *__restrict __path,
                         char *__restrict __buf, size_t __len)
                       __THROW __nonnull ((1, 2)) __wur;

