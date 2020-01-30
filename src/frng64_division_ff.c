/* Implementation of double precision floating-point number generators
	 through division of a random integer by another random integer.

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
#include <assert.h>
#include <fpnglib/frng64_division_ff.h>
#include <fpnglib/lcg.h>

// State for a float random generator that divides a random integer by a constant
typedef struct {
	fpngl_irng_t *irngN; // RNG for the numerator
	fpngl_irng_t *irngD; // RNG for the denominator
} frng_division_state_t;


static double nextf64(frng_division_state_t *frng)
{
	return fpngl_irng_next64(frng->irngN)/fpngl_irng_next64(frng->irngD);
}

static void next_arrayf64(frng_division_state_t *frngstate, double *T, uint32_t n)
{
	uint64_t TD[n];
	// Casting double* T to uint64_t *T to avoid creating a temp
	fpngl_irng_array64(frngstate->irngN,(uint64_t*)T,n);
	fpngl_irng_array64(frngstate->irngD,TD,n);
	for (uint32_t i = 0; i < n ; ++i) {
		T[i] = ((uint64_t*)T)[i]/TD[i];
	}
}

static uint64_t frng64_seed(frng_division_state_t *frngstate)
{
	// We can return the seed from either irngD or irgnN since they are the same.
	return fpngl_irng_seed(frngstate->irngD);
}

static void frng64_delete(frng_division_state_t *frngstate)
{
	fpngl_irng_delete(frngstate->irngN);
	fpngl_irng_delete(frngstate->irngD);
	free(frngstate);
}

fpngl_frng64_t *fpngl_bydivision_ff_new(uint64_t seed, const char *name,
																				fpngl_irng_t *irng_num,
																				fpngl_irng_t *irng_denom)
{
	frng_division_state_t *frngstate = malloc(sizeof(frng_division_state_t));
	
	if (frngstate == NULL) {
		return NULL;
	}

	frngstate->irngN = irng_num;
	frngstate->irngD = irng_denom;

	return  fpngl_frng64_new(name, frngstate,
													 (double (*)(void*))nextf64,
													 (void (*)(void*, double*, uint32_t))next_arrayf64,
													 (void (*)(void*))frng64_delete,
													 (uint64_t (*)(void*))frng64_seed);
}

