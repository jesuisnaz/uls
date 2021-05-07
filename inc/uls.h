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
    int link_len;
    int usr_len;
    int grp_len;
    int size_len;
    int day_len;
} t_ls;

// File stats
char *permissions(t_stat *p_stat);
__nlink_t nlink(t_stat *p_stat);
char *get_pw_name(t_stat *p_stat);
char *get_gr_name(t_stat *p_stat);
char *mtime(t_stat *p_stat);
char get_filetype_char(t_stat *p_stat);
int get_block_size(char* directory, t_ls *ls);
int get_file_size(t_stat *p_stat);

// Output alignment
int get_link_len(t_list *files, t_stat *p_stat);
int get_usr_len(t_list *files, t_stat *p_stat);
int get_grp_len(t_list *files, t_stat *p_stat);
int get_size_len(t_list *files, t_stat *p_stat);
int get_day_len(t_list *files, t_stat *p_stat);
