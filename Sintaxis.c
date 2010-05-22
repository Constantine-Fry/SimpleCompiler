/*
 *  Sintaxis.c
 *  SimpleCompiler
 *
 *  Created by Constantine Fry on 4/21/10.
 *  Copyright 2010 Home. All rights reserved.
 *
 */

#include "Sintaxis.h"
#include "NodeTable.h"


int stmts(){
	if (EMPTY == CurrToken) {
		return AddLeaf(EMPTY, 0);
		return;
	}
	if (RIGHT_FIG_BRECKET == CurrToken) {
		return;
	}
	else {
		int stmtNode = stmt();
		int stmtsNode = stmts();
		return AddNode(STMT, stmtNode, stmtsNode);
	}
}

int stmt()
{
	switch (CurrToken) {
		case INT32:
			mutch(INT32); 
			Token tokL = mutch(IDENTIFIER);
			int idNum = Lookup(gResult, 1, INT32);
			int nodeL = AddLeaf(tokL, idNum);
			if(CurrToken == MOV_OP){
				Token tok = mutch(MOV_OP); 
				int nodeR = boool();
				mutch(COMM_POINT);
				return AddNode(tok, nodeL,nodeR);
			}
			mutch(COMM_POINT);
			int nodeR = AddLeaf(NUMBER, 0);
			return AddNode(MOV_OP, nodeL, nodeR);
			break;
		case INT16:
			mutch(INT16); 
			Token tokL = mutch(IDENTIFIER);
			int idNum = Lookup(gResult, 1, INT16);
			int nodeL = AddLeaf(tokL, idNum);
			if(CurrToken == MOV_OP){
				Token tok = mutch(MOV_OP); 
				int nodeR = boool();
				mutch(COMM_POINT);
				return AddNode(tok, nodeL,nodeR);
			}
			mutch(COMM_POINT);
			int nodeR = AddLeaf(NUMBER, 0);
			return AddNode(MOV_OP, nodeL, nodeR);
			break;
			
		case DO:
			mutch(DO);
			int nodeL = stmt(); 
			mutch(WHILE);
			mutch(LEFT_BRECKET);
			int nodeR = boool();
			mutch(RIGHT_BRECKET);
			mutch(COMM_POINT);
			return AddNode(DO, nodeL, nodeR);
			break;
			
		case IF:
			mutch(IF); 
			mutch(LEFT_BRECKET);
			int nodeL = boool();
			mutch(RIGHT_BRECKET);
			int nodeR = stmt();
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
			Token tok =  mutch(IDENTIFIER);
			int idNode = AddLeaf(IDENTIFIER, gResult);
			tok = mutch(MOV_OP);
			int exprNode = boool();
			mutch(COMM_POINT);
			return AddNode(tok, idNode, nodeNum);
			break;

		default:
			printf("Syntaxes error\n");
			break;
	}
}

int expr(){
	int NodeL = term();
	switch (CurrToken) {
		case ADD_OP:
			Token tok = mutch(ADD_OP);
			int nodeR = term();
			return AddNode(tok, nodeL, nodeR);
			break;
		case SUB_OP:
			Token tok = mutch(SUB_OP);
			int nodeR = term();
			return AddNode(tok, nodeL, nodeR);
			break;
		default:
			break;
	}
	return NodeL;
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

int factor(){
	switch (CurrToken) {
		case NUMBER:
			Token tok = mutch(NUMBER);
			return AddLeaf(tok, gResult);
			break;
		case IDENTIFIER:
			Token tok = mutch(IDENTIFIER);
			return AddLeaf(tok, gResult);
			break;
		case LEFT_BRECKET:
			mutch(LEFT_BRECKET);
			int a = boool();
			mutch(RIGHT_BRECKET);
			return a;
			break;
		default:
			//printf("Syntaxes error\n");
			break;
	}
}


Token mutch(Token tok)
{
	Token temp = CurrToken;
	if (CurrToken == tok) {
		CurrToken = lex();
		return temp;
	}
	else {
		printf("В строке %d пропущен %s\n", line, (char*)gResult);
	}
	
}

int boool(){
	int nodeL = join();
	switch (CurrToken) {
		case OR_OP:
			Token tok = mutch(OR_OP);
			int nodeR = join();
			return AddNode(tok, nodeL, nodeR);
			break;
		default:
			break;
	}
	return nodeL;
}

int join(){
	int NodeL = equality();
	switch (CurrToken) {
		case AND_OP:
			Token tok = mutch(AND_OP);
			int nodeR = equality();
			return AddNode(tok, nodeL, nodeR);
			break;
		default:
			break;
	}
	return NodeL;
}

int equality(){
	int NodeL = rel();
	switch (CurrToken) {
		case EQ_OP:
			Token tok = mutch(EQ_OP);
			int nodeR = rel();
			return AddNode(tok, nodeL, nodeR);
			break;
		case NE_OP:
			Token tok = mutch(NE_OP);
			int nodeR = rel();
			return AddNode(tok, nodeL, nodeR);
			break;

		default:
			break;
	}
	return NodeL;
}

int rel(){
	int NodeL = expr();
	switch (CurrToken) {
		case LES_OP:
			Token tok = mutch(LES_OP);
			int nodeR = expr();
			return AddNode(tok, nodeL, nodeR);
			break;
			
		case GREAT_OP:
			Token tok = mutch(GREAT_OP);
			int nodeR = expr();
			return AddNode(tok, nodeL, nodeR);
			break;
			
		case LE_OP:
			Token tok = mutch(LE_OP);
			int nodeR = expr();
			return AddNode(tok, nodeL, nodeR);
			break;
			
		case GE_OP:
			Token tok = mutch(GE_OP);
			int nodeR = expr();
			return AddNode(tok, nodeL, nodeR);
			break;

		default:
			break;
	}
	return NodeL;
}

int unary(){
	int NodeL = factor();
	switch (CurrToken) {
		case NOT_OP :
			Token tok = mutch(NOT_OP);
			int nodeR = factor();
			return AddNode(tok, nodeL, nodeR);
			break;
			
		case SUB_OP:
			Token tok = mutch(SUB_OP);
			int nodeR = factor();
			return AddNode(tok, nodeL, nodeR);
			break;
		default:
			break;
	}
	return NodeL;
}

