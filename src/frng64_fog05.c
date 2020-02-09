/* Generation of a random double precision number according to
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

#include <global.h>
#include <stdlib.h>
#include <fpnglib/frng64_fog05.h>
#include <fpnglib/lcg.h>
#include <fpnglib/irange.h>
#include <fpnglib/types.h>
#include <fpnglib/constants64.h>

static double nextf64(fpngl_irng_t *irng)
{
	uint64_t v = fpngl_n_bits64(fpngl_irng_next64(irng),53);
	// Separating the decision bit from the 52 bits fractional part.
	uint32_t b = v & 1;
	uint64_t f = v >> 1;
	fpngl_uintf64_t res = {.ui = (0x3ff0000000000000 | f)};
	return (b == 0) ? res.d - 1.0 : res.d - (1-fpngl_u64);
}

static void next_arrayf64(fpngl_irng_t *irng, double *T, uint32_t n)
{
	for (uint32_t i = 0; i < n ; ++i) {
		T[i] = nextf64(irng);
	}
}

static uint64_t frng64_seed(fpngl_irng_t *irng)
{
	return fpngl_irng_seed(irng);
}

static void frng64_delete(fpngl_irng_t *irng)
{
	fpngl_irng_delete(irng);
}

fpngl_frng64_t *fpngl_fog05(fpngl_irng_t *irng, uint64_t seed)
{
	assert(seed == fpngl_irng_seed(irng));
	return fpngl_frng64_new("fog05",
													irng,
													(double (*)(void*))nextf64,
													(void (*)(void*, double*, uint32_t))next_arrayf64,
													(void (*)(void*))frng64_delete,
													(uint64_t (*)(void*))frng64_seed);
}

