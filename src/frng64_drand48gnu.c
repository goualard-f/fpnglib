/* Generation of a random double precision number by using the implementation
	 of rand48t() in GNU C.

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
#include <fpnglib/frng64_drand48gnu.h>
#include <fpnglib/irng64_t.h>
#include <fpnglib/lcg.h>
#include <fpnglib/frng_t.h>

static double nextf64(fpngl_irng64_t *irng)
{
	uint64_t f = fpngl_irng64_next64(irng);
	fpngl_uintf64_t res = {.ui = (0x3ff0000000000000 | (f << 4))};
	return res.d - 1.0;
}

static void next_arrayf64(fpngl_irng64_t *irng, double *T, uint32_t n)
{
	for (uint32_t i = 0; i < n ; ++i) {
		T[i] = nextf64(irng);
	}
}

static uint64_t frng64_seed(fpngl_irng64_t *irng)
{
	return fpngl_irng64_seed(irng);
}

static void frng64_delete(fpngl_irng64_t *irng)
{
	fpngl_irng64_delete(irng);
}

fpngl_frng64_t *fpngl_drand48gnu(uint64_t seed)
{
	fpngl_irng64_t *irng = fpngl_drand48_lcg64(seed);
	if (irng == NULL) {
		return NULL;
	}
	return fpngl_frng64_new("drand48gnu",
													irng, 0.0, 0x1.fffffffffffffp-1,
													(double (*)(void*))nextf64,
													(void (*)(void*, double*, uint32_t))next_arrayf64,
													(void (*)(void*))frng64_delete,
													(uint64_t (*)(void*))frng64_seed);
}

