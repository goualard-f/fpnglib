/* Encapsulation of an RNG producing 64 bits random integers.

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
#include <fpnglib/irng64_t.h>

typedef struct fpngl_irng_t fpngl_irng_t;
uint64_t fpngl_irng_next64(fpngl_irng_t *rng);

struct fpngl_irng64_t {
	uint64_t seed; // The seed used
	const char *name; // Name of the RNG
	uint64_t min;
	uint64_t max;
	void* state; // State of the RNG
	void* (*copy_state)(void *state); // Return a copy of the internal state `state`
	uint32_t (*next32)(void*);
	uint64_t (*next64)(void*);
	uint64_t (*nextk)(void *state, uint32_t k);
	void (*next_array32)(void *state, uint32_t *T, uint32_t n);
	void (*next_array64)(void *state, uint64_t *T, uint32_t n);
	void (*delete)(void*); // Destructor
};


static uint64_t next64to64(fpngl_irng_t *rng)
{
	return fpngl_irng_next64(rng);
}

/*
	That function returns a copy of the internal state of the irng32. It is 
	used only internally in the library. As such, it is not advertized 
	in the header file.
 */
void* fpngl_irng64_copy_state_internal(fpngl_irng64_t* rng)
{
	return rng->copy_state(rng->state);
}

uint32_t (*fpngl_irng64_next32_internal(fpngl_irng64_t *rng))(void*)
{
	return rng->next32;
}

uint64_t (*fpngl_irng64_next64_internal(fpngl_irng64_t *rng))(void*)
{
	return rng->next64;
}

uint64_t (*fpngl_irng64_next_internal(fpngl_irng64_t *rng))(void*)
{
	return (uint64_t(*)(void*))next64to64;
}

uint64_t (*fpngl_irng64_nextk_internal(fpngl_irng64_t *rng))(void*,uint32_t)
{
	return rng->nextk;
}

void (*fpngl_irng64_next_array32_internal(fpngl_irng64_t *rng))(void*,uint32_t*,uint32_t) 
{
	return rng->next_array32;
}

void (*fpngl_irng64_next_array64_internal(fpngl_irng64_t *rng))(void*,uint64_t*,uint32_t)
{
	return rng->next_array64;
}

void (*fpngl_irng64_delete_internal(fpngl_irng64_t *rng))(void*)
{
	return rng->delete;
}

fpngl_irng64_t *fpngl_irng64_new(uint64_t seed,
																 const char* name,
																 uint64_t min, uint64_t max,
																 void *state,
																 void* (*copy_state)(void*),
																 uint32_t (*next32)(void*),
																 uint64_t (*next64)(void*),
																 uint64_t (*nextk)(void *state, uint32_t k),
																 void (*next_array32)(void *state,
																											uint32_t *T, uint32_t n),
																 void (*next_array64)(void *state,
																											uint64_t *T, uint32_t n),
																 void (*delete)(void*))
{
	fpngl_irng64_t *rng = malloc(sizeof(fpngl_irng64_t));
	assert(rng != NULL);

	rng->seed = seed;
	rng->name = name;
	rng->min = min;
	rng->max = max;
	rng->state = state;
	rng->copy_state = copy_state;
	rng->next32 = next32;
	rng->next64 = next64;
	rng->nextk = nextk;
	rng->next_array32 = next_array32;
	rng->next_array64 = next_array64;
	rng->delete = delete;
	return rng;
}


// Releases all resources acquired by the pseudo-random generator 'rng'
void fpngl_irng64_delete(fpngl_irng64_t* rng)
{
	assert(rng != NULL && rng->state != NULL);
	rng->delete(rng->state);
	free(rng);
}

// Return next pseudo-random number
uint32_t fpngl_irng64_next32(fpngl_irng64_t *rng)
{
	assert(rng != NULL && rng->next32 != NULL && rng->state != NULL);
	return rng->next32(rng->state);
}

// Return next pseudo-random number
uint64_t fpngl_irng64_next64(fpngl_irng64_t *rng)
{
	assert(rng != NULL && rng->next32 != NULL && rng->state != NULL);
	return rng->next64(rng->state);
}

uint64_t fpngl_irng64_nextk(fpngl_irng64_t *rng, uint32_t k)
{
	assert(rng != NULL && rng->nextk != NULL && rng->state != NULL);
	return rng->nextk(rng->state,k);
}

void fpngl_irng64_array32(fpngl_irng64_t *rng, uint32_t *T, uint32_t n)
{
	assert(rng != NULL && rng->next_array32 != NULL && rng->state != NULL);
	rng->next_array32(rng->state,T,n);
}

void fpngl_irng64_array64(fpngl_irng64_t *rng, uint64_t *T, uint32_t n)
{
	assert(rng != NULL && rng->next_array64 != NULL && rng->state != NULL);
	rng->next_array64(rng->state,T,n);
}

// Return the seed used by the RNG
uint64_t fpngl_irng64_seed(fpngl_irng64_t *rng)
{
	assert(rng != NULL);
	return rng->seed;
}

// Return the name of the RNG used
const char *fpngl_irng64_name(fpngl_irng64_t *rng)
{
	assert(rng != NULL);	
	return rng->name;
}

// Return the minimum value the RNG can return
uint64_t fpngl_irng64_min(fpngl_irng64_t *rng)
{
	assert(rng != NULL);
	return rng->min;
}

// Return the maximum value the RNG can return
uint64_t fpngl_irng64_max(fpngl_irng64_t *rng)
{
	assert(rng != NULL);
	return rng->max;
}

