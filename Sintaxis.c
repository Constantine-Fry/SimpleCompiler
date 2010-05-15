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
			if(CurrToken == MOV_OP){
				mutch(MOV_OP); 
				bool();
			}
			mutch(COMM_POINT);
			break;
		case INT16:
			mutch(INT16); 
			mutch(IDENTIFIER); 
			if(CurrToken == MOV_OP){
				mutch(MOV_OP); 
				bool();
			}
			mutch(COMM_POINT);
			break;
			
		case DO:
			mutch(DO); 
			stmt(); 
			mutch(WHILE);
			mutch(LEFT_BRECKET);
			bool();
			mutch(RIGHT_BRECKET);
			mutch(COMM_POINT);
			break;
			
		case IF:
			mutch(IF); 
			mutch(LEFT_BRECKET);
			bool();
			mutch(RIGHT_BRECKET);
			stmt();
			if(CurrToken == ELSE){
				mutch(ELSE);
				stmt();
			}
			mutch(COMM_POINT);
			break;
			
		case LEFT_FIG_BRECKET:
			mutch(LEFT_FIG_BRECKET);
			stmts();
			mutch(RIGHT_FIG_BRECKET);
			break;
			
		case IDENTIFIER:
			mutch(IDENTIFIER);
			mutch(MOV_OP);
			bool();
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
	unary();
	switch (CurrToken) {
		case MUL_OP:
			mutch(MUL_OP);
			unary();
			break;
		case DIV_OP:
			mutch(DIV_OP);
			unary();
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
			bool();
			mutch(RIGHT_BRECKET);
			break;
		default:
			//printf("Syntaxes error\n");
			break;
	}
}

void stmts(){
	if (EMPTY == CurrToken) {
		return;
	}
	if (RIGHT_FIG_BRECKET == CurrToken) {
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

void bool(){
	join();
	switch (CurrToken) {
		case OR_OP:
			mutch(OR_OP);
			join();
			break;
		default:
			break;
	}
}

void join(){
	equality();
	switch (CurrToken) {
		case AND_OP:
			mutch(AND_OP);
			equality();
			break;
		default:
			break;
	}
}

void equality(){
	rel();
	switch (CurrToken) {
		case EQ_OP:
			mutch(EQ_OP);
			rel();
			break;
		case NE_OP:
			mutch(NE_OP);
			rel();
			break;

		default:
			break;
	}
}

void rel(){
	expr();
	switch (CurrToken) {
		case LES_OP:
			mutch(LES_OP);
			expr();
			break;
			
		case GREAT_OP:
			mutch(GREAT_OP);
			expr();
			break;
			
		case LE_OP:
			mutch(LE_OP);
			expr();
			break;
			
		case GE_OP:
			mutch(GE_OP);
			expr();
			break;

		default:
			break;
	}
}

void unary(){
	factor();
	switch (CurrToken) {
		case NOT_OP :
			mutch(NOT_OP);
			factor();
			break;
			
		case SUB_OP:
			mutch(SUB_OP);
			factor();
			break;
		default:
			break;
	}
}

