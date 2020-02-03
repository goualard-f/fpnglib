/* Computation of a double precision random number using the RNG
   by L'Ecuyer and Simard, generalized by Kolonko, Gu and Wu.

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
#include <fpnglib/frng64_LESKGW.h>
#include <fpnglib/irange.h>

typedef struct {
	fpngl_irng64_t *irng64;
	double M; // maximum value for irng64 plus one;
	double sqM; // Square of the maximum value for irng64 plus one
} leskgw_state_t;

static double LESKGW_nextf64(leskgw_state_t *state)
{
	uint64_t v1 = fpngl_irng64_next64(state->irng64);
	uint64_t v2 = fpngl_irng64_next64(state->irng64);
	return v1/state->M + v2/state->sqM;
}

static void LESKGW_next_arrayf64(leskgw_state_t *state,
																 double *T, uint32_t n)
{
	for (uint32_t i = 0; i < n; ++i) {
		T[i] = LESKGW_nextf64(state);
	}
}

static uint64_t LESKGW_seed(leskgw_state_t *state)
{
	return fpngl_irng64_seed(state->irng64);
}

static void LESKGW_delete(leskgw_state_t *state)
{
	fpngl_irng64_delete(state->irng64);
	free(state);
}


fpngl_frng64_t *fpngl_LESKGW(fpngl_irng64_t *irng64, uint64_t seed)
{
	leskgw_state_t *state = malloc(sizeof(leskgw_state_t));
	if (state == NULL) {
		return NULL;
	}
	state->irng64 = irng64;
	// Warning: fpngl_irng64_max(irng64)+1.0 must be representable
	// as a double precision number.
	state->M = fpngl_irng64_max(irng64)+1.0;
	// Warning: (fpngl_irng64_max(irng64)+1.0)^2 must be representable
	// as a double precision number.
	state->sqM = state->M*state->M;
	
	return  fpngl_frng64_new("LESKGW", state,
													 (double (*)(void*))LESKGW_nextf64,
													 (void (*)(void*, double*, uint32_t))LESKGW_next_arrayf64,
													 (void (*)(void*))LESKGW_delete,
													 (uint64_t (*)(void*))LESKGW_seed);
}
