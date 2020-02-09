/*  Generation of a random double precision number according to
	 the method by [Agner Fog](https://digitalcommons.wayne.edu/jmasm/vol14/iss1/23/).

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

#ifndef __fpngl_frng64_fog05_h__
#define __fpngl_frng64_fog05_h__

#include <fpnglib/fpngl_config.h>
#include <stdint.h>
#include <fpnglib/frng64_t.h>
#include <fpnglib/irng_t.h>

#ifdef __cplusplus
extern "C" {
#endif

	/*
		Same as Method fpngl_fog97(), except that we generate 53 random bits and we use 
		the 53rd to choose whether to subtract either $1$ or $1-\delta$ 
		(with $\delta=2^{-53}$ for `double`) from the random floating-point number 
		obtained in $[1,2)$. 
		The methods may generate all the floating-points numbers of the 
		form $k\times 2^{-53}$, for $k\in\{0,\dots,2^{53}-1\}$, and removes the bias 
		concerning the LSB being always 0.
	 */
	fpngl_frng64_t *fpngl_fog05(fpngl_irng_t *irng, uint64_t seed);
	
#ifdef __cplusplus
}
#endif

#endif // __fpngl_frng64_fog05_h__
