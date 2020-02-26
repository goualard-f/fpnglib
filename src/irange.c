/* Manipulation of the domain of the random integers produced.

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
#include <fpnglib/irange.h>

uint32_t fpngl_n_bits32(uint32_t v, uint32_t n)
{
	assert(n <= 32);
	return v >> (32-n);
}

uint64_t fpngl_n_bits64(uint64_t v, uint32_t n)
{
	assert(n <= 64);
	return v >> (64-n);
}

uint32_t fpngl_ubound32(fpngl_irng_t *irng, uint32_t a)
{
	uint32_t x = fpngl_irng_next32(irng);
	uint64_t m = (uint64_t)x * (uint64_t)a;
	uint32_t l = (uint32_t)m;
	if (l < a) {
		uint32_t t = -a;
		if (t >= a) {
			t -= a;
			if (t >= a) {
				t %= a;
			}
		}
		while (l < t) {
			x = fpngl_irng_next32(irng);
			m = (uint64_t)x * (uint64_t)a;
			l = (uint32_t)m;
		}
	}
	return m >> 32;
}

uint64_t fpngl_ubound64(fpngl_irng_t *irng, uint64_t a)
{
	uint64_t x = fpngl_irng_next64(irng);
#if HAVE_UINT128_T
	// Code from: https://lemire.me/blog/2019/06/06/nearly-divisionless-random-integer-generation-on-various-systems/
  __uint128_t m = (__uint128_t)x * ( __uint128_t )a;
  uint64_t l = (uint64_t)m;
  if (l < a) {
    uint64_t t = -a % a;
    while (l < t) {
      x = fpngl_irng_next64(irng);
      m = (__uint128_t)x * (__uint128_t)a;
      l = (uint64_t)m;
    }
  }
  return m >> 64;
#else
#  if HAVE___BUILTIN_CLZ
	assert(a != 0);
	// Bitmask with Rejection (Unbiased) — Apple's Method
	// from https://www.pcg-random.org/posts/bounded-rands.html
	uint64_t mask = ~uint64_t(0);
	--a;
	mask >>= __builtin_clz(range | 1);
	uint64_t x;
	do {
		x = fpngl_irng_next64(irng) & mask;
	} while (x > a);
	return x;
#  else
	// Debiased Modulo (Once) — Java's Method
	// from https://www.pcg-random.org/posts/bounded-rands.html
	uint64_t x, t;
	do {
		x = fpngl_irng_next64(irng);
		r = x % a;
	} while (x - r > (-a));
	return r;
#  endif
#endif
}

int32_t fpngl_range32(fpngl_irng_t *irng, int32_t a, int32_t b)
{
	int32_t k = b-a;
	return fpngl_ubound32(irng,k) + a;
}

int64_t fpngl_range64(fpngl_irng_t *irng, int64_t a, int64_t b)
{
	int64_t k = b-a;
	return fpngl_ubound64(irng,k) + a;
}

