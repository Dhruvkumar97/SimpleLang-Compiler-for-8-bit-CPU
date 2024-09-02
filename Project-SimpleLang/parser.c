#include"parser.h"

void initParse(parser *par)
{
    parseAdv(par);
}

void parseAdv(parser *par)
{
    getNextToken(par->file, &par->currentToken);
}

void freeAST(TNode *node)
{
    if(!node) return;

    freeAST(node->left);
    freeAST(node->right);
    free(node);
}

TNode *parseStart(parser *par)
{
    TNode *root = NULL;
    TNode *node = NULL;

    while(par->currentToken.type != EOF_TOKEN)
    {
	node = parseStatement(par);

	if(!root)
	{
	    root = node;
	}
	else
	{
	    TNode *temp = root;

	    while(temp->right)
	    {
		temp = temp->right;
	    }

	    temp->right = node;
	}
    }

    return root;
}

TNode *parseStatement(parser *par)
{
    TNode *node = NULL;

    if(par->currentToken.type == INT_TOKEN)
    {
	parseAdv(par);

	if(par->currentToken.type == IDEN_TOKEN)
	{
	    node = (TNode *)malloc(sizeof(TNode));
	    node->type = VAR_DECL_NODE;
	    node->visit = NOT_VISITED;
	    strcpy(node->text, par->currentToken.text);
	    node->left = NULL;
	    node->right = NULL;
	    parseAdv(par);

	    if(par->currentToken.type == SEMICOLON_TOKEN) parseAdv(par);
	}
    }
    else if(par->currentToken.type == IDEN_TOKEN)
    {
	node = (TNode *)malloc(sizeof(TNode));
	node->type = ASSIGN_NODE;
	node->visit = NOT_VISITED;
	strcpy(node->text, par->currentToken.text);
	parseAdv(par);

	if(par->currentToken.type == ASSIGN_TOKEN)
	{
	    parseAdv(par);
	    node->right = parseExp(par);

	    while(par->currentToken.type == SEMICOLON_TOKEN || par->currentToken.type == RBRACE_TOKEN)
	    {
		parseAdv(par);
	    }
	}

    }
    else if(par->currentToken.type == IF_TOKEN)
    {
	parseAdv(par);
	if(par->currentToken.type == LPAREN_TOKEN)
	{
	    parseAdv(par);
	    node = (TNode *)malloc(sizeof(TNode));
	    node->type = CONDITIONAL_NODE;
	    node->visit = NOT_VISITED;
	    strcpy(node->text, "if");
	    node->left = parseExp(par);
	}

	if(par->currentToken.type == RPAREN_TOKEN)
	{
	    parseAdv(par);
	    if(par->currentToken.type == LBRACE_TOKEN)
	    {
		parseAdv(par);
		node->right = parseStatement(par);
	    }
	}
    }

    return node;
}

TNode *parseExp(parser *par)
{
    TNode *left = parsePrimary(par);

    while(par->currentToken.type == PLUSE_TOKEN || par->currentToken.type == MINUS_TOKEN || par->currentToken.type == DOUBLE_EQ_TOKEN)
    {
	TNode *node = (TNode *)malloc(sizeof(TNode));
	node->type = OPER_NODE;
	node->visit = NOT_VISITED;
	strcpy(node->text, par->currentToken.text);
	node->left = left;
	parseAdv(par);
	node->right = parseExp(par);
	left = node;
    }

    return left;
}

TNode *parsePrimary(parser *par)
{
    TNode *node = (TNode *)malloc(sizeof(TNode));
    node->visit = NOT_VISITED;
    strcpy(node->text, par->currentToken.text);
    node->left = NULL;
    node->right = NULL;

    if(par->currentToken.type == NUM_TOKEN)
    {
	node->type = CONST_NODE;
    }
    else if(par->currentToken.type == IDEN_TOKEN)
    {
	node->type = VAR_NODE;
    }

    parseAdv(par);
    return node;
}
