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
	This implementation of the Walker/Vose algoritm is a C reimplementation of
	the java version by Keith Schwarz:
	https://www.keithschwarz.com/interesting/code/?dir=alias-method
*/

#include <global.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <fpnglib/discrete_distribution.h>
#include <fpnglib/uistack.h>
#include <fpnglib/frng64_division_k.h>
#include <fpnglib/irange.h>

struct fpngl_ddistribution_t {
	fpngl_frng64_t *frng;
	fpngl_irng_t *irng;
	uint32_t *alias;
	double *probability;
	uint32_t n; 
};

fpngl_ddistribution_t *fpngl_ddistribution_new(fpngl_irng_t *rng,
																							 const double P[], uint32_t szP)
{
	fpngl_ddistribution_t *dist = malloc(sizeof(fpngl_ddistribution_t));
	dist->irng = rng;
	dist->frng = fpngl_div53(rng,fpngl_irng_seed(rng));
	dist->alias = calloc(szP,sizeof(uint32_t));
	dist->probability = calloc(szP,sizeof(double));
	dist->n = szP;
	double average = 1.0/szP;
	double *probabilities = calloc(szP,sizeof(double));
	assert(szP < (1UL << 30)); // uistack cannot contain more than 2^30 elements
	memcpy(probabilities,P,szP*sizeof(double));
	fpngl_uistack_t *small = fpngl_uistack_new();
	fpngl_uistack_t *large = fpngl_uistack_new();

	for (uint32_t i = 0; i < szP; ++i) {
		if (probabilities[i] >= average) {
			fpngl_uistack_push(large,i);
		} else {
			fpngl_uistack_push(small,i);
		}
	}

	while (!fpngl_uistack_empty(small) && !fpngl_uistack_empty(large)) {
		uint32_t less = fpngl_uistack_pop(small);
		uint32_t more = fpngl_uistack_pop(large);
		dist->probability[less] = probabilities[less]*szP;
		dist->alias[less] = more;

		probabilities[more] = (probabilities[more] + probabilities[less]) - average;
		if (probabilities[more] >= average) {
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
	free(probabilities);
	return dist;
}
	
void fpngl_ddistribution_delete(fpngl_ddistribution_t* dd)
{
	assert(dd != NULL);
	fpngl_frng64_delete(dd->frng); // Also deletes dist->irng
	free(dd->alias);
	free(dd->probability);
	free(dd);
}

uint32_t fpngl_ddistribution_next32(fpngl_ddistribution_t *dd)
{
	assert(dd != NULL);
	uint32_t column = fpngl_ubound32(dd->irng,dd->n);
	double d = fpngl_frng64_nextf64(dd->frng);
	bool coinToss = d < dd->probability[column];
	FPNGL_DEBUG("G/P: %g %g\n",d,dd->probability[column]);
	FPNGL_DEBUG("C/T: %u %d\n",column,coinToss);
	return (coinToss) ? column : dd->alias[column];
}
