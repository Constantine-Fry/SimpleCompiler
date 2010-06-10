/*
 *  Lex.c
 *  SimpleCompiler
 *
 *  Created by Constantine Fry on 4/21/10.
 *  Copyright 2010 Home. All rights reserved.
 *
 */

#include "Lex.h"
line =1;
//Ключевые слова
char *gKeywords[] = { "break", "case", "continue", "do", "else", "for",
	"goto", "if", "int16", "int32", "switch", "while",0
};

int lex(void)
{
	yytext = lllexeme;
	while (1) {
		switch (gCharMap[*gPointToSourceTxt]) {
			case NEWLINE:
				++line;
				
				break;
				
			case LETTER:
				return GetString(&gPointToSourceTxt);
				break;
				
			case DIGIT:
				return GetNumber(&gPointToSourceTxt);
				break;
				
			case ETX://конец текста
				return EMPTY;
				break;
				
			case OTHER:
				if (gPointToSourceTxt[0] == '/' &&
					gPointToSourceTxt[1] == '*') {
					SkipComment(&gPointToSourceTxt);
					break;
				}
				
				if (gPointToSourceTxt[0] == '{') {
					++gPointToSourceTxt;
					return LEFT_FIG_BRECKET;
				}
				if (gPointToSourceTxt[0] == '}') {
					++gPointToSourceTxt;
					return RIGHT_FIG_BRECKET;
				}
				if (gPointToSourceTxt[0] == '(') {
					++gPointToSourceTxt;
					return LEFT_BRECKET;
				}
				if (gPointToSourceTxt[0] == ')') {
					++gPointToSourceTxt;
					return RIGHT_BRECKET;
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
//	if (IDENTIFIER == tok) {
//		gResult = Lookup((char*)lllexeme,1,tok);
//	}else {
//		gResult = lllexeme;
//	}
	gResult = lllexeme;
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
		(*operation)++;
		return GE_OP;
	}
	if (pointToSourceTxt[0] == '<' &&
		pointToSourceTxt[1] == '=') {
		//<=
		(*operation)++;
		(*operation)++;
		return LE_OP;
	}
	if (pointToSourceTxt[0] == '!' &&
		pointToSourceTxt[1] == '=') {
		//!=
		(*operation)++;
		(*operation)++;
		return NE_OP;
	}
	if (pointToSourceTxt[0] == '+' &&
		pointToSourceTxt[1] == '+') {
		//++
		(*operation)++;
		(*operation)++;
		return INC_OP;
	}
	
	if (pointToSourceTxt[0] == '-' &&
		pointToSourceTxt[1] == '-') {
		//--
		(*operation)++;
		(*operation)++;
		return DEC_OP;
	}
	if (pointToSourceTxt[0] == '=' &&
		pointToSourceTxt[1] == '=') {
		//--
		(*operation)++;
		(*operation)++;
		return EQ_OP;
	}
	
	if (pointToSourceTxt[0] == '<') {
		// ;
		(*operation)++;
		return LE_OP;
	}
	if (pointToSourceTxt[0] == '>') {
		// ;
		(*operation)++;
		return GREAT_OP;
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
	
	gResult = lllexeme;
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