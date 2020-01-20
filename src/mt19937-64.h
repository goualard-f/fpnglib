/* Original 64 bits Mersenne Twister by Nishimura & Matsumoto.

	 Some cosmetic modifications made for the FPNGlib library. The biggest 
	 modification is the creationg of a local state instead of a global state to allow
	 parallel calls and more than one MT.

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

#ifndef __mt19937_64_h__
#define __mt19937_64_h__

#include <fpnglib/fpngl_config.h>
#include <stdint.h>
#include <fpnglib/rng_t.h>

#ifdef __cplusplus
extern "C" {
#endif

fpngl_irng64_t *fpngl_new_mt19937_64(uint64_t seed);

fpngl_irng_t *fpngl_new_mt19937(uint64_t seed);




// State of an MT19937-64 RNG
typedef struct fpngl_mt19937_64_state_t fpngl_mt19937_64_state_t;

/*
	Initialize the state for an MT19937-64 RNG with the seed `seed`.
	Return NULL if the memory for representing the state could not be allocated.
	The user should call fpngl_free_mt19937_64() to free the memory allocated 
	when the RNG is not needed anymore.
 */
fpngl_mt19937_64_state_t *fpngl_init_mt19937_64(uint64_t seed);


fpngl_mt19937_64_state_t *fpngl_init_mt19937_64_by_array64(uint64_t init_key[],
																													 uint64_t key_length);

void fpngl_free_mt19937_64(fpngl_mt19937_64_state_t *state);

uint64_t fpngl_mt19937_64_next64(fpngl_mt19937_64_state_t *state);

/* Return k random bits. The value of `k` must be in [1,64]. 
	 Use preferentially fpngl_mt19937_64_to_32_next() for k=32 and 
	 fpngl_mt19937_64_next() for k=64.
*/
uint64_t fpngl_mt19937_64_next_k(fpngl_mt19937_64_state_t *state, uint32_t k);

uint32_t fpngl_mt19937_64_next32(fpngl_mt19937_64_state_t *state);

void fpngl_mt19937_64_array32(fpngl_mt19937_64_state_t *state, uint32_t *T, uint32_t n);
void fpngl_mt19937_64_array64(fpngl_mt19937_64_state_t *state, uint64_t *T, uint32_t n);


#ifdef __cplusplus
}
#endif
	
#endif // __mt19937_64_h__
