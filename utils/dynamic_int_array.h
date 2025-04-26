#ifndef DYNAMIC_INT_ARRAY_H
#define DYNAMIC_INT_ARRAY_H

#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    size_t size;
    size_t capacity;
    int* data;
    bool is_dynamic_memory;
    bool is_sorted;
} DynamicIntArray;

DynamicIntArray* new_empty_array();
bool init_array(DynamicIntArray* arr);
int append_value(DynamicIntArray* arr, int value);
int find_value_index(DynamicIntArray* arr, int value);
bool remove_value_at_index(DynamicIntArray *arr, int index, int *out_ptr);
bool pop(DynamicIntArray* arr, int* out_ptr);
bool add_array(DynamicIntArray* parent_arr, DynamicIntArray* child_array_to_add);
void print_array(DynamicIntArray* arr);
bool free_array_memory(DynamicIntArray* arr);
int get_value_at_index(DynamicIntArray* arr, size_t index, int* out_ptr);

#ifdef __cplusplus
}
#endif

#endif // DYNAMIC_INT_ARRAY_H