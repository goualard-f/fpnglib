/*  Generation of a random double precision number by creating a 52 bits fractional
		part at random and setting the biased exponent to -1023 to get a float in
		`[1,2)`, then subtracting 1 from it to get a float in `[0,1)`.

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

#ifndef __fpngl_frng64_fog97_h__
#define __fpngl_frng64_fog97_h__

#include <fpnglib/fpngl_config.h>
#include <stdint.h>
#include <fpnglib/frng64_t.h>
#include <fpnglib/irng_t.h>

#ifdef __cplusplus
extern "C" {
#endif

	/*
		The method is described by [Saito and Matsumoto](https://link.springer.com/chapter/10.1007/978-3-642-04107-5_38) and linked to a work by 
		Agner Fog in 1997. They note that it can also be used to compute a number 
		in (0,1] by performing 2−𝑟 instead of 𝑟−1. 
		Though it is not said by Saito and Matsumoto, the subtraction 𝑟−1 is errorless 
		thanks to Sterbenz's theorem. The method is also discussed in 
		Numerical Recipes in FORTRAN 77, Second Ed., 1992, p. 275.

		The same method is used by [Nicolau Werneck ](https://xor0110.wordpress.com/2010/09/24/how-to-generate-floating-point-random-numbers-efficiently/)  to generate random floating-point numbers in [−1,1]
.	 */
	fpngl_frng64_t *fpngl_fog97(fpngl_irng_t *irng, uint64_t seed);
	
#ifdef __cplusplus
}
#endif

#endif // __fpngl_frng64_fog97_h__
