#include "libmx.h"

void mx_printlist(t_list *head) {
    if (!head) {
        mx_printstrn("Empty");
    }
    t_list *print_node = head;
    for ( ; print_node; print_node = print_node->next) {
        mx_printstrn(print_node->data);
    }
    mx_printstrn("----------");

}
