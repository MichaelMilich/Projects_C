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
    float result;
    bool did_calculate = parse_expression(&lexer,&result);
    if(!did_calculate){
        printf("[ERROR] input was in the wrong format. stoping calculation \n");
        return 1;
    }
    printf("Result: %f\n", result);
    return 0;
}