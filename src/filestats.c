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

__nlink_t nlink(s_stat *filestat) {
    return filestat->st_nlink;
}

char *get_pw_name(s_stat *filestat) {
    return getpwuid(filestat->st_uid)->pw_name;
}

char *get_gr_name(s_stat *filestat) {
    return getgrgid(filestat->st_gid)->gr_name;
}

char *mtime(s_stat *filestat) {
    return mx_strndup(ctime(&(filestat->st_mtime)) + 4, NTIME_LEN - 13);
}
