#ifndef STRING_TO_ARRAY_H
#define STRING_TO_ARRAY_H

#include "dynamic_int_array.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

bool check_format(const char *input_string);
DynamicIntArray *convert_string_to_dynamic_int_array(char *input_string);
char *trim_token(char *token);
bool convert_to_int(const char *token, int *result);
bool convert_to_float(const char *token, float *result);

#ifdef __cplusplus
}
#endif

#endif // STRING_TO_ARRAY_H