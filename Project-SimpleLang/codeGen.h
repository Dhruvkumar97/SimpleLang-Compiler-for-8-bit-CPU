#ifndef CODEGEN_H
#define CODEGEN_H

#include"lexer.h"
#include"parser.h"

#define USING 1
#define NOT_USING 2
#define SET 3
#define UNSET 4

void generateDataSeg(FILE *outputfile, int varCount, TNode *node);
void generateAssembly(TNode *node, FILE *outputfile);

#endif
