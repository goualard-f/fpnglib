/* Generation of 32 bits random integers with the von Neumann/Metropolis algorithm.

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

#ifndef __fpngl_irng32_vnm_h__
#define __fpngl_irng32_vnm_h__

#include <fpnglib/fpngl_config.h>
#include <stdint.h>
#include <fpnglib/irng32_t.h>

#ifdef __cplusplus
extern "C" {
#endif

	/*
		Generation of random floating-poing numbers according to the paper 
		_Various techniques used in connection with random digits_, John von Neumann. 
		In A.S. Householder, G.E. Forsythe, and H.H. Germond, eds. Monte Carlo Method, 
		National Bureau of Standards Applied Mathematics Series, vol. 12:pp. 36--38.

		The seed must be greater than 255, and preferably much larger, otherwise
		the function will only return 0.
	 */
	fpngl_irng32_t *fpngl_von_neumann_metropolis(uint32_t seed);
	
#ifdef __cplusplus
}
#endif

#endif // __fpngl_irng32_vnm_h__
