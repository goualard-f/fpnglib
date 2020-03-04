/* Creation of double precision floating-point number with some properties

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

#ifndef __fpngl_float64_h__
#define __fpngl_float64_h__

#include <fpnglib/fpngl_config.h>
#include <stdint.h>
#include <fpnglib/irng_t.h>
#include <fpnglib/types.h>
#include <fpnglib/discrete_distribution.h>

#ifdef __cplusplus
extern "C" {
#endif
	
	/*
	 Return a double precision number that is 'n' floating-point numbers after 'v'.
	 
	 The parameter n must be in the interval [0, 0xffe0000000000000].
  */
  double fpngl_nextafter64(double v, uint64_t n);
  
  /*
	 Return a double precision that is 'n' floating-point numbers before 'v'.
  */
  double fpngl_previous64(double v, uint64_t n);
  
  // Return a random subnormal double precision number
  double fpngl_subnormal64(fpngl_irng_t *rng);
  // Return +0.0 or -0.0 randomly with even probability
  double fpngl_zero64(fpngl_irng_t *rng);
  // Return +oo or -oo randomly with even probability
  double fpngl_inf64(fpngl_irng_t *rng);
  // Return a normal double precision number in [fngl_lambda64,fpngl_max64]
  double fpngl_normal64(fpngl_irng_t *rng);
  // Return a nan
  double fpngl_nan64(fpngl_irng_t *rng);

  /*
	 create_double -- Returns a double precision number
	 according to the specifications:
  
  - s: possible sign 
  - minexp: minimum exponent (biased) in [0,2047]
  - maxexp: maximum exponent (biased) in [0,2047]
  - minfrac: minimum fractional part expressed as an unsigned integer
             between 0x0000000000000000 and 0x000fffffffffffff
  - maxfrac: maximum fractional part expressed as an unsigned integer
             between 0x0000000000000000 and 0x000fffffffffffff
  - andmask: AND mask applied to the 64 bits of the number created.
             Should be 0xffffffffffffffff if no mask is needed.
  - ormask:  OR mask applied to the 64 bits of the number created.
             Should be 0x0000000000000000 if no mask is needed

  WARNING: For better performances, the consistency of the defining
  values are not checked.
*/
  double fpngl_float64(fpngl_irng_t *rng,
											 fpngl_sign_t s,
											 uint32_t minexp, uint32_t maxexp, 
											 uint64_t minfrac, uint64_t maxfrac, 
											 uint64_t andmask,
											 uint64_t ormask);

	// Create a probability distribution for the five classes of floats:
	// { zero, subnormal, normal, infinite, nan }
	fpngl_distribution_t *fpngl_class_float64_new(fpngl_irng_t *irng,
																								 const double P[static 5]);
  /*
	 Return a floating-point number from one of the four classes:
	 { zero, subnormal, normal, infinite, nan }
	 with a probability according to fpd.
  */
  double fpngl_float64_distrib(fpngl_distribution_t *fpd);

  /*
  Computes the number of floats (bounds included) from a to b.
  Return 0 if either a or b are infinites or NaNs.
  Return 1 if a == b
  \pre a must be smaller or equal to b
*/
uint64_t fpngl_distance_float64(double a, double b);

/*
  Computes the number of floats (bounds included) from a to b.
  Returns a negative value if a > b
  Return 0 if either a or b are infinites or NaNs.
  Return 1 if a == b
*/
int64_t fpngl_signed_distance_float64(double a, double b);

 
#ifdef __cplusplus
}
#endif

#endif // __fpngl_float64_h__
