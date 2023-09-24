#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int check_validity(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Please insert one input to the program %s\n", argv[0]);
        return -1;
    }

    // Check if the input is zero
    if (strcmp(argv[1], "0") == 0)
    {
        printf("The input is zero.\n");
        return 0;
    }

    char *endptr;
    long input = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0')
    {
        printf("Invalid input, '%s' is not an integer.\n", argv[1]);
        return -1;
    }

    return (int)input;
}

int main(int argc, char *argv[])
{
    int input = check_validity(argc, argv);
    if (input == -1)
    {
        return 1;
    }

    srand(time(NULL)); // Initialization for random number generation
    int *int_array = (int *)malloc(sizeof(int) * input);

    // Check if memory was allocated
    if (int_array == NULL)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    float sum = 0.0;
    for (int i = 0; i < input; ++i)
    {
        int_array[i] = rand() % 1000;
        sum += int_array[i];
        printf("int_array[%d]=%d \n", i, int_array[i]);
    }

    printf("The average of int_array = %f\n", sum / input);
    free(int_array);

    return 0;
}