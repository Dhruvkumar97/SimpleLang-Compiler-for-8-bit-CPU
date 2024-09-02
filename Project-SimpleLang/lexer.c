#include"lexer.h"

void getNextToken(FILE *file, Token *token)
{
    int c;

    while((c = fgetc(file)) != EOF)
    {
	if(isspace(c)) continue;

	if(isalpha(c))
	{
	    int len = 0;
	    token->text[len++] = c;

	    while(isalnum(c = fgetc(file)))
	    {
		if(len < MAX_LEN - 1) token->text[len++] = c;
	    }
	    ungetc(c, file);
	    token->text[len] = '\0';

	    if(strcmp(token->text, "int") == 0)
	    {
		token->type = INT_TOKEN;
	    }
	    else if(strcmp(token->text, "if") == 0)
	    {
		token->type = IF_TOKEN;
	    }
	    else
	    {
		token->type = IDEN_TOKEN;
	    }
	    return;
	}
	else if(isdigit(c))
	{
	    int len = 0;
	    token->text[len++] = c;

	    while(isdigit(c = fgetc(file)))
	    {
		if(len < MAX_LEN - 1) token->text[len++] = c;
	    }
	    ungetc(c, file);
	    token->text[len] = '\0';
	    token->type = NUM_TOKEN;
	    return;
	}

	switch(c)
	{
	    case '+': token->type = PLUSE_TOKEN; strcpy(token->text, "+"); return;
	    case '-': token->type = MINUS_TOKEN; strcpy(token->text, "-"); return;
	    case ';': token->type = SEMICOLON_TOKEN; strcpy(token->text, ";"); return;
	    case '(': token->type = LPAREN_TOKEN; strcpy(token->text, "("); return;
	    case ')': token->type = RPAREN_TOKEN; strcpy(token->text, ")"); return;
	    case '{': token->type = LBRACE_TOKEN; strcpy(token->text, "{"); return;
	    case '}': token->type = RBRACE_TOKEN; strcpy(token->text, "}"); return;
	    case '=':
		      if((c = fgetc(file)) == '=')
		      {
			  token->type = DOUBLE_EQ_TOKEN;
			  strcpy(token->text, "==");
		      }
		      else
		      {
			  ungetc(c, file);
			  token->type = ASSIGN_TOKEN;
			  strcpy(token->text, "=");
		      }
		      return;
	}
    }

    token->type = EOF_TOKEN;
    token->text[0] = '\0';
}
