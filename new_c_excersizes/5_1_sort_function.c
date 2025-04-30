/*
Sort Function:
Write a function that sorts an array. Use a function pointer to call it.
*/

#include "string_to_array.h"
#include <time.h> // for timestamping

typedef void (*SortFunction)(DynamicIntArray *arr);

SortFunction get_sorting_function(char* input_string);

SortFunction get_sorting_function(char* input_string){
    if (strcmp(input_string, "quick_sort") == 0) {
        return quick_sort;
    } else if (strcmp(input_string, "merge_sort") == 0) {
        return merge_sort;
    } else if (strcmp(input_string, "naive_sort") == 0) {
        return naive_sort;
    } else {
        return NULL; // or a default sort function
    }
}


int main(int argc, char *argv[]) {
    // Check input arguments
    if (argc != 3) {
       printf("Usage: %s <String1>, <String2>\n", argv[0]);
       printf("<String1> is the sorting function: ( quick_sort / merge_sort / naive_sort ) \n");
       printf("<String2> is the array represented as string (for example "
              "'[1,5,8,2]') \n");
       return 1;
    }    

    int length = strlen(argv[2]);
    char *s = malloc(length + 1);
    if (s == NULL)
       return 1;
    strcpy(s, argv[2]);
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
       printf("[PARSING_ERROR] couldn't create dynamic int array");
       free(s);
       return 1;
    }

    SortFunction sorter = get_sorting_function(argv[1]);
    if (sorter == NULL) {
        printf("[SORT_PARSER] Unknown sorting function: %s\n", argv[1]);
        return 1;
    }

    clock_t start_time = clock();
    sorter(arr);
    clock_t end_time = clock();

    print_array(arr);
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Sorting took %.6f seconds.\n", time_taken);

    free(s);
    free_array_memory(arr);
    return 0;
}