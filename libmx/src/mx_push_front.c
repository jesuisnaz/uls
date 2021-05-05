#include "libmx.h"

void mx_push_front(t_list **list, void *data) {
    t_list *node = mx_create_node(data);
    if(node) {
        if(*list == NULL) {
            *list = node;
        }
        else {
            node->next = *list;
            *list = node;
        }
    }
}
