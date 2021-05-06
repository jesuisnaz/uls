#include "libmx.h"

int mx_longest_in_list(t_list *list) {
    int max = 0;
    if (list == NULL) {
        return max;
    }
    else {
        t_list *tmp = list;
        max = mx_strlen(tmp->data);
        while(tmp->next) {
            tmp = tmp->next;
            if (mx_strlen(tmp->data) > max) max = mx_strlen(tmp->data);
        }
        return max;
    }
}
