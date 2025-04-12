/*
Find Max and Min:
Write a program to find the maximum and minimum elements in a 1D array.
*/
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define LEN(arr) (sizeof(arr) / sizeof(arr[0]))

int find_max(int arr[], int arr_len) {
    if (arr_len == 0)
        return INT_MIN;

    int max = arr[0];
    for (int i = 0; i < arr_len; i++) {
        if (max < arr[i]) {
            max = arr[i];
        }
    }
    return max;
}

int find_min(int arr[], int arr_len) {
    if (arr_len == 0)
        return INT_MAX;

    int min = arr[0];
    for (int i = 0; i < arr_len; i++) {
        if (min > arr[i]) {
            min = arr[i];
        }
    }
    return min;
}

// Test functions
bool test_find_min_empty_arr() {
    int arr[1]; // Dummy array
    int result = find_min(arr, 0);
    return result == INT_MAX; // Check if the function returns INT_MAX
}

bool test_find_min_arr_one_element() {
    int arr[] = {1};
    int expected = 1;
    int result = find_min(arr, LEN(arr));
    return expected == result;
}

bool test_find_min_arr_many_elements() {
    int arr[] = {4, 7, 2, 0, -1};
    int expected = -1;
    int result = find_min(arr, LEN(arr));
    return expected == result;
}

bool test_find_min_arr_many_elements_same() {
    int arr[] = {0, 0, 0, 0, 0};
    int expected = 0;
    int result = find_min(arr, LEN(arr));
    return expected == result;
}

bool test_find_max_empty_arr() {
    int arr[1]; // Dummy array
    int result = find_max(arr, 0);
    return result == INT_MIN; // Check if the function returns INT_MIN
}

bool test_find_max_arr_one_element() {
    int arr[] = {1};
    int expected = 1;
    int result = find_max(arr, LEN(arr));
    return expected == result;
}

bool test_find_max_arr_many_elements() {
    int arr[] = {4, 7, 2, 0, -1};
    int expected = 7;
    int result = find_max(arr, LEN(arr));
    return expected == result;
}

bool test_find_max_arr_many_elements_same() {
    int arr[] = {0, 0, 0, 0, 0};
    int expected = 0;
    int result = find_max(arr, LEN(arr));
    return expected == result;
}

bool run_tests() {
    if (!test_find_min_empty_arr()) {
        printf("Test failed: test_find_min_empty_arr\n");
        return false;
    }
    if (!test_find_min_arr_one_element()) {
        printf("Test failed: test_find_min_arr_one_element\n");
        return false;
    }
    if (!test_find_min_arr_many_elements()) {
        printf("Test failed: test_find_min_arr_many_elements\n");
        return false;
    }
    if (!test_find_min_arr_many_elements_same()) {
        printf("Test failed: test_find_min_arr_many_elements_same\n");
        return false;
    }
    if (!test_find_max_empty_arr()) {
        printf("Test failed: test_find_min_empty_arr\n");
        return false;
    }
    if (!test_find_max_arr_one_element()) {
        printf("Test failed: test_find_min_arr_one_element\n");
        return false;
    }
    if (!test_find_max_arr_many_elements()) {
        printf("Test failed: test_find_min_arr_many_elements\n");
        return false;
    }
    if (!test_find_max_arr_many_elements_same()) {
        printf("Test failed: test_find_min_arr_many_elements_same\n");
        return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
    if (!run_tests()) {
        return 1;
    }
    // Check input arguments
    if (argc != 3) {
        printf("Usage: %s <String1> <String2>\n", argv[0]);
        printf("<String1> is the function: find_min / find_max \n");
        printf("<String2> is the array represented as string (for example "
               "'[1,5,8,2]')");
        return 1;
    }
    if (strcmp(argv[1], "find_min") != 0 && !strcmp(argv[1], "find_max") != 0) {
        printf("input for <String1> can only be find_min or find_max, provided "
               "input was %s",
               argv[1]);
        return 1;
    }
}