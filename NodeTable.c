/*
 *  NodeTable.c
 *  SimpleCompiler
 *
 *  Created by Constantine Fry on 5/22/10.
 *  Copyright 2010 Home. All rights reserved.
 *
 */

#include "NodeTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IdentifierTable.h"
#include "IntStack.h"

#define EAX (unsigned char*)"eax\0"
#define EBX (unsigned char*)"ebx\0"

char* registers[] = {"ebx\0","ecx\0",0};
char* small_registers[] = {"bx\0","cx\0",0};

char code[1000] = "GLOBAL start\nEXTERN write,read\nSEGMENT .text\n\nstart:\0";
char vars[300] = "\n\n\n	push 0\n	mov eax,1\n	int 80h\nSEGMENT .data\n\0";

#define ARR_SIZE 1
#define TEMP_VAR_SIZE 13
#define NHASH 10000000000

NodeInt hash(NodeInt a, NodeInt b, NodeInt c);
Node* nodetab[NHASH];

int Count = 0;


NodeInt AddNode(Token op, NodeInt left ,NodeInt middle,NodeInt right){
	NodeInt a = hash((NodeInt)op,left,right);
	NodeInt h = hash(a,0,0);
	if (0 == nodetab[h] ) {
		Count++;
		Node *node = (Node*)malloc(sizeof(Node));
		node->left = left;
		node->middle = middle;
		node->right = right;
		node->ident = op;
		node->value = -1;
		nodetab[h] = node;
	}
	return h;
}


NodeInt AddLeaf(Token op,NodeInt value){
	NodeInt h = hash((NodeInt)op,value,0);
	if (NULL == nodetab[h] ) {
		Count++;
		Node *node = (Node*)malloc(sizeof(Node));
		node->left = -1;
		node->right = -1;
		node->middle = -1;
		node->ident = op;
		node->value = value;
		nodetab[h] = node;
	}
	return h;
}
/*
 int Lookup(int value,Token op, int left , int right)  {  
 int h = Hash((int)op,left,right);
 if (0 != nodetab[h] ) {
 count++;
 Node *node = (Node*)malloc(sizeof(Node));
 node->left = left;
 node->right = right;
 node->ident = op;
 node->value = value;
 nodetab[h] = node;
 }
 return h;
 }
 */
NodeInt hash(NodeInt a,NodeInt b,NodeInt c){
	a -= b; a -= c; a ^= (c>>13);
	b -= c; b -= a; b ^= (a<<8); 
	c -= a; c -= b; c ^= (b>>13); 
	a -= b; a -= c; a ^= (c>>12);  
	b -= c; b -= a; b ^= (a<<16); 
	c -= a; c -= b; c ^= (b>>5); 
	a -= b; a -= c; a ^= (c>>3);  
	b -= c; b -= a; b ^= (a<<10); 
	c -= a; c -= b; c ^= (b>>15);
	if (NHASH < c) {
		printf("NodeTable: array is small fo me.\n,%ld > %ld\n",c,NHASH);
	}
	return c;
}


char *gTokenToDisplay1[] = { "break", "case", "continue", "do", "else", "for",
	"goto", "if", "int16", "int32", "switch", "while",
	
	"++","--","&","||","<",">","<=",">=","==","!=","*","-","/","+","=",";",":","id","num",0
};

int maxCount[256] ={0};
char g_temp[TEMP_VAR_SIZE];



void AddVar(char* str,Token type){
	strncat(vars,str,strlen(str));
	char * str1;
	if (INT32 == type) {
		str1 = "	DD 0\n\0";
	}else {
		str1 = "	DW 0\n\0";
	}
	
	strncat(vars,str1,strlen(str1));
}

char* GetRegister(int num,Token type){
	if (num > ARR_SIZE) {
		//char temp[TEMP_VAR_SIZE];
		char *temp = malloc(sizeof(char)*TEMP_VAR_SIZE);
		memset(temp,0,sizeof(char)*TEMP_VAR_SIZE);
		sprintf(temp,"t%d",num- ARR_SIZE);
		if (maxCount[ num-ARR_SIZE]==0 ) {
			maxCount[ num-ARR_SIZE]=1 ;
			AddVar(temp,type);
		}
		if (type == INT16) {
			sprintf(g_temp,"word [%s]",temp);
		}else{
			sprintf(g_temp,"[%s]",temp);
		}
		free(temp);
		return g_temp;
		
	}else {
		if(type != INT16){
			return registers[num];
		}else {
			return small_registers[num];
		}
		
		
	}
	
}

char* GetEAXByType(Token type){
	if(type != INT16){
		return "eax";
	}else {
		return "ax";
	}
}

char* GetESIByType(Token type){
	if(type != INT16){
		return "esi";
	}else {
		return "si";
	}
}

char *add= "add";
char *sub = "sub";
char* GetOpeation(Token type){
	if (type == SUB_OP) {
		return sub;
	}
	if (type == ADD_OP) {
		return add;
	}
	return NULL;
}

int result = 0;
int useFunction = 0;
Token gen(NodeInt num, int reg){
	switch (nodetab[num]->ident) {
		case MOV_OP:{
			Token ltype = gen(nodetab[num]->left,0);
			Token rtype = gen(nodetab[num]->right,0);
			if (ltype < rtype) {
				memset(code,0,sizeof(char)*1000);
				memset(vars,0,sizeof(char)*300);
				printf("Error:преобразование типов\n");
				result = -1;
				return -1;
			}
			TypeVal* id = getStruct(nodetab[nodetab[num]->left]->value);
			char *tempCom = malloc(sizeof(char)*23);
			sprintf(tempCom,"\n	mov [%s], %s",id->identifier,GetRegister(0,id->type));
			strncat(code,tempCom,strlen(tempCom));
			free(tempCom);
			return 1;
		}
			
		case NUMBER:{
			int number = nodetab[num]->value;
			char *tempCom = malloc(sizeof(char)*23);
			char *eax = GetEAXByType(INT16);
			sprintf(tempCom,"\n	xor eax,eax\n	mov %s, %d",eax,number);
			strncat(code,tempCom,strlen(tempCom));
			
			memset(tempCom,0,sizeof(char)*23);
			sprintf(tempCom,"\n	mov %s,eax",GetRegister(reg,INT32));
			strncat(code,tempCom,strlen(tempCom));
			free(tempCom);
			return INT16;
		}
			
		case IDENTIFIER:{
			TypeVal* id = getStruct(nodetab[num]->value);
			if (!id->isUse) {
				AddVar(id->identifier,id->type);
				id->isUse = 1;
			}else {
				char *tempCom = malloc(sizeof(char)*23);
				char *eax = GetEAXByType(id->type);
				sprintf(tempCom,"\n	xor eax,eax\n	mov %s,[%s]",eax ,id->identifier);
				strncat(code,tempCom,strlen(tempCom));
				
				memset(tempCom,0,sizeof(char)*23);
				sprintf(tempCom,"\n	mov %s,%s",GetRegister(reg,id->type) ,eax);
				strncat(code,tempCom,strlen(tempCom));
				free(tempCom);
			}
			return id->type;
		}
			
			
		case ADD_OP:
		case SUB_OP:{
			Token rtype =gen(nodetab[num]->right, (reg+1));
			Token ltype =gen(nodetab[num]->left, (reg+2));
			
			
			char *tempCom = malloc(sizeof(char)*23);
			char *eax = GetEAXByType(rtype);
			sprintf(tempCom,"\n	mov %s, %s" ,eax,GetRegister(reg+1,rtype));
			strncat(code,tempCom,strlen(tempCom));
			memset(tempCom,0,sizeof(char)*TEMP_VAR_SIZE);
			
			
			char *temp = malloc(sizeof(char)*TEMP_VAR_SIZE) ;
			//
			memcpy(temp,GetRegister(reg+2,rtype),sizeof(char)*TEMP_VAR_SIZE);
			//
			sprintf(tempCom,"\n	%s %s, %s",GetOpeation(nodetab[num]->ident),eax ,temp);
			strncat(code,tempCom,strlen(tempCom));
			//free(temp);
			Token resType = (ltype == INT32 || rtype == INT32) ? INT32 : INT16;
			memset(tempCom,0,sizeof(char)*23);
			eax = GetEAXByType(resType);
			sprintf(tempCom,"\n	mov %s, %s",GetRegister(reg,resType),eax);
			strncat(code,tempCom,strlen(tempCom));
			free(tempCom);
			return resType;	
		}
			
		case MUL_OP:{
			Token rtype =gen(nodetab[num]->right, (reg+1));
			Token ltype =gen(nodetab[num]->left, (reg+2));
			
			char *tempCom = malloc(sizeof(char)*23);
			char *eax = GetEAXByType(rtype);
			sprintf(tempCom,"\n	mov %s, %s" ,eax,GetRegister(reg+1,rtype));
			strncat(code,tempCom,strlen(tempCom));
			memset(tempCom,0,sizeof(char)*TEMP_VAR_SIZE);
			

			char *esi = GetESIByType(rtype);
			sprintf(tempCom,"\n	mov %s, %s" ,esi,GetRegister(reg+2,rtype));
			strncat(code,tempCom,strlen(tempCom));
			memset(tempCom,0,sizeof(char)*TEMP_VAR_SIZE);
			
			
			

			sprintf(tempCom,"\n	mul %s" ,esi);
			strncat(code,tempCom,strlen(tempCom));
			memset(tempCom,0,sizeof(char)*TEMP_VAR_SIZE);
			
			if (rtype == INT16) {
				sprintf(tempCom,"\n	mov di,dx\n		shl edi,16\n	mov di,ax\n" );
			}else {
				sprintf(tempCom,"\n mov	edi, eax" );
			}

			strncat(code,tempCom,strlen(tempCom));
			memset(tempCom,0,sizeof(char)*TEMP_VAR_SIZE);
			
			sprintf(tempCom,"\n	mov %s,edi",GetRegister(reg,INT32));
			strncat(code,tempCom,strlen(tempCom));
			free(tempCom);
			return INT32;
		}
			
			
			
			
		case FUNCTION:{
			Token type =  gen(nodetab[num]->right,reg+1);
			char *tempCom = malloc(sizeof(char)*23);
			char *temp = malloc(sizeof(char)*TEMP_VAR_SIZE) ;
			//
			memcpy(temp,GetRegister(reg+1,type),sizeof(char)*TEMP_VAR_SIZE);
			sprintf(tempCom,"\nxor ebx,ebx\n	mov %s,%s",GetRegister(reg, type),temp);
			strncat(code,tempCom,strlen(tempCom));
			
			memset(tempCom,0,sizeof(char)*23);
			TypeVal* id = getStruct(nodetab[nodetab[num]->left]->value);
			sprintf(tempCom,"\n	call %s",id->identifier);
			strncat(code,tempCom,strlen(tempCom));
			
			memset(tempCom,0,sizeof(char)*23);
			sprintf(tempCom,"\n	mov %s,eax",GetRegister(reg, INT32));
			strncat(code,tempCom,strlen(tempCom));
			free(tempCom);
			useFunction = 1;
			return 1;
		}
			
			
		case STMTS:{
			char * str = "\n;stmts:\0";
			strncat(code,str ,strlen(str)-1);
			gen(nodetab[num]->left,0);
			gen(nodetab[num]->right,0);
			return result;
		}
		case STMT:{
			return gen(nodetab[num]->left,-1);
		}
			
		case EMPTY:{
			return 1;
		}
		default:
			memset(code,0,sizeof(char)*1000);
			memset(vars,0,sizeof(char)*300);
			printf("Error : программа еще не готова\n");
			result = -1;
			return -1;
	}
}

void LogCode(){
	printf("%s\n%s",code,vars);
}

void SaveCode(FILE* file){
	fprintf(file,"%s\n%s",code,vars);
}

void printNodes(NodeInt num){
	switch (nodetab[num]->ident) {
			
		case IDENTIFIER:{
			TypeVal *str = getStruct(nodetab[num]->value);
			printf("(%s)%s", gTokenToDisplay1[str->type],str->identifier);
			return;
		}
			
		case NUMBER:
			printf("%d", nodetab[num]->value);
			return;
			
		case STMTS:
			printNodes(nodetab[num]->left);
			printNodes(nodetab[num]->right);
			return;
			
		case STMT:
			printNodes(nodetab[num]->left);
			//printNodes(nodetab[num]->right);
			return;
			
		case IF:
			printf("\nif (");
			printNodes(nodetab[num]->left);
			printf(")\n{\n");
			printNodes(nodetab[num]->right);
			printf("}\n");
			break;
		case ELSE:
			printf("\nif (");
			printNodes(nodetab[num]->left);
			printf(")\n{\n");
			printNodes(nodetab[num]->right);
			printf("}else{\n");
			printNodes(nodetab[num]->middle);
			printf("}\n");
			break;
			
		case DO:
			printf("\nDO{");
			printNodes(nodetab[num]->left);
			printf("\n}while(");
			printNodes(nodetab[num]->right);
			printf(")\n");
			break;
			
			
		case EMPTY:
			printf("\n");
			return;
			
		default:
			break;
	}
	if (nodetab[num]->ident >=INC_OP && nodetab[num]->ident<= NOT_OP) {
		printNodes(nodetab[num]->left);
		printf(" %s ",gTokenToDisplay1[nodetab[num]->ident]);
		printNodes(nodetab[num]->right);
		return;
	}
}
