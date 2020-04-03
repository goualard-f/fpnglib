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

#include <global.h>
#include <math.h>
#include <stdlib.h>
#include <fpnglib/frng64_golang.h>
#include <fpnglib/irange.h>

static double golang_nextf64(fpngl_irng_t *irng)
{
	double res;
	do {
		uint64_t v = fpngl_irng_next64(irng);
		res = (v >> 1)*0x1p-63; // 1 == 64 - 63
	} while (res == 1.0);
	return res;
}

static void golang_next_arrayf64(fpngl_irng_t *irng,
																 double *T, uint32_t n)
{
	for (uint32_t i = 0; i < n; ++i) {
		T[i] = golang_nextf64(irng);
	}
}

fpngl_frng64_t *fpngl_golang(fpngl_irng_t *irng, uint64_t seed)
{
	assert(fpngl_irng_seed(irng) == seed);
	return  fpngl_frng64_new("golang", irng, 0.0, 0x1.fffffffffffffp-1, 
													 (double (*)(void*))golang_nextf64,
													 (void (*)(void*, double*, uint32_t))golang_next_arrayf64,
													 (void (*)(void*))fpngl_irng_delete,
													 (uint64_t (*)(void*))fpngl_irng_seed);
}
