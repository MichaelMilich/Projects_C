/*
Sum of Array Elements:
Write a program to find the sum of elements in an array using pointers.
*/
#include "string_to_array.h"

int sum(int* array, int size){
    int sum_var = 0;
    int index = 0;
    while (index < size){
        sum_var += *array;
        array++;
        index++;
    }
    return sum_var;
}

int main(int argc, char *argv[]) {
     // Check input arguments
     if (argc != 2) {
        printf("Usage: %s <String>\n", argv[0]);
        printf("<String> is the array represented as string (for example "
               "'[1,5,8,2]')");
        return 1;
    }

    int length = strlen(argv[1]);
    char *s = malloc(length + 1);
    if (s == NULL)
        return 1;
    strcpy(s, argv[1]);
    if (!check_format(s)) {
        printf("[FORMAT_ERROR] the provided sting %s is not in a format of an "
               "array \n",
               s);
        free(s);
        return 1;
    }

    printf("✓ The string '%s' is in the correct format.\n", s);
    DynamicIntArray *arr = convert_string_to_dynamic_int_array(s);
    if (arr == NULL) {
        printf("[PARSING_ERROR]");
        free(s);
        return 1;
    }
    int arr_sum = sum(arr->data,arr->size);
    print_array(arr);
    printf("sum = %d\n",arr_sum);

    
    free(s);
    free_array_memory(arr);
    return 0;
}