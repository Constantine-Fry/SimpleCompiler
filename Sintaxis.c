/*
 *  Sintaxis.c
 *  SimpleCompiler
 *
 *  Created by Constantine Fry on 4/21/10.
 *  Copyright 2010 Home. All rights reserved.
 *
 */

#include "Sintaxis.h"

void stmt()
{
	switch (CurrToken) {
		case INT32 :
			mutch(INT32); 
			mutch(IDENTIFIER); 
			mutch(MOV_OP); 
			expr();
			mutch(COMM_POINT);
			break;
		default:
			printf("Syntaxes error\n");
			break;
	}
}

void expr(){
	term();
	switch (CurrToken) {
		case ADD_OP:
			mutch(ADD_OP);
			term();
			break;
		case SUB_OP:
			mutch(SUB_OP);
			term();
			break;
		default:
			break;
	}
}

void term(){
	factor();
	switch (CurrToken) {
		case MUL_OP:
			mutch(MUL_OP);
			factor();
			break;
		case DIV_OP:
			mutch(DIV_OP);
			break;
		default:
			break;
	}
}

void factor(){
	switch (CurrToken) {
		case NUMBER:
			mutch(NUMBER);
			break;
		case IDENTIFIER:
			mutch(IDENTIFIER);
			break;
		case LEFT_BRECKET:
			mutch(LEFT_BRECKET);
			expr();
			mutch(RIGHT_BRECKET);
			break;
		default:
			printf("Syntaxes error\n");
			break;
	}
}

void stmts(){
	if (EMPTY == CurrToken) {
		return;
	}
	else {
		stmt();
		stmts();
	}
}

void mutch(Token tok)
{
	if (CurrToken == tok) {
		CurrToken = lex();
	}
	else {
		printf("В строке %d пропущен %s\n", line, (char*)gResult);
	}

}
