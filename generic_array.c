#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define LEN(arr) (sizeof(arr) / sizeof(arr[0]))

void print_generic_array(void *array, int length, size_t type_size, void (*element_print)(int, void *));
void print_int(int index, void *element);
void print_char(int index, void *element);
void print_float(int index, void *element);

/**
 * @brief prints an array of a given length from the types of int/char or float.
 * To do so, the function must know about the array length and type_size in bytes.
 * To print the varaibles the function must recieve the correct printing function.
 *
 * @param array pointer to the first element in the array. It has to be void so we can pass any type.
 * @param length The length of the array.
 * @param type_size the amout of bytes a single element of the array is takings.
 * @param element_print the function to print the element.
 */
void print_generic_array(void *array, int length, size_t type_size, void (*element_print)(int, void *))
{
    for (int i = 0; i < length; ++i)
    {
        // NOTE: (char *) is a pointer to a single byte and hence it is the best usage for generic pointers aritmentics.
        // we can't use (void *) because it doesn't point to anything and does not have any size ( i think).
        (*element_print)(i, (char *)array + i * type_size);
    }
}

void print_int(int index, void *element)
{
    int *int_ptr = (int *)element;
    printf("array[%d] = %d \n", index, *int_ptr);
}

void print_char(int index, void *element)
{
    char *char_ptr = (char *)element;
    printf("array[%d] = %c \n", index, *char_ptr);
}

void print_float(int index, void *element)
{
    float *float_ptr = (float *)element;
    printf("array[%d] = %f \n", index, *float_ptr);
}

int main(int argc, char *argv[])
{
    int int_arr[] = {1, 2, 3, 4, 5, 6, 7, 99};
    char string[] = "Hello, World!";
    float float_arr[] = {1.1, 2.2, 33.3, 4.4, 5.001};
    void *int_print_func = print_int;
    void *char_print_func = print_char;
    void *float_print_func = print_float;

    printf("printing int_arr : \n");
    print_generic_array(int_arr, LEN(int_arr), sizeof(int), int_print_func);
    printf("####### DONE ##### \n");

    printf("printing string : \n");
    print_generic_array(string, LEN(string), sizeof(char), char_print_func);
    printf("####### DONE ##### \n");

    printf("printing string : \n");
    print_generic_array(float_arr, LEN(float_arr), sizeof(float), float_print_func);
    printf("####### DONE ##### \n");

    return 0;
}