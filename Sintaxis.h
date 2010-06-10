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
#include "NodeTable.h"

NodeInt stmt();
NodeInt stmts();
NodeInt expr();
Token mutch(Token tok);
NodeInt boool();
NodeInt term();
NodeInt unary();
NodeInt join();
NodeInt rel();
NodeInt equality();


#endif 