/* Program example simulating the flipping of a coin

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

/*
	Showing the bias introduced by using the modulo to draw integers in a specific 
	range.
 */

#include <stdio.h>
#include <stdint.h>
#include <fpnglib/mt19937ar.h>
#include <fpnglib/irange.h>

const uint32_t seed = 42;
const uint64_t niters = 1000000000;

fpngl_irng32_t *irng32a;
fpngl_irng32_t *irng32b;

uint32_t fair(void)
{
	return fpngl_ubound32(irng32a,2);
}


uint32_t biased(void)
{
	return fpngl_ubound32(irng32b,3) % 2;
}

int main(void)
{
	uint64_t fairT[2] = {0, 0};
	uint64_t biasedT[2] = {0, 0};

	irng32a = fpngl_mt19937v32(seed);
	irng32b = fpngl_mt19937v32(seed);
	
	for (uint64_t i = 0; i < niters; ++i) {
		++fairT[fair()];
		++biasedT[biased()];
	}
	printf("Percentage of zeros (fair):\t %f\n",100*(fairT[0]/(double)niters));
	printf("Percentage of zeros (biased):\t %f\n",100*(biasedT[0]/(double)niters));
	
	fpngl_irng32_delete(irng32a);
	fpngl_irng32_delete(irng32b);
}
