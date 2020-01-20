/* Original 32 bits Mersenne Twister by Nishimura & Matsumoto.

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

#ifndef __mt19937ar_h__
#define __mt19937ar__h__

#include <fpnglib/fpngl_config.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// State of an MT19937-32 RNG
typedef struct fpngl_mt19937_32_state_t fpngl_mt19937_32_state_t;

/*
	Initialize the state for an MT19937-32 RNG with the seed `seed`.
	Return NULL if the memory for representing the state could not be allocated.
	The user should call fpngl_free_mt19937_32() to free the memory allocated 
	when the RNG is not needed anymore.
 */
fpngl_mt19937_32_state_t *fpngl_init_mt19937_32(uint32_t seed);

fpngl_mt19937_32_state_t *fpngl_init_mt19937_32_by_array32(uint32_t init_key[],
																													 uint32_t key_length);

void fpngl_free_mt19937_32(fpngl_mt19937_32_state_t *state);

uint32_t fpngl_mt19937_32_next(fpngl_mt19937_32_state_t *state);

#ifdef __cplusplus
}
#endif

	
#endif // __mt19937ar_h__
