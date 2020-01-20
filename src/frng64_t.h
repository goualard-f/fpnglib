/* Encapsulation of an RNG able to produce double precision floats

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

#ifndef __fpngl_frng64_t_h__
#define __fpngl_frng64_t_h__

#include <fpnglib/fpngl_config.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct fpngl_frng64_t fpngl_frng64_t;

	fpngl_frng64_t *fpngl_new_frng64_co(uint64_t seed,
																			const char *name,
																			void *state,
																			double (*nextd64)(void*),
																			void (*next_arrayd64)(void *state,
																														double *T, uint32_t n),
																			void (*delete)(void*));
	void fpngl_delete_frng64(fpngl_frng64_t *rng);

	
#ifdef __cplusplus
}
#endif

#endif // __fpngl_frng64_t_h__
