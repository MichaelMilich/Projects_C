#include "string_to_array.h"

/*
checks if the input string has the format of an array.
string representing an array starts with '[' and ends with ']' without anything
before and after expect whitespace. Input: char* input_string : the string
provided. Output: bool representation if the string is in the format of an
array.
*/
bool check_format(const char *input_string) {
    if (input_string == NULL)
        return false;

    // Skip leading whitespace
    while (isspace(*input_string))
        input_string++;

    size_t len = strlen(input_string);
    if (len < 2)
        return false;

    // Skip trailing whitespace
    const char *end = input_string + len - 1;
    while (end > input_string && isspace(*end))
        end--;

    // Check that it starts with [ and ends with ]
    if (*input_string != '[' || *end != ']')
        return false;

    int bracket_balance = 0;
    const char *ptr = input_string;
    while (ptr <= end) {
        if (*ptr == '[') {
            bracket_balance++;
        } else if (*ptr == ']') {
            bracket_balance--;
            if (bracket_balance < 0)
                return false; // closing too early
        }
        ptr++;
    }

    return bracket_balance == 0;
}

DynamicIntArray *convert_string_to_dynamic_int_array(char *input_string) {
    if (input_string == NULL) {
        return NULL;
    }

    DynamicIntArray *arr = new_empty_array();
    if (arr == NULL) {
        return NULL;
    }

    char *token = strtok(input_string, ",");
    while (token != NULL) {
        token = trim_token(token);
        if (*token == '\0') {
            // Skip empty tokens (e.g., extra commas)
            token = strtok(NULL, ",");
            continue;
        }

        int number;
        if (convert_to_int(token, &number)) {
            append_value(arr, number);
        } else {
            break;
        }

        token = strtok(NULL, ",");
    }
    return arr;
}

// Helper to trim brackets and whitespace
char *trim_token(char *token) {
    // Skip leading spaces and '['
    while (*token && (isspace(*token) || *token == '[')) {
        token++;
    }

    // Remove trailing spaces and ']'
    char *end = token + strlen(token) - 1;
    while (end > token && (isspace(*end) || *end == ']')) {
        *end = '\0';
        end--;
    }

    return token;
}

bool convert_to_int(const char *token, int *result) {
    char *endptr;
    *result = strtol(token, &endptr, 10);
    while (isspace(*endptr)) endptr++;
    return *endptr == '\0';
}

bool convert_to_float(const char *token, float *result) {
    char *endptr;
    *result = strtod(token, &endptr);
    return *endptr == '\0';
}

