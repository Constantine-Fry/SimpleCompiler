/*
 *  TokenList.h
 *  SimpleCompiler
 *
 *  Created by Constantine Fry on 4/9/10.
 *  Copyright 2010 Home. All rights reserved.
 *
 */
#ifndef _TOKENLIST_H
#define    _TOKENLIST_H

#include "lexems.h"


struct node  
{  
	void* value;
	Token  ident;
	struct node *next;  
}*Head; 

void Append(Token ident,void *lexeme);
void Display();
int Count();
void Flush();

#endif    /* _TOKENLIST_H */