/* Computation of a double precision random number using the RNG
   rationalLCG10 by Morgenstern.

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

#include <global.h>
#include <math.h>
#include <stdlib.h>
#include <fpnglib/frng64_rationalLCG10.h>
#include <fpnglib/lcg.h>

static double rationalLCG10_nextf64(fpngl_irng64_t *irng64)
{
	uint64_t s = fpngl_irng64_next64(irng64);
	uint64_t q = fpngl_irng64_next64(irng64);
	if (s < q) {
		return s/(double)q;
	} else {
		return q/(double)s;
	}
}

static void rationalLCG10_next_arrayf64(fpngl_irng64_t *irng64,
																				double *T, uint32_t n)
{
	for (uint32_t i = 0; i < n; ++i) {
		T[i] = rationalLCG10_nextf64(irng64);
	}
}

fpngl_frng64_t *fpngl_rationalLCG10(uint64_t seed)
{
	fpngl_irng64_t *irng64 = fpngl_mupad_lcg64(seed);
	if (irng64 == NULL) {
		return NULL;
	}
	return  fpngl_frng64_new("rationalLCG10", irng64,
													 (double (*)(void*))rationalLCG10_nextf64,
													 (void (*)(void*, double*, uint32_t))rationalLCG10_next_arrayf64,
													 (void (*)(void*))fpngl_irng64_delete,
													 (uint64_t (*)(void*))fpngl_irng64_seed);
}
