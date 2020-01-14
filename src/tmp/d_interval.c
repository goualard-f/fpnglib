/* Generation of intervals with random double precision bounds

	Copyright 2019 University of Nantes, France.

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

#include <assert.h>
#include <math.h>
#include <fpnglib/fpu.h>
#include <fpnglib/d_interval.h>
#include <fpnglib/fp_double.h>
#include <fpnglib/constants.h>

void fpngl_d_interval(fpngl_fp_distribution_t* fpd, double *l, double *r)
{
  double ll = fpngl_d_create_by_distrib(fpd);
  double rr = fpngl_d_create_by_distrib(fpd);
  
  if ((ll == rr) && isinf(ll)) { // [ -oo, -oo ] || [ +oo, +oo ] => replaced by [-oo, +oo]
	 *l = -fpngl_d_infinity;
	 *r = fpngl_d_infinity;;
  } else {
	 if (ll > rr) {
		*l = rr;
		*r = ll;
	 } else {
		*l = ll;
		*r = rr;
	 }
  }
}

static inline unsigned long int randsize(fpngl_rng_t *rng, uint32_t min, uint32_t max)
{
  return fpngl_rand(rng) % (max - min + 1) + min;
}

void fpngl_d_interval_by_size(fpngl_fp_distribution_t* fpd,
										uint64_t szfpmin, uint64_t szfpmax,
										double* l, double* r)
{
  assert(szfpmin >= 1 && szfpmax >= 1);

  double ll = fpngl_d_create_by_distrib(fpd);
  if (ll > 0 && isinf(ll)) {
	 *l = -fpngl_d_infinity;
  }
  uint64_t v = randsize(fpngl_get_rng(fpd),szfpmin-1,szfpmax-1);
  *r = fpngl_d_next(*l,v);
}
