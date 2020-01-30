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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <fpnglib/frng64_division_fc.h>
#include <fpnglib/lcg.h>

// State for a float random generator that divides a random integer by a constant
typedef struct {
	fpngl_irng_t *irng;
	double denominator;
} frng_division_state_t;


static double nextf64(frng_division_state_t *frng)
{
	return fpngl_irng_next64(frng->irng)/frng->denominator;
}

static void next_arrayf64(frng_division_state_t *frngstate, double *T, uint32_t n)
{
	// Casting double* T to uint64_t *T to avoid creating a temp
	fpngl_irng_array64(frngstate->irng,(uint64_t*)T,n);
	for (uint32_t i = 0; i < n ; ++i) {
		T[i] = ((uint64_t*)T)[i]/frngstate->denominator;
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

fpngl_frng64_t *fpngl_bydivision_fc_new(const char *name,
																				fpngl_irng_t *irng,
																				uint64_t denominator)
{
	assert(denominator != 0);
	frng_division_state_t *frngstate = malloc(sizeof(frng_division_state_t));
	
	if (frngstate == NULL) {
		return NULL;
	}
	
	frngstate->irng = irng;
	frngstate->denominator = denominator; // BEWARE: what if some rounding takes place?
	assert((uint64_t)frngstate->denominator == denominator);

	return  fpngl_frng64_new(name, frngstate,
													 (double (*)(void*))nextf64,
													 (void (*)(void*, double*, uint32_t))next_arrayf64,
													 (void (*)(void*))frng64_delete,
													 (uint64_t (*)(void*))frng64_seed);
}

fpngl_frng64_t *fpngl_matlabp5(uint64_t seed)
{
	return fpngl_bydivision_fc_new("matlabp5",
																 fpngl_irng_new64(fpngl_minstd64(seed)),1UL<<31);
}

fpngl_frng64_t *fpngl_drand48bsd(uint64_t seed)
{
	return fpngl_bydivision_fc_new("drand48bsd",
																 fpngl_irng_new64(fpngl_drand48_lcg64(seed)),1UL<<48);
}

fpngl_frng64_t *fpngl_mupad(uint64_t seed)
{
	return fpngl_bydivision_fc_new("mupad",
																 fpngl_irng_new64(fpngl_mupad_lcg64(seed)),
																 0xe8d4a50ff5UL);
}

static double java_nextf64(frng_division_state_t *frng)
{
	uint64_t xa = fpngl_irng_next64(frng->irng);
	uint64_t xb = fpngl_irng_next64(frng->irng);
	return (0x1p+27*trunc(xa*0x1p-22)+trunc(xb*0x1p-21))*0x1p-53;
}

static void java_next_arrayf64(frng_division_state_t *frngstate,
															 double *T, uint32_t n)
{
	// Creating the array dynamically to avoid a size limitation on the stack
	uint64_t *T2 = calloc(2*n,sizeof(uint64_t));
	assert(T2 != NULL);
	fpngl_irng_array64(frngstate->irng,T2,2*n);
	uint32_t j = 0;
	for (uint32_t i = 0; i < 2*n ; i+=2) {
		T[j++] =  (0x1p+27*trunc(T2[i]*0x1p-22)+trunc(T2[i+1]*0x1p-21))*0x1p-53;
	}
	free(T2);
}

fpngl_frng64_t *fpngl_java(uint64_t seed)
{
	frng_division_state_t *frngstate = malloc(sizeof(frng_division_state_t));
	
	if (frngstate == NULL) {
		return NULL;
	}

	frngstate->irng = fpngl_irng_new64(fpngl_drand48_lcg64(seed));
	frngstate->denominator = 0x1.0p53; 

	return  fpngl_frng64_new("java", frngstate,
													 (double (*)(void*))java_nextf64,
													 (void (*)(void*, double*, uint32_t))java_next_arrayf64,
													 (void (*)(void*))frng64_delete,
													 (uint64_t (*)(void*))frng64_seed);
}

