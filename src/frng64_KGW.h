/* Computation of a double precision random number using the RNG
   by Kolonko, Gu, and Wu.

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

#ifndef __fpngl_frng64_KGW_h__
#define __fpngl_frng64_KGW_h__

#include <fpnglib/fpngl_config.h>
#include <fpnglib/frng64_t.h>
#include <fpnglib/irng_t.h>

#ifdef __cplusplus
extern "C" {
#endif

	/*
		Implementation of the method proposed by 
		Kolonko, Gu, and Wu 
		(https://ideas.repec.org/a/eee/matcom/v157y2019icp130-142.html)
		to create a floating-point number in $(0,1)$ from two random integers.
		
		Generate a floating-point number in ``(0,1)`` by dividing one random integer 
		modulo `M` by another. 
		Three different cases are considered to avoid generating `0` and `1`.

		# Arguments
		- `irng64`: Random Number generator returning an integer in ``[0,M-1]``
		- `seed`: the seed used by `irng64`

		The RNG produced owns the IRNG `irng64` and is responsible for its destruction.
	*/
	fpngl_frng64_t *fpngl_KGW(fpngl_irng_t *irng, uint64_t seed);
	
#ifdef __cplusplus
}
#endif

#endif // __fpngl_frng64_KGW_h__
