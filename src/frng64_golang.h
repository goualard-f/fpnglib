/* Computation of a double precision random number using the RNG
   from the Go language.

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

#ifndef __fpngl_frng64_golang_h__
#define __fpngl_frng64_golang_h__

#include <fpnglib/fpngl_config.h>
#include <fpnglib/frng64_t.h>
#include <fpnglib/irng_t.h>

#ifdef __cplusplus
extern "C" {
#endif

	/*
		The method used in the Go language consists in generating a 63 bits 
		random integer and dividing the result by `2^{63}`.

		The authors state that, when the random integer is close to `2^{63}`, 
		the result after the division might be exactly equal to `1.0` while it should 
		always be less. As a consequence, they reject the result and draw another number 
		if the result is `1.0`.
		In effect, the only possible such case is when the integer drawn is `2^{63}-1`, 
		which needs to be rounded to `2^{63}` when converted to a double precision 
		floating-point number.

		*See*: [Go source](https://golang.org/src/math/rand/rand.go?s=5359:5391#L168)
		
		*/
	fpngl_frng64_t *fpngl_golang(fpngl_irng_t *irng, uint64_t seed);

	
#ifdef __cplusplus
}
#endif

#endif // __fpngl_frng64_golang_h__
