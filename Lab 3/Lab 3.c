#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


struct node{
    int data;
    struct node *next;
};

char *my_strcat(char *dest, char *src);
int my_strcmp_rec(char *str1, char *str2);
int my_atoi(char *str);
int is_cycle_in_linked_list(struct node *node);

void append(struct node *head /* first element in list*/, int value);


int main() {
    printf("Hello, World!\n");

    char str1[] = {'H', 'i', '\0'};
    printf("%s\n", str1);

    char str2[] = {'B', 'y', 'e', '\0'};
    printf("%s\n", str2);

    char str3[] = "Hello\0";
    printf("%s\n", str3);

    char str4[] = "e\0";
    printf("%s\n", str4);

    my_strcat(str1, str2);
    puts(str1);
    puts(my_strcat(str1, str2));

    char str5[] = "-280\0";
    printf("%d\n", my_atoi(str5) + 4);

    printf("%d\n", my_strcmp_rec(str3, str4));

    struct node *node0 = (struct node *)malloc(sizeof(struct node));
    node0->data = 3;
    node0->next = NULL;
    append(node0, 2);
    append(node0, 1);
    append(node0, 2);

    printf("%d\n", is_cycle_in_linked_list(node0));

    struct node *node1 = (struct node *)malloc(sizeof(struct node));
    node1->data = 3;
    node1->next = NULL;
    append(node1, 2);
    append(node1, 1);
    append(node1, 1);

    printf("%d\n", is_cycle_in_linked_list(node1));
    return 0;

}


char *my_strcat(char *dest, char *src) {
    char *dest_p = dest;
    while (*dest != '\0') {
        dest++;
    }
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return dest_p;
}


int my_strcmp_rec(char *str1, char *str2) {

    if (! *str1 && ! *str2 ) {
        return 0;
    }

    if (*str1 != *str2) {
        return *str1 - *str2;
    }

    return my_strcmp_rec(str1++, str2++);
}


int my_atoi(char *str) {
    int num = 0;
    int sign = 1;

    // check if number in string is signed
    if (*str == '+' || *str == '-') {
        if (*str == '-') {
            sign = -1;
        }
        str++;
    }
    // iterates through string characters and adds each digit to the end of the number
    while (*str != '\0') {
        if (isdigit(*str)) {
            // moves the current number's decimal place one to the right to make room for next digit
            num *= 10;
            num += *(str)-'0';
        }
        str++;
    }
    return num * sign;
}

int is_cycle_in_linked_list(struct node *node) {
    // Returns 1 if there is a cycle in the linked list, otherwise returns 0
    if (! node->next) {
        return 0;
    }

    struct node *slow = node;
    struct node *fast = node->next;

    while (slow != fast) {
        if (! slow->next || ! fast->next || ! fast->next->next) {
            return 0;
        }
        slow = slow->next;
        fast = fast->next->next;
    }
    return 1;
}



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

/*  Learned:

    When making a string, the number inside of the brackets needs to be length of string +1 to allow the memory to put in a '\0' element to stop the string.
    Otherwise, the string is not stopped and the next string you make will be added to the previous one.
    Including the \0 as the last element is optional as long as the string has the right number in the brackets.

    Leaving the number inside of the brackets blank:
    If the number in the brackets is left blank, the \0 will not be automatically added and strange characters will appear at the end of strings and strings will be appended to each other.
    If the number in the brackets is left blank but \0 is added as the last element, strings will work properly

    puts(char *): prints a string given a pointer to a character
    stops printing when pointer is pointing to \0


    Questions:

    When do we use malloc?
    Do we need to malloc a chunk of memory for strings when concatenating?
    What is the correct solution to the tortoise-hare algorithm?

*/