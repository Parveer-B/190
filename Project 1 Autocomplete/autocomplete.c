#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "autocomplete.h"

int my_strcmp(char *str1, char *str2);
int substrcmp(char *substr, char *str);
void *get_term(char *line, char *dest);
double get_weight(char *line, char *copy_string);
int cmpfunc2(struct term *term1, struct term *term2);

void read_in_terms(struct term **terms, int *pnterms, char *filename) {
    char line[200];
    FILE *fp = fopen(filename, "r");

    // stores the number of lines (the first row of the document) as a variable
    char number_of_lines[10];
    fgets(number_of_lines, sizeof(number_of_lines), fp);

    // converts number of lines into an int
    *pnterms = atoi(number_of_lines);
    
    *terms = (struct term *)malloc(sizeof(struct term) * (*pnterms));
    char copy_string[20];
    char new_term[200];
    
    for(int i = 0; i < *pnterms; i++){    
        // store the line as a string in line
        fgets(line, sizeof(line), fp);
    
        // set the weight of the term using the function get_weight
        (*terms + i)->weight = get_weight(line, copy_string);

        // uses get_term and copies the string onto *terms->term
        get_term(line, new_term);
        strcpy(((*terms + i)->term), new_term);
        
    }
    int i;
    qsort(*terms, *pnterms, sizeof(struct term), my_strcmp);

    fclose(fp);
}


double get_weight(char *line, char *copy_string) {
    while (*line == ' ') {
        line++;
    }
    int i = 0;
    
    while ((*line != ' ') && (*line != '\t')) {
        
        copy_string[i] = *line;
        i++;
        line++;
    }
    copy_string[i] = '\0';
    return atof(copy_string);

}


void *get_term(char *line, char *dest) {
    
    while (*line == ' ') {
        line++;
    }
    while ((*line <= '9') && (*line >= '0')) {
        line++;
    }
    while ((*line == '\t') || (*line == ' ')) {
        line++;
    }
    int i = 0;
    while (*line != '\n') {
        dest[i] = *line;
        i++;
        line++;
    dest[i] = '\0';
    }
}


int substrcmp(char *substr, char *str) {
    // Returns 1 if substr is higher lexicographically than the first n letters of str, where n is the length of substr
    // "       -1 "   "    "    lower "
    // Returns 0 if the substr matches the first n letters of str
    for (int i = 0; i < strlen(substr); i++) {
        if (substr[i] > str[i]) {
            return 1;
        }
        else if (substr[i] < str[i]) {
            return -1;
        }
    }

    return 0;
}


int my_strcmp(char *str1, char *str2) {
    // Returns a positive integer if str1 is higher than str2, 0 if they are the same, or a negative integer if lower 
    while (*str1 && *str2) {

        if (*str1 > *str2) {
            return 1;
        }
        else if (*str1 < *str2) {
            return -1;
        }
        str1++;
        str2++;
    }
    return 0;
}


int lowest_match(struct term *terms, int nterms, char *substr) {
    // Given the pointer to the first term, the number of terms and a substring, 
    // returns the index of the first term that matches the string substring

    if (strlen(substr) > 200) {
        return -1;
    }

    // The terms are already in lexicographic ordering
    int low = 0, high = nterms - 1, res = -1, order;

    // binary search
    while (low <= high) {

        int mid = (low + high) / 2;
        order = substrcmp(substr, terms[mid].term);

        if (order < 0) {
            // if the term at mid is higher lexicographically
            high = mid - 1;
            // exclude the term at ind mid because it is high
        }
        else if (order > 0) {
            // if the term at mid is lower lexicographically
            low = mid + 1;
            // exclude the term at ind mid because it is lower
        }
        // if terms[mid].term matches the substring, update result to it
        // move to the lower half to find the first occurance
        else {
            res = mid;
            // make the highest index one below the middle to search for lowest match
            high = mid - 1;
            // cut down the indices and keep moving high down until low and high are the same index
        }
    }
    return res;
}


int highest_match(struct term *terms, int nterms, char *substr) {
    // Given the pointer to the first term, the number of terms and a substring, 
    // returns the index of the last term that matches the string substring

    if (strlen(substr) > 200) {
        return -1;
    }
    
    // The terms are already in lexicographic ordering
    int low = 0, high = nterms - 1, res = -1, order;

    // binary search
    while (low <= high) {

        int mid = (low + high) / 2;
        order = substrcmp(substr, terms[mid].term);

        if (order < 0) {
            // if the term at mid is higher lexicographically
            high = mid - 1;
            // exclude the term at ind mid because it is high
        }
        else if (order > 0) {
            // if the term at mid is lower lexicographically
            low = mid + 1;
            // exclude the term at ind mid because it is lower
        }
        // if terms[mid].term matches the substring, update result to it
        // move to the upper half to find the first occurance
        else {
            res = mid;
            low = mid + 1;
        }
    }
    return res;
}


void autocomplete(struct term **answer, int *n_answer, struct term *terms, int nterms, char *substr){
    int lowestmatch = lowest_match(terms, nterms, substr);
    int highestmatch = highest_match(terms, nterms, substr);
    if((lowestmatch == -1) && (highestmatch == -1)){
        //printf("No cities found");
        *n_answer = 0;
        return;
    }
    *n_answer = highestmatch - lowestmatch + 1;
    *answer = (struct term *)malloc(sizeof(struct term) * (*n_answer));

    int i;
    for(i=0; i<*n_answer; i++){
        strcpy(((*answer + i)->term), terms[lowestmatch+i].term);
        (*answer + i) -> weight = terms[lowestmatch + i].weight;

    }
    qsort(*answer, *n_answer, sizeof(struct term), cmpfunc2);
}


int cmpfunc2(struct term *term1, struct term *term2) {
    return term2->weight - term1->weight;
}

// pointer++ moves it to the next one automatically detecting what the size of the value is that it's pointing to