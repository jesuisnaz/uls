#include "libmx.h"

void mx_del_node_data(t_list *node) {
    if (node->data) {
        free(node->data);
        node->data = NULL;
    }
}
