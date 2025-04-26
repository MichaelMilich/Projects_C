#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void swap(int *ptr_1, int *ptr_2) {
    int temp = *ptr_1;
    *ptr_1 = *ptr_2;
    *ptr_2 = temp;
}

bool convert_to_int(const char *token, int *result) {
    char *endptr;
    *result = strtol(token, &endptr, 10);
    while (isspace((unsigned char)*endptr))
        endptr++;
    return *endptr == '\0';
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <Int> <Int>\n", argv[0]);
        return 1;
    }

    int a, b;
    bool a_res = convert_to_int(argv[1], &a);
    bool b_res = convert_to_int(argv[2], &b);
    if (!a_res || !b_res) {
        printf("Error: Invalid input, expected two integers.\n");
        return 1;
    }

    printf("Inputs are: a = %d, b = %d\n", a, b);
    swap(&a, &b);
    printf("After swap: a = %d, b = %d\n", a, b);

    return 0;
}