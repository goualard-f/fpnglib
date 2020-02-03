/* Computing of an approximation of π with a Monte Carlo method and various RNGs

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
#include <math.h>
#include <fpnglib/frng64_division_fc.h>
#include <fpnglib/frng64_java.h>
#include <fpnglib/mt19937ar.h>
#include <fpnglib/mt19937-64.h>
#include <fpnglib/irng_t.h>
#include "ctiming.h"

// Approximation of π to 53 bits
const double m_pi = 0x1.921fb54442d18p+1;

// Estimating the value of π by throwing darts into a unit circle.
double pi(fpngl_frng64_t *frng, uint32_t niters)
{
	uint32_t in_circle = 0;
	
	for (uint32_t i = 0; i < niters; ++i) {
		double x = fpngl_frng64_nextf64(frng);
		double y = fpngl_frng64_nextf64(frng);
		in_circle += ((x*x + y*y) <= 1);
	}
	return 4*((double)in_circle / niters);
}

void pi_monte_carlo(fpngl_frng64_t *frng)
{
	printf(">>>>> Méthode %s\n",fpngl_frng64_name(frng));
	double approx = pi(frng,1000000);
	printf("Approximation of π: %.16g\n",approx);
	printf("Relative error: %g\n",fabs(approx-m_pi)/m_pi);
}

int main(void)
{
	const uint64_t seed = 314159;
	fpngl_irng_t *irng32 = fpngl_irng_new32(fpngl_mt19937v32(seed));
	fpngl_irng_t *irng64 = fpngl_irng_new64(fpngl_mt19937v64(seed));
	const uint32_t nmethods = 6;
	fpngl_frng64_t *frngT[6] = {fpngl_bydivision_fc_new("MT19937/32",
																											irng32,fpngl_irng_max(irng32)),
															fpngl_bydivision_fc_new("MT19937/64",
																											irng64,fpngl_irng_max(irng64)),
															
															fpngl_matlabp5(seed),
															fpngl_drand48bsd(seed),
															fpngl_mupad(seed),
															fpngl_java(seed)
	};

	for (uint32_t i = 0; i < nmethods; ++i) {
		long t0 = get_usertime();
		pi_monte_carlo(frngT[i]);
		long t1 = get_usertime();
		printf("Time for %s: %ld μs\n\n",fpngl_frng64_name(frngT[i]),t1-t0);
		fpngl_frng64_delete(frngT[i]);
	}
}
