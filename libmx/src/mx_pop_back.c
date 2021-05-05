#include "libmx.h"

void mx_pop_back(t_list **head) {
    t_list *del_node = NULL;
    if(head == NULL || *head == NULL) {
        return;
    }
    else if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
    }
    else {
        del_node = *head;
        while(del_node && del_node->next->next) {
            del_node = del_node->next;
        }
        free(del_node->next);
        del_node->next = NULL;

    }
}
