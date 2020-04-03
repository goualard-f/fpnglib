/* Encapsulation of an RNG able to produce single precision floats

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
#include <fpnglib/frng32_t.h>


struct fpngl_frng32_t {
	void *state;
	const char *name;
	float min;
	float max;
	float(*nextf32)(void*);
	void (*next_arrayf32)(void *state, float *T, uint32_t n);
	void (*delete)(void*);
	uint32_t (*seed)(void *);
};

fpngl_frng32_t *fpngl_frng32_new(const char *name,
																 void *state,
																 float min, float max,
																 float (*nextf32)(void*),
																 void (*next_arrayf32)(void *state,
																											 float *T, uint32_t n),
																 void (*delete)(void*),
																 uint32_t (*seed)(void*))
{
	fpngl_frng32_t *rng = malloc(sizeof(fpngl_frng32_t));
	assert(rng != NULL);
	rng->state = state;
	rng->name = name;
	rng->nextf32 = nextf32;
	rng->next_arrayf32 = next_arrayf32;
	rng->delete = delete;
	rng->seed = seed;
	rng->min = min;
	rng->max = max;
	return rng;
}

const char *fpngl_frng32_name(fpngl_frng32_t *frng)
{
	return frng->name;
}

void fpngl_frng32_delete(fpngl_frng32_t *frng)
{
	frng->delete(frng->state);
	free(frng);
}

uint32_t fpngl_frng32_seed(fpngl_frng32_t *frng)
{
	return frng->seed(frng->state);
}


float fpngl_frng32_nextf32(fpngl_frng32_t *frng)
{
	return frng->nextf32(frng->state);
}

void fpngl_frng32_next_arrayf32(fpngl_frng32_t *frng, float *T, uint32_t n)
{
	frng->next_arrayf32(frng->state,T,n);
}

float fpngl_frng32_min(fpngl_frng32_t *frng)
{
	return frng->min;
}

float fpngl_frng32_max(fpngl_frng32_t *frng)
{
	return frng->max;
}

