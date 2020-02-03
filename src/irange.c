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
#include <assert.h>
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

uint32_t fpngl_ubound32(fpngl_irng32_t *irng32, uint32_t a)
{
	uint32_t x = fpngl_irng32_next32(irng32);
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
			x = fpngl_irng32_next32(irng32);
			m = (uint64_t)x * (uint64_t)a;
			l = (uint32_t)m;
		}
	}
	return m >> 32;
}

uint64_t fpngl_ubound64(fpngl_irng64_t *irng64, uint64_t a)
{
	// TODO
	assert(0);
	return 0;
}

int32_t fpngl_range32(fpngl_irng32_t *irng32, int32_t a, int32_t b)
{
	int32_t k = b-a;
	return fpngl_ubound32(irng32,k) + a;
}

int64_t fpngl_range64(fpngl_irng64_t *irng64, int64_t a, int64_t b)
{
	// TODO
	assert(0);
	return 0;
}

