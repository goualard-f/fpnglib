/* Computation of a double precision random number using the RNG
   in java.util.Random.

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

#include <global.h>
#include <math.h>
#include <stdlib.h>
#include <fpnglib/frng64_java.h>
#include <fpnglib/lcg.h>
#include <fpnglib/irng64_t.h>

static double java_nextf64(fpngl_irng64_t *irng)
{
	uint64_t xa = fpngl_irng64_next64(irng);
	uint64_t xb = fpngl_irng64_next64(irng);
	return (0x1p+27*trunc(xa*0x1p-22)+trunc(xb*0x1p-21))*0x1p-53;
}

static void java_next_arrayf64(fpngl_irng64_t *irng,
															 double *T, uint32_t n)
{
	// Creating the array dynamically to avoid a size limitation on the stack
	uint64_t *T2 = calloc(2*n,sizeof(uint64_t));
	assert(T2 != NULL);
	fpngl_irng64_array64(irng,T2,2*n);
	uint32_t j = 0;
	for (uint32_t i = 0; i < 2*n ; i+=2) {
		T[j++] =  (0x1p+27*trunc(T2[i]*0x1p-22)+trunc(T2[i+1]*0x1p-21))*0x1p-53;
	}
	free(T2);
}


fpngl_frng64_t *fpngl_java(uint64_t seed)
{
	fpngl_irng64_t *irng = fpngl_drand48_lcg64(seed);
	if (irng == NULL) {
		return NULL;
	}
	return  fpngl_frng64_new("java", irng, 0.0, 0x1.fffffffffffffp-1,
													 (double (*)(void*))java_nextf64,
													 (void (*)(void*, double*, uint32_t))java_next_arrayf64,
													 (void (*)(void*))fpngl_irng64_delete,
													 (uint64_t (*)(void*))fpngl_irng64_seed);
}

