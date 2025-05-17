#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_UNARY_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_CARET,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_EOF,
    TOKEN_INVALID
} TokenType;

const char *token_type_name(TokenType type) {
    switch (type) {
        case TOKEN_NUMBER:      return "TOKEN_NUMBER";
        case TOKEN_PLUS:        return "TOKEN_PLUS";
        case TOKEN_MINUS:       return "TOKEN_MINUS";
        case TOKEN_STAR:        return "TOKEN_STAR";
        case TOKEN_SLASH:       return "TOKEN_SLASH";
        case TOKEN_CARET:       return "TOKEN_CARET";
        case TOKEN_LPAREN:      return "TOKEN_LPAREN";
        case TOKEN_RPAREN:      return "TOKEN_RPAREN";
        case TOKEN_EOF:         return "TOKEN_EOF";
        case TOKEN_INVALID:     return "TOKEN_INVALID";
        case TOKEN_UNARY_MINUS: return "TOKEN_UNARY_MINUS";
        default:                return "UNKNOWN_TOKEN";
    }
}

typedef struct {
    TokenType type;
    float value;  // Only used if type == TOKEN_NUMBER
} Token;

#endif
