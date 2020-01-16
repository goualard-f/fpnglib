/* Linear Congruential Generators

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

#include <stdlib.h>
#include <fpnglib/lcg.h>

struct fpngl_lcg64_state_t {
	uint64_t st; // State
	uint64_t m;
	uint64_t a;
	uint64_t c;
};

fpngl_lcg64_state_t *fpngl_init_lcg64(uint64_t seed, uint64_t m, uint64_t a, uint64_t c)
{
	fpngl_lcg64_state_t *state = malloc(sizeof(fpngl_lcg64_state_t));
	if (state == NULL) {
		return NULL;
	}
	state->st = seed;
	state->m = m;
	state->a = a;
	state->c = c;
	return state;
}

void fpngl_free_lcg64(fpngl_lcg64_state_t *state)
{
	free(state);
}


uint64_t fpngl_lcg64_next(fpngl_lcg64_state_t *state)
{
	state->st = (state->a*state->st + state->c) % state->m;
	return state->st;
}
