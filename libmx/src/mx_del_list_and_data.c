#include "libmx.h"

void mx_del_list_and_data(t_list **list) {
    t_list *node = *list;
    t_list *prev = NULL;
    while (node) {
        mx_del_node_data(node);
        if (node == *list) {
            mx_pop_front(list);
            node = *list;
            continue;
        } else {
            prev->next = node->next;
            free(node);
            node = prev;
            continue;
        }
        prev = node;
        node = node->next;
    }
}
