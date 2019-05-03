/*  Functions generating random integers

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

#include <stdlib.h>
#include <fpnglib/random.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

// Random number generator
struct fpngl_rng_t {
  gsl_rng *rng;
  const char *name;
  unsigned long int seed;
};

// Floating-point distribution
struct fpngl_fp_distribution_t {
  fpngl_rng_t *rng;
  gsl_ran_discrete_t *dd;
};


fpngl_rng_t *fpngl_create_rng(unsigned long int seed)
{
  fpngl_rng_t *rng = malloc(sizeof(fpngl_rng_t));
  if (rng == NULL) {
	 return NULL;
  }
  
  if (seed != 0) {
	 gsl_rng_default_seed = seed;
  } else {
	 gsl_rng_env_setup();
  }
  rng->rng = gsl_rng_alloc(gsl_rng_default);
  if (rng->rng == NULL) {
	 return NULL;
  }
  rng->name = gsl_rng_name(rng->rng);
  rng->seed = gsl_rng_default_seed;
  return rng;
}

void fpngl_delete_rng(fpngl_rng_t *rng)
{
  gsl_rng_free(rng->rng);
  free(rng);
}


unsigned long int fpngl_rand(fpngl_rng_t *rng)
{
  return gsl_rng_get(rng->rng);
}

unsigned long int fpngl_get_seed(fpngl_rng_t *rng)
{
  return rng->seed;
}


fpngl_fp_distribution_t *fpngl_new_fp_distribution(fpngl_rng_t *rng,
																	const double P[4])
{
  fpngl_fp_distribution_t *fpd = malloc(sizeof(fpngl_fp_distribution_t));
  if (fpd == NULL) {
	 return NULL;
  }
  fpd->rng = rng;
  fpd->dd = gsl_ran_discrete_preproc(4,P);
  if (fpd->dd == NULL) {
	 return NULL;
  }
  return fpd;
}

void fpngl_delete_fp_distribution(fpngl_fp_distribution_t* fpd)
{
  if (fpd == NULL) return;
  
  gsl_ran_discrete_free(fpd->dd);
  free(fpd);
}

size_t fpngl_fp_distribution_value(fpngl_fp_distribution_t *fpd)
{
  return gsl_ran_discrete(fpd->rng->rng, fpd->dd);
}


fpngl_rng_t* fpngl_get_rng(fpngl_fp_distribution_t *fpd)
{
  return fpd->rng;
}
