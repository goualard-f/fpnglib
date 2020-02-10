/* Sampling from a discrete distribution.

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
	These functions address the problem of drawing an integer $i\in[0,n]$ with
	probability $p_i$, where the $p_i$s are double precision floating-point
	numbers.
 */

#ifndef __fpngl_discrete_distribution_h__
#define __fpngl_discrete_distribution_h__

#include <fpnglib/fpngl_config.h>
#include <fpnglib/irng_t.h>

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct fpngl_ddistribution_t fpngl_ddistribution_t;
	
  /* 
		 Create a structure to handle sampling from a discrete distribution.
		 \return NULL if the result cannot be allocated
		 The fpngl_ddistribution_t object owns the rng and is responsible for
		 its destruction.
		 @precondition \sum P = 1
  */
	fpngl_ddistribution_t *fpngl_ddistribution_new(fpngl_irng_t *rng,
																								 const double P[], uint32_t szP);
	
  /* Free memory allocated to represent the distribution `dd`.
  */
  void fpngl_ddistribution_delete(fpngl_ddistribution_t* dd);

  // Return a random value according to the distribution in `dd`.
  uint32_t fpngl_ddistribution_next32(fpngl_ddistribution_t *dd);

	// Return the RNG used internally.
	fpngl_irng_t *fpngl_ddistribution_rng(fpngl_ddistribution_t *dd);

#ifdef __cplusplus
}
#endif

#endif // __fpngl_discrete_distribution_h__
