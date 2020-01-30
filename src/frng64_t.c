/* Encapsulation of an RNG able to produce double precision floats

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
#include <fpnglib/frng64_t.h>


struct fpngl_frng64_t {
	void *state;
	const char *name;
	double (*nextf64)(void*);
	void (*next_arrayf64)(void *state, double *T, uint32_t n);
	void (*delete)(void*);
	uint64_t (*seed)(void *);
};

fpngl_frng64_t *fpngl_frng64_new(const char *name,
																 void *state,
																 double (*nextf64)(void*),
																 void (*next_arrayf64)(void *state,
																											 double *T, uint32_t n),
																 void (*delete)(void*),
																 uint64_t (*seed)(void*))
{
	fpngl_frng64_t *rng = malloc(sizeof(fpngl_frng64_t));
	if (rng == NULL) {
		return NULL;
	}
	rng->state = state;
	rng->name = name;
	rng->nextf64 = nextf64;
	rng->next_arrayf64 = next_arrayf64;
	rng->delete = delete;
	rng->seed = seed;
	return rng;
}

const char *fpngl_frng64_name(fpngl_frng64_t *frng)
{
	return frng->name;
}

void fpngl_frng64_delete(fpngl_frng64_t *frng)
{
	frng->delete(frng->state);
	free(frng);
}

uint64_t fpngl_frng64_seed(fpngl_frng64_t *frng)
{
	return frng->seed(frng->state);
}


double fpngl_frng64_nextf64(fpngl_frng64_t *frng)
{
	return frng->nextf64(frng->state);
}

void fpngl_frng64_next_arrayf64(fpngl_frng64_t *frng, double *T, uint32_t n)
{
	frng->next_arrayf64(frng->state,T,n);
}
