#include "libmx.h"

t_list *mx_create_node(void *data) {
    t_list *node = malloc(sizeof(t_list));
    if(!data) {
        return NULL;
    }
    else {
        node->data = data;
        node->next = NULL;
        return node;
    }
}
