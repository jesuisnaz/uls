#include "libmx.h"

int mx_list_size(t_list *list) {
    if (list == NULL) {
        return 0;
    }
    else {
        t_list *tmp = list;
        int i = 1;
        while(tmp->next) {
            tmp = tmp->next;
            i++;
        }
        return i;
    }
}
