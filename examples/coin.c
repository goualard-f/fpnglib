/* Program example simulating the flipping of a coin.

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

#include <stdio.h>
#include <stdint.h>
#include <fpnglib/mt19937ar.h>
#include <fpnglib/irng_t.h>
#include <fpnglib/irange.h>

const uint32_t seed = 42;
const uint64_t niters = 10000000;

uint32_t fair(fpngl_irng_t *irng)
{
	return fpngl_ubound32(irng,2);
}


uint32_t biased(fpngl_irng_t *irng)
{
	return fpngl_ubound32(irng,3) % 2;
}

int main(void)
{
	uint64_t head_or_tail[2] = {0, 0};
	
	fpngl_irng_t *irng = fpngl_irng_new32(fpngl_mt19937v32(seed));
	
	for (uint64_t i = 0; i < niters; ++i) {
		++head_or_tail[fpngl_ubound32(irng,2)];
	}
	printf("heads: %.2f%%\n",100*(head_or_tail[0]/(double)niters));
	
	fpngl_irng_delete(irng);
}
