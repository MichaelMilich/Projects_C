#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define LEN(arr) (sizeof(arr) / sizeof(arr[0]))

int my_strlen(char *string);
void reverse_string(char *string);
void print_string(char *string);

int my_strlen(char *string)
{
    int i = 0;
    while (*string != '\0') // Corrected the comparison here
    {
        i++;
        string++;
    }
    return i;
}

void reverse_string(char *string)
{
    int start = 0;
    int end = my_strlen(string) - 1;
    char temp_1, temp_2;
    while (end > start)
    {
        temp_1 = string[start];
        temp_2 = string[end];
        string[start] = temp_2;
        string[end] = temp_1;
        --end;
        ++start;
    }
}

void print_string(char *string)
{
    int i = 0;
    while (*string != '\0') // Corrected the comparison here
    {
        printf("%c", *string);
        string++;
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    char string[] = "Hello My name Is misha !";
    int len = my_strlen(string);
    printf("The length of the string is %d\n", len); // Added newline
    print_string(string);
    reverse_string(string);
    print_string(string);
    return 0;
}