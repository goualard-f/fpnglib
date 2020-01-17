/* Various auxiliary functions

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

#ifndef __utilities_h__
#define __utilities_h__

#include <stdint.h>

// Return 1 if its argument is an odd number and 0 otherwise
inline int fpngl_odd(uint64_t n)
{
	return (n & 1);
}

// Return 1 if its argument is an even number and 0 otherwise
inline int fpngl_even(uint64_t n)
{
	return !fpngl_odd(n);
}

#endif // __utilities_h__
