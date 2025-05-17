#include "calc_parser.h"
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Include math.h for the pow() function
#include <math.h>

// --- Helper Prototypes ---
static bool expr(Lexer *lexer, float *result);
static bool term(Lexer *lexer, float *result);
static bool factor(Lexer *lexer, float *result);
static bool base(Lexer *lexer, float *result);
static bool eat(Lexer *lexer, TokenType type);

bool parse_expression(Lexer *lexer, float *result) {
    *result = 0.0f;
    if (lexer == NULL){
        printf("[ERROR] Lexer is NULL\n");  
        return false;
    }
    bool did_calculate =  expr(lexer, result);
    if (lexer->current_token.type != TOKEN_EOF){
        printf("[ERROR] Unexpected token %d\n", lexer->current_token.type);
        return false;
    }
    return did_calculate;
}

static bool expr(Lexer *lexer, float *result) {
    if (lexer == NULL){
        printf("[ERROR] Lexer is NULL\n");  
        return false;
    }
    bool did_calculate = term(lexer, result);
    if (!did_calculate){
        printf("[ERROR] Failed to calculate term\n");  
        return did_calculate;
    }
    while (lexer->current_token.type == TOKEN_PLUS ||
           lexer->current_token.type == TOKEN_MINUS) {
        if (lexer->current_token.type == TOKEN_PLUS) {
            if (!eat(lexer, TOKEN_PLUS)){
                printf("[ERROR] Failed to eat TOKEN_PLUS\n");  
                return false;
            }
            float temp_result = 0.0f;
            did_calculate = term(lexer, &temp_result);
            if (!did_calculate){
                printf("[ERROR] Failed to calculate term\n");  
                return did_calculate;
            }
            *result += temp_result;
        } else if (lexer->current_token.type == TOKEN_MINUS) {
            if (!eat(lexer, TOKEN_MINUS)){
                printf("[ERROR] Failed to eat TOKEN_MINUS\n");  
                return false;
            }
            float temp_result = 0.0f;
            did_calculate = term(lexer, &temp_result);
            if (!did_calculate){
                printf("[ERROR] Failed to calculate term\n");  
                return did_calculate;
            }
            *result -= temp_result;
        }
    }
    return true;
}

static bool term(Lexer *lexer, float *result) {
    if (lexer == NULL)
        return false;
    bool did_calculate = factor(lexer, result);
    if (!did_calculate){
        printf("[ERROR] Failed to calculate factor\n");  
        return did_calculate;
    }
    while (lexer->current_token.type == TOKEN_STAR ||
           lexer->current_token.type == TOKEN_SLASH) {
        if (lexer->current_token.type == TOKEN_STAR) {
            if (!eat(lexer, TOKEN_STAR)){
                printf("[ERROR] Failed to eat TOKEN_STAR\n");  
                return false;
            }
            float temp_result = 0.0f;
            did_calculate = factor(lexer, &temp_result);
            if (!did_calculate){
                printf("[ERROR] Failed to calculate factor\n");  
                return did_calculate;
            }
            *result *= temp_result;
        } else if (lexer->current_token.type == TOKEN_SLASH) {
            if (!eat(lexer, TOKEN_SLASH)){
                printf("[ERROR] Failed to eat TOKEN_SLASH\n");  
                return false;
            }
            float temp_result = 0.0f;
            did_calculate = factor(lexer, &temp_result);
            if (!did_calculate){
                printf("[ERROR] Failed to calculate factor\n");  
                return did_calculate;
            }
            if (temp_result==0.0f){
                fprintf(stderr, "[ERROR] can't do division by zero");
                return false;
            }
            *result /= temp_result;
        }
    }
    return true;
}

static bool factor(Lexer *lexer, float *result) {
    if (lexer == NULL){
        printf("[ERROR] Lexer is NULL\n");  
        return false;
    }
    bool did_calculate = base(lexer, result);
    if (!did_calculate){
        printf("[ERROR] Failed to calculate base\n");  
        return did_calculate;
    }
    while (lexer->current_token.type == TOKEN_CARET) {
        if (lexer->current_token.type == TOKEN_CARET) {
            if (!eat(lexer, TOKEN_CARET)){
                printf("[ERROR] Failed to eat TOKEN_CARET\n");  
                return false;
            }
            float temp_result = 0.0f;
            did_calculate = base(lexer, &temp_result);
            if (!did_calculate){
                printf("[ERROR] Failed to calculate base\n");  
                return did_calculate;
            }
            *result = pow(*result, temp_result);
        }
    }
    return true;
}

static bool base(Lexer *lexer, float *result) {
    if (lexer == NULL){
        printf("[ERROR] Lexer is NULL\n");  
        return false;
    }
    if (lexer->current_token.type == TOKEN_NUMBER) {
        *result = lexer->current_token.value;
        if (!eat(lexer, TOKEN_NUMBER)){
            printf("[ERROR] Failed to eat TOKEN_NUMBER\n");  
            return false;
        }
        return true;
    } else if (lexer->current_token.type == TOKEN_UNARY_MINUS) {
        if (!eat(lexer, TOKEN_UNARY_MINUS)){
            printf("[ERROR] Failed to eat TOKEN_UNARY_MINUS\n");  
            return false;
        }
        float temp_result = 0.0f;
        if (!base(lexer, &temp_result)){
            printf("[ERROR] Failed to calculate base after unary minus\n");  
            return false;
        }
        *result = -temp_result;
        return true;
    } else if (lexer->current_token.type == TOKEN_LPAREN) {
        float temp_result = 0.0f;
        if (!eat(lexer, TOKEN_LPAREN)){
            printf("[ERROR] Failed to eat TOKEN_LPAREN\n");  
            return false;
        }
        if (!expr(lexer, &temp_result)){
            printf("[ERROR] Failed to calculate expr\n");  
            return false;
        }
        *result = temp_result;
        if (!eat(lexer, TOKEN_RPAREN)){
            printf("[ERROR] Failed to eat TOKEN_RPAREN\n");  
            return false;
        }
        return true;
    }
    return false;
}

static bool eat(Lexer *lexer, TokenType type) {
    if (lexer == NULL){
        printf("[ERROR] Lexer is NULL\n");  
        return false;
    }
    if (lexer->current_token.type == type) {
        lexer_get_next_token(lexer);
        return true;
    } else{
        fprintf(stderr, "[ERROR] Expected token %d but got %d\n", type, lexer->current_token.type);
        return false;
    }
}