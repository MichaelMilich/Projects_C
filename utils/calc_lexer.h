#ifndef LEXER_H
#define LEXER_H

#include "calc_token.h"

typedef struct {
    const char *input;
    size_t pos;
    char current_char;
    Token current_token;
} Lexer;

void lexer_init(Lexer *lexer, const char *input);
Token lexer_get_next_token(Lexer *lexer);

#endif
