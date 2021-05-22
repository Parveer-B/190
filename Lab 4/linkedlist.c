#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

// Appending

void append_int(node *head, int value) {
    APPEND(0, int);
}

void append_float(node *head, float value) {
    APPEND(1, float);
}

void append_double(node *head, double value) {
    APPEND(2, double);
}

// Insert

void insert_int(node *head, int value, int ind) {
    if (ind == 0) {
        INSERT_AT_0(0, int);}
    else {
        INSERT_AT_IND(0, int);}
}

void insert_float(node *head, float value, int ind) {
    if (ind == 0) {
        INSERT_AT_0(1, float);}
    else {
        INSERT_AT_IND(1, float);}
}

void insert_double(node *head, double value, int ind) {
    if (ind == 0) {
        INSERT_AT_0(2, double);}
    else {
        INSERT_AT_IND(2, double);}
}

// Delete

int remove_int(node **head, int value) {

    // removing the first element in the list
    if (*(int *)((*head)->p_data) == value) {
        // freeing the memory of the first node
        free(*head);
        // changing the pointer to the first node to the second
        *head = (*head)->next;
        return 1;
    }
    else {
        node *p_node = *head;
        while (1) {
            // If next node is NULL
            if (! (int *)(p_node->next)) {
                return -1;
            }
            // If the next node contains the value being removed
            if (*(int *)((p_node->next)->p_data) == value) {
                // Connect the current node to the node after the next one
                LINK(p_node, (p_node->next)->next);
                // Free the memory associated with the pointer to the next node
                free((p_node)->next);
                return 1;
            }
            // Go to the next node
            p_node = p_node->next;
        }
    }
}

int remove_float(node **head, float value) {

    // removing the first element in the list
    if (*(float *)((*head)->p_data) == value) {
        // freeing the memory of the first node
        free(*head);
        // changing the pointer to the first node to the second
        *head = (*head)->next;
        return 1;
    }
    else {
        node *p_node = *head;
        while (1) {
            // If next node is NULL
            if (! (float *)(p_node->next)) {
                return -1;
            }
            // If the next node contains the value being removed
            if (*(float *)((p_node->next)->p_data) == value) {
                LINK(p_node, (p_node->next)->next);
                free((p_node)->next);
                return 1;
            }
            // Go to the next node
            p_node = p_node->next;
        }
    }
}

int remove_double(node **head, double value) {

    // removing the first element in the list
    if (*(double *)((*head)->p_data) == value) {
        // freeing the memory of the first node
        free(*head);
        // changing the pointer to the first node to the second
        *head = (*head)->next;
        return 1;
    }
    else {
        node *p_node = *head;
        while (1) {
            // If next node is NULL
            if (! (int *)(p_node->next)) {
                return -1;
            }
            // If the next node contains the value being removed
            if (*(double *)((p_node->next)->p_data) == value) {
                LINK(p_node, (p_node->next)->next);
                free((p_node)->next);
                return 1;
            }
            // Go to the next node
            p_node = p_node->next;
        }
    }
}

int free_list(node *head) {
    while (head->next) {
        node *temp_node = head;
        free(temp_node);
        head = head->next;
    }
    free(head);
    return 1;
}


// Helper

node * get_last_node(node *head) {
    node *cur = head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    return cur;
}

node *get_node_at_ind(node *head, int ind) {
    while (ind > 1) {
        if (head->next == NULL) {
            return NULL;
        }
        head = head->next;
        ind--;
    }
    return head;
}

// Printing

int print_linked_full_list(node *head) {
    while(head != NULL) {
        if (head->type == 0) {
            printf("%d\n", *(int *)(head->p_data));
        }
        else if (head->type == 1) {
            printf("%f\n", *(float *)(head->p_data));
        }
        else if (head->type == 2) {
            printf("%f\n", *(double *)(head->p_data));
        }
        head = head->next;
    }
    return 0;
}