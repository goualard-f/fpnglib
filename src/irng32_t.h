/* Encapsulation of an RNG producing 32 bits random integers.

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

#ifndef __fpngl_irng32_t_h__
#define __fpngl_irng32_t_h__

#include <fpnglib/fpngl_config.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

	// Opaque type for defining a generic RNG returning a 32 bits integer
	typedef struct fpngl_irng32_t fpngl_irng32_t;

	// Creation of an RNG that can compute 32 bits random integers
	fpngl_irng32_t *fpngl_irng32_new(uint32_t seed,
																	 const char *name,
																	 uint32_t min, uint32_t max,
																	 void *state,
																	 void* (*copy_state)(void*),
																	 uint32_t (*next32)(void*),
																	 uint64_t (*next64)(void*),
																	 uint32_t (*nextk)(void *state, uint32_t k),
																	 void (*next_array32)(void *state,
																												uint32_t *T, uint32_t n),
																	 void (*next_array64)(void *state,
																												uint64_t *T, uint32_t n),
																	 void (*delete)(void*));
	
	// Release all resources acquired by the pseudo-random generator 'rng'
	void fpngl_irng32_delete(fpngl_irng32_t* rng);
	
	// Return the next 32 bits pseudo-random number
	uint32_t fpngl_irng32_next32(fpngl_irng32_t *rng);

	// Return the next 64 bits pseudo-random number
	uint64_t fpngl_irng32_next64(fpngl_irng32_t *rng);
	
	// Return `k` leftmost bits from a random 32 bits integer.
	// The value of `k` must be in $[1,31]$. 
	uint32_t fpngl_irng32_nextk(fpngl_irng32_t *rng, uint32_t k);
	/*
		Fills array T with `n` 32 bits pseudo-random integers.
		The array must have been allocated beforehand.
		The value `n` must be greater than 0.
	*/
	void fpngl_irng32_array32(fpngl_irng32_t *rng, uint32_t *T, uint32_t n);
	/*
		Fills array T with `n` 64 bits pseudo-random integers.
		The array must have been allocated beforehand.
		The value `n` must be greater than 0.
	*/
	void fpngl_irng32_array64(fpngl_irng32_t *rng, uint64_t *T, uint32_t n);


	// Return the seed used by the RNG
	uint32_t fpngl_irng32_seed(fpngl_irng32_t *rng);
	
	// Return the name of the RNG used
	const char *fpngl_irng32_name(fpngl_irng32_t *rng);
	
	// Return the minimum value the RNG can return
	uint32_t fpngl_irng32_min(fpngl_irng32_t *rng);
	
	// Return the maximum value the RNG can return
	uint32_t fpngl_irng32_max(fpngl_irng32_t *rng);

	
#ifdef __cplusplus
}
#endif

#endif // __fpngl_irng32_t_h__
