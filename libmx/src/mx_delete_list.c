#include "libmx.h"

void mx_delete_list(t_list **list) {
    while (*list != NULL) {
        mx_pop_front(list);
    }
}
