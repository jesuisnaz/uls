#pragma once

#include "libmx.h"

#include <stdlib.h>

#define __USE_MISC
#define NTIME_LEN 25
#define PATH_MAX 50
#define FLAG_COUNT 10

#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

typedef struct t_ls {
    char **dirnames;
    int *flags;
} s_ls;

