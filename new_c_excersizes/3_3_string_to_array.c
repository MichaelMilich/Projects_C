/*
 * write a script that gets as input a string and outputs the array it represents
 * string in the format of '[1,2,3,45]' will be an array of [1,2,3,45] (int)
 * string in the format of '[1.0,2.1,3.5]' will be an array of floats
 * string that does not follow the rules of '[]' at the start and end - will throw an error.
 * bonus: create parser for any size of arrays. 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

/*
checks if the input string has the format of an array.
string representing an array starts with '[' and ends with ']' without anything before and after expect whitespace.
Input:
    char* input_string : the string provided.
Output:
    bool representation if the string is in the format of an array.
*/
bool check_format(const char* input_string) {
    if (input_string == NULL) return false;

    // Skip leading whitespace
    while (isspace(*input_string)) input_string++;

    size_t len = strlen(input_string);
    if (len < 2) return false;

    // Skip trailing whitespace
    const char* end = input_string + len - 1;
    while (end > input_string && isspace(*end)) end--;

    // Check that it starts with [ and ends with ]
    if (*input_string != '[' || *end != ']') return false;

    int bracket_balance = 0;
    const char* ptr = input_string;
    while (ptr <= end) {
        if (*ptr == '[') {
            bracket_balance++;
        } else if (*ptr == ']') {
            bracket_balance--;
            if (bracket_balance < 0) return false; // closing too early
        }
        ptr++;
    }

    return bracket_balance == 0;
}

bool convert_to_int(const char* token, int* result) {
    char* endptr;
    *result = strtol(token, &endptr, 10);
    return *endptr == '\0';
}

bool convert_to_float(const char* token, float* result) {
    char* endptr;
    *result = strtod(token, &endptr);
    return *endptr == '\0';
}



int main(int argc, char *argv[]) {
    // Check input arguments
    if (argc != 2) {
        printf("Usage: %s <String>\n", argv[0]);
        printf("<String> is the array represented as string (for example "
               "'[1,5,8,2]')");
        return 1;
    }

    int length = strlen(argv[1]);
    char* s = malloc(length + 1);
    if (s == NULL) return 1;
    strcpy(s, argv[1]);
    if (!check_format(s))
    {
        printf("[FORMAT_ERROR] the provided sting %s is not in a format of an array \n", s);
        free(s);
        return 1;
    }

    printf("✓ The string '%s' is in the correct format.\n", s);
    free(s);
    return 0;
    
}