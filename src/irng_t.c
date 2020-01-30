/* Encapsulation of an RNG able to produce 32 bits and 64 bits random integers.

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
#include <fpnglib/irng_t.h>

// Declaring functions that are not advertized in the header files
// as they are used only internally.
void* fpngl_irng32_state_internal(fpngl_irng32_t* rng);
uint32_t (*fpngl_irng32_next32_internal(fpngl_irng32_t *rng))(void*);
uint64_t (*fpngl_irng32_next64_internal(fpngl_irng32_t *rng))(void*);
uint64_t (*fpngl_irng32_next_internal(fpngl_irng32_t *rng))(void*);
uint32_t (*fpngl_irng32_nextk_internal(fpngl_irng32_t *rng))(void*,uint32_t);
void (*fpngl_irng32_next_array32_internal(fpngl_irng32_t *rng))(void*,uint32_t*,uint32_t);
void (*fpngl_irng32_next_array64_internal(fpngl_irng32_t *rng))(void*,uint64_t*,uint32_t);
void (*fpngl_irng32_delete_internal(fpngl_irng32_t *rng))(void*);
void* fpngl_irng64_state_internal(fpngl_irng64_t* rng);
uint32_t (*fpngl_irng64_next32_internal(fpngl_irng64_t *rng))(void*);
uint64_t (*fpngl_irng64_next64_internal(fpngl_irng64_t *rng))(void*);
uint64_t (*fpngl_irng64_next_internal(fpngl_irng64_t *rng))(void*);
uint64_t (*fpngl_irng64_nextk_internal(fpngl_irng64_t *rng))(void*,uint32_t);
void (*fpngl_irng64_next_array32_internal(fpngl_irng64_t *rng))(void*,uint32_t*,uint32_t);
void (*fpngl_irng64_next_array64_internal(fpngl_irng64_t *rng))(void*,uint64_t*,uint32_t);
void (*fpngl_irng64_delete_internal(fpngl_irng64_t *rng))(void*);




struct fpngl_irng_t {
	uint64_t seed; // The seed used
	const char *name; // Name of the RNG
	uint64_t min;
	uint64_t max;
	void* state; // State of the RNG
	uint32_t (*next32)(void*);
	uint64_t (*next64)(void*);
	uint64_t (*next)(void*);
	union {
		uint32_t (*nextk32)(void *state, uint32_t k);
		uint64_t (*nextk64)(void *state, uint32_t k);
	};
	void (*next_array32)(void *state, uint32_t *T, uint32_t n);
	void (*next_array64)(void *state, uint64_t *T, uint32_t n);
	void (*delete)(void*); // Destructor
	bool is_irng64;
};

fpngl_irng_t *fpngl_irng_new32(fpngl_irng32_t *irng32)
{
	fpngl_irng_t *irng = malloc(sizeof(fpngl_irng_t));
	if (irng == NULL) {
		return NULL;
	}
	irng->is_irng64 = false;
	irng->seed = (uint64_t)fpngl_irng32_seed(irng32);
	irng->name = fpngl_irng32_name(irng32);
	irng->min = (uint64_t)fpngl_irng32_min(irng32);
	irng->max = (uint64_t)fpngl_irng32_max(irng32);
	irng->state = fpngl_irng32_state_internal(irng32);
	irng->next32 = fpngl_irng32_next32_internal(irng32);
	irng->next64 = fpngl_irng32_next64_internal(irng32);
	irng->next = fpngl_irng32_next_internal(irng32);
	irng->next_array32 = fpngl_irng32_next_array32_internal(irng32);
	irng->next_array64 = fpngl_irng32_next_array64_internal(irng32);
	irng->delete = fpngl_irng32_delete_internal(irng32);
	irng->nextk32 = fpngl_irng32_nextk_internal(irng32);
	return irng;
}

fpngl_irng_t *fpngl_irng_new64(fpngl_irng64_t *irng64)
{
	fpngl_irng_t *irng = malloc(sizeof(fpngl_irng_t));
	if (irng == NULL) {
		return NULL;
	}
	irng->is_irng64 = true;
	irng->seed = fpngl_irng64_seed(irng64);
	irng->name = fpngl_irng64_name(irng64);
	irng->min = fpngl_irng64_min(irng64);
	irng->max = fpngl_irng64_max(irng64);
	irng->state = fpngl_irng64_state_internal(irng64);
	irng->next32 = fpngl_irng64_next32_internal(irng64);
	irng->next64 = fpngl_irng64_next64_internal(irng64);
	irng->next = fpngl_irng64_next_internal(irng64);
	irng->next_array32 = fpngl_irng64_next_array32_internal(irng64);
	irng->next_array64 = fpngl_irng64_next_array64_internal(irng64);
	irng->delete = fpngl_irng64_delete_internal(irng64);
	irng->nextk64 = fpngl_irng64_nextk_internal(irng64);
	return irng;
}


// Releases all resources acquired by the pseudo-random generator 'rng'
void fpngl_irng_delete(fpngl_irng_t* rng)
{
	rng->delete(rng->state);
	free(rng);
}

// Return next 32 bits pseudo-random number
uint32_t fpngl_irng_next32(fpngl_irng_t *rng)
{
	return rng->next32(rng->state);
}

// Return next 64 bits pseudo-random number
uint64_t fpngl_irng_next64(fpngl_irng_t *rng)
{
	return rng->next64(rng->state);
}

// Return next pseudo-random number cast to 64 bits
uint64_t fpngl_irng_next(fpngl_irng_t *rng)
{
	return rng->next(rng);
}



// Return next k bits pseudo-random number
uint64_t fpngl_irng_nextk(fpngl_irng_t *rng, uint32_t k)
{
	if (rng->is_irng64) {
		return rng->nextk64(rng->state,k);
	} else {
		if (k <= 32) {
			return (uint64_t)rng->nextk32(rng->state,k);
		} else {
			return (((uint64_t)rng->next32(rng->state)) << 32) |
				(uint64_t)rng->nextk32(rng->state,32-k);
		}
	}
}

/*
 Fills array T with `n` 32 bits pseudo-random integers.
 The array must have been allcoated beforehand.
*/
void fpngl_irng_array32(fpngl_irng_t *rng, uint32_t *T, uint32_t n)
{
	return rng->next_array32(rng->state,T,n);
}

/*
 Fills array T with `n` 64 bits pseudo-random integers.
 The array must have been allcoated beforehand.
*/
void fpngl_irng_array64(fpngl_irng_t *rng, uint64_t *T, uint32_t n)
{
	return rng->next_array64(rng->state,T,n);
}

// Return the seed used by the RNG
uint64_t fpngl_irng_seed(fpngl_irng_t *rng)
{
	return rng->seed;
}

// Return the name of the RNG used
const char *fpngl_irng_name(fpngl_irng_t *rng)
{
	return rng->name;
}

// Return the minimum value the RNG can return
uint64_t fpngl_irng_min(fpngl_irng_t *rng)
{
	return rng->min;
}

// Return the maximum value the RNG can return
uint64_t fpngl_irng_max(fpngl_irng_t *rng)
{
	return rng->max;
}
