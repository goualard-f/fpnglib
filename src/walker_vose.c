/* Implementation of the Walker/Vose algorithm for sampling from a discrete 
	 distribution.

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
	This implementation of the Walker/Vose algoritm is mostly a 
	C reimplementation of	the java version by Keith Schwarz:
	https://www.keithschwarz.com/interesting/code/?dir=alias-method
*/

#include <global.h>
#include <stdlib.h>
#include <string.h>
#include <fpnglib/discrete_distribution.h>
#include <fpnglib/uistack.h>
#include <fpnglib/frng64_division_k.h>
#include <fpnglib/irange.h>

struct fpngl_distribution_t {
	fpngl_frng64_t *frng;
	fpngl_irng_t *irng;
	uint32_t *alias;
	double *probability;
	uint32_t n; 
};

fpngl_distribution_t *fpngl_distribution_new(fpngl_irng_t *rng,
																							 const double P[], uint32_t szP)
{
	assert(szP <= (1UL << 30)); // uistack cannot contain more than 2^30 elements
	assert(rng != NULL);
	fpngl_distribution_t *dist = malloc(sizeof(fpngl_distribution_t));
	assert(dist != NULL);
	dist->irng = rng;
	// The FRNG used cannot be chosen at present. Should we reconsider that?
	dist->frng = fpngl_div32(rng);
	dist->alias = calloc(szP,sizeof(uint32_t));
	assert(dist->alias != NULL);
	dist->probability = calloc(szP,sizeof(double));
	assert(dist->probability != NULL);
	dist->n = szP;
	double *probabilities = calloc(szP,sizeof(double));
	assert(probabilities != NULL);
	
	fpngl_uistack_t *small = fpngl_uistack_new();
	fpngl_uistack_t *large = fpngl_uistack_new();

	for (uint32_t i = 0; i < szP; ++i) {
		probabilities[i] = P[i]*szP;
		if (probabilities[i] >= 1.0) {
			fpngl_uistack_push(large,i);
		} else {
			fpngl_uistack_push(small,i);
		}
	}

	while (!fpngl_uistack_empty(small) && !fpngl_uistack_empty(large)) {
		uint32_t less = fpngl_uistack_pop(small);
		uint32_t more = fpngl_uistack_pop(large);
		dist->probability[less] = probabilities[less];
		dist->alias[less] = more;

		probabilities[more] = probabilities[more] + probabilities[less] - 1.0;
		if (probabilities[more] >= 1.0) {
			fpngl_uistack_push(large,more);
		} else {
			fpngl_uistack_push(small,more);
		}
	}

	while (!fpngl_uistack_empty(small)) {
		dist->probability[fpngl_uistack_pop(small)] = 1.0;
	}
	while (!fpngl_uistack_empty(large)) {
		dist->probability[fpngl_uistack_pop(large)] = 1.0;
	}
	fpngl_uistack_delete(small);
	fpngl_uistack_delete(large);
	free(probabilities);

	return dist;
}
	
void fpngl_distribution_delete(fpngl_distribution_t* dd)
{
	assert(dd != NULL);
	fpngl_frng64_delete(dd->frng); // Also deletes dist->irng
	free(dd->alias);
	free(dd->probability);
	free(dd);
}

uint32_t fpngl_distribution_next32(fpngl_distribution_t *dd)
{
#if 0
	uint32_t column = fpngl_ubound32(dd->irng,dd->n);
	double d = fpngl_frng64_nextf64(dd->frng);
	return (d < dd->probability[column]) ? column : dd->alias[column];
#endif
	// Code taken from GSL 2.6 (gsl_ran_discrete() in randist/discrete.c)
	double u = fpngl_frng64_nextf64(dd->frng) * dd->n;
	uint32_t c = u;
	u -= c;
	double f = dd->probability[c];
	if (f == 1.0) {
		return c;
	}
	if (u < f) {
		return c;
	} else {
		return dd->alias[c];
	}
}

fpngl_irng_t *fpngl_distribution_rng_internal(fpngl_distribution_t *dd)
{
	assert(dd != NULL);
	return dd->irng;
}
