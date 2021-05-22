#include <stdio.h>
#include <stdlib.h>

// Structs: node for ints, num_node for ints, floats, doubles
struct node{
    int data;
    struct node *next;
};

struct num_node{
    void *p_data; //a pointer to data (allocated with malloc)
    int type; // 0 if int, 1 if float, 2 if double
    struct num_node *next;
};

// Appending to linked lists
void append(struct node *head /* first element in list*/, int value);
void append_int(struct num_node *head, int value);
void append_float(struct num_node *head, float value);
void append_double(struct num_node *head, double value);

// Helper functions
struct num_node * get_last_node(struct num_node *node);

// Printing linked lists
int print_linked_list(struct node *head);
void print_linked_list_rec(struct node *head);
int print_linked_full_list(struct num_node *head);


int main() {
    struct node *node0 = (struct node *)malloc(sizeof(struct node));
    node0->data = 3;
    node0->next = NULL;
    append(node0, 5);
    append(node0, 3);
    append(node0, 1);
    append(node0, 6);
    print_linked_list(node0);
    print_linked_list_rec(node0);

    printf("\n\n");
    struct num_node *any_num = (struct num_node *)malloc(sizeof(struct num_node));

    any_num->p_data = (double *)malloc(sizeof(double));
    *(double *)(any_num->p_data) = 12;
    any_num->type = 2;
    any_num->next = NULL;

    append_float(any_num, 10);
    append_float(any_num, 8);
    append_float(any_num, 6);
    append_int(any_num, 1);
    append_double(any_num, 34);
    append_double(any_num, 34);
    append_double(any_num, 34);
    append_int(any_num, 7);
    append_int(any_num, 7);
    append_int(any_num, 7);
    print_linked_full_list(any_num);

    return 0;
}


// Appending to linked lists

void append(struct node *head /* first element in list*/, int value) {
    struct node *cur = head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    struct node *node = (struct node *)malloc(sizeof(struct node));
    node->data = value;
    node->next = NULL;
    cur->next = node;
}

void append_int(struct num_node *head, int value) {
    struct num_node *cur = get_last_node(head);

    struct num_node *node = (struct num_node *)malloc(sizeof(struct num_node));

    node->p_data = (int *)malloc(sizeof(int));
    *(int *)(node->p_data) = value;
    node->type = 0;
    node->next = NULL;
    cur->next = node;
}

void append_float(struct num_node *head, float value) {
    struct num_node *cur = get_last_node(head);

    struct num_node *node = (struct num_node *)malloc(sizeof(struct num_node));

    node->p_data = (int *)malloc(sizeof(float));
    *(float *)(node->p_data) = value;
    node->type = 1;
    node->next = NULL;
    cur->next = node;
}

void append_double(struct num_node *head, double value) {
    struct num_node *cur = get_last_node(head);

    struct num_node *node = (struct num_node *)malloc(sizeof(struct num_node));

    node->p_data = (int *)malloc(sizeof(double));
    *(double *)(node->p_data) = value;
    node->type = 2;
    node->next = NULL;
    cur->next = node;
}


// Helper

struct num_node * get_last_node(struct num_node *node) {
    struct num_node *cur = node;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    return cur;
}


// Printing linked lists

int print_linked_list(struct node *head) {
    while(head != NULL) {
        printf("%d\n", head->data);
        head = head->next;
    }
    return 0;
}

void print_linked_list_rec(struct node *head) {
    if (head == NULL) {
        return;
    }
    printf("%d\n", head->data);
    print_linked_list_rec(head->next);
    // better/more "recursive" way to write this function?
}

int print_linked_full_list(struct num_node *head) {
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

// How do I make an "append_any" function that takes either an int, float, or double?
// Old code for appending (extra useless variable):
//  double *value_p = (double *)malloc(sizeof(double));
//    *value_p = value;
//    node->p_data = value_p;*/
//    node->type = 2;
//    node->next = NULL;
//    cur->next = node;