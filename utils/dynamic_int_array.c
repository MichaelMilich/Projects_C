#include "dynamic_int_array.h"
#include <stdio.h> // for printf in print_array

#define INITIAL_CAPACITY 4

DynamicIntArray *new_empty_array() {
    DynamicIntArray *arr = malloc(sizeof(DynamicIntArray));
    if (arr == NULL)
        return NULL;

    arr->size = 0;
    arr->capacity = INITIAL_CAPACITY;
    arr->is_dynamic_memory = true;
    arr->data = malloc(arr->capacity * sizeof(int));
    if (arr->data == NULL) {
        free(arr);
        return NULL;
    }

    return arr;
}

bool init_array(DynamicIntArray *arr) {
    arr->size = 0;
    arr->capacity = INITIAL_CAPACITY;
    arr->data = malloc(arr->capacity * sizeof(int));
    arr->is_dynamic_memory = false;

    return arr->data != NULL;
}

bool free_array_memory(DynamicIntArray *arr) {
    if (arr == NULL)
        return false;
    free(arr->data);
    if (arr->is_dynamic_memory) {
        free(arr);
    }
    return true;
}

bool resize_array(DynamicIntArray *arr, size_t new_capacity) {
    int *new_data = realloc(arr->data, new_capacity * sizeof(int));
    if (new_data == NULL)
        return false;
    arr->data = new_data;
    arr->capacity = new_capacity;
    return true;
}

int append_value(DynamicIntArray *arr, int value) {
    if (arr == NULL)
        return -1;
    if (arr->size >= arr->capacity) {
        size_t new_capacity = arr->capacity * 2;
        if (!resize_array(arr, new_capacity))
            return -1;
    }
    arr->data[arr->size] = value;
    arr->size++;
    return arr->size - 1;
}

int find_value_index(DynamicIntArray *arr, int value) {
    if (arr == NULL)
        return -1;
    // I can't assume the array is sorted.
    // TODO: write sort functions
    for (int i = 0; i < arr->size; i++) {
        if (arr->data[i] == value)
            return i;
    }
    return -1;
}

bool remove_value_at_index(DynamicIntArray *arr, int index, int *out_ptr) {
    if (arr == NULL || out_ptr == NULL)
        return false;
    if (arr->size <= (size_t)index)
        return false;
    *out_ptr = arr->data[index];
    for (int i = index; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }
    arr->size--;
    if (arr->size < arr->capacity / 2 && arr->capacity > 4) {
        size_t new_capacity = arr->capacity / 2;
        resize_array(arr, new_capacity); // ignore failure on shrink
    }
    return true;
}

bool pop(DynamicIntArray *arr, int *out_ptr) {
    if (arr == NULL || arr->size == 0 || out_ptr == NULL)
        return false;
    *out_ptr =
        arr->data[arr->size - 1]; // write to memory out_ptr points to the value
                                  // of arr->data[arr->size - 1]
    arr->size--;
    return true;
}

bool add_array(DynamicIntArray *parent_arr,
               DynamicIntArray *child_array_to_add) {
    if (parent_arr == NULL || child_array_to_add == NULL)
        return false;

    size_t needed_capacity = parent_arr->size + child_array_to_add->size;
    if (parent_arr->capacity < needed_capacity) {
        if (!resize_array(parent_arr, needed_capacity * 2))
            return false;
    }

    for (size_t i = 0; i < child_array_to_add->size; i++) {
        parent_arr->data[parent_arr->size + i] = child_array_to_add->data[i];
    }

    parent_arr->size += child_array_to_add->size;
    return true;
}

void print_array(DynamicIntArray *arr) {
    if (arr == NULL)
        return;
    printf("[");
    for (size_t i = 0; i < arr->size - 1; i++) {
        printf(" %d,", arr->data[i]);
    }
    printf(" %d ]\n", arr->data[arr->size - 1]);
}

int get_value_at_index(DynamicIntArray* arr, size_t index, int* out_ptr) {
    if (arr == NULL || out_ptr == NULL) return -1;
    if (index >= arr->size) return -1;
    *out_ptr = arr->data[index];
    return 0;
}