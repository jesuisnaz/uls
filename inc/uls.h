#pragma once

#include "libmx.h"

#include <stdlib.h>

#define __USE_MISC
#define NTIME_LEN 25
#define PATH_MAX 50

#define FLAG_l 0x1
#define FLAG_a 0x2
#define FLAG_r 0x3
#define FLAG_1 0x4
#define FLAG_A 0x5
#define FLAG_d 0x6
#define FLAG_h 0x7
#define FLAG_at 0x8

#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

typedef struct t_ls {
    char flags;
} s_ls;

