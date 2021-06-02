#include "libmx.h"

void mx_delete_list(t_list **list) {
    while (*list != NULL) {
        if ((*list)->data) {
            free((*list)->data);
            (*list)->data = NULL;
        }
        mx_pop_front(list);
    }
}
