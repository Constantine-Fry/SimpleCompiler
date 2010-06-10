/*
 *  Sintaxis.c
 *  SimpleCompiler
 *
 *  Created by Constantine Fry on 4/21/10.
 *  Copyright 2010 Home. All rights reserved.
 *
 */

#include "Sintaxis.h"


void* lexeme;


NodeInt stmts(){
	if (EMPTY == CurrToken) {
		
		return AddLeaf(EMPTY, 0);
	}
	if (RIGHT_FIG_BRECKET == CurrToken) {
		return 1;
	}
	else {
		NodeInt stmtNode = stmt();
		if (stmtNode == 0) {
			return 0;
		}
		NodeInt stmtsNode = stmts();
		return AddNode(STMTS, stmtNode, 0,stmtsNode);
	}
}

NodeInt stmt()
{
	switch (CurrToken) {
		case INT32:{
			mutch(INT32); 
			Token tokL = mutch(IDENTIFIER);
			int idNum = Lookup(lexeme, 1, INT32);
			NodeInt nodeL = AddLeaf(tokL, idNum);
			if(CurrToken == MOV_OP){
				Token tok = mutch(MOV_OP); 
				NodeInt nodeR = boool();

					mutch(COMM_POINT);

				return AddNode(tok, nodeL,0,nodeR);
			}
			mutch(COMM_POINT);
			NodeInt nodeR = AddLeaf(NUMBER, 0);
			return AddNode(MOV_OP, nodeL, 0,nodeR);
			break;
		}
		case INT16:{
			mutch(INT16); 
			Token tokL = mutch(IDENTIFIER);
			int idNum = Lookup(lexeme, 1, INT16);
			NodeInt nodeL = AddLeaf(tokL, idNum);
			if(CurrToken == MOV_OP){
				Token tok = mutch(MOV_OP); 
				NodeInt nodeR = boool();
				mutch(COMM_POINT);
				return AddNode(tok, nodeL,0,nodeR);
			}
			mutch(COMM_POINT);
			NodeInt nodeR = AddLeaf(NUMBER, 0);
			return AddNode(MOV_OP, nodeL, 0,nodeR);
			break;
		}
			
		case DO:{
			mutch(DO);
			NodeInt nodeL = stmt(); 
			mutch(WHILE);
			mutch(LEFT_BRECKET);
			NodeInt nodeR = boool();
			mutch(RIGHT_BRECKET);
			mutch(COMM_POINT);
			return AddNode(DO, nodeL, 0,nodeR);
			break;
		}
			
		case IF:{
			Token tok = mutch(IF); 
			mutch(LEFT_BRECKET);
			NodeInt nodeL = boool();
			mutch(RIGHT_BRECKET);
			NodeInt nodeR = stmt();
			NodeInt nodeM = 0;
			if(CurrToken == ELSE){
				tok = mutch(ELSE);
				nodeM = stmt();
			}
			return AddNode(tok, nodeL, nodeM, nodeR);
			break;
		}
			
		case LEFT_FIG_BRECKET:{
			mutch(LEFT_FIG_BRECKET);
			NodeInt node = stmts();
			mutch(RIGHT_FIG_BRECKET);
			return AddNode(STMT, node, 0, 0);
			break;
		}
			
		case IDENTIFIER:{
			Token tok =  mutch(IDENTIFIER);

			
			if(CurrToken == MOV_OP){
				int idNum = Lookup(lexeme,0,0);
				if (idNum < 0){
					printf("Syntax error:В строке %d использована не объявленая переменная \n",line);
					return 0;
				}
				NodeInt idLeaf = AddLeaf(IDENTIFIER, idNum);
				
				tok = mutch(MOV_OP);
				NodeInt nodeR = boool();
				mutch(COMM_POINT);
				return AddNode(tok, idLeaf, 0,nodeR);
			}
			if(CurrToken == LEFT_BRECKET){
				int idNum = Lookup(lexeme,1,0);
				if (idNum < 0){
					printf("Syntax error:В строке %d использована не объявленая переменная \n",line);
					return 0;
				}
				NodeInt idLeaf = AddLeaf(IDENTIFIER, idNum);
				
				mutch(LEFT_BRECKET);
				NodeInt nodeR =boool();
				mutch(RIGHT_BRECKET);
				mutch(COMM_POINT);
				return AddNode(FUNCTION, idLeaf, 0, nodeR);
			}
			break;
		}
			
		case CONTINUE:{
			return AddNode(CONTINUE, 0, 0, 0);
		}
			
		case BREAK:{
			return AddNode(BREAK, 0, 0, 0);
		}
			
			
		default:
			printf("Syntaxes error\n");
			return 0;
			break;
	}
}

NodeInt expr(){
	NodeInt nodeL = term();
	switch (CurrToken) {
		case ADD_OP:{
			Token tok = mutch(ADD_OP);
			NodeInt nodeR = expr();
			return AddNode(tok, nodeL, 0,nodeR);
			break;
		}
		case SUB_OP:{
			Token tok = mutch(SUB_OP);
			NodeInt nodeR = expr();
			return AddNode(tok, nodeL, 0,nodeR);
			break;
		}
		default:
			break;
	}
	return nodeL;
}

NodeInt term(){
	NodeInt nodeL = unary();
	switch (CurrToken) {
		case MUL_OP:{
			Token tok = mutch(MUL_OP);
			NodeInt nodeR = term();
			return AddNode(tok, nodeL, 0,nodeR);
			break;
		}
		case DIV_OP:{
			Token tok = mutch(DIV_OP);
			NodeInt nodeR = term();
			return AddNode(tok, nodeL, 0,nodeR);
			break;
		}
		default:
			break;
	}
	return nodeL;
}

NodeInt factor(){
	switch (CurrToken) {
		case NUMBER:{
			Token tok = mutch(NUMBER);
			return AddLeaf(tok, atoi(lexeme));
			break;
		}
		case IDENTIFIER:{
			mutch(IDENTIFIER);
			if(CurrToken == LEFT_BRECKET){
				int idNum = Lookup(lexeme,1,0);
				if (idNum < 0){
					printf("Syntax error:В строке %d использована не объявленая переменная \n",line);
					return 0;
				}
				NodeInt idLeaf = AddLeaf(IDENTIFIER, idNum);
				
				//mutch(LEFT_BRECKET);
				NodeInt nodeR =boool();
				//mutch(RIGHT_BRECKET);

				return AddNode(FUNCTION, idLeaf, 0, nodeR);
			}else {
				int idNum = Lookup(lexeme,0,0);
				if (idNum < 0){
					printf("Syntax error:В строке %d использована не объявленая переменная \n",line);
					return 0;
				}
				return AddLeaf(IDENTIFIER, idNum);
			}

			break;
		}


		case LEFT_BRECKET:{
			mutch(LEFT_BRECKET);
			if (RIGHT_BRECKET == CurrToken) {
				mutch(RIGHT_BRECKET);
				return	AddLeaf(EMPTY, 0);
			}
			NodeInt a = boool();
			mutch(RIGHT_BRECKET);
			return a;
			break;
		}
		default:
			//printf("Syntaxes error\n");
			break;
	}
	return -1;
}


Token mutch(Token tok)
{
	Token temp = CurrToken;
	if (CurrToken == tok) {
		lexeme = gResult;
		CurrToken = lex();
		return temp;
	}
	
	printf("Syntax error: В строке %d пропущен %s\n", line, (char*)lexeme);
	return -1;
}

NodeInt boool(){
	NodeInt nodeL = join();
	switch (CurrToken) {
		case OR_OP:{
			Token tok = mutch(OR_OP);
			NodeInt nodeR = join();
			return AddNode(tok, nodeL, 0,nodeR);
			break;
		}
		default:
			break;
	}
	return nodeL;
}

NodeInt join(){
	int nodeL = equality();
	switch (CurrToken) {
		case AND_OP:{
			Token tok = mutch(AND_OP);
			NodeInt nodeR = equality();
			return AddNode(tok, nodeL, 0,nodeR);
			break;
		}
		default:
			break;
	}
	return nodeL;
}

NodeInt equality(){
	NodeInt nodeL = rel();
	switch (CurrToken) {
		case EQ_OP:{
			Token tok = mutch(EQ_OP);
			NodeInt nodeR = rel();
			return AddNode(tok, nodeL, 0,nodeR);
			break;
		}
		case NE_OP:{
			Token tok = mutch(NE_OP);
			NodeInt nodeR = rel();
			return AddNode(tok, nodeL,0, nodeR);
			break;
		}
		default:
			break;
	}
	return nodeL;
}

NodeInt rel(){
	NodeInt nodeL = expr();
	switch (CurrToken) {
		case LES_OP:{
			Token tok = mutch(LES_OP);
			NodeInt nodeR = expr();
			return AddNode(tok, nodeL, 0,nodeR);
			break;
		}
			
		case GREAT_OP:{
			Token tok = mutch(GREAT_OP);
			NodeInt nodeR = expr();
			return AddNode(tok, nodeL, 0,nodeR);
			break;
		}
			
		case LE_OP:{
			Token tok = mutch(LE_OP);
			NodeInt nodeR = expr();
			return AddNode(tok, nodeL, 0,nodeR);
			break;
		}
			
		case GE_OP:{
			Token tok = mutch(GE_OP);
			NodeInt nodeR = expr();
			return AddNode(tok, nodeL, 0,nodeR);
			break;
		}
		default:
			break;
	}
	return nodeL;
}

NodeInt unary(){
	NodeInt nodeL = factor();
	switch (CurrToken) {
		case NOT_OP :{
			Token tok = mutch(NOT_OP);
			NodeInt nodeR = factor();
			return AddNode(tok, nodeL,0, nodeR);
			break;
		}
			
		case SUB_OP:{
			Token tok = mutch(SUB_OP);
			NodeInt nodeR = factor();
			return AddNode(tok, nodeL, 0,nodeR);
			break;
		}
			
		default:
			break;
	}
	return nodeL;
}

