#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define LEN(arr) (sizeof(arr) / sizeof(arr[0]))

int findMin(int array[], int len);
int findMax(int array[], int len);
int find_max_n_dimention(int array_n[], int array_sizes[], int n);
int find_min_n_dimention(int array_n[], int array_sizes[], int n);
int find_n_dimen_size(int array_sizes[], int n);
void *find_generic_min(void *array, int len, size_t type_size, int (*is_larger_func)(void *, void *));
int first_larger_second_char(void *first, void *second);
void *find_generic_min_n_dinen(void *array, int array_sizes[], int n, size_t type_size, int (*is_larger_func)(void *, void *));

/**
 * @brief finds the minimum of a 1d int array.
 *
 * @param array the 1d int array
 * @return int the minimum value in the array
 */
int findMin(int array[], int len)
{
    int min = array[0];
    int index = 0;
    while (index < len)
    {
        /* code */
        if (min > array[index])
        {
            min = array[index];
        }
        index++;
    }
    return min;
}

/**
 * @brief finds the maximum of a 1d int array.
 *
 * @param array the 1d int array
 * @return int the maximum value in the array
 */
int findMax(int array[], int len)
{
    int max = array[0];
    int index = 0;
    while (index < len)
    {
        /* code */
        if (max < array[index])
        {
            max = array[index];
        }
        // second change
        index++;
    }
    return max;
}

/**
 * @brief finds the maximum in an n dimentional int array.
 * Uses the fact that all the values are stored one next to another within memory to accses them as if it is 1D array.
 *
 * @param array_n the n-dimentional array.
 * @param array_sizes the size of each dimention - should be of len(array_sizes) = n-1
 * @param n the number of dimentions
 * @return int max value of the array
 */
int find_max_n_dimention(int array_n[], int array_sizes[], int n)
{
    int size = find_n_dimen_size(array_sizes, n);
    int max = findMax(array_n, size);
    return max;
}

int find_n_dimen_size(int array_sizes[], int n)
{
    int size = 1;
    for (int i = 0; i < n; ++i)
    {
        size *= array_sizes[i];
    }
    return size;
}
int find_min_n_dimention(int array_n[], int array_sizes[], int n)
{
    int size = find_n_dimen_size(array_sizes, n);
    int min = findMin(array_n, size);
    return min;
}

void *find_generic_min(void *array, int len, size_t type_size, int (*is_larger_func)(void *, void *))
{
    void *min = array;
    char *next_elem = (char *)array;
    int result = 0; // result can be TRUE - the first element is larger or FALSE otherwise.
    for (int i = 0; i < len; ++i)
    {
        next_elem = (char *)array + i * type_size;
        result = (*is_larger_func)(min, (void *)next_elem);
        if (result == TRUE)
        {
            min = (void *)next_elem;
        }
    }
    return min;
}

int first_larger_second_char(void *first, void *second)
{
    char char_first = *(char *)first;
    char char_second = *(char *)second;
    if (toupper(char_first) > toupper(char_second))
    {
        return TRUE;
    }
    return FALSE;
}

void *find_generic_min_n_dinen(void *array, int array_sizes[], int n, size_t type_size, int (*is_larger_func)(void *, void *))
{
    int size = find_n_dimen_size(array_sizes, n);
    printf("the %d dimention array size in 1D is %d \n", n, size);
    void *min = find_generic_min(array, size, type_size, is_larger_func);
    return min;
}

int main(void)
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int b[] = {0};
    int c[] = {11, 0, 24, -2, 33};
    printf("the minimum of a[] is %d, maximum is %d \n", findMin(a, LEN(a)), findMax(a, LEN(a)));
    printf("the minimum of b[] is %d, maximum is %d \n", findMin(b, LEN(b)), findMax(b, LEN(b)));
    printf("the minimum of c[] is %d, maximum is %d \n", findMin(c, LEN(c)), findMax(c, LEN(c)));
    int d[][2] = {{10, -2}, {-4, 100}, {1, 2}, {33, -33}};
    int e[][2][3] = {
        {{1, 2, 3},
         {5, -10, 20}},
        {{9, 4, 7},
         {5, -14, 99}},
    };
    int d_sizes[] = {LEN(d), LEN(d[0])};
    int e_sizes[] = {LEN(e), LEN(e[0]), LEN(e[0][0])};

    printf("the minimum of d[] is %d, maximum is %d \n", find_min_n_dimention(d, d_sizes, 2), find_max_n_dimention(d, d_sizes, 2));
    printf("the minimum of e[] is %d, maximum is %d \n", find_min_n_dimention(e, e_sizes, 3), find_max_n_dimention(e, e_sizes, 3));
    printf("size of d = %d, size of d[0] is %d \n", LEN(d), LEN(d[0]));
    printf("size of e = %d, size of e[0] is %d, size of e[0][0] %d \n", LEN(e), LEN(e[0]), LEN(e[0][0]));

    // char chars2[][5] = {{'H', 'L', "l", 'o', 'Z'}, {'a', 'Z', 'z', 'A', '['}};
    // int char_sizes[] = {LEN(chars2), LEN(chars2[0])};
    // int dimen = LEN(char_sizes);
    // int (*char_compare_func)(void *, void *) = first_larger_second_char;
    // void *void_min = find_generic_min_n_dinen(chars2, char_sizes, dimen, sizeof(char), char_compare_func);
    // char *char_min = (char *)void_min;
    // printf("The minimum of chars2[][] is %c \n", *char_min);

    int (*char_compare_func)(void *, void *) = first_larger_second_char;
    char strings[][5][3] = {{{'h', 'e', 'l'}, {'l', 'o', '@'}, {'#', '!', 'y'}, {'n', 'a', 'm'}, {'e', '$', 'i'}}, {{'s', '%', 'M'}, {'i', 's', 'h'}, {'a', '^', 'h'}, {'Z', '6', '7'}, {'3', '3', '3'}}};
    int strings_sizes[] = {LEN(strings), LEN(strings[0]), LEN(strings[0][0])};
    int dimen = LEN(strings_sizes);
    printf("size of strings = %d, size of strings[0] is %d , size of strings[0][0] is %d \n", LEN(strings), LEN(strings[0]), LEN(strings[0][0]));
    void *void_min = find_generic_min_n_dinen(strings, strings_sizes, dimen, sizeof(char), char_compare_func);
    char *char_min = (char *)void_min;
    printf("The minimum of strings[][][] is %c", *char_min);
    return 0;
}