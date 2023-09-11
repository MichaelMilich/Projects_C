#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define LEN(arr) (sizeof(arr) / sizeof(arr[0]))

int findMin(int array[], int len);
int findMax(int array[], int len);
int find_max_n_dimention(int array_n[], int array_sizes[], int n);
int find_min_n_dimention(int array_n[], int array_sizes[], int n);
int find_n_dimen_size(int array_sizes[], int n);

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

int main(void)
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int b[] = {0};
    int c[] = {11, 0, 24, -2, 33};
    printf("the minimum of a[] is %d, maximum is %d \n", findMin(a, LEN(a)), findMax(a, LEN(a)));
    printf("the minimum of b[] is %d, maximum is %d \n", findMin(b, LEN(b)), findMax(b, LEN(b)));
    printf("the minimum of c[] is %d, maximum is %d \n", findMin(c, LEN(c)), findMax(c, LEN(c)));
    int d[][2] = {{10, -2}, {-4, 100}};
    int e[][2][3] = {
        {{1, 2, 3},
         {5, -10, 20}},
        {{9, 4, 7},
         {5, -14, 99}},
    };
    int d_sizes[] = {LEN(d), LEN(d[0])};
    int e_sizes[] = {LEN(e), LEN(e[0]), LEN(e[0][0])};

    printf("the minimum of d[] is %d, maximum is %d \n", find_min_n_dimention(b, d_sizes, 2), find_max_n_dimention(b, d_sizes, 2));
    printf("the minimum of e[] is %d, maximum is %d \n", find_min_n_dimention(c, e_sizes, 3), find_max_n_dimention(c, e_sizes, 3));
    return 0;
}