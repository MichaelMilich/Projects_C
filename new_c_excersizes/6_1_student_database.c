/*
Student Database:
Create a structure to specify data on students given as: Roll number, Name, Department, Course, Year of joining. 
Write a program to print these.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// Function declarations
void print_usage(const char *program_name);
void process_function(const char *func_name, const char *filepath, const char *param);

int main(int argc, char *argv[]) {
    char *func_name = NULL;
    char *filepath = NULL;
    char *param = NULL;

    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--func") == 0 && i + 1 < argc) {
            func_name = argv[++i];
        } else if (strcmp(argv[i], "--filepath") == 0 && i + 1 < argc) {
            filepath = argv[++i];
        } else if (strcmp(argv[i], "--param") == 0 && i + 1 < argc) {
            param = argv[++i];
        }
    }

    // Check if required arguments are provided
    if (func_name == NULL || filepath == NULL) {
        print_usage(argv[0]);
        return 1;
    }

    // Process the function
    process_function(func_name, filepath, param);

    return 0;
}

void print_usage(const char *program_name) {
    printf("Usage: %s --func <function_name> --filepath <file_path> [--param <parameters>]\n", program_name);
    printf("Example: %s --func read --filepath data.txt --param \"param1,param2\"\n", program_name);
}

void process_function(const char *func_name, const char *filepath, const char *param) {
    printf("Function: %s\n", func_name);
    printf("Filepath: %s\n", filepath);
    if (param != NULL) {
        printf("Parameters: %s\n", param);
    }
}