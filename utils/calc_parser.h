#ifndef PARSER_H
#define PARSER_H

#include "calc_lexer.h"
#include <stdbool.h>

bool parse_expression(Lexer *lexer, float *result);  // Main entry point

#endif
