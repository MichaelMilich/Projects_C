/*
Write a program that prints the multiplication table of two given numbers
using a for loop. Try to implement the same using a while loop and a goto
statement.
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void print_multiplication_for_loop(int number_1, int number_2) {
    printf("printing the multiplication of %d and %d in a for loop \n",
           number_1, number_2);
    for (int i = 0; i <= number_1; i++) {
        for (int j = 0; j <= number_2; j++) {
            printf("%d ", i * j);
        }
        printf("\n");
    }
}

void print_multiplication_while_loop(int number_1, int number_2) {
    printf("printing the multiplication of %d and %d in a while loop \n",
           number_1, number_2);
    int i = 0;
    while (i <= number_1) {
        int j =0;
        while (j <= number_2) {
            printf("%d ", i * j);
            j++;
        }
        printf("\n");
        i++;
    }
}

void print_multiplication_goto_loop(int number_1, int number_2) {
    printf("printing the multiplication of %d and %d in a goto loop \n",
           number_1, number_2);
    int i = 0, j = 0;
    if (number_1 > 20 || number_2 > 20) {
        printf("Warning: Large inputs may cause excessive output.\n");
    }

i_loop:
    if (i > number_1) {
        goto exit_statement;
    }
    j = 0;

j_loop:
    if (j > number_2) {
        printf("\n");
        i++;
        goto i_loop;
    }
    printf("%d ", i * j);
    j++;
    goto j_loop;

exit_statement:
    printf("done with goto \n");
    return;
}

int main(int argc, char *argv[]) {

    // Check input arguments
    if (argc != 3) {
        printf("Usage: %s <integer1> <integer2>\n", argv[0]);
        return 1;
    }

    char *endptr1;
    long num1 = strtol(argv[1], &endptr1, 10);
    char *endptr2;
    long num2 = strtol(argv[2], &endptr2, 10);

    if (*endptr1 != '\0' || num1 < INT_MIN || num1 > INT_MAX) {
        printf("Invalid input. Please enter a valid integer.\n");
        return 1;
    }
    if (*endptr2 != '\0' || num2 < INT_MIN || num2 > INT_MAX) {
        printf("Invalid input. Please enter a valid integer.\n");
        return 1;
    }

    print_multiplication_for_loop((int)num1, (int)num2);
    print_multiplication_while_loop((int)num1, (int)num2);
    print_multiplication_goto_loop((int)num1, (int)num2);

    return 0;
}