/* Generation of 32 bits random integers with the von Neumann/Metropolis algorithm.

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
#include <stdlib.h>
#include <fpnglib/irng32_vnm.h>

typedef struct {
	uint32_t val;
} vnm_state_t;

static vnm_state_t* vnm_init(uint32_t seed)
{
	vnm_state_t *state = malloc(sizeof(vnm_state_t));
	if (state == NULL) {
		return NULL;
	}
	state->val = seed;
	return state;
}

static uint32_t vnm_next32(vnm_state_t *state)
{
	uint64_t v = (uint32_t)state->val;
	
	state->val = (uint32_t)(((v*v) & 0x0000ffffffff0000) >> 16);
	return state->val;
}

static uint64_t vnm_next64(vnm_state_t *state)
{
	return (((uint64_t)vnm_next32(state)) << 32) | (uint64_t)(vnm_next32(state));
}

static uint32_t vnm_nextk(vnm_state_t *state, uint32_t k)
{
	assert(k <= 32 && k != 0);
	return vnm_next32(state) >> (32-k);
}

static void vnm_array32(vnm_state_t *state, uint32_t *T, uint32_t n)
{
	for (uint32_t i = 0; i < n; ++i) {
		T[i] = vnm_next32(state);
	}
}

static void vnm_array64(vnm_state_t *state, uint64_t *T, uint32_t n)
{
	// Should we try to use next32() instead to fill T cast as a (uint32_t*) ?
	for (uint32_t i = 0; i < n; ++i) {
		T[i] = vnm_next64(state);
	}
}

static void vnm_free(vnm_state_t *state)
{
	free(state);
}

fpngl_irng32_t *fpngl_von_neumann_metropolis(uint32_t seed)
{
	return fpngl_irng32_new(seed,"von neumann/metropolis",0,0xffffffff,
													vnm_init(seed),
													(uint32_t (*)(void*))vnm_next32,
													(uint64_t (*)(void*))vnm_next64,
													(uint32_t (*)(void*, uint32_t))vnm_nextk,
													(void (*)(void*, uint32_t *, uint32_t))vnm_array32,
													(void (*)(void*, uint64_t *, uint32_t))vnm_array64,
													(void (*)(void*))vnm_free);
}

