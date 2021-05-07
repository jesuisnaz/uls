#include "libmx.h"

t_list *mx_sort_list(t_list *lst, bool(*cmp)(void *, void *)) {
    t_list *node;
    void *tmp;
    // stop sorting if no swaps after first iteration
    bool no_swaps = true;

    for(int i = 0; i < mx_list_size(lst); i++) {
        node = lst;
        for (int j = 0; j < mx_list_size(lst)-1; j++) {
            if(cmp(node->data, node->next->data)) {
                tmp = node->data;
                node->data = node->next->data;
                node->next->data = tmp;
                no_swaps = false;
            }
            node = node->next;
        }
        if (no_swaps) return lst;
    }
    return lst;
}
