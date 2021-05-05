#include "libmx.h"

void mx_pop_front(t_list **head) {
    t_list *del_node = NULL;
    if(head == NULL || *head == NULL) {
        return;
    }
    else if((*head)->next == NULL) {
        free(*head);
        *head = NULL;
    }
    else {
        del_node = (*head)->next;
        free(*head);
        *head = del_node;
    }
}
