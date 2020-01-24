/* Original 64 bits Mersenne Twister by Nishimura & Matsumoto.

	 Some cosmetic modifications made for the FPNGlib library. The biggest 
	 modification is the creationg of a local state instead of a global state to allow
	 parallel calls and more than one MT RNG.

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

/* 
   A C-program for MT19937-64 (2004/9/29 version).
   Coded by Takuji Nishimura and Makoto Matsumoto.

   This is a 64-bit version of Mersenne Twister pseudorandom number
   generator.

   Before using, initialize the state by using init_genrand64(seed)  
   or init_by_array64(init_key, key_length).

   Copyright (C) 2004, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.                          

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

     1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

     3. The names of its contributors may not be used to endorse or promote 
        products derived from this software without specific prior written 
        permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

   References:
   T. Nishimura, ``Tables of 64-bit Mersenne Twisters''
     ACM Transactions on Modeling and 
     Computer Simulation 10. (2000) 348--357.
   M. Matsumoto and T. Nishimura,
     ``Mersenne Twister: a 623-dimensionally equidistributed
       uniform pseudorandom number generator''
     ACM Transactions on Modeling and 
     Computer Simulation 8. (Jan. 1998) 3--30.

   Any feedback is very welcome.
   http://www.math.hiroshima-u.ac.jp/~m-mat/MT/emt.html
   email: m-mat @ math.sci.hiroshima-u.ac.jp (remove spaces)
*/

#include <global.h>
#include <stdlib.h>
#include <assert.h>
#include <fpnglib/mt19937-64.h>
#include <fpnglib/utilities.h>

#define NN 312
#define MM 156
#define MATRIX_A 0xB5026F5AA96619E9ULL
#define UM 0xFFFFFFFF80000000ULL /* Most significant 33 bits */
#define LM 0x7FFFFFFFULL /* Least significant 31 bits */

typedef struct fpngl_mt19937v64_state_t {
	/* The array for the state vector */
	uint64_t mt[NN]; 
	int mti; 
} fpngl_mt19937v64_state_t;



/* initializes mt[NN] with a seed */
fpngl_mt19937v64_state_t *fpngl_init_mt19937v64(uint64_t seed)
{
	fpngl_mt19937v64_state_t *state = malloc(sizeof(fpngl_mt19937v64_state_t));
	if (state == NULL) { // Error in allocating memory for the state?
		return NULL;
	}
	state->mti = NN;
	
	state->mt[0] = seed;
	for (int mti=1; mti<NN; mti++) {
		state->mt[mti] =  (6364136223846793005ULL * (state->mt[mti-1] ^
																								 (state->mt[mti-1] >> 62)) + mti);
	}
	return state;
}

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
fpngl_mt19937v64_state_t *fpngl_init_mt19937v64_by_array64(uint64_t init_key[],
																													 uint64_t key_length)
{
	uint64_t i = 1, j = 0, k = (NN>key_length ? NN : key_length);
	fpngl_mt19937v64_state_t *state = fpngl_init_mt19937v64(19650218ULL);

	for (; k; k--) {
		state->mt[i] = (state->mt[i] ^ ((state->mt[i-1] ^
																		 (state->mt[i-1] >> 62)) * 3935559000370003845ULL))
			+ init_key[j] + j; /* non linear */
		i++; j++;
		if (i>=NN) {
			state->mt[0] = state->mt[NN-1];
			i=1;
		}
		if (j>=key_length) {
			j=0;
		}
	}
	for (k=NN-1; k; k--) {
		state->mt[i] = (state->mt[i] ^ ((state->mt[i-1] ^
																		 (state->mt[i-1] >> 62)) * 2862933555777941757ULL))
			- i; /* non linear */
		i++;
		if (i>=NN) {
			state->mt[0] = state->mt[NN-1];
			i=1;
		}
	}
	state->mt[0] = 1ULL << 63; /* MSB is 1; assuring non-zero initial array */
	return state;
}

void fpngl_free_mt19937v64(fpngl_mt19937v64_state_t *state)
{
	free(state);
}


/* generates a random number on [0, 2^64-1]-interval */
uint64_t fpngl_mt19937v64_next64(fpngl_mt19937v64_state_t *state)
{
	int i;
	uint64_t x;
	static const uint64_t mag01[2]={0ULL, MATRIX_A};

	if (state->mti >= NN) { /* generate NN words at one time */
		for (i=0;i<NN-MM;i++) {
			x = (state->mt[i]&UM)|(state->mt[i+1]&LM);
			state->mt[i] = state->mt[i+MM] ^ (x>>1) ^ mag01[(int)(x&1ULL)];
		}
		for (;i<NN-1;i++) {
			x = (state->mt[i]&UM)|(state->mt[i+1]&LM);
			state->mt[i] = state->mt[i+(MM-NN)] ^ (x>>1) ^ mag01[(int)(x&1ULL)];
		}
		x = (state->mt[NN-1]&UM)|(state->mt[0]&LM);
		state->mt[NN-1] = state->mt[MM-1] ^ (x>>1) ^ mag01[(int)(x&1ULL)];
		
		state->mti = 0;
	}
  
	x = state->mt[state->mti++];
	
	x ^= (x >> 29) & 0x5555555555555555ULL;
	x ^= (x << 17) & 0x71D67FFFEDA60000ULL;
	x ^= (x << 37) & 0xFFF7EEE000000000ULL;
	x ^= (x >> 43);
	
	return x;
}


fpngl_irng64_t *fpngl_new_mt19937v64_64(uint64_t seed)
{
	return  fpngl_new_irng64(seed,"mt19937-64",0,0xffffffffffffffff,
													 fpngl_init_mt19937v64(seed),
													 (uint64_t (*)(void*))fpngl_mt19937v64_next64,
													 (void (*)(void*))fpngl_free_mt19937v64);
}


uint32_t fpngl_mt19937v64_next32(fpngl_mt19937v64_state_t *state)
{
	uint64_t v = fpngl_mt19937v64_next64(state);
	return (uint32_t)(v >> 32);
}

void fpngl_mt19937v64_array32(fpngl_mt19937v64_state_t *state, uint32_t *T, uint32_t n)
{
	// Filling the array two 32 bits values at a time.
	for (uint64_t *p = (uint64_t*)T; p < (uint64_t*)T+n/2; ++p) { // Default implementation
		*p = fpngl_mt19937v64_next64(state);
	}
	// odd(n) => there is still the last cell to fill
	if (fpngl_odd(n)) {
		*(T+n-1)= (uint32_t)(fpngl_mt19937v64_next64(state)>>32);
	}
}

void fpngl_mt19937v64_array64(fpngl_mt19937v64_state_t *state, uint64_t *T, uint32_t n)
{
	for (uint32_t i = 0; i < n; ++i) {
		T[i] = fpngl_mt19937v64_next64(state);
	}
}

uint64_t fpngl_mt19937v64_nextk(fpngl_mt19937v64_state_t *state, uint32_t k)
{
	assert(k < 65 && k != 0);
	return fpngl_mt19937v64_next64(state) >> (64-k);
}


fpngl_irng_t *fpngl_new_mt19937v64(uint64_t seed)
{
	return  fpngl_new_irng(seed,"mt19937-64",0,0xffffffffffffffff,
														fpngl_init_mt19937v64(seed),
														(uint32_t (*)(void*))fpngl_mt19937v64_next32,
														(uint64_t (*)(void*))fpngl_mt19937v64_next64,
														(uint64_t (*)(void*,uint32_t))fpngl_mt19937v64_nextk,
														(void (*)(void*, uint32_t*,uint32_t))fpngl_mt19937v64_array32,
														(void (*)(void*, uint64_t*,uint32_t))fpngl_mt19937v64_array64,
														(void (*)(void*))fpngl_free_mt19937v64);
}
