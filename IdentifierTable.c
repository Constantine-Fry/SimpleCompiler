/*
 *  IdentifierTable.c
 *  SimpleCompiler
 *
 *  Created by Constantine Fry on 4/10/10.
 *  Copyright 2010 Home. All rights reserved.
 *
 */

#include "IdentifierTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NHASH 1000 
#define  MULTIPLIER 31 // для ASCII лучше всего подхдят два мноителя: 31 и 37

unsigned int Hash(char *str);
TypeVal* symtab[NHASH];

int count = 0;

int Lookup(char *identifier,int create, Type type)  
{  

	int h;
	TypeVal *sym;
	h = Hash(identifier);
	if (NULL == symtab[h] && !create) {

		return -33;
	}
//	for(sym = symtab[h];sym != NULL; sym = sym->next)
//		if (strcmp(identifier, sym->identifier) == 0) {
//			return sym;
//		}
	if (create) {
		count++;
		sym = (TypeVal*)malloc(sizeof(TypeVal));
		sym->identifier = (char*) malloc(sizeof(char)*strlen(identifier)-1);
		memset(sym->identifier,0,sizeof(char)*strlen(identifier)-1);
		strcpy(sym->identifier,(const char*)identifier);
		sym->type = type;
		sym->next = symtab[h];
		sym->isUse = 0;
		symtab[h] = sym;
	}
	return h;
}

TypeVal* getStruct(int num){
	return symtab[num];
}

unsigned int Hash(char *str){
	unsigned int h;
	unsigned char *p;
	h = 0;
	for (p = str; *p != '\0'; p++) {
		h = MULTIPLIER * h + *p;
	}
	return (h%NHASH);
}


void PrintTypeValList(TypeVal *sym)
{
	TypeVal *temp;
	printf("[");
	while(NULL != sym)  
	{  
		temp = sym->next;
		printf("(%s,%d)",sym->identifier,sym->type); 
		sym=temp;  
	}
	printf("]\n"); 
}

void DisplayIdTable()  
{  
	int i;
	for (i = 0; i < NHASH; i++)
		if (NULL != symtab[i]){
			printf("IDtable[%d]: ", i); 
			PrintTypeValList(symtab[i]);
		}
}  

int CountIdTable()  
{  
    return count;
}

void DeleteTypeValList(TypeVal *sym)
{
	TypeVal *temp;
	while(NULL != sym)  
	{  
		temp = sym->next;
		free(sym->identifier);
		free(sym);  
		sym=temp;  
	}
}

void FlushIdTable()
{
	int i;
	for (i = 0; i < NHASH; i++)
		if (NULL != symtab[i]) 
			DeleteTypeValList(symtab[i]);
	printf("IDTable was flush\n");
}
