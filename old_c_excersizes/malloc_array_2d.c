#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
int check_validity_arg(char *argv[], int index)
{
    // Check if the input is zero
    if (strcmp(argv[index], "0") == 0)
    {
        printf("The input is zero.\n");
        return 0;
    }
    char *endptr;
    long input = strtol(argv[index], &endptr, 10);
    if (*endptr != '\0')
    {
        printf("Invalid input, '%s' is not an integer.\n", argv[index]);
        return -1;
    }

    return (int)input;
}

int check_validity_all(int argc, char *argv[], int *d1_ptr, int *d2_ptr)
{
    if (argc != 3)
    {
        printf("Please insert two integers to the program %s\n", argv[0]);
        return -1;
    }

    *d1_ptr = check_validity_arg(argv, 1);
    *d2_ptr = check_validity_arg(argv, 2);
    if (*d1_ptr == -1 || *d2_ptr == -1)
    {
        return -1;
    }
}

int main(int argc, char *argv[])
{
    int d1 = 0, d2 = 0;
    int input = check_validity_all(argc, argv, &d1, &d2);
    if (input == -1)
    {
        return 1;
    }

    srand(time(NULL)); // Initialization for random number generation
    int *int_array = (int *)malloc(sizeof(int) * d1 * d2);

    // Check if memory was allocated
    if (int_array == NULL)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    float sum = 0.0;

    printf("int_array = { \n");
    for (int i = 0; i < d1; ++i)
    {
        printf("      ");
        for (int j = 0; j < d2; ++j)
        {
            int_array[i * d2 + j] = rand() % 1000;
            sum += int_array[i * d2 + j];
            printf("%d ", int_array[i * d2 + j]);
        }
        printf("\n");
    }
    printf(" }  \n");

    printf("The average of int_array = %f\n", sum / (d1 * d2));
    free(int_array);

    return 0;
}