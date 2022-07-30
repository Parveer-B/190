#include <stdio.h>
#include <stdlib.h>

void make_int_var_10(int *var);
void insert_sort(int arr[], int length);
void print_array(int arr[], int length);
void merge_sort(int arr[], int length);


int main() {
    int a = 5;
    printf("%d\n", a);
    printf("%d\n", &a);

    make_int_var_10(&a);
    printf("%d\n", a);
    printf("%d\n", &a);

    int arr1[12] = {6, 5, 4, 16, 10, 3, 3, 3, 2, 3, 2, 1};
    insert_sort(arr1, 12);

    return 0;
}


void print_array(int arr[], int length) {
    printf("(%d", arr[0]);
    for (int i = 1; i < length; i++) {
        printf(", %d", arr[i]);
    }
    printf(")\n");

}


void insert_sort(int arr[], int length) {
    // Performs insertion sort on a given array of integers with its length
    
    if (length <= 1) {
        return;
    }
    
    // iterates through array starting from the first element
    for (int *point = &arr[0] + 1; point < &arr[0] + length * 1; point++) {

        int *moving_point = point;  // saves where the element started for moving all the values between where it started
                                    // and where it ended up 1 element
        int value = *point;         // saves the value the pointer was pointing to to assign to the new pointer

        int *finder = point;        // original point can't be changed for next iteration to start at the next element

        while (value < *(finder - 1) && finder > &arr[0]) { // stops if the pointer is on the first element in the array
            // if the element that is being pointed to is smaller than the value that is being moved
            finder -= 1;
        }

        for (moving_point; moving_point > finder; moving_point--) {
            *moving_point = *(moving_point - 1);
        }

        *finder = value;

        printf("Moved %d from position %d to position %d\n", value, point - arr, finder - arr);
        print_array(arr, length);
        printf("\n");

    }
}


void make_int_var_10(int *var) {
    *var = 10;
}

// Questions:
// More space-efficient solution?
// More time-efficient solution?

// Learned:
// Arrays do not pass information about their own size when taken out of the local scope (i.e. used as an argument)
// so their length needs to be passed separately
// Incrementing pointer by 1 moves it by 4 bytes
// sizeof(array) outputs size of array excluding first element
// Logical and operator '&&' expects operands to be boolean expressions
// otherwise if another value is used 0 is false, non-zero is true
// does not evaluate second operand if first is false, saving time
// bitwise operators always evaluate both operands
