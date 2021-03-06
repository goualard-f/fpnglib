/* Manipulation of the domain of the random integers produced.

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

/*
	+ Reduction of the domain by shifting
	+ Shift to some specific domain [a,b]
 */

#ifndef __irange_h__
#define __irange_h__

#include <fpnglib/fpngl_config.h>
#include <stdint.h>
#include <fpnglib/irng_t.h>

#ifdef __cplusplus
extern "C" {
#endif

	
	/*
		Return a random integer in the domain [0,a) using the RNG `irng`.

		The algorithm used is the one presented by Lemire in:

		Fast Random Integer Generation in an Interval. Daniel Lemire. 
		ACM Transactions on Modeling and Computer Simulation, 29(1), 2019,
		
		and modified by O'Neill (http://www.pcg-random.org/posts/bounded-rands.html).
		
	*/
	uint32_t fpngl_ubound32(fpngl_irng_t *irng, uint32_t a);
	uint64_t fpngl_ubound64(fpngl_irng_t *irng, uint64_t a);

	/*
		Return a number in the domain `[a, b)`.
	 */
	int32_t fpngl_range32(fpngl_irng_t *irng, int32_t a, int32_t b);
	int64_t fpngl_range64(fpngl_irng_t *irng, int64_t a, int64_t b);

	
#ifdef __cplusplus
}
#endif

#endif // __irange_h__
