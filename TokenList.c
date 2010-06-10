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


void flush(struct node* aNode);

char *gTokenToDisplay[] = { "break", "case", "continue", "do", "else", "for",
	"goto", "if", "int16", "int32", "switch", "while", "write","read",
	
	"++","--","&","||","<=",">=","==","!=","*","-","/","+","=",";",":","id","num",0
};
/*

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
*/
void Display()  
{  
//    struct node *cur_ptr;  
//    
//    cur_ptr=Head;      
//	
//    if(cur_ptr==NULL)  
//    {   
//		printf("\nList is Empty");  
//		return;  
//    }
//	
//    //traverse the entire linked list   
//	
//    while(cur_ptr!=NULL)  
//    {  
//		switch (cur_ptr->ident) {
//			case NUMBER:
//				printf("<%s,%s> ",gTokenToDisplay[(int)cur_ptr->ident],(char*)cur_ptr->value);
//				break;
//			case IDENTIFIER:
//				printf("<%s,%s> ",gTokenToDisplay[(int)cur_ptr->ident],((TypeVal*)cur_ptr->value)->identifier);
//				break;	
//			default:
//				printf("<%s> ",gTokenToDisplay[(int)cur_ptr->ident]);
//				break;
//		}
//		 
//		cur_ptr=cur_ptr->next;  
//    }  
//    printf("\n");  
}  


/*

void Flush(){
	flush(Head->left);
	flush(Head->right);
	free(Head->value);
	printf("tree was flush\n");
	return;
}

void flush(struct node* aNode)
{
	if (NULL != aNode) {
		flush(aNode->left);
		flush(aNode->right);
	}
	free(aNode->value);
}
*/
