#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calc_lexer.h"
#include "calc_parser.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s \"expression\"\n", argv[0]);
        return 1;
    }

    Lexer lexer;
    lexer_init(&lexer, argv[1]);
    float result = parse_expression(&lexer);
    printf("Result: %f\n", result);
    return 0;
}