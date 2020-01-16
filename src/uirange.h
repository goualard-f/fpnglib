/* Manipulation of the domain of the random integers produced.

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
	+ Reduction of the domain by shifting
	+ Shift to some specific domain [a,b]
 */

#ifndef __uirange_h__
#define __uirange_h__

#include <stdint.h>

/*
	Return an bits unsigned integer composed with the `n` highest bits of `v`.
	
 */
uint32_t fpngl_get_n_bits32(uint32_t v, uint32_t n);
uint64_t fpngl_get_n_bits64(uint64_t v, uint32_t n);

/*
	Return an integer in the domain [a,b]
 */


#endif // __uirange_h__
