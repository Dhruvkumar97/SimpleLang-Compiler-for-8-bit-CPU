#ifndef LEXER_H
#define LEXER_H

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

#define MAX_LEN 20

typedef enum
{
    INT_TOKEN, IDEN_TOKEN, IF_TOKEN,
    NUM_TOKEN, SEMICOLON_TOKEN, PLUSE_TOKEN,
    MINUS_TOKEN, ASSIGN_TOKEN, DOUBLE_EQ_TOKEN,
    LPAREN_TOKEN, RPAREN_TOKEN, LBRACE_TOKEN,
    RBRACE_TOKEN, EOF_TOKEN
} TokenDataType;

typedef struct
{
    TokenDataType type;
    char text[MAX_LEN];
}Token;

void getNextToken(FILE *file, Token *token);

#endif
