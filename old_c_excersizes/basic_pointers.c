#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define LEN(arr) (sizeof(arr) / sizeof(arr[0]))

void int_swap(int **ptr1, int **ptr2);
int sum_arr(int *array, int len);
void *generic_sum(void *array, int len, size_t type_size, void *(*generic_add)(void *, void *));
void *float_add(void *float_sum, void *float_2);

void int_swap(int **ptr1, int **ptr2)
{
    int *temp = *ptr2;
    *ptr2 = *ptr1;
    *ptr1 = temp;
}

int sum_arr(int *array, int len)
{
    int sum = 0;
    for (int i = 0; i < len; ++i)
    {
        sum = sum + *array;
        array++;
    }
    return sum;
}

void *generic_sum(void *array, int len, size_t type_size, void *(*generic_add)(void *, void *))
{
    void *sum = array;
    void *next;
    for (int i = 1; i < len; ++i)
    {
        next = (void *)((char *)array + i * type_size);
        sum = generic_add(sum, next);
    }
    return sum;
}

void *float_add(void *float_sum, void *float_2)
{
    float *float_ptr_1 = (float *)float_sum;
    float *float_ptr_2 = (float *)float_2;
    float sum = (*float_ptr_1 + *float_ptr_2);
    float *sum_ptr = &sum;
    return (void *)sum_ptr;
}

int main(int argc, char *argv[])
{
    int a = 10;
    int b = 20;
    int *ptr1 = &a;
    int *ptr2 = &b;
    printf("ptr1 points at value of %d \n", *ptr1);
    printf("ptr2 points at value of %d \n", *ptr2);

    int_swap(&ptr1, &ptr2);
    printf("ptr1 points at value of %d \n", *ptr1);
    printf("ptr2 points at value of %d \n", *ptr2);

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int sum = sum_arr(arr, LEN(arr));
    printf("the sum of arr = %d \n", sum);

    float arr_f[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
    void *(*float_add_func)(void *, void *) = float_add;
    float f_sum = *((float *)generic_sum(arr_f, LEN(arr_f), sizeof(float), float_add_func));
    printf("the sum of arr_f = %f \n", f_sum);

    return 0;
}