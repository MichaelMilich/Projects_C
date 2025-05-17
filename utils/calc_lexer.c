#include "calc_lexer.h"
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Helper Prototypes ---
static void skip_whitespace(Lexer *lexer);
static void advance(Lexer *lexer);
static void get_number(Lexer *lexer, Token *token);
static bool convert_to_float(const char *string, float *result, size_t start_index, size_t end_index);
static bool is_unary_minus(Lexer *lexer);

// --- Lexer Initialization ---
void lexer_init(Lexer *lexer, const char *input) {
    if (lexer == NULL || input == NULL)
        return;

    lexer->input = input;
    lexer->pos = 0;
    lexer->current_char = lexer->input[lexer->pos];
    lexer->current_token.type = TOKEN_INVALID;
    lexer->current_token.value = 0.0f;
    lexer_get_next_token(lexer);
}

// --- Lexer Core ---
Token *lexer_get_next_token(Lexer *lexer) {
    if (lexer == NULL)
        return NULL;

    skip_whitespace(lexer);

    if (lexer->current_char == '\0') {
        lexer->current_token.type = TOKEN_EOF;
        return &lexer->current_token;
    }

    if (isdigit(lexer->current_char) || lexer->current_char == '.') {
        get_number(lexer, &lexer->current_token);
        return &lexer->current_token;
    }

    char ch = lexer->current_char;
    advance(lexer);

    switch (ch) {
        case '+':
            lexer->current_token.type = TOKEN_PLUS;
            break;
        case '-':
            lexer->current_token.type = is_unary_minus(lexer) ? TOKEN_UNARY_MINUS : TOKEN_MINUS;
            break;
        case '*':
            lexer->current_token.type = TOKEN_STAR;
            break;
        case '/':
            lexer->current_token.type = TOKEN_SLASH;
            break;
        case '^':
            lexer->current_token.type = TOKEN_CARET;
            break;
        case '(':
            lexer->current_token.type = TOKEN_LPAREN;
            break;
        case ')':
            lexer->current_token.type = TOKEN_RPAREN;
            break;
        default:
            lexer->current_token.type = TOKEN_INVALID;
            break;
    }

    return &lexer->current_token;
}

// --- Helpers ---
static void skip_whitespace(Lexer *lexer) {
    while (lexer->current_char != '\0' && isspace(lexer->current_char)) {
        advance(lexer);
    }
}

static void advance(Lexer *lexer) {
    lexer->pos++;
    lexer->current_char = lexer->input[lexer->pos];
}

static void get_number(Lexer *lexer, Token *token) {
    size_t start_index = lexer->pos;

    while (lexer->current_char != '\0' &&
           (isdigit(lexer->current_char) || lexer->current_char == '.')) {
        advance(lexer);
    }

    size_t end_index = lexer->pos;
    float result;
    bool ok = convert_to_float(lexer->input, &result, start_index, end_index);

    if (ok) {
        token->type = TOKEN_NUMBER;
        token->value = result;
    } else {
        token->type = TOKEN_INVALID;
        token->value = 0.0f;
    }
}

static bool convert_to_float(const char *string, float *result, size_t start_index, size_t end_index) {
    if (string == NULL || result == NULL || end_index <= start_index)
        return false;

    size_t len = end_index - start_index;
    char *buffer = (char *)malloc(len + 1);
    if (buffer == NULL)
        return false;

    strncpy(buffer, string + start_index, len);
    buffer[len] = '\0';

    char *endptr;
    *result = strtof(buffer, &endptr);
    bool success = (*endptr == '\0');  // Fully consumed
    free(buffer);
    return success;
}

static bool is_unary_minus(Lexer *lexer) {
    // A minus is unary if:
    // 1. It's at the start of the expression
    // 2. It follows an opening parenthesis
    // 3. It follows an operator
    if (lexer->pos == 1)  // At start of expression
        return true;
    
    // Look at the previous non-whitespace character
    int prev_pos = lexer->pos - 2;  // -2 because we already advanced past the minus
    while (prev_pos >= 0 && isspace(lexer->input[prev_pos]))
        prev_pos--;
    
    if (prev_pos < 0)  // Only whitespace before this
        return true;
        
    char prev_char = lexer->input[prev_pos];
    return prev_char == '(' || prev_char == '+' || prev_char == '-' || 
           prev_char == '*' || prev_char == '/' || prev_char == '^';
}
