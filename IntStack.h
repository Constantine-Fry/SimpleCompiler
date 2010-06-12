/*
 *  StackForBreak.h
 *  SimpleCompiler
 *
 *  Created by Constantine Fry on 5/27/10.
 *  Copyright 2010 Home. All rights reserved.
 *
 */

#ifndef _STACK2_H_
#define _STACK2_H_

#include <stdlib.h>

/* Type of a stack node. */
struct node_struct
{
	long int data;
	struct node_struct *next;
};

/* Type of a stack object. */
typedef struct node_struct *int_stack;

/* Initialize a stack object. */
void int_stack_init(int_stack *s);

/* Push the integer val onto the stack. */
long int int_stack_push(int_stack *s, long int val);

/* Pop the top integer off the stack.  Return success. */
long int int_stack_pop(int_stack *s, long int *val);

/* Return the top item of stack s, if any, else 0. */
int int_stack_top(const int_stack *s);

/* Tell if the stack is empty. */
int int_stack_empty(const int_stack *s);

/* Destroy the stack object denoted by s.  This frees any dynamically-allocated
 memory associated with the stack. */
void int_stack_tini(int_stack *s);

/* Return the total amount of dynamically-allocated memory
 currently in use by all int_stacks. */
size_t int_stack_mem_usage(void);

#endif
