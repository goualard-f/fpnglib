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

/*
  To be library-agnostic, an interval is represented by a simple pair of 
  two double precision floating-point numbers.
 */

#ifndef __fpngl_d_interval_hpp__
#define __fpngl_d_interval_hpp__

#include <stdint.h>
#include <fpnglib/random.h>

#ifdef __cplusplus
extern "C" {
#endif

  /*
	 Return the left and right bounds of an interval where the bounds are created
	 according to the probability distribution fpd.
  */
  void fpngl_d_interval(fpngl_fp_distribution_t* fpd, double *l, double *r);

  /*
	 Return the bounds of a random interval containing between szfpmin 
	 and szfpmax floating-point numbers, including the bounds themselves.
	 As a consequence, szfpmin and szfpmax must be greater or equal to 1.

	 The distribution fpd should not allow for infinite bounds, otherwise
	 the size of the resulting interval cannot be properly assessed.
	 \TODO Change the way fpngl_d_unfp() computes its result for intervals
	 with infinite bounds?
  */
  void fpngl_d_interval_by_size(fpngl_fp_distribution_t* fpd,
										  uint64_t szfpmin, uint64_t szfpmax,
										  double* l, double* r);

  
#ifdef __cplusplus
}
#endif

#endif // __fpngl_d_interval_hpp__

