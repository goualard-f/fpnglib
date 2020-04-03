/* Encapsulation of an RNG able to produce single precision floats

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

#ifndef __fpngl_frng32_t_h__
#define __fpngl_frng32_t_h__

#include <fpnglib/fpngl_config.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
	/* 
		 Opaque type encapsulating an RNG producing single precision 
		 floating-point numbers.
		 Only pointers to the structure can be manipulated by the user.
	*/
	typedef struct fpngl_frng32_t fpngl_frng32_t;

	/*
		Constructor for a single precision fp RNG.
		One must provide pointers to functions:
		* nextf32: function returning the next random floating-point number
		* next_arrayf32: function filling an array with `n` random single
		precision numbers.
		A pointer to the opaque internal state `state` of the underlying RNG
		must also be provided.
	 */
	fpngl_frng32_t *fpngl_frng32_new(const char *name,
																	 void *state,
																	 float min, float max,
																	 float (*nextf32)(void*),
																	 void (*next_arrayf32)(void *state,
																												 float *T, uint32_t n),
																	 void (*delete)(void*),
																	 uint32_t (*seed)(void*));
	
	// Reclaim memory used by the opaque representation of the RNG
	void fpngl_frng32_delete(fpngl_frng32_t *frng);

	// Return the next random double precision number computed with the RNG
	float fpngl_frng32_nextf32(fpngl_frng32_t *frng);

	/*
		Fill the array `T` with `n` random floating-point numbers.

		@caution Some FRNG may allocate a temporary array of `2n` uint32_t integers.
	*/
	void fpngl_frng32_next_arrayf32(fpngl_frng32_t *frng, float *T, uint32_t n);


	// Return the name of the FRNG
	const char* fpngl_frng32_name(fpngl_frng32_t *frng);

	// Return the minimum value of the domain in which floats are drawn
	float fpngl_frng32_min(fpngl_frng32_t *frng);
	// Return the maximum value of the domain in which floats are drawn
	float fpngl_frng32_max(fpngl_frng32_t *frng);
		
	// Return the seed used by the FRNG. May be `0` if the underlying IRNG
	// was initialized with an array and not a unique integer.
	uint32_t fpngl_frng32_seed(fpngl_frng32_t *frng);
	
#ifdef __cplusplus
}
#endif

#endif // __fpngl_frng32_t_h__
