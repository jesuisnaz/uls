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
#define FLAG_at 040

#define NO_ACCESS_TMPL ": cannot access"
#define INV_OPTION_TMPL ": invalid option -- '"
#define CAL_YEAR_OFFSET 20

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
} t_ls;

// Err Handling
void print_error_no_file(char *filename, t_ls *ls);
void print_error_no_flag(char flag, t_ls *ls);
void invalid_flag(char flag, t_ls *ls);

// Parsing
void parse_args(int argc, char **args, t_list **files, t_ls *ls);
void add_flag(t_ls *ls, char *flag);

// Printing
void output_files(t_list **files, t_ls *ls);
void print_entries_l(DIR *dirp, t_ls *ls);
void print_entries(DIR *dirp, t_ls *ls);

// Utils
char *get_uls_path(char *path);
char *get_curr_year();
bool is_curr_or_prev_dir(char *dir);
char *prepare_path(char *dir, char* file);
bool cmp(void *data1, void *data2);
bool cmp_r(void *data1, void *data2);

// File stats
char *permissions(t_stat *p_stat);
__nlink_t nlink(t_stat *p_stat);
char *get_pw_name(t_stat *p_stat);
char *get_gr_name(t_stat *p_stat);
char *mtime(t_stat *p_stat);
char get_filetype_char(t_stat *p_stat);
int get_block_size(char* directory, t_ls *ls);
int get_file_size(t_stat *p_stat);
char *get_file_year(t_stat *p_stat);
char *get_year_or_date(t_stat *p_stat, t_ls *uls);

// Output alignment
void set_field_lens(t_list *entry_names, t_ls *ls, t_stat *p_stat);
