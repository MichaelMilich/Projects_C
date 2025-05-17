#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "calc_lexer.h"
#include "calc_parser.h"

void print_help(const char *program_name) {
    printf("Usage: %s [--help] [--verbose] \"expression\"\n", program_name);
    printf("Evaluate a mathematical expression.\n\n");
    printf("Options:\n");
    printf("  --help       Show this help message\n");
    printf("  --verbose    Print debug tokens as they're parsed\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        print_help(argv[0]);
        return 1;
    }

    bool verbose = false;
    const char *expression = NULL;

    // Handle options
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--help") == 0) {
            print_help(argv[0]);
            return 0;
        } else if (strcmp(argv[i], "--verbose") == 0) {
            verbose = true;
        } else {
            expression = argv[i];
        }
    }

    if (expression == NULL) {
        fprintf(stderr, "[ERROR] No expression provided.\n");
        print_help(argv[0]);
        return 1;
    }

    Lexer lexer;
    lexer_init(&lexer, expression);

    // Verbose mode: print tokens
    if (verbose) {
        printf("Tokens:\n");
        Token *t;
        do {
            t = lexer_get_next_token(&lexer);
            if (t->type == TOKEN_NUMBER)
                printf("TOKEN_NUMBER: %f\n", t->value);
            else
                printf("TOKEN: %s\n", token_type_name(t->type));
        } while (t->type != TOKEN_EOF);

        // Reset lexer before parsing again
        lexer_init(&lexer, expression);
    }

    float result;
    if (!parse_expression(&lexer, &result)) {
        printf("[ERROR] Invalid expression.\n");
        return 1;
    }

    printf("Result: %f\n", result);
    return 0;
}