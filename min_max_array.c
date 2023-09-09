#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define LEN(arr) (sizeof(arr) / sizeof(arr[0]))

int findMin(int array[], int len);
int findMax(int array[], int len);

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
        index++;
    }
    return max;
}

int main(void)
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int b[] = {0};
    int c[] = {11, 0, 24, -2, 33};
    printf("the minimum of a[] is %d, maximum is %d \n", findMin(a, LEN(a)), findMax(a, LEN(a)));
    printf("the minimum of b[] is %d, maximum is %d \n", findMin(b, LEN(b)), findMax(b, LEN(b)));
    printf("the minimum of c[] is %d, maximum is %d \n", findMin(c, LEN(c)), findMax(c, LEN(c)));
    return 0;
}