#include "uls.h"

int get_block_size(char* directory, t_ls *ls) {
    int size = 0;

    DIR *d = NULL;
    struct dirent *dir = NULL;
    struct stat fileStat;
    d = opendir(directory);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (mx_strcmp(dir->d_name, ".") == 0 ||
                mx_strcmp(dir->d_name, "..") == 0) {
                if ((ls->flags & FLAG_A) != 0 || (ls->flags & FLAG_a) == 0) {
                    continue;
                }
            }
            if (dir->d_name[0] == '.' &&
                       ((ls->flags & (FLAG_A | FLAG_a)) == 0)) {
                continue;
            }
            char info_path[PATH_MAX + 1];
            mx_strcpy(info_path, directory);
            if (directory[mx_strlen(directory) - 1] != '/')
                mx_strcat(info_path, "/");
            mx_strcat(info_path, dir->d_name);
            stat(info_path, &fileStat);
            size += fileStat.st_blocks;
        }
    }
    closedir(d);
    return size / 2;
}

int get_file_size(t_stat *p_stat) {
    return p_stat->st_size;
}

char *permissions(t_stat *stat_p) {
    const char chars[] = "rwxrwxrwx";
    mode_t mode = stat_p->st_mode;
    size_t mode_count = 9;
    char *buf = mx_strnew(mode_count);

    for (size_t i = 0; i < mode_count; i++) {
        buf[i] = (mode & (1 << (8 - i))) ? chars[i] : '-';
    }
    return buf;
}

__nlink_t nlink(t_stat *p_stat) {
    return p_stat->st_nlink;
}

char *get_pw_name(t_stat *p_stat) {
    return getpwuid(p_stat->st_uid)->pw_name;
}

char *get_gr_name(t_stat *p_stat) {
    return getgrgid(p_stat->st_gid)->gr_name;
}

char *mtime(t_stat *p_stat) {
    return mx_strndup(ctime(&(p_stat->st_mtime)) + 4, NTIME_LEN - 13);
}

char get_filetype_char(t_stat *p_stat) {
    switch (p_stat->st_mode & S_IFMT) {
        case S_IFLNK:
            return 'l';
        case S_IFSOCK:
            return 's';
        case S_IFREG:
            return '-';
        case S_IFDIR:
            return 'd';
        case S_IFBLK:
            return 'b';
        case S_IFCHR:
            return 'c';
        case S_IFIFO:
            return 'p';
        default:
            return '-';
    }
}

char *get_file_year(t_stat *p_stat) {
    return mx_strndup(ctime(&(p_stat->st_mtime)) + CAL_YEAR_OFFSET, 4);
}

char *get_year_or_date(t_stat *p_stat, t_ls *uls) {
    return mx_strcmp(uls->curr_year, get_file_year(p_stat)) > 0 ? get_file_year(p_stat) : mx_strdup(mtime(p_stat));
}
