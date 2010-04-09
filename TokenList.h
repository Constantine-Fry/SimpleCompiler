/*
 *  TokenList.h
 *  SimpleCompiler
 *
 *  Created by Constantine Fry on 4/9/10.
 *  Copyright 2010 Home. All rights reserved.
 *
 */
struct node  
{  
	 char* value;
	int ident;
	struct node *next;  
}*Head; 

void Append(int ident,unsigned char *lexeme);
void Display();
int Count();
void Flush();