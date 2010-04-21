/*
 *  Lex.h
 *  SimpleCompiler
 *
 *  Created by Constantine Fry on 4/21/10.
 *  Copyright 2010 Home. All rights reserved.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _LEX_H
#define    _LEX_H

//#include "lexems.h"
#include "IdentifierTable.h"
#include "TokenList.h"

int GetNumber(unsigned char** num);
int GetLexemeType(unsigned  char* lexeme);
void SkipComment(unsigned char** comments);
int GetCodeOperation(unsigned char** operation);
int GetString(unsigned char** str);
int lex(void);

#define LEXSIZ	31	/* size of lexeme/identifier;
					 only first 31 characters are considered */


/* char llbuf[BUFSIZ];	*/
unsigned char lllexeme[LEXSIZ+1];	/* +1 for '\0' */
unsigned char *yytext;	/* pointer to lllexeme */
unsigned char* gSourceTxt;
unsigned char* gPointToSourceTxt;

Token CurrToken;
int line;

void* gResult;

#endif 