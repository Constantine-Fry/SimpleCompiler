/*
 *  Sintaxis.h
 *  SimpleCompiler
 *
 *  Created by Constantine Fry on 4/21/10.
 *  Copyright 2010 Home. All rights reserved.
 *
 */

#ifndef _SIN_H
#define    _SIN_H

#include "Lex.h"

int stmt();
int stmts();
int expr();
Token mutch(Token tok);
int boool();
int term();
int unary();
int join();
int rel();
int equality();


#endif 