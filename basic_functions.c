#include <stdio.h>
#include <stdlib.h>
#include "generic_array.c"

#define TRUE 1
#define FALSE 0
#define LEN(arr) (sizeof(arr) / sizeof(arr[0]))

int min_position(int *array, int len);
void selection_sort(int *array, int len);

int min_position(int *array, int len)
{
    int min_pos = 0;
    for (int i = 0; i < len; ++i)
    {
        if (array[min_pos] > array[i])
        {
            min_pos = i;
        }
    }
    return min_pos;
}

void selection_sort(int *array, int len)
{
    int current_min_pos;
    int temp;
    for (int i = 0; i < len; ++i)
    {
        current_min_pos = i + min_position(array + i, len - i);
        if (current_min_pos != i)
        {
            temp = array[i];
            array[i] = array[current_min_pos];
            array[current_min_pos] = temp;
        }
    }
}

void selection_sort_call(int *array, int len, void (*sort)(int *, int))
{
    sort(array, len);
}

int main(int argc, char *argv[])
{
    int arr[] = {9, 20, 8, 100, 19, 17, 6};
    int len = LEN(arr);
    void *int_print_func = print_int;
    void *sort_array = selection_sort;
    printf("printing int_arr : \n");
    print_generic_array(arr, len, sizeof(int), int_print_func);
    printf("####### DONE ##### \n");
    selection_sort_call(arr, len, sort_array);
    printf("printing int_arr : \n");
    print_generic_array(arr, len, sizeof(int), int_print_func);
    printf("####### DONE ##### \n");

    return 0;
}