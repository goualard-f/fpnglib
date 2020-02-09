/* Stack of 32 bits unsigned integers.

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

#ifndef __fpngl_uistack_h__
#define __fpngl_uistack_h__

#include <fpnglib/fpngl_config.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct fpngl_uistack_t fpngl_uistack_t;

	/*
		Create a new stack of 32 bits unsigned ints
		@return NULL if the stack could not be allocated

		An fpngl_uistack_t cannot contain more than 2^30 integers
	*/
	fpngl_uistack_t *fpngl_uistack_new(void);

	// Push the value  `v` on top of the stack `stack`.
	void fpngl_uistack_push(fpngl_uistack_t *stack, uint32_t v);

	// Remove the top element of `stack` and return it
	// Shall not be called on an empty stack
	uint32_t fpngl_uistack_pop(fpngl_uistack_t *stack);

	// Return `true` if `stack` has no element and `false` otherwise
	bool fpngl_uistack_empty(fpngl_uistack_t *stack);

	// Delete a stack
	void fpngl_uistack_delete(fpngl_uistack_t *stack);
	
#ifdef __cplusplus
}
#endif

#endif // __fpngl_uistack_h__
