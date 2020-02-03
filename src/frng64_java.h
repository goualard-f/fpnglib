/* Computation of a double precision random number using the RNG
   in java.util.Random.

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

#ifndef __fpngl_frng64_java_h__
#define __fpngl_frng64_java_h__

#include <fpnglib/fpngl_config.h>
#include <fpnglib/frng64_t.h>

#ifdef __cplusplus
extern "C" {
#endif

	/*
		Computation of a random floating-point number in `[0,1)` by calling twice 
		the same LCG as `drand48()` and combining the two results.
		According to L'Ecuyer and Simard, this is the RNG from `java.util.Random`.
		See also: https://docs.oracle.com/javase/8/docs/api/java/util/Random.html

		@caution Calling fpngl_frng64_next_arrayf64() for this RNG creates on the heap a
		a temporary array twice the size of the one passed as an argument.
	 */
	fpngl_frng64_t *fpngl_java(uint64_t seed);

	
#ifdef __cplusplus
}
#endif

#endif // __fpngl_frng64_java_h__
