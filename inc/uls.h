#pragma once

#include "libmx.h"

#include <stdlib.h>

#define __USE_MISC
#define NTIME_LEN 25
#define PATH_MAX 50

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
#include <pwd.h>
#include <grp.h>
#include <time.h>

typedef struct dirent s_dirent;

typedef struct t_ls {
    char flags;
    bool (*cmp_p)(void *, void *);
} s_ls;

