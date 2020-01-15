/* Signatures for the RNGs

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

#ifndef __rng_t_h__
#define __rng_t_h__

#include <stdint.h>

/*
	Prototype for an RNG returning a 32 bits integer.
 */
typedef uint32_t (*fpngl_irng32fun_t)(void*);

/*
	Prototype for an RNG returning a 64 bits integer.
 */
typedef uint64_t (*fpngl_irng64fun_t)(void*);

/*
	Type for defining a generic RNG returning a 32 bits integer.
 */
typedef struct {
	void* state; // State of the RNG
	fpngl_irng32fun_t next; // Function returning the next random integer
} fpngl_irng32_t;

/*
	Type for defining a generic RNG returning a 64 bits integer.
 */
typedef struct {
	void* state; // State of the RNG
	fpngl_irng64fun_t next; // Function returning the next random integer
} fpngl_irng64_t;

#endif // __rng_t_h__
