/*
Write a program that takes a number as input and uses if-else statements to
check whether the number is even or odd.
*/

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool is_even(int number) { return number % 2 == 0; }

// Test functions
bool test_is_even_with_odd_number() {
    int num = 3;
    return !is_even(num); // Expect false
}

bool test_is_even_with_even_number() {
    int num = 2;
    return is_even(num); // Expect true
}

bool test_is_even_with_zero() {
    int num = 0;
    return is_even(num); // Expect true
}

bool test_is_even_with_large_number() {
    int num = INT_MAX;
    return !is_even(num); // Expect false
}

bool run_tests() {
    if (!test_is_even_with_odd_number()) {
        printf("Test failed: Odd number test\n");
        return false;
    }
    if (!test_is_even_with_even_number()) {
        printf("Test failed: Even number test\n");
        return false;
    }
    if (!test_is_even_with_zero()) {
        printf("Test failed: Zero test\n");
        return false;
    }
    if (!test_is_even_with_large_number()) {
        printf("Test failed: Large number test\n");
        return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
    // Run tests
    if (!run_tests()) {
        return 1;
    }

    // Check input arguments
    if (argc != 2) {
        printf("Usage: %s <integer>\n", argv[0]);
        return 1;
    }

    char *endptr;
    long num = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || num < INT_MIN || num > INT_MAX) {
        printf("Invalid input. Please enter a valid integer.\n");
        return 1;
    }

    if (is_even((int)num)) {
        printf("%ld is an even number.\n", num);
    } else {
        printf("%ld is an odd number.\n", num);
    }

    return 0;
}