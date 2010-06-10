//#include "lexems.h"
//#include "IdentifierTable.h"
//#include "TokenList.h"
#include "Sintaxis.h"

//#include "Lex.h"
// TODO: gresult -> yylval

// TODO: добавить унарный минус

unsigned char* OpenFile(char *path){
    FILE *source;
    source = fopen("prog","r");
    if(source == NULL){
        fputs("File not found\n",stderr);
        exit(1);
    }
	
    fseek(source,0,SEEK_END);
    long fileSize = ftell(source);
    rewind(source);
	
	//+1 для EOF
    unsigned char* gBuffer =(unsigned char*) malloc(sizeof(unsigned char)*(fileSize+1));
    if(gBuffer == NULL){
        fputs("Memory error\n",stderr);
        exit(2);
    }
    size_t result = fread(gBuffer,1,fileSize,source);
    if (result != fileSize){
        fputs("Reading error\n",stderr);
        exit(3);
    }
	gBuffer[fileSize + 1] = ETX;
    fclose(source);
	
    return gBuffer;
}

void SaveToFile(char *filename){
	FILE*  shfd = fopen(filename,"w");
	if (shfd < 0) {
		perror("open");
		return;
	}
	SaveCode(shfd);
	fclose(shfd);
}

int main (int argc, const char * argv[]) 
{
	printf("BEGIN\n");
    gSourceTxt = OpenFile("prog");
    printf("\nOpened:\n%s\n", gSourceTxt);
    gPointToSourceTxt = gSourceTxt;
	
	CurrToken = (Token)lex();
	int root = stmts();
	if (root  != 0 ) {
		printf("\nTokens:\n");
		printNodes(root);
		printf("\nCode:\n");
		int a = gen(root, 0);
		if(a == 0){
			LogCode();
			SaveToFile("output.asm");
		}
	}
	system("nasm -f macho  output.asm");
	system("nasm -f macho  lib.asm");
	system("rm output");
	system("ld -o output output.o lib.o -arch i386");
	//system("./output");
	printf("\n");
	DisplayIdTable();
	FlushIdTable();
	free(gSourceTxt);
	printf("\nEND\n");
    return 0;
}
