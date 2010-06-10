/*
 *  IdentifierTable.h
 *  SimpleCompiler
 *
 *  Created by Constantine Fry on 4/10/10.
 *  Copyright 2010 Home. All rights reserved.
 *
 */
typedef enum type_{
	NULLTYPE,
	INT16_,
	INT32_,
	LABEL,
}Type;

typedef struct TypeVal TypeVal;
struct TypeVal 
{  
	char* identifier;
	Type type;
	struct TypeVal *next;
	int isUse;
}; 

int Lookup(char *identifier,int create, Type type);
void DisplayIdTable();
int CountIdTable();
void FlushIdTable();
TypeVal* getStruct(int num);
