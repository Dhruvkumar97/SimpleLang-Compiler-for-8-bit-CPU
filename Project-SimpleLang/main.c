#include"codeGen.h"

int isEmpty(FILE *file)
{
    fseek(file, 0, SEEK_END);

    long size = ftell(file);

    fseek(file, 0, SEEK_SET);

    return size == 0;
}

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
	fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
	return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if(!file)
    {
	perror("Failed to open input file.");
	return 1;
    }

    if(isEmpty(file) == 1)
    {
	fprintf(stderr, "Cannot process. Input file is empty.\n");
	fclose(file);
	return 1;
    }

    printf("File opened Successfully.\n");

    parser parse;
    parse.file = file;

    initParse(&parse);

    TNode *ast = parseStart(&parse);
    fclose(file);

    FILE *outputfile = fopen("output.asm", "w");
    if(!outputfile)
    {
	perror("Failed to open outputfile.");
	return 1;
    }

    fprintf(outputfile, "; Assembly code for SimpleLang\n\n");
    generateAssembly(ast,outputfile);

    fclose(outputfile);

    freeAST(ast);

    return 0;
}
