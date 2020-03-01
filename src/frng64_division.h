/* Implementation of double precision floating-point number generators
	 through division of a random integer by a constant integer.

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

#ifndef __fpngl_frng64_division_h__
#define __fpngl_frng64_division_h__

#include <fpnglib/fpngl_config.h>
#include <fpnglib/frng64_t.h>
#include <fpnglib/irng_t.h>

#ifdef __cplusplus
extern "C" {
#endif

	/*
		Generation of a random float by division of the result of an integer RNG `f`
		by a constant `c`.
		The FRNG created owns the IRNG passed as second parameter and is responsible
		for its destruction.
	*/
	fpngl_frng64_t *fpngl_bydivision_new(const char *name,
																					fpngl_irng_t *irng,
																					uint64_t denominator);

	/*
		Double precision floating-point generator used by MATLAB until MATLAB 5.

		Return a floating-point number in `[0,1)`.
	 */
	fpngl_frng64_t *fpngl_matlabp5(uint64_t seed);

	/*
    The POSIX drand48() function as implemented in FreeBSD. 
       Returns a floating-point number in ``[0,1)`` with only 48 bits of entropy.
    *Source*: [IEEE Std 1003.1-2017](http://pubs.opengroup.org/onlinepubs/9699919799/functions/drand48.html) 
		and https://opensource.apple.com/source/Libc/Libc-583/gen/FreeBSD/erand48.c.auto.html
	 */
	fpngl_frng64_t *fpngl_drand48bsd(uint64_t seed);

	/*
		LCG generator used in Maple 10 and MuPAD Pro 3.1, according to 
		[Morgenstern](https://link.springer.com/chapter/10.1007%2F978-3-540-69995-8_90)
		
		Return a floating-point number in `(0,1)`.
	 */
	fpngl_frng64_t *fpngl_mupad(uint64_t seed);

#ifdef __cplusplus
}
#endif

#endif // __fpngl_frng64_division_h__
