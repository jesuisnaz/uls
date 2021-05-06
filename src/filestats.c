#include "uls.h"

char *permissions(struct stat *stat_p) {
    const char chars[] = "rwxrwxrwx";
    mode_t mode = stat_p->st_mode;
    size_t mode_count = 9;
    char *buf = mx_strnew(mode_count);

    for (size_t i = 0; i < mode_count; i++) {
        buf[i] = (mode & (1 << (8 - i))) ? chars[i] : '-';
    }
    return buf;
}

__nlink_t nlink(s_stat *p_stat) {
    return p_stat->st_nlink;
}

char *get_pw_name(s_stat *p_stat) {
    return getpwuid(p_stat->st_uid)->pw_name;
}

char *get_gr_name(s_stat *p_stat) {
    return getgrgid(p_stat->st_gid)->gr_name;
}

char *mtime(s_stat *p_stat) {
    return mx_strndup(ctime(&(p_stat->st_mtime)) + 4, NTIME_LEN - 13);
}

char get_filetype_char(s_stat *p_stat) {
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
