#include"codeGen.h"

int varCount = 0, conditional_reached = UNSET, regA = NOT_USING, regB = NOT_USING, textSegflag = UNSET;

void generateDataSeg(FILE *outputfile, int varCount, TNode *node)
{
    if(node != NULL && node->type == VAR_DECL_NODE)
    {
	fprintf(outputfile, "%s = %d\n", node->text, varCount);
	node->visit = VISITED;
	generateDataSeg(outputfile, varCount + 1, node->right);
    }
}

void generateAssembly(TNode *node, FILE *outputfile)
{
    if(!node)
    {
	printf("Cannot process. AST is Empty.\n");
	return;
    }

    if(textSegflag == SET)
    {
	fprintf(outputfile, ".text\n");
	textSegflag = UNSET;
    }

    switch(node->type)
    {
	case VAR_DECL_NODE:
	    if(node->visit == NOT_VISITED)
	    {
		fprintf(outputfile, ".data\n");
		generateDataSeg(outputfile, varCount, node);
		textSegflag = SET;
		fprintf(outputfile, "\n\n");
	    }
	    break;
	case ASSIGN_NODE:
	    if(node->visit == NOT_VISITED)
	    {
		generateAssembly(node->right, outputfile);
		fprintf(outputfile, "mov M A %%%s\n\n", node->text);
		node->visit = VISITED;
		regA = NOT_USING;
		regB = NOT_USING;

		if(conditional_reached == SET) 
		{
		    conditional_reached = UNSET;
		    return;
		}
	    }
	    break;
	case VAR_NODE:
	    if(node->visit == NOT_VISITED)
	    {
		if(regA == NOT_USING)
		{
		    fprintf(outputfile, "mov A M %%%s\n", node->text);
		    regA = USING;
		}
		else if(regB == NOT_USING)
		{
		    fprintf(outputfile, "mov B M %%%s\n", node->text);
		    regB = USING;
		}
		node->visit = VISITED;
		return;
	    }
	    break;
	case CONST_NODE:
	    if(node->visit == NOT_VISITED)
	    {
		if(regA == NOT_USING)
		{
		    fprintf(outputfile, "ldi A %s\n", node->text);
		    regA = USING;
		}
		else if(regB == NOT_USING)
		{
		    fprintf(outputfile, "ldi B %s\n", node->text);
		    regB = USING;
		}
		node->visit = VISITED;
		return;
	    }
	    break;
	case OPER_NODE:
	    if(node->visit == NOT_VISITED)
	    {
		if(strcmp(node->text, "+") == 0)
		{
		    generateAssembly(node->left, outputfile);
		    generateAssembly(node->right, outputfile);
		    fprintf(outputfile, "add\n");
		    node->visit = VISITED;
		    return;
		}
		else if(strcmp(node->text, "-") == 0)
		{
		    generateAssembly(node->left, outputfile);
		    generateAssembly(node->right, outputfile);
		    fprintf(outputfile, "sub\n");
		    node->visit = VISITED;
		    return;
		}
		if(strcmp(node->text, "==") == 0)
		{
		    generateAssembly(node->left, outputfile);
		    generateAssembly(node->right, outputfile);
		    fprintf(outputfile, "cmp\n");
		    node->visit = VISITED;
		    return;
		}
	    }
	    break;
	case CONDITIONAL_NODE:
	    if(node->visit == NOT_VISITED)
	    {
		generateAssembly(node->left, outputfile);
		fprintf(outputfile, "jne %%skip\n");
		regA = NOT_USING;
		regB = NOT_USING;
		conditional_reached = SET;
		generateAssembly(node->right, outputfile);
		fprintf(outputfile, "skip:\n");
		fprintf(outputfile, "hlt\n");
	    }
	    break;
    }

    if(node->right)
    {
	generateAssembly(node->right, outputfile);
    }
}
