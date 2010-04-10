#define LEXSIZ	31	/* size of lexeme/identifier;
only first 31 characters are considered */


int GetNumber(unsigned char** num);
int GetLexemeType(unsigned  char* lexeme);
void SkipComment(unsigned char** comments);
int GetCodeOperation(unsigned char** operation);
int GetString(unsigned char** str);
int lex(void);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
#include "lexems.h"
#include "IdentifierTable.h"
#include "TokenList.h"

/* char llbuf[BUFSIZ];	*/
unsigned char lllexeme[LEXSIZ+1];	/* +1 for '\0' */
unsigned char *yytext;	/* pointer to lllexeme */
unsigned char* gSourceTxt;
unsigned char* gPointToSourceTxt;

//Ключевые слова
char *gKeywords[] = { "break", "case", "continue", "do", "else", "for",
	"goto", "if", "int16", "int32", "switch", "while", 0
};


void* gResult;


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
    Token id;
	while (1) {
		id = (Token)lex();
		if (-1 == id) {
			break;
		}
		Append(id,gResult);
		
		//printf("value = %s, token = %d\n", (char*)gResult, id);
	}
	Display();
	DisplayIdTable();
	Flush();
	FlushIdTable();
	free(gSourceTxt);
	printf("\nEND\n");
    return 0;
}

int lex(void)
{
	yytext = lllexeme;
	while (1) {
		switch (gCharMap[*gPointToSourceTxt]) {
			case LETTER:
				return GetString(&gPointToSourceTxt);
				break;
				
			case DIGIT:
				return GetNumber(&gPointToSourceTxt);
				break;
				
			case ETX://конец текста
				return -1;
				break;
				
			case OTHER:
				if (gPointToSourceTxt[0] == '/' &&
					gPointToSourceTxt[1] == '*') {
					SkipComment(&gPointToSourceTxt);
					break;
				}
				return GetCodeOperation(&gPointToSourceTxt);
				break;
				
			default:
				break;
		}
		gPointToSourceTxt++;
	}
}

void SkipComment(unsigned char** comments)
{
	char sym1, sym2;
	sym2 = *((*comments)++);
	while (1)
	{
		sym1 = sym2;
		if (sym1 == EOF)
			break;
		sym2 = *((*comments)++);
		if ((sym1 == '*') && (sym2 == '/'))
		{
			(*comments)--;
			break;
		}           
	}
}

int GetString(unsigned char** str)
{
	*yytext++ = **str;
	while (*(++(*str)) && (gCharMap[**str] == LETTER || 
									  gCharMap[**str] == DIGIT))
		*yytext++ = **str;
	
	*yytext = '\0';		/* identifier < 32 characters */
	yytext[LEXSIZ] = '\0';	/* idenfier > 32 characters */
	
	Token tok = GetLexemeType(lllexeme);
	if (IDENTIFIER == tok) {
		gResult = Lookup((char*)lllexeme,1,tok);
	}else {
		gResult = lllexeme;
	}
	return tok;
}

int GetCodeOperation(unsigned char** operation)
{
	gResult = NULL;
	unsigned char *pointToSourceTxt = *operation;
	if (pointToSourceTxt[0] == '>' &&
		pointToSourceTxt[1] == '=') {
		//>=
		(*operation)++;
		return GE_OP;
	}
	if (pointToSourceTxt[0] == '<' &&
		pointToSourceTxt[1] == '=') {
		//<=
		(*operation)++;
		return LE_OP;
	}
	if (pointToSourceTxt[0] == '!' &&
		pointToSourceTxt[1] == '=') {
		//!=
		(*operation)++;
		return NE_OP;
	}
	if (pointToSourceTxt[0] == '+' &&
		pointToSourceTxt[1] == '+') {
		//++
		(*operation)++;
		return INC_OP;
	}
	
	if (pointToSourceTxt[0] == '-' &&
		pointToSourceTxt[1] == '-') {
		//--
		(*operation)++;
		return DEC_OP;
	}
	
	if (pointToSourceTxt[0] == '-') {
		// -
		(*operation)++;
		return SUB_OP;
	}
	if (pointToSourceTxt[0] == '+') {
		// +
		(*operation)++;
		return ADD_OP;
	}
	if (pointToSourceTxt[0] == '*') {
		// *
		(*operation)++;
		return MUL_OP;
	}
	if (pointToSourceTxt[0] == '/') {
		// /
		(*operation)++;
		return DIV_OP;
	}
	if (pointToSourceTxt[0] == '=') {
		// =
		(*operation)++;
		return MOV_OP;
	}
	if (pointToSourceTxt[0] == ';') {
		// ;
		(*operation)++;
		return COMM_POINT;
	}
	if (pointToSourceTxt[0] == ':') {
		// ;
		(*operation)++;
		return DOUBLE_POINT;
	}
	
	return -2;
}

int GetLexemeType(unsigned char* lexeme)
{
	int i;
	for (i = 0; gKeywords[i] != '\0'; i++)
		if (strcmp(gKeywords[i], (const char*)lexeme) == 0)
			return i;//потому что нумерация в массиве gKeywords совпадает с нумерацией Token
	return IDENTIFIER;
}

int GetNumber(unsigned char** num)
{
	//char c;
	(*num)--;
	while (gCharMap[ *(++(*num))] == DIGIT)
		*yytext++ = **num;
	*yytext = '\0';
	gResult = lllexeme;
	return NUMBER;
}
