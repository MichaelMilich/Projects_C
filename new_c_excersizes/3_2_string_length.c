/*
String Length: Write a program to find the length of a string without using the built-in strlen() function.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int string_length(const char *string) {
    if (string == NULL) {
        return -1;
    }
    int len = 0;
    while (*string != '\0') {
        len++;
        string++;
    }
    return len;
}

int main(int argc, char *argv[]) {
    // Check input arguments
    if (argc != 2) {
        printf("Usage: %s <String>\n", argv[0]);
        return 1;
    }
    int len = string_length(argv[1]);
    printf("length of string %s is %d \n", argv[1], len);
    return 0;
}