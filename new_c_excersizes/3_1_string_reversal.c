/*
String Reversal: Write a program that reverses a string in-place (i.e., don't
use another array).
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Returns a malloc'ed reversed string, caller must free it
char* reverse_string(const char* input) {
    int length = strlen(input);
    char* s = malloc(length + 1);
    if (s == NULL) return NULL;

    strcpy(s, input);
    int min_index = 0;
    int max_index = length - 1;
    while (max_index > min_index) {
        char temp_char = s[max_index];
        s[max_index] = s[min_index];
        s[min_index] = temp_char;
        min_index++;
        max_index--;
    }
    return s;
}

// Free a string allocated by reverse_string
void free_string(char* str) {
    printf("calling free on a string \n");
    free(str);
}

int main(int argc, char *argv[]) {
    // Check input arguments
    if (argc != 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *s = reverse_string(argv[1]);
    printf("The output is: %s\n", s);

    free_string(s); // Always free memory you malloc
    return 0;
}