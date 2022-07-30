#if !defined(LINKEDLIST_h)
#define LINKEDLIST_h

// node struct for ints, floats, doubles
// typedef to "node"

typedef struct node{
    void *p_data; //a pointer to data (allocated with malloc)
    int type; // 0 if int, 1 if float, 2 if double
    struct node *next;
} node;


#define CREATE_NODE(p_node) node *p_node = (node *)malloc(sizeof(node));

#define ADD_VALUE(p_node, value, c_type, type_int) {            \
    p_node->p_data = (c_type *)malloc(sizeof(c_type));          \
    *(c_type*)(p_node->p_data) = value;                         \
    p_node->type = type_int;                                    \
}                                                               \

#define LINK(p_node, next_node) (p_node)->next = next_node;

#define APPEND(type_int, c_type) {                              \
    node *cur = get_last_node(head);                            \
    CREATE_NODE(new_node);                                      \
    ADD_VALUE(new_node, value, c_type, type_int)                \
    LINK(new_node, NULL)                                        \
    LINK(cur, new_node)                                         \
}                                                               \

#define INSERT_AT_0(type_int, c_type) {                         \
    CREATE_NODE(new_node);                                      \
    LINK(new_node, head->next)                                  \
    new_node->type = head->type;                                \
    new_node->p_data = head->p_data;                            \
                                                                \
    LINK(head, new_node)                                        \
    ADD_VALUE(head, value, c_type, type_int)                    \
}

#define INSERT_AT_IND(type_int, c_type) {                       \
    head = get_node_at_ind(head, ind);                          \
    if (head != NULL) {                                         \
        CREATE_NODE(new_node);                                  \
        ADD_VALUE(new_node, value, c_type, type_int)            \
        LINK(new_node, head->next)                              \
        LINK(head, new_node)                                    \
    }                                                           \
    else {                                                      \
        return;                                                 \
    }                                                           \
}

// Appending
void append_int(node *head, int value);
void append_float(node *head, float value);
void append_double(node *head, double value);

// Insert
void insert_int(node *head, int value, int ind);
void insert_float(node *head, float value, int ind);
void insert_double(node *head, double value, int ind);

// Deleting
int remove_int(node **head, int value);
int remove_float(node **head, float value);
int remove_double(node **head, double value);
int free_list(node *head);

// Helper functions
node *get_last_node(node *head);
node *get_node_at_ind(node *head, int ind);

// Printing
int print_linked_full_list(node *head);

#endif