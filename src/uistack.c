/* Implementation of a stack of 32 bits unsigned integers.

	Copyright 2019--2020 University of Nantes, France.

	This file is part of the FPNGlib library.

	The FPNGlib library is free software; you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by the 
	Free Software Foundation; either version 3 of the License, or (at your
	option) any later version.
	
	The FPNGlib library is distributed in the hope that it will be useful, but
	WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
	or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
	for more details.
	
	You should have received copies of the GNU General Public License and the
	GNU Lesser General Public License along with the FPNGlib Library.  If not,
	see https://www.gnu.org/licenses/. 	
	
 */

/*
	An fpngl_uistack_t stack is created with enough room for at most 
	DEFAULT_SIZE integers (16, by default). If
	more than 16 integers are pushed onto the stack, it grows by doubling its size
	(which incurs a deallocation and a reallocation as well as a copy of all the
	elements already in the stack).
 */

#include <global.h>
#include <stdlib.h>
#include <fpnglib/uistack.h>

// Initial size of the stack by default
const uint32_t DEFAULT_SIZE = 16;

const int32_t STACK_EMPTY = -1;

struct fpngl_uistack_t {
	uint32_t *T;
	int32_t top; // Index of the first position occupied (STACK_EMPTY for an empty stack)
	uint64_t size; // Maximum number of elements in the stack
};

fpngl_uistack_t *fpngl_uistack_new(void)
{
	fpngl_uistack_t *stack = malloc(sizeof(fpngl_uistack_t));
	assert(stack != NULL);

	// Allocating a stack sufficient for at most DEFAULT_SIZE elements by default
	stack->size = DEFAULT_SIZE;
	stack->T = calloc(stack->size,sizeof(uint32_t));
	assert(stack->T != NULL);
	stack->top = STACK_EMPTY;
	return stack;
}

void fpngl_uistack_push(fpngl_uistack_t *stack, uint32_t v)
{
	assert(stack != NULL);
	++stack->top;
	if (stack->top == stack->size) { // We must allocate a bigger stack?
		assert(stack->size < (1UL << 30));
		stack->T = realloc(stack->T,2*stack->size*sizeof(uint32_t));
		assert(stack->T != NULL);
		stack->size *= 2;
	}
	stack->T[stack->top] = v;
}


uint32_t fpngl_uistack_pop(fpngl_uistack_t *stack)
{
	assert(stack != NULL && stack->top != STACK_EMPTY);
	return stack->T[stack->top--];
}

bool fpngl_uistack_empty(fpngl_uistack_t *stack)
{
	assert(stack != NULL);
	return stack->top == STACK_EMPTY;
}

void fpngl_uistack_delete(fpngl_uistack_t *stack)
{
	assert(stack != NULL);
	free(stack->T);
}
