#ifndef PARSER_H
#define PARSER_H

#include"lexer.h"

#define VISITED 1
#define NOT_VISITED 0

typedef enum
{
    VAR_DECL_NODE,
    ASSIGN_NODE,
    OPER_NODE,
    VAR_NODE,
    CONST_NODE,
    CONDITIONAL_NODE
}NodeDataType;

typedef struct TreeNode
{
    NodeDataType type;
    char text[MAX_LEN];
    int visit;
    struct TreeNode *left;
    struct TreeNode *right;
}TNode;

typedef struct
{
    FILE *file;
    Token currentToken;
}parser;

void initParse(parser *par);
void parseAdv(parser *par);
void freeAST(TNode *node);
TNode *parseStart(parser *par);
TNode *parseStatement(parser *par);
TNode *parseExp(parser *par);
TNode *parsePrimary(parser *par);

#endif
