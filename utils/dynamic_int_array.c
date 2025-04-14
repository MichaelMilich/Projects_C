// dynamic_int_array.c
#include "dynamic_int_array.h"
#include <stdio.h>  // for printf in print_array

#define INITIAL_CAPACITY 4

DynamicIntArray* new_empty_array(){
    DynamicIntArray *arr = malloc(sizeof(DynamicIntArray));
    if(arr==NULL) 
        return NULL;

    arr->size = 0;
    arr->capacity = INITIAL_CAPACITY;
    arr->is_dynamic_memory=true;
    arr->data =  malloc(arr->capacity * sizeof(int)); 
    if(arr->data==NULL){
        free(arr);
        return NULL;
    }

    return arr;
}

bool init_array(DynamicIntArray* arr) {
    arr->size = 0;
    arr->capacity = INITIAL_CAPACITY;
    arr->data = malloc(arr->capacity * sizeof(int));
    arr->is_dynamic_memory = false;

    return arr->data != NULL;
}

bool free_array_memory(DynamicIntArray* arr){
    if (arr == NULL) return false;
    free(arr->data);
    if (arr->is_dynamic_memory) {
        free(arr);
    }
    return true;
    
}