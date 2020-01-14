/* Floating-point number generation (double precision format)

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

#ifndef __fpngl_fp_double_h__
#define __fpngl_fp_double_h__

#include <stdint.h>
#include <fpnglib/fp.h>
#include <fpnglib/random.h>

#ifdef __cplusplus
extern "C" {
#endif

  typedef union {
	 double d;
	 uint64_t i;
  } fpngl_dui_t;

 
  /*
	 Return a double precision number that is 'n' floating-point numbers after 'v'.
	 
	 The parameter n must be in the interval [1, 0x7fe0000000000000].
  */
  double fpngl_d_next(double v, uint64_t n);
  
  /*
	 Return a double precision that is 'n' floating-point numbers before 'v'.
  */
  double fpngl_d_previous(double v, uint64_t n);
  
  // Return a random denormal double precision number
  double fpngl_d_create_denormal(fpngl_rng_t *rng);
  // Return +0.0 or -0.0 randomly with even probability
  double fpngl_d_create_zero(fpngl_rng_t *rng);
  // Return +oo or -oo randomly with even probability
  double fpngl_d_create_inf(fpngl_rng_t *rng);
  // Return a normal double precision number in [fngl_d_lambda,fpngl_d_max]
  double fpngl_d_create_normal(fpngl_rng_t *rng);
  // Return a nan
  double fpngl_d_create_nan(fpngl_rng_t *rng);

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
  double fpngl_d_create_by_field(fpngl_rng_t *rng,
											fpngl_sign_t s, uint32_t minexp, uint32_t maxexp, 
											uint64_t minfrac, uint64_t maxfrac, 
											uint64_t andmask,
											uint64_t ormask);
  

  /*
	 Return a floating-point number from one of the four classes:
	 { zero, denormalized, normalized, infinite, nan }
	 with a probability according to fpd.
  */
  double fpngl_d_create_by_distrib(fpngl_fp_distribution_t *fpd);

  /*
  Computes the number of floats (bounds included) from a to b.
  Return 0 if either a or b are infinites or NaNs.
  Return 1 if a == b
  \pre a must be smaller or equal to b
*/
uint64_t fpngl_d_unfp(double a, double b);

/*
  Computes the number of floats (bounds included) from a to b.
  Returns a negative value if a > b
  Return 0 if either a or b are infinites or NaNs.
  Return 1 if a == b
*/
int64_t fpngl_d_nfp(double a, double b);
  

  
#ifdef __cplusplus
}
#endif

#endif // __fpngl_fp_double_h__
