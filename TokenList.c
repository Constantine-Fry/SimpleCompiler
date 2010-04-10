/*
 *  TokenList.c
 *  SimpleCompiler
 *
 *  Created by Constantine Fry on 4/9/10.
 *  Copyright 2010 Home. All rights reserved.
 *
 */

#include "TokenList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IdentifierTable.h"

char *gTokenToDisplay[] = { "break", "case", "continue", "do", "else", "for",
	"goto", "if", "int16", "int32", "switch", "while",
	
	"++","--","&","||","<=",">=","==","!=","*","-","/","+","=",";",":","id","num",0
};


void Append(Token num,void *lexeme)  
{  
    struct node *temp,*r;  
	
    temp=(struct node *)malloc(sizeof(struct node));  
    temp->ident = num;
	
	switch (num) {
		case NUMBER:
			temp->value = (char*) malloc(sizeof(lexeme));
			strcpy(temp->value,(const char*)lexeme);
			break;
		case IDENTIFIER:
			temp->value = lexeme;
			break;	
		default:
			break;
	}
	//temp->value = lexeme;
	
    // Copying the Head location into another node.  
    r=Head;  
	
    if (Head == NULL) // If List is empty we create First Node.  
    {  
		Head=temp;  
		Head->next =NULL;  
    }  
    else  
    {       // Traverse down to end of the list.   
		while(r->next != NULL)  
			r=r->next;  
		
		// Appending at the end of the list.  
		temp->next=NULL;  
		r->next =temp;    
    }  
} 

void Display()  
{  
    struct node *cur_ptr;  
    
    cur_ptr=Head;      
	
    if(cur_ptr==NULL)  
    {   
		printf("\nList is Empty");  
		return;  
    }
	
    //traverse the entire linked list   
	
    while(cur_ptr!=NULL)  
    {  
		switch (cur_ptr->ident) {
			case NUMBER:
				printf("<%s,%s> ",gTokenToDisplay[(int)cur_ptr->ident],(char*)cur_ptr->value);
				break;
			case IDENTIFIER:
				printf("<%s,%s> ",gTokenToDisplay[(int)cur_ptr->ident],((TypeVal*)cur_ptr->value)->identifier);
				break;	
			default:
				printf("<%s> ",gTokenToDisplay[(int)cur_ptr->ident]);
				break;
		}
		 
		cur_ptr=cur_ptr->next;  
    }  
    printf("\n");  
}  

int Count()  
{  
    struct node *cur_ptr;  
    int c=0;  
	
    cur_ptr=Head;  
	
    while(cur_ptr!=NULL)  
    {  
		cur_ptr=cur_ptr->next;  
		c++;  
    }  
    return(c);  
}

void Flush()
{
	struct node *temp;  
	while( Head!=NULL)  
	{  
        temp = Head->next;
		if (NUMBER == Head->ident) {
			free(Head->value);
		}
        free(Head);  
        Head=temp;  
	}
	printf("list was flush\n");
}

