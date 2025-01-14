#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
// Write a program that takes a number as input and uses if-else statements to check whether the number is even or odd.


int is_even(int number){
    if (number %2 ==0){
        return TRUE;
    }
    return FALSE;
}

int test_is_even(){
    // testing if the number is odd
    int num = 3;
    int expected = FALSE;
    

}

int main(int argc, char *argv[])
{
    // Check if an argument is provided
    if (argc != 2) {
        printf("Usage: %s <integer>\n", argv[0]);
        return 1;
    }

    // Convert the argument from string to integer
    int num = atoi(argv[1]);
    if(num==0){
        printf("input number was 0, zero is zero \n");
        return 0;
    }
    
    if(is_even(num)){
        printf("%d is an even number! \n", num);
    } else {
        printf("%d is an odd number! \n ", num);
    }
    return 0;
}