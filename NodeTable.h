/*
 *  NodeTable.h
 *  SimpleCompiler
 *
 *  Created by Constantine Fry on 5/22/10.
 *  Copyright 2010 Home. All rights reserved.
 *
 */
#include "lexems.h"
#include <stdio.h>

typedef struct Node Node;
struct Node  
{  
	int value;
	Token  ident;
	int left;
	int right;
	int middle;
}; 

typedef unsigned int NodeInt;

NodeInt AddNode(Token op, NodeInt left , NodeInt middle,NodeInt right);
NodeInt AddLeaf(Token op, NodeInt value);
void LogCode();
void printNodes(NodeInt num);
Token gen(NodeInt num, int reg);
void SaveCode(FILE* file);