
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h> 

static void partition(int *data, int n);
static void swap(int *ptr_1, int *ptr_2);

static void partition(int *data, int n){
    int pivot = data[0];
    int i = -1, j=n;
    while(true){
        do{ i++;} while(data[i]<pivot);
        do{ j--;} while(data[j]>pivot);
        if(i>j) break;
        swap(&data[i],&data[j]);
    }
}

static void swap(int *ptr_1, int *ptr_2) {
    int temp = *ptr_1;
    *ptr_1 = *ptr_2;
    *ptr_2 = temp;
}

int lomuto_partition(int *arr, int n) {
    int pivot = arr[0];
    int i = 1;
    for (int j = 1; j < n; j++) {
        if (arr[j] < pivot) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[0], &arr[i - 1]);
    return i - 1; // New index of pivot
}

int main() {
    int arr[] = {2,7,-1,3,4,0};
    int n = sizeof(arr) / sizeof(arr[0]);
    lomuto_partition(arr, n);
    
    for (int i = 0; i < n; i++) 
        printf("%d ", arr[i]); 
    printf("\n");
    return 0; // output is 5 3 8 4 2 7 1 10 instead of 1 3 2 4 8 7 5 10 
}