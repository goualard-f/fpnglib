/* Linear Congruential Generators

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

#ifndef __lcg_h__
#define __lcg_h__

#include <fpnglib/fpngl_config.h>
#include <stdint.h>
#include <fpnglib/irng64_t.h>
#include <fpnglib/irng_t.h>

#ifdef __cplusplus
extern "C" {
#endif

	fpngl_irng64_t *fpngl_new_lcg64(uint64_t seed, const char *name,
																	 uint64_t m, uint64_t a, uint64_t c);
	
	fpngl_irng_t *fpngl_new_lcg(uint64_t seed, const char *name,
															uint64_t m, uint64_t a, uint64_t c);

	/*
		MINSTD implementation of Park/Miller RNG
		*See*: _Random Number Generators: Good Ones Are Hard to Find_. S. K. Park 
		and K.W. Miller. Comm. ACM 31(10), 1988.
	*/
	fpngl_irng_t *fpngl_minstd(uint64_t seed);

	/*
		RNG proposed in the GNU Libc for `rand()`. This is not the default 
		implementation of `rand()`, as of glibc 2.29.
	 */
	fpngl_irng_t *fpngl_lcg_gnu_c(uint64_t seed);
	
	/*
		RANDU RNG in the Scientific Subroutine Package on IBM Mainframe.
		
		*Source*: Numerical Computing with MATLAB. Steve Moler. Chap. 9
		*/
	fpngl_irng_t *fpngl_randu(uint64_t seed);

	/*
		LCG used by the GNU and FreeBSD implementations of drand48().
		
		This LCG is also used by java.util.Random, according to L'Ecuyer and Simard
		(see also: https://docs.oracle.com/javase/8/docs/api/java/util/Random.html).

		*Source:* [IEEE Std 1003.1-2017](http://pubs.opengroup.org/onlinepubs/9699919799/functions/drand48.html) and https://github.com/lattera/glibc/blob/master/stdlib/erand48_r.c
		*Source:* https://opensource.apple.com/source/Libc/Libc-583/gen/FreeBSD/erand48.c.auto.html
	 */ 
	fpngl_irng_t *fpngl_drand48_lcg(uint64_t seed);
	
	/*
		MuPAD LCG used in MuPAD Pro 3.1 and Maple 10 according to 
		[Morgenstern](https://link.springer.com/chapter/10.1007%2F978-3-540-69995-8_90)
	 */
	fpngl_irng_t *fpngl_mupad_lcg(uint64_t seed);
	
#ifdef __cplusplus
}
#endif


#endif // __lcg_h__
