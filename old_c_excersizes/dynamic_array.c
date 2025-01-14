#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INITIAL_SIZE 10

typedef struct DynamicArray DynamicArray;
int add_element(DynamicArray *d_arr, int element);
void delete_DynamicArray(DynamicArray *d_arr);

struct DynamicArray
{
    int *array;
    int length;
    int capacity;
};

/**
 * @brief creates a new dynamic array and returns pointer to the memory of the dynamic array.
 * This function will further be exposed in dynamic_array.h for usage in other c files.
 *
 * @return DynamicArray* pointer to newly created dynamic array.
 */
DynamicArray *new_DynamicArray()
{
    DynamicArray *d_arr = (DynamicArray *)malloc(sizeof(DynamicArray));
    if (!d_arr)
        return NULL; // Check if d_arr allocation failed
    d_arr->length = 0;
    d_arr->capacity = INITIAL_SIZE;
    d_arr->array = (int *)malloc(INITIAL_SIZE * sizeof(int));
    if (!d_arr->array)
    {
        free(d_arr);
        return NULL; // Handle memory allocation failure for the internal array.
    }

    return d_arr;
}

/**
 * @brief creates a new dynamic array and returns pointer to the memory of the dynamic array.
 * This function will further be exposed in dynamic_array.h for usage in other c files.
 *
 * @return DynamicArray* pointer to newly created dynamic array.
 */
DynamicArray *new_DynamicArray_custom_capacity(int cap)
{
    DynamicArray *d_arr = (DynamicArray *)malloc(sizeof(DynamicArray));
    if (!d_arr)
        return NULL; // Check if d_arr allocation failed
    d_arr->length = 0;
    d_arr->capacity = cap;
    d_arr->array = (int *)malloc(d_arr->capacity * sizeof(int));
    if (!d_arr->array)
    {
        free(d_arr);
        return NULL; // Handle memory allocation failure for the internal array.
    }

    return d_arr;
}

/**
 * @brief adds and element to the dynamic array.
 * If the array is already full, we will reallocate memory for the array to have double its size and then add the element.
 *
 * @param d_arr the dynamic array to which we want to add an element.
 * @param element the element we want to add to the end of the array.
 * @return int FALSE(0) if the operation didn't work or TRUE(1) if the operation worked.
 */
int add_element(DynamicArray *d_arr, int element)
{
    if (d_arr->length == d_arr->capacity)
    {
        int new_capacity = d_arr->capacity * 2;
        int *new_array = (int *)realloc(d_arr->array, new_capacity * sizeof(int));
        if (!new_array)
            return false;

        d_arr->array = new_array;
        d_arr->capacity = new_capacity;
    }
    d_arr->array[d_arr->length] = element;
    d_arr->length += 1;
    return true;
}

/**
 * @brief removes an element from the dynamic array.
 * if the removal was succsesful and the dynamic array capacity is larger than twice it's length
 * the function will reallocate the size of the array to half its current capacity
 *
 * @param d_arr DynamicArray
 * @param index the index of element to remove
 * @return int TRUE (1) if the element was removed, FALSE(0) if was not capable to remove / resize.
 */
int remove_at_index(DynamicArray *d_arr, int index)
{
    if (index > d_arr->length)
        return false;
    for (int i = index; i < d_arr->length - 1; ++i)
    {
        d_arr->array[i] = d_arr->array[i + 1];
    }
    d_arr->length -= 1;
    if (d_arr->capacity > d_arr->length * 2)
    {
        int new_capacity = d_arr->capacity / 2;
        int *new_array = (int *)realloc(d_arr->array, new_capacity * sizeof(int));
        if (!new_array)
            return false;
        d_arr->array = new_array;
        d_arr->capacity = new_capacity;
    }
    return true;
}

/**
 * @brief Finds the index of a given value in a dynamic array. return -1 if no such value found in the array.
 *
 * @param d_arr dynamic array.
 * @param value the value we are looking for
 * @return int the index of value or -1 if there is no such value.
 */
int index_of_value(DynamicArray *d_arr, int value)
{
    for (int i = 0; i < d_arr->length; ++i)
    {
        if (d_arr->array[i] == value)
            return i;
    }
    return -1;
}

/**
 * @brief checks if the dynamic array contains the given value
 *
 * @param d_arr dynamic array.
 * @param value the value we are looking for
 * @return int
 */
int does_contain_value(DynamicArray *d_arr, int value)
{
    return (index_of_value(d_arr, value) != -1);
}

/**
 * @brief Tries to remove the value from the dynamic array.
 * if the value is in the dynamic array, this function calls remove_at_index
 *
 * @param d_arr DynamicArray
 * @param value the value we want to remove
 * @return int TRUE (1) if the element was removed, FALSE(0) if was not capable to remove / resize.
 */
int remove_value(DynamicArray *d_arr, int value)
{
    int index = index_of_value(d_arr, value);
    if (index == -1)
        return false;
    return remove_at_index(d_arr, index);
}

/**
 * @brief checks if the dynamic array is empty.
 *
 * @param d_arr
 * @return int
 */
int is_empty(DynamicArray *d_arr)
{
    if (d_arr->length == 0)
        return true;
    return false;
}

/**
 * @brief Get the element at index object.
 *
 * @param d_arr DynamicArray
 * @param index the index of element to get
 * @param result the pointer to the element at index, will be set only if there is an element at index
 * @return int true if found the element, false otherwise
 */
int get_element_at_index(DynamicArray *d_arr, int index, int *result)
{
    if (index >= d_arr->length)
    {
        return false;
    }
    *result = d_arr->array[index];
    return true;
}

/**
 * @brief set the element at index object.
 *
 * @param d_arr DynamicArray
 * @param index the index of element to set
 * @return int true if found the element, false otherwise
 */
int set_element_at_index(DynamicArray *d_arr, int index, int value)
{
    if (index >= d_arr->length)
    {
        return false;
    }
    d_arr->array[index] = value;
    return true;
}

/**
 * @brief frees the memory of the dynaic array
 * DONT FORGET TO CALL THIS AT THE END OF YOUR WORK.
 *
 * @param d_arr DynamicArray
 */
void delete_DynamicArray(DynamicArray *d_arr)
{
    free(d_arr->array);
    free(d_arr);
}