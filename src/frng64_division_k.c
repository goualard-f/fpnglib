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

#include <global.h>
#include <stdlib.h>
#include <math.h>
#include <fpnglib/frng64_division_k.h>
#include <fpnglib/lcg.h>

// State for a float random generator that divides a random integer by a constant
typedef struct {
	fpngl_irng_t *irng;
	uint64_t mask;
	double denominator;
} frng_division_state_t;


static double nextf64(frng_division_state_t *frng)
{
	/* 
		 Keeping only the `k` lowest bits. 
		 Note : we keep the `k` lowest bits (which may be low quality) instead of
		 the `k` highest bits because the random integer produced may be a 
		 `uint32_t` cast to an `uint64_t`, and we would get only zeros in that case.
	*/
	return (fpngl_irng_next(frng->irng) & frng->mask)/frng->denominator;
}

static void next_arrayf64(frng_division_state_t *frngstate, double *T, uint32_t n)
{
	// Casting double* T to uint64_t *T to avoid creating a temp
	fpngl_irng_array64(frngstate->irng,(uint64_t*)T,n);
	for (uint32_t i = 0; i < n ; ++i) {
		T[i] = (((uint64_t*)T)[i] & frngstate->mask)/frngstate->denominator;
	}
}

static uint64_t frng64_seed(frng_division_state_t *frngstate)
{
	return fpngl_irng_seed(frngstate->irng);
}

static void frng64_delete(frng_division_state_t *frngstate)
{
	fpngl_irng_delete(frngstate->irng);
	free(frngstate);
}

fpngl_frng64_t *fpngl_bydivision_k_new(const char *name,
																			 double min, double max,
																			 fpngl_irng_t *irng,
																			 uint32_t k,
																			 uint64_t denominator)
{
	assert(denominator != 0);
	assert(k >= 1 && k <= 64);
	frng_division_state_t *frngstate = malloc(sizeof(frng_division_state_t));
	assert(frngstate != NULL);
	
	frngstate->irng = irng;
	frngstate->mask = (1UL << k) - 1;
	frngstate->denominator = denominator; // BEWARE: what if some rounding takes place?
	if ((uint64_t)frngstate->denominator != denominator) {
		FPNGL_WARNING("Warning: %lu rounded to %.0f\n",denominator,frngstate->denominator);
	}
	return  fpngl_frng64_new(name, frngstate, min, max,
													 (double (*)(void*))nextf64,
													 (void (*)(void*, double*, uint32_t))next_arrayf64,
													 (void (*)(void*))frng64_delete,
													 (uint64_t (*)(void*))frng64_seed);
}

fpngl_frng64_t *fpngl_div53(fpngl_irng_t *irng, uint64_t seed)
{
	assert(fpngl_irng_seed(irng) == seed);
	return fpngl_bydivision_k_new("div53",0.0, 0x1.fffffffffffffp-1, irng, 53, 1UL << 53);									
}

fpngl_frng64_t *fpngl_div32(fpngl_irng_t *irng, uint64_t seed)
{
	assert(fpngl_irng_seed(irng) == seed);
	return fpngl_bydivision_k_new("div32", 0.0, 0x1.fffffffep-1,irng, 32, 1UL << 32);									
}


