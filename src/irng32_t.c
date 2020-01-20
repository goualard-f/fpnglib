/* Encapsulation of an RNG producing 32 bits random integers.

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
#include <fpnglib/irng32_t.h>

struct fpngl_irng32_t {
	uint32_t seed; // The seed used
	const char *name; // Name of the RNG
	uint32_t min;
	uint32_t max;
	void* state; // State of the RNG
	uint32_t (*next32)(void*); // Function returning the next random integer
	void (*delete)(void*); // Destructor
};


fpngl_irng32_t *fpngl_new_irng32(uint32_t seed,
																 const char* name,
																 uint32_t min, uint32_t max,
																 void *state,
																 uint32_t (*next32)(void*),
																 void (*delete)(void*))
{
	fpngl_irng32_t *rng = malloc(sizeof(fpngl_irng32_t));
	if (rng == NULL) {
		return NULL;
	}
	rng->seed = seed;
	rng->name = name;
	rng->min = min;
	rng->max = max;
	rng->state = state;
	rng->next32 = next32;
	rng->delete = delete;
	return rng;
}

// Releases all resources acquired by the pseudo-random generator 'rng'
void fpngl_delete_irng32(fpngl_irng32_t* rng)
{
	rng->delete(rng->state);
	free(rng);
}

// Return next pseudo-random number
uint32_t fpngl_irng32_next32(fpngl_irng32_t *rng)
{
	return rng->next32(rng->state);
}

// Return the seed used by the RNG
uint32_t fpngl_irng32_seed(fpngl_irng32_t *rng)
{
	return rng->seed;
}

// Return the name of the RNG used
const char *fpngl_get_irng32_name(fpngl_irng32_t *rng)
{
	return rng->name;
}

// Return the minimum value the RNG can return
uint32_t fpngl_irng32_min(fpngl_irng32_t *rng)
{
	return rng->min;
}

// Return the maximum value the RNG can return
uint32_t fpngl_irng32_max(fpngl_irng32_t *rng)
{
	return rng->max;
}

