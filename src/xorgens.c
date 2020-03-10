/* Implementation of xorgens algorithms by Richard P. Brent.

	 The code given here is a slight modification of the files xorgens.h and xorgens.c 
	 available at https://maths-people.anu.edu.au/~brent/random.html to obey the 
	 conventions of FPNGlib. The original copyright statement is given after this
	 comment.

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

/* xorgens.c version 3.06, R. P. Brent, 20080920..20171215

==========================================================================
|                                                                        |
|  Copyright (C) 2004, 2006, 2008, 2017 R. P. Brent.                                 |
|                                                                        |
|  This program is free software; you can redistribute it and/or         |
|  modify it under the terms of the GNU General Public License,          |
|  version 2, June 1991, as published by the Free Software Foundation.   |
|  For details see http://www.gnu.org/copyleft/gpl.html .                |
|                                                                        |
|  If you would like to use this software but the GNU GPL creates legal  |
|  problems, then please contact the author to negotiate a special       |
|  agreement.                                                            |
|                                                                        |
==========================================================================

   For type definitions see xorgens.h */


#include <global.h>
#include <stdlib.h>
#include <string.h>
#include <fpnglib/xorgens.h>
#include <fpnglib/utilities.h>

typedef struct {
	uint32_t seed;
	uint32_t w;
	uint32_t weyl;
	uint32_t zero;
	uint32_t x[128];
	int i;
} xor4096iv32_state_t;

typedef struct {
	uint64_t seed;
	uint64_t w;
	uint64_t weyl;
	uint64_t zero;
	uint64_t x[128];
	int i;
} xor4096iv64_state_t;

static void *copy_state32(xor4096iv32_state_t *state)
{
	xor4096iv32_state_t *c = malloc(sizeof(xor4096iv32_state_t));
	assert(c != NULL);
	memcpy(c,state,sizeof(xor4096iv32_state_t));
	return c;
}

static void *copy_state64(xor4096iv64_state_t *state)
{
	xor4096iv64_state_t *c = malloc(sizeof(xor4096iv64_state_t));
	assert(c != NULL);
	memcpy(c,state,sizeof(xor4096iv64_state_t));
	return c;
}

static xor4096iv32_state_t *xor4096iv32_init(uint32_t seed)
{
	xor4096iv32_state_t *state = malloc(sizeof(xor4096iv32_state_t));
	assert(state != NULL);

	state->seed = seed;
	state->zero = 0;
	state->i = -1;
	return state;
}

static void xor4096iv32_free(xor4096iv32_state_t *state)
{
	free(state);
}

static uint32_t xor4096iv32_next32(xor4096iv32_state_t *state)
{
  /* 32-bit or 64-bit integer random number generator 
     with period at least 2**4096-1.
     
     It is assumed that "UINT" is a 32-bit or 64-bit integer 
     (see typedef statements in xorgens.h).
     
     xor4096i should be called exactly once with nonzero seed, and
     thereafter with zero seed.  
     
     One random number uniformly distributed in [0..2**wlen) is returned,
     where wlen = 8*sizeof(UINT) = 32 or 64.
		 
     R. P. Brent, 20060628.
  */
	
#define wlen 32
#define r    128
#define s    95
#define a    17
#define b    12
#define c    13
#define d    15
#define ws   16

		uint32_t t, v;
		unsigned int k;
  
		if (state->i < 0) { /* Initialisation necessary */
			
			/* weyl = odd approximation to 2**wlen*(3-sqrt(5))/2. */

      state->weyl = 0x61c88647;
			v = state->seed;

			for (k = wlen; k > 0; k--) {   /* Avoid correlations for close seeds */
				v ^= v<<10; v ^= v>>15;      /* Recurrence has period 2**wlen-1 */ 
				v ^= v<<4;  v ^= v>>13;      /* for wlen = 32 or 64 */
      }
			for (state->w = v, k = 0; k < r; k++) { /* Initialise circular array */
				v ^= v<<10; v ^= v>>15; 
				v ^= v<<4;  v ^= v>>13;
				state->x[k] = v + (state->w += state->weyl);                
      }
			for (state->i = r-1, k = 4*r; k > 0; k--) { /* Discard first 4*r results */ 
				t = state->x[state->i = (state->i+1)&(r-1)];
				t ^= t<<a;  t ^= t>>b; 
				v = state->x[(state->i+(r-s))&(r-1)];
				v ^= v<<c;
				v ^= v>>d;          
				state->x[state->i] = t^v;       
      }
    }
    
  /* Apart from initialisation (above), this is the generator */

		t = state->x[state->i = (state->i+1)&(r-1)];  /* Assumes that r is a power of two */
		v = state->x[(state->i+(r-s))&(r-1)];            /* Index is (i-s) mod r */
		t ^= t<<a;  t ^= t>>b;             /* (I + L^a)(I + R^b) */
		v ^= v<<c;  v ^= v>>d;             /* (I + L^c)(I + R^d) */
		state->x[state->i] = (v ^= t);                   /* Update circular array */
		state->w += state->weyl;                         /* Update Weyl generator */
		return (v + (state->w^(state->w>>ws)));          /* Return combination */

#undef wlen
#undef r
#undef s
#undef a
#undef b
#undef c
#undef d
#undef ws 
}

static uint64_t xor4096iv32_next64(xor4096iv32_state_t *state)
{
	return (((uint64_t)xor4096iv32_next32(state)) << 32) |
		(uint64_t)xor4096iv32_next32(state);
}

static void xor4096iv32_array32(xor4096iv32_state_t *state, uint32_t *T, uint32_t n)
{
	for (uint32_t i = 0; i < n; ++i) {
		T[i] = xor4096iv32_next32(state);
	}
}

static void xor4096iv32_array64(xor4096iv32_state_t *state, uint64_t *T, uint32_t n)
{
	// Should we try to use next32() instead to fill T cast as a (uint32_t*) ?
	for (uint32_t i = 0; i < n; ++i) {
		T[i] = xor4096iv32_next64(state);
	}
}

static uint32_t xor4096iv32_nextk(xor4096iv32_state_t *state, uint32_t k)
{
	assert(k <= 32 && k != 0);
	return xor4096iv32_next32(state) >> (32-k);
}

fpngl_irng32_t *fpngl_xor4096iv32(uint32_t seed)
{
	return fpngl_irng32_new(seed,"xor4096iv32",0,0xffffffff,
													xor4096iv32_init(seed),
													(void* (*)(void*))copy_state32,
													(uint32_t (*)(void*))xor4096iv32_next32,
													(uint64_t (*)(void*))xor4096iv32_next64,
													(uint32_t (*)(void*, uint32_t))xor4096iv32_nextk,
													(void (*)(void*, uint32_t *, uint32_t))xor4096iv32_array32,
													(void (*)(void*, uint64_t *, uint32_t))xor4096iv32_array64,
													(void (*)(void*))xor4096iv32_free);
}

static xor4096iv64_state_t *xor4096iv64_init(uint32_t seed)
{
	xor4096iv64_state_t *state = malloc(sizeof(xor4096iv64_state_t));
	assert(state != NULL);

	state->seed = seed;
	state->zero = 0;
	state->i = -1;
	return state;
}

static void xor4096iv64_free(xor4096iv64_state_t *state)
{
	free(state);
}

static uint64_t xor4096iv64_next64(xor4096iv64_state_t *state)
{
  /* 32-bit or 64-bit integer random number generator 
     with period at least 2**4096-1.
     
     It is assumed that "UINT" is a 32-bit or 64-bit integer 
     (see typedef statements in xorgens.h).
     
     xor4096i should be called exactly once with nonzero seed, and
     thereafter with zero seed.  
     
     One random number uniformly distributed in [0..2**wlen) is returned,
     where wlen = 8*sizeof(UINT) = 32 or 64.

     R. P. Brent, 20060628.
  */

#define wlen 64
#define r    64
#define s    53
#define a    33
#define b    26
#define c    27
#define d    29
#define ws   27

  uint64_t t, v;
  unsigned int k;
  
  if (state->i < 0) {
  
  /* weyl = odd approximation to 2**wlen*(3-sqrt(5))/2. */

		state->weyl = ((((uint64_t)0x61c88646)<<16)<<16) + (uint64_t)0x80b583eb;
                 
    v = state->seed;  /* v must be nonzero */

    for (k = wlen; k > 0; k--) {   /* Avoid correlations for close seeds */
      v ^= v<<10; v ^= v>>15;      /* Recurrence has period 2**wlen-1 */ 
      v ^= v<<4;  v ^= v>>13;      /* for wlen = 32 or 64 */
      }
    for (state->w = v, k = 0; k < r; k++) { /* Initialise circular array */
      v ^= v<<10; v ^= v>>15; 
      v ^= v<<4;  v ^= v>>13;
      state->x[k] = v + (state->w+=state->weyl);                
      }
    for (state->i = r-1, k = 4*r; k > 0; k--) { /* Discard first 4*r results */ 
      t = state->x[state->i = (state->i+1)&(r-1)];
			t ^= t<<a;  t ^= t>>b; 
      v = state->x[(state->i+(r-s))&(r-1)];
			v ^= v<<c;  v ^= v>>d;          
      state->x[state->i] = t^v;       
      }
    }
    
  /* Apart from initialisation (above), this is the generator */

  t = state->x[state->i = (state->i+1)&(r-1)];  /* Assumes that r is a power of two */
  v = state->x[(state->i+(r-s))&(r-1)];            /* Index is (i-s) mod r */
  t ^= t<<a;  t ^= t>>b;             /* (I + L^a)(I + R^b) */
  v ^= v<<c;  v ^= v>>d;             /* (I + L^c)(I + R^d) */
  state->x[state->i] = (v ^= t);                   /* Update circular array */
  state->w += state->weyl;                         /* Update Weyl generator */
  return (v + (state->w^(state->w>>ws)));          /* Return combination */

#undef wlen
#undef r
#undef s
#undef a
#undef b
#undef c
#undef d
#undef ws 
  }

static uint32_t xor4096iv64_next32(xor4096iv64_state_t *state)
{
	uint64_t v = xor4096iv64_next64(state);
	return (uint32_t)(v >> 32);
}

static void xor4096iv64_array32(xor4096iv64_state_t *state,
															 uint32_t *T, uint32_t n)
{
	// Filling the array two 32 bits values at a time.
	for (uint64_t *p = (uint64_t*)T; p < (uint64_t*)T+n/2; ++p) { // Default implementation
		*p = xor4096iv64_next64(state);
	}
	// odd(n) => there is still the last cell to fill
	if (fpngl_odd(n)) {
		*(T+n-1)= (uint32_t)(xor4096iv64_next64(state) >> 32);
	}
}

static void xor4096iv64_array64(xor4096iv64_state_t *state,
															 uint64_t *T, uint32_t n)
{
	for (uint32_t i = 0; i < n; ++i) {
		T[i] = xor4096iv64_next64(state);
	}
}

static uint64_t xor4096iv64_nextk(xor4096iv64_state_t *state, uint32_t k)
{
	assert(k <= 65 && k != 0);
	// Returning only the `k` highest bits of the first 32 bits if `k`
	// is smaller or equal to 32 to have the same behavior as the LCGs (see lcg.c).
	if (k <= 32) {
		return (xor4096iv64_next64(state) >> (32-k)) & 0x00000000ffffffff;
	} else {
		return xor4096iv64_next64(state) >> (64-k);
	}
}


fpngl_irng64_t *fpngl_xor4096iv64(uint64_t seed)
{
	return  fpngl_irng64_new(seed,
													 "xor4096iv64",
													 0, 0xffffffffffffffff,
													 xor4096iv64_init(seed),
													 (void* (*)(void*))copy_state64,
													 (uint32_t (*)(void*))xor4096iv64_next32,
													 (uint64_t (*)(void*))xor4096iv64_next64,
													 (uint64_t (*)(void*,uint32_t))xor4096iv64_nextk,
													 (void (*)(void*,uint32_t*, uint32_t))xor4096iv64_array32,
													 (void (*)(void*,uint64_t*, uint32_t))xor4096iv64_array64,
													 (void (*)(void*))xor4096iv64_free);
}


static float xor4096rv32_nextf32(xor4096iv32_state_t *state)
{
  /* 64-bit or 32-bit real random number generator 
     with period at least 2**4096-1.
     
     It is assumed that "UINT" is a 32-bit or 64-bit integer and "UREAL"
     is "double" or "float". If "double" this is an IEEE standard
     floating-point number with 53 bits in the fraction; if "single" it 
     has 24 bits in the fraction (including 1 implicit bit in each case).
     
     In the 64-bit integer case, the method used is to call xor4096i to get
     64 random bits, then the high 53 (for double) or 24 bits (for float)
     are scaled to the open interval (0.0, 1.0), except that they are
     discarded if all zero.

     In the 32-bit integer case, one or two calls to xor4096i are made to
     get 32 or 64 random bits, some are discarded, and the remaining bits
     (if nonzero) are scaled to the open interval (0.0, 1.0).  

     xor4096r should be called exactly once with nonzero seed, and
     thereafter with zero seed.

     One random number of type UREAL is returned per call.
     
     The results be should uniformly distributed in (0.0, 1.0) to the
     resolution of the floating-point system (0.5**53 or 0.5**24).  

     The results are never exactly 0.0 or 1.0.

     R. P. Brent, 20060628.
     */
     
#define UINT64 0
#define UINT32 1
#define UREAL64 0
#define UREAL32 1

/* sr = number of bits discarded = 11 for double, 40 or 8 for float */
 
#define sr (11*UREAL64 +(40*UINT64 + 8*UINT32)*UREAL32)

/* ss (used for scaling) is 53 or 21 for double, 24 for float */

#define ss ((53*UINT64 + 21*UINT32)*UREAL64 + 24*UREAL32)

/* SCALE is 0.5**ss, SC32 is 0.5**32 */

#define SCALE ((float)1/(float)((uint32_t)1<<ss)) 
#define SC32  ((float)1/((float)65536*(float)65536)) 

  float res;
  
  res = 0.0f; 
  while (res == 0.0f)               /* Loop until nonzero result.   */
    {                                   /* Usually only one iteration . */
    res = (float)(xor4096iv32_next32(state)>>sr);  /* Discard sr random bits.  */
    state->seed = (uint32_t)0;                     /* Zero seed for next time. */
    if (UINT32 && UREAL64)              /* Need another call to xor4096i. */
      res += SC32*(float)xor4096iv32_next32(state);/* Add low-order 32 bits. */
    }
  return (SCALE*res);                   /* Return result in (0.0, 1.0). */  

#undef UINT64
#undef UINT32
#undef UREAL64
#undef UREAL32
#undef SCALE
#undef SC32
#undef sr
#undef ss
}


static double xor4096rv64_nextf64(xor4096iv64_state_t *state)
{
  /* 64-bit or 32-bit real random number generator 
     with period at least 2**4096-1.
     
     It is assumed that "UINT" is a 32-bit or 64-bit integer and "UREAL"
     is "double" or "float". If "double" this is an IEEE standard
     floating-point number with 53 bits in the fraction; if "single" it 
     has 24 bits in the fraction (including 1 implicit bit in each case).
     
     In the 64-bit integer case, the method used is to call xor4096i to get
     64 random bits, then the high 53 (for double) or 24 bits (for float)
     are scaled to the open interval (0.0, 1.0), except that they are
     discarded if all zero.

     In the 32-bit integer case, one or two calls to xor4096i are made to
     get 32 or 64 random bits, some are discarded, and the remaining bits
     (if nonzero) are scaled to the open interval (0.0, 1.0).  

     xor4096r should be called exactly once with nonzero seed, and
     thereafter with zero seed.

     One random number of type UREAL is returned per call.
     
     The results be should uniformly distributed in (0.0, 1.0) to the
     resolution of the floating-point system (0.5**53 or 0.5**24).  

     The results are never exactly 0.0 or 1.0.

     R. P. Brent, 20060628.
     */

#define UINT64 1
#define UINT32 0
#define UREAL64 1
#define UREAL32 0

/* sr = number of bits discarded = 11 for double, 40 or 8 for float */
 
#define sr (11*UREAL64 +(40*UINT64 + 8*UINT32)*UREAL32)

/* ss (used for scaling) is 53 or 21 for double, 24 for float */

#define ss ((53*UINT64 + 21*UINT32)*UREAL64 + 24*UREAL32)

/* SCALE is 0.5**ss, SC32 is 0.5**32 */

#define SCALE ((double)1/(double)((uint64_t)1<<ss)) 
#define SC32  ((double)1/((double)65536*(double)65536)) 

  double res = 0.0;
  
  while (res == 0.0)               /* Loop until nonzero result.   */
    {                                   /* Usually only one iteration . */
    res = (double)(xor4096iv64_next64(state)>>sr);  /* Discard sr random bits.  */
    state->seed = (uint64_t)0;                     /* Zero seed for next time. */
    if (UINT32 && UREAL64)              /* Need another call to xor4096i. */
      res += SC32*(double)xor4096iv64_next64(state);/* Add low-order 32 bits. */
    }
  return (SCALE*res);                   /* Return result in (0.0, 1.0). */  

#undef UINT64
#undef UINT32
#undef UREAL64
#undef UREAL32
#undef SCALE
#undef SC32
#undef sr
#undef ss
}


static void xor4096rv32_next_arrayf32(xor4096iv32_state_t *state, float *T, uint32_t n)
{
	for (uint32_t i = 0; i < n; ++i) {
		T[i] = xor4096rv32_nextf32(state);
	}
}

static void xor4096rv64_next_arrayf64(xor4096iv64_state_t *state, double *T, uint32_t n)
{
	for (uint32_t i = 0; i < n; ++i) {
		T[i] = xor4096rv64_nextf64(state);
	}
}

static uint32_t xor4096iv32_seed(xor4096iv32_state_t *irng)
{
	return irng->seed;
}

static uint32_t xor4096iv64_seed(xor4096iv64_state_t *irng)
{
	return irng->seed;
}

fpngl_frng32_t *fpngl_xor4096rv32(uint32_t seed)
{
	return fpngl_frng32_new("xor4096rv32",xor4096iv32_init(seed),
													(float (*)(void*))xor4096rv32_nextf32,
													(void (*)(void *,float*,uint32_t))xor4096rv32_next_arrayf32,
													(void (*)(void*))xor4096iv32_free,
													(uint32_t (*)(void*))xor4096iv32_seed);
}


fpngl_frng64_t *fpngl_xor4096rv64(uint64_t seed)
{
	return fpngl_frng64_new("xor4096rv64",xor4096iv64_init(seed),
													(double (*)(void*))xor4096rv64_nextf64,
													(void (*)(void *,double*,uint32_t))xor4096rv64_next_arrayf64,
													(void (*)(void*))xor4096iv64_free,
													(uint64_t (*)(void*))xor4096iv64_seed);
}	
	
