/* Program example drawing numbers according to some discrete distribution.

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
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <fpnglib/mt19937ar.h>
#include <fpnglib/irng_t.h>
#include <fpnglib/discrete_distribution.h>
#include "ctiming.h"

#define SZP 10

const uint32_t seed = 42;
const uint64_t niters = 100000000;


void fill_array(double *P, uint32_t sz)
{
	srand(seed);
	double sum = 0.0;
	for (uint32_t i = 0; i < sz; ++i) {
		P[i] = rand()/((double)RAND_MAX+1);
		sum += P[i];
	}
	// Normalizing to get a sum of probabilities equal to 1
	for (uint32_t i = 0; i < sz; ++i) {
		P[i] /= sum;
	}
}

int main(void)
{
	double P[SZP];
	fill_array(P,SZP);

	uint64_t histo[SZP];
	memset(histo,0,SZP*sizeof(uint64_t));
				 
	fpngl_irng_t *irng = fpngl_irng_new32(fpngl_mt19937v32(seed));
	fpngl_distribution_t *dd = fpngl_distribution_new(irng, P, SZP);

	long begin = get_usertime();
	for (uint64_t i = 0; i < niters; ++i) {
		++histo[fpngl_distribution_next32(dd)];
	}
	long end = get_usertime();
	
	double discrepancy = 0.0;
	for (uint32_t i = 0; i < SZP; ++i) {
		discrepancy += fabs(histo[i]/(double)niters - P[i]);
	}
	printf("\nSum of discrepancies: %g\n",discrepancy);

	printf("Time: %ld μs\n",end-begin);
	
	fpngl_distribution_delete(dd);
}
