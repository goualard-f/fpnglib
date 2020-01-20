/* Encapsulation of an RNG able to produce 32 bits and 64 bits random integers.

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

#ifndef __irng_t_h__
#define __irng_t_h__

#include <fpnglib/fpngl_config.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
	
	typedef struct fpngl_irng_t fpngl_irng_t;

	/*
		Creating a RNG capable of computing 32 bits and 64 bits random integers.
		BEWARE: the seed is an uint64_t integer, even for RNGs that should take
		a 32 bits integer. This is up to the user to provide a correct value for
		each underlying RNG.
	 */	
	fpngl_irng_t *fpngl_new_irng(uint64_t seed,
															 const char *name,
															 uint64_t min, uint64_t max,
															 void *state,
															 uint32_t (*next32)(void *state),
															 uint64_t (*next64)(void *state),
															 uint64_t (*nextk)(void *state, uint32_t k),
															 void (*next_array32)(void *state,
																										uint32_t *T, uint32_t n),
															 void (*next_array64)(void *state,
																										uint64_t *T, uint32_t n),
															 void (*delete)(void*));
	
	// Releases all resources acquired by the pseudo-random generator 'rng'
	void fpngl_delete_irng(fpngl_irng_t* rng);
	
	// Return next 32 bits pseudo-random number
	uint32_t fpngl_irng_next32(fpngl_irng_t *rng);
	// Return next 64 bits pseudo-random number
	uint64_t fpngl_irng_next64(fpngl_irng_t *rng);
	/* Return k random bits. The value of `k` must be in [1,64]. 
		 Use preferentially fpngl_irng_next32() for k=32 and 
		 fpngl_irng_next64() for k=64.
	*/
	uint64_t fpngl_irng_nextk(fpngl_irng_t *rng, uint32_t k);
	/*
		Fills array T with `n` 32 bits pseudo-random integers.
		The array must have been allocated beforehand.
		The value `n` must be greater than 0.
	*/
	void fpngl_irng_array32(fpngl_irng_t *rng, uint32_t *T, uint32_t n);
	/*
		Fills array T with `n` 64 bits pseudo-random integers.
		The array must have been allocated beforehand.
		The value `n` must be greater than 0.
	*/
	void fpngl_irng_array64(fpngl_irng_t *rng, uint64_t *T, uint32_t n);
	
	// Return the seed used by the RNG
	uint64_t fpngl_irng_seed(fpngl_irng_t *rng);
	
	// Return the name of the RNG used
	const char *fpngl_irng_name(fpngl_irng_t *rng);
	
	// Return the minimum value the RNG can return
	uint64_t fpngl_irng_min(fpngl_irng_t *rng);
	
	// Return the maximum value the RNG can return
	uint64_t fpngl_irng_max(fpngl_irng_t *rng);
	
#ifdef __cplusplus
}
#endif

#endif // __irng_t_h__
