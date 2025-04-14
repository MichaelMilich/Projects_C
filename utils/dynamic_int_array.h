// dynamic_int_array.h
#ifndef DYNAMIC_INT_ARRAY_H
#define DYNAMIC_INT_ARRAY_H

#include <stdlib.h>
#include <stdbool.h>

// Struct definition
typedef struct {
    size_t size;
    size_t capacity;
    bool is_dynamic_memory;
    int* data;
} DynamicIntArray;

DynamicIntArray* new_empty_array();
bool init_array(DynamicIntArray* arr);
bool append_value(DynamicIntArray* arr, int value);
int find_value_index(DynamicIntArray* arr, int value);
bool remove_value_at_index(DynamicIntArray* arr, int value);
bool add_array(DynamicIntArray* parent_arr, DynamicIntArray* child_array_to_add);
void print_array(DynamicIntArray* arr);
bool free_array_memory(DynamicIntArray* arr);

#endif // DYNAMIC_INT_ARRAY_H