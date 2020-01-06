/* Functions generating random integers

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
  The seed for the random generators can be provided through the GSL_RNG_SEED 
  environment variable. If that variable is not set, the value 0 is used instead.
  

 */

#ifndef __fpngl_random_h__
#define __fpngl_random_h__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct fpngl_rng_t  fpngl_rng_t;

  /* Initializes the seed for the pseudo-random generators to 'seed'
	  If seed==0, tries to retrieve a seed value from the GSL_RNG_SEED
	  environment variable. Failing that, uses the default seed for the
	  random generator used (see GSL documentation).
	  
	  Return NULL if memory cannot be allocated to represent the generator.
  */
  fpngl_rng_t *fpngl_create_rng(unsigned long int seed);

  // Releases all resources acquired by the pseudo-random generator 'r'
  void fpngl_delete_rng(fpngl_rng_t* rng);

  // Return next pseudo-random number
  unsigned long int fpngl_rand(fpngl_rng_t *rng);

  // Return the seed used by the RNG
  unsigned long int fpngl_get_seed(fpngl_rng_t *rng);

  // Return the name of the RNG used (see GSL documentation for more info.
  const char *fpngl_get_rng_name(fpngl_rng_t *rng);

  // Return the maximum value the RNG can return
  unsigned long int fpngl_get_rng_max(fpngl_rng_t *rng);

  // Return the minimum value the RNG can return
  unsigned long int fpngl_get_rng_min(fpngl_rng_t *rng);
  
  typedef struct fpngl_fp_distribution_t fpngl_fp_distribution_t;

  /* Create a structure to handle the distribution of possible floating-point
	  numbers according to five categories:
	  { pzero, pdenorm, pnorm, pinf, pnan }
	  $\sum P$ needs not be equal to 1.
	  \return NULL if the result cannot be allocated
  */
  fpngl_fp_distribution_t *fpngl_new_fp_distribution(fpngl_rng_t *rng,
																	  const double P[5]);

  /* Free memory allocated to represent the floating-point number
	  distribution fpd.
  */
  void fpngl_delete_fp_distribution(fpngl_fp_distribution_t* fpd);

  // Return a random value according to the distribution in fpd
  size_t fpngl_fp_distribution_value(fpngl_fp_distribution_t *fpd);

  // Return the rng used in fpd
  fpngl_rng_t* fpngl_get_rng(fpngl_fp_distribution_t *fpd);
  
#ifdef __cplusplus
}
#endif


#endif // __fpgnl_random_h__
