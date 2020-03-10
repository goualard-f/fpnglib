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

#include <global.h>
#include <stdlib.h>
#include <string.h>
#include <fpnglib/lcg.h>
#include <fpnglib/utilities.h>

typedef struct lcg64_state_t {
	uint64_t st; // State
	uint64_t m;
	uint64_t a;
	uint64_t c;
} lcg64_state_t;


static void *copy_state(lcg64_state_t *state)
{
	lcg64_state_t *c = malloc(sizeof(lcg64_state_t));
	assert(c != NULL);
	memcpy(c,state,sizeof(lcg64_state_t));
	return c;
}

static lcg64_state_t *lcg64_init(uint64_t seed, uint64_t m, uint64_t a, uint64_t c)
{
	lcg64_state_t *state = malloc(sizeof(lcg64_state_t));
	assert(state != NULL);
	state->st = seed;
	state->m = m;
	state->a = a;
	state->c = c;
	return state;
}

static void free_lcg64(lcg64_state_t *state)
{
	free(state);
}


static uint64_t lcg64_next64(lcg64_state_t *state)
{
	state->st = (state->a*state->st + state->c) % state->m;
	return state->st;
}


static uint32_t lcg64_next32(lcg64_state_t *state)
{
	state->st = ((uint32_t)state->a*(uint32_t)state->st + (uint32_t)state->c) % (uint32_t)state->m;
	return state->st;
}

static void lcg64_array32(lcg64_state_t *state, uint32_t *T, uint32_t n)
{
	// Filling the array two 32 bits values at a time.
	for (uint64_t *p = (uint64_t*)T; p < (uint64_t*)T+n/2; ++p) { // Default implementation
		*p = lcg64_next64(state);
	}
	// odd(n) => there is still the last cell to fill
	if (fpngl_odd(n)) {
		*(T+n-1)= (uint32_t)(lcg64_next64(state)>>32);
	}
}

static void lcg64_array64(lcg64_state_t *state, uint64_t *T, uint32_t n)
{
	for (uint32_t i = 0; i < n; ++i) {
		T[i] = lcg64_next64(state);
	}
}

static uint64_t lcg64_nextk(lcg64_state_t *state, uint32_t k)
{
	assert(k <= 65);
	/* 
		 Some LCG may fill only the 32 lowest bits. To avoid returning only zeros, 
		 we return the k highest bit in the first 32 bits word if k is lower than 32.
	 */
	if (k <= 32) {
		return (lcg64_next64(state) >> (32-k)) & 0x00000000ffffffff;
	} else {
		return lcg64_next64(state) >> (64-k);
	}
}


fpngl_irng64_t *fpngl_lcg64_new(uint64_t seed, const char *name,
																uint64_t m, uint64_t a, uint64_t c)
{
	return  fpngl_irng64_new(seed,name,
													 0, // Minimum
													 m-1, // Maximum
													 lcg64_init(seed,m,a,c),
													 (void* (*)(void*))copy_state,
													 (uint32_t (*)(void*))lcg64_next32,
													 (uint64_t (*)(void*))lcg64_next64,
													 (uint64_t (*)(void*,uint32_t))lcg64_nextk,
													 (void (*)(void*, uint32_t*,uint32_t))lcg64_array32,
													 (void (*)(void*, uint64_t*,uint32_t))lcg64_array64,
													 (void (*)(void*))free_lcg64);
}

fpngl_irng64_t *fpngl_minstd64(uint64_t seed)
{
	return fpngl_lcg64_new(seed,"minstd64",(1UL << 31) - 1,16807,0);
}

fpngl_irng64_t *fpngl_gnuc_lcg64(uint64_t seed)
{
	return fpngl_lcg64_new(seed,"gnuc_lcg64",(1UL << 31),1103515245,12345);
}

fpngl_irng64_t *fpngl_randu64(uint64_t seed)
{
	return fpngl_lcg64_new(seed,"randu64",(1UL << 31),65539,0);
}

fpngl_irng64_t *fpngl_drand48_lcg64(uint64_t seed)
{
	return fpngl_lcg64_new(seed,"drand48_lcg64",1UL<<48,25214903917,11);
}

fpngl_irng64_t *fpngl_mupad_lcg64(uint64_t seed)
{
	return fpngl_lcg64_new(seed,"mupad_lcg64",0xe8d4a50ff5UL,427419669081UL,0);
}
