/* Computation of a double precision random number using the RNG
   by Kolonko, Gu, and Wu.

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
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <fpnglib/frng64_lecuyer_simard.h>
#include <fpnglib/irange.h>

typedef struct {
	fpngl_irng_t *irng;
	double eps0; // ε₀
	double eps1; // 1-ε₁
	double truncHM; // trunc((fpngl_irng_max(irng)+1)/2)
} kgw_state_t;

static double KGW_nextf64(kgw_state_t *state)
{
	uint64_t x1 = fpngl_irng_next64(state->irng);
	uint64_t x2 = fpngl_irng_next64(state->irng);
	FPNGL_DEBUG("V: %lu %lu\n",x1,x2);
	if (x1 == x2) {
		if (x1 <= state->truncHM-1) {
			return state->eps0;
		} else {
			return state->eps1;
		}
	}
	if (x1 == 0) {
		return state->eps0;
	}
	if (x2 == 0) {
		return state->eps1;
	}
	if (x1 >= x2) {
		return x2/x1;
	} else {
		return x1/x2;
	}
}

static void KGW_next_arrayf64(kgw_state_t *state,
																 double *T, uint32_t n)
{
	for (uint32_t i = 0; i < n; ++i) {
		T[i] = KGW_nextf64(state);
	}
}

static uint64_t KGW_seed(kgw_state_t *state)
{
	return fpngl_irng_seed(state->irng);
}

static void KGW_delete(kgw_state_t *state)
{
	fpngl_irng_delete(state->irng);
	free(state);
}


fpngl_frng64_t *fpngl_KGW(fpngl_irng_t *irng, uint64_t seed)
{
	kgw_state_t *state = malloc(sizeof(kgw_state_t));
	if (state == NULL) {
		return NULL;
	}
	state->irng = irng;
	// Warning: fpngl_irng_max(irng)+1.0 must be representable
	// as a double precision number.
	double M = fpngl_irng_max(irng)+1.0;
	// Warning: (fpngl_irng_max(irng)+1.0)^2 must be representable
	// as a double precision number.
	double sqM = M*M;
	state->truncHM = trunc(M/2);
	state->eps0 = (M-1+state->truncHM)/(2*sqM);
	state->eps1 = 1-(2*M - 1 - state->truncHM)/(2*sqM);
	return  fpngl_frng64_new("KGW", state,
													 (double (*)(void*))KGW_nextf64,
													 (void (*)(void*, double*, uint32_t))KGW_next_arrayf64,
													 (void (*)(void*))KGW_delete,
													 (uint64_t (*)(void*))KGW_seed);
}
