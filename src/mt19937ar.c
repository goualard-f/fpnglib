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

/* 
   A C-program for MT19937, with initialization improved 2002/1/26.
   Coded by Takuji Nishimura and Makoto Matsumoto.

   Before using, initialize the state by using init_genrand(seed)  
   or init_by_array(init_key, key_length).

   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
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


   Any feedback is very welcome.
   http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
   email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
*/

#include <global.h>
#include <stdlib.h>
#include <assert.h>
#include <fpnglib/mt19937ar.h>

/* Period parameters */  
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

typedef struct {
	uint32_t mt[N]; /* the array for the state vector  */
	int mti;
} mt19937v32_state_t;
	
/* initializes mt[N] with a seed */
static mt19937v32_state_t *mt19937v32_init(uint32_t s)
{
	mt19937v32_state_t *state = malloc(sizeof(mt19937v32_state_t));
	if (state == NULL) { // Error in allocating memory for the state?
		return NULL;
	}
	state->mti = N;
	state->mt[0]= s & 0xffffffffUL;
	for (int mti=1; mti<N; mti++) {
		state->mt[mti] = (1812433253UL * (state->mt[mti-1] ^ (state->mt[mti-1] >> 30))
											+ mti); 
		/* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
		/* In the previous versions, MSBs of the seed affect   */
		/* only MSBs of the array mt[].                        */
		/* 2002/01/09 modified by Makoto Matsumoto             */
		state->mt[mti] &= 0xffffffffUL;
		/* for >32 bit machines */
	}
	return state;
}


/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
/* slight change for C++, 2004/2/26 */
static mt19937v32_state_t *mt19937v32_init_by_array32(const uint32_t init_key[],
																											uint32_t key_length)
{
	int i = 1, j = 0, k = (N>key_length ? N : key_length);
	mt19937v32_state_t *state = mt19937v32_init(19650218UL);
	for (; k; k--) {
		state->mt[i] = (state->mt[i] ^ ((state->mt[i-1] ^
																		 (state->mt[i-1] >> 30)) * 1664525UL))
			+ init_key[j] + j; /* non linear */
		state->mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
		i++; j++;
		if (i>=N) { state->mt[0] = state->mt[N-1]; i=1; }
		if (j>=key_length) j=0;
    }
	for (k=N-1; k; k--) {
		state->mt[i] = (state->mt[i] ^ ((state->mt[i-1] ^
																		 (state->mt[i-1] >> 30)) * 1566083941UL))
          - i; /* non linear */
		state->mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
		i++;
		if (i>=N) { state->mt[0] = state->mt[N-1]; i=1; }
	}

	state->mt[0] = 0x80000000UL; /* MSB is 1; assuring non-zero initial array */
	return state;
}



static void mt19937v32_free(mt19937v32_state_t *state)
{
	free(state);
}

/* generates a random number on [0,0xffffffff]-interval */
static uint32_t mt19937v32_next32(mt19937v32_state_t *state)
{
	uint32_t y;
	static const uint32_t mag01[2]={0x0UL, MATRIX_A};
	/* mag01[x] = x * MATRIX_A  for x=0,1 */
	
	if (state->mti >= N) { /* generate N words at one time */
		int kk;
		for (kk=0;kk<N-M;kk++) {
			y = (state->mt[kk]&UPPER_MASK)|(state->mt[kk+1]&LOWER_MASK);
			state->mt[kk] = state->mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
		}
		for (;kk<N-1;kk++) {
			y = (state->mt[kk]&UPPER_MASK)|(state->mt[kk+1]&LOWER_MASK);
			state->mt[kk] = state->mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
		}
		y = (state->mt[N-1]&UPPER_MASK)|(state->mt[0]&LOWER_MASK);
		state->mt[N-1] = state->mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

		state->mti = 0;
	}
  
	y = state->mt[state->mti++];

	/* Tempering */
	y ^= (y >> 11);
	y ^= (y << 7) & 0x9d2c5680UL;
	y ^= (y << 15) & 0xefc60000UL;
	y ^= (y >> 18);
	
	return y;
}


static uint64_t mt19937v32_next64(mt19937v32_state_t *state)
{
	return (((uint64_t)mt19937v32_next32(state)) << 32) |
		(uint64_t)mt19937v32_next32(state);
}


static void mt19937v32_array32(mt19937v32_state_t *state, uint32_t *T, uint32_t n)
{
	for (uint32_t i = 0; i < n; ++i) {
		T[i] = mt19937v32_next32(state);
	}
}

static void mt19937v32_array64(mt19937v32_state_t *state, uint64_t *T, uint32_t n)
{
	// Should we try to use next32() instead to fill T cast as a (uint32_t*) ?
	for (uint32_t i = 0; i < n; ++i) {
		T[i] = mt19937v32_next64(state);
	}
}

static uint32_t mt19937v32_nextk(mt19937v32_state_t *state, uint32_t k)
{
	assert(k <= 32 && k != 0);
	return mt19937v32_next32(state) >> (32-k);
}


fpngl_irng32_t *fpngl_mt19937v32(uint32_t seed)
{
	return fpngl_irng32_new(seed,"mt19937v32",0,0xffffffff,
													mt19937v32_init(seed),
													(uint32_t (*)(void*))mt19937v32_next32,
													(uint64_t (*)(void*))mt19937v32_next64,
													(uint32_t (*)(void*, uint32_t))mt19937v32_nextk,
													(void (*)(void*, uint32_t *, uint32_t))mt19937v32_array32,
													(void (*)(void*, uint64_t *, uint32_t))mt19937v32_array64,
													(void (*)(void*))mt19937v32_free);
}

fpngl_irng32_t *fpngl_mt19937v32_by_array(const uint32_t init_key[],
																					uint32_t key_length)
{
	return fpngl_irng32_new(0,"mt19937v32",0,0xffffffff,
													mt19937v32_init_by_array32(init_key, key_length),
													(uint32_t (*)(void*))mt19937v32_next32,
													(uint64_t (*)(void*))mt19937v32_next64,
													(uint32_t (*)(void*, uint32_t))mt19937v32_nextk,
													(void (*)(void*, uint32_t *, uint32_t))mt19937v32_array32,
													(void (*)(void*, uint64_t *, uint32_t))mt19937v32_array64,
													(void (*)(void*))mt19937v32_free);
}
