#define LEXSIZ	31	/* size of lexeme/identifier;
only first 31 characters are considered */

char NextSym(void);
void PrevSym(void);
int get_num(void);
int GetLexemeType(unsigned  char* lexeme);
void Comment();
int lex(void);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexems.h"

/* char llbuf[BUFSIZ];	*/
unsigned char lllexeme[LEXSIZ+1];	/* +1 for '\0' */
unsigned char *yytext;	/* pointer to lllexeme */
unsigned char* gSourceTxt;
unsigned char* gPointToSourceTxt;


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

int main (int argc, const char * argv[]) 
{
	printf("BEGIN\n");
    gSourceTxt = OpenFile("prog");
    printf("\nOpened:\n%s\n", gSourceTxt);
    gPointToSourceTxt = gSourceTxt;
    
	
	printf("\nTokens:\n");
    int id;
	while (1) {
		id = lex();
		if (-1 == id) {
			break;
		}
		printf("Token = %s, value = %d\n", lllexeme, id);
	} 
	free(gSourceTxt);
	printf("\nEND\n");
    return 0;
}

int lex(void)
{
	//	char sym1, sym2;
	yytext = lllexeme;
	//sym1 = *gPointToSourceTxt;
	while (1) {
		switch (gCharMap[*gPointToSourceTxt]) {
			case LETTER:
				*yytext++ = *gPointToSourceTxt;
				while (*(++gPointToSourceTxt) && (gCharMap[*gPointToSourceTxt] == LETTER || 
												  gCharMap[*gPointToSourceTxt] == DIGIT))
					*yytext++ = *gPointToSourceTxt;
				
				*yytext = '\0';		/* identifier < 32 characters */
				yytext[LEXSIZ] = '\0';	/* idenfier > 32 characters */
				//PrevSym();	/* push back nonalnum char or '_' */
				return GetLexemeType(lllexeme);
				break;
			case DIGIT:
				return get_num();
				break;
				
			case ETX://конец текста
				return -1;
				break;
				
			case OTHER:
				*yytext = '\0';
				if (gPointToSourceTxt[0] == '/' &&
					gPointToSourceTxt[1] == '*') {
					Comment();
					break;
				}

				if (gPointToSourceTxt[0] == '>' &&
					gPointToSourceTxt[1] == '=') {
					//>=
					gPointToSourceTxt++;
					return GE_OP;
				}
				if (gPointToSourceTxt[0] == '<' &&
					gPointToSourceTxt[1] == '=') {
					//<=
					gPointToSourceTxt++;
					return LE_OP;
				}
				if (gPointToSourceTxt[0] == '!' &&
					gPointToSourceTxt[1] == '=') {
					//!=
					gPointToSourceTxt++;
					return NE_OP;
				}
				if (gPointToSourceTxt[0] == '+' &&
					gPointToSourceTxt[1] == '+') {
					//++
					gPointToSourceTxt++;
					return INC_OP;
				}

				if (gPointToSourceTxt[0] == '-' &&
					gPointToSourceTxt[1] == '-') {
					//--
					gPointToSourceTxt++;
					return DEC_OP;
				}
				
				if (gPointToSourceTxt[0] == '-') {
					// -
					gPointToSourceTxt++;
					return SUB_OP;
				}
				if (gPointToSourceTxt[0] == '+') {
					// +
					gPointToSourceTxt++;
					return ADD_OP;
				}
				if (gPointToSourceTxt[0] == '*') {
					// *
					gPointToSourceTxt++;
					return MUL_OP;
				}
				if (gPointToSourceTxt[0] == '/') {
					// /
					gPointToSourceTxt++;
					return DIV_OP;
				}
				if (gPointToSourceTxt[0] == '=') {
					// =
					gPointToSourceTxt++;
					return MOV_OP;
				}
				
				break;
				
			default:
				break;
		}
		gPointToSourceTxt++;
		//sym1 = NextSym();
	}
}

char NextSym(void)
{
	return (char) *(++gPointToSourceTxt);
}

void PrevSym(void)
{
    --gPointToSourceTxt;
}

void Comment(void)
{
	char sym1, sym2;
	sym2 = NextSym();
	while (1)
	{
		sym1 = sym2;
		if (sym1 == EOF)
			break;
		sym2 = NextSym();
		if ((sym1 == '*') && (sym2 == '/'))
		{
			break;
		}           
	}
}

int GetLexemeType(unsigned char* lexeme)
{
	int i;
	for (i = 0; gKeywords[i] != '\0'; i++)
		if (strcmp(gKeywords[i], lexeme) == 0)
			return KEYWORD;
	return IDENTIFIER;
}

int get_num(void)
{
	char c;
	PrevSym();
	while (gCharMap[(c = NextSym())] == DIGIT)
		*yytext++ = c;
	*yytext = '\0';
}