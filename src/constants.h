/* Useful double precision constants.

	Copyright 2019 University of Nantes, France.

	This file is part of the FPNGlib library.

	The FPNGlib library brary is free software; you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by the 
	Free Software Foundation; either version 3 of the License, or (at your
	option) any later version.
	
	The FPNGlib Library is distributed in the hope that it will be useful, but
	WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
	or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
	for more details.
	
	You should have received copies of the GNU General Public License and the
	GNU Lesser General Public License along with the FPNGlib Library.  If not,
	see https://www.gnu.org/licenses/. 	
	
 */
#ifndef __constants_h__
#define __constants_h__

#include <float.h>

/*
  Defining constants according to:
  Accuracy and Stability of Numerical Algorithms. 
  Nicholas J. Higham. SIAM
 */

// Number of bits in the significand of a double precision number
const double fpngl_d_t = 53;
// Smallest unbiased exponent of a double precision number
const double fpngl_d_emin = -1022;
// Largest unbiased exponent of a double precision number
const double fpngl_d_emax = 1023;
const double fpngl_d_u = 0.5*DBL_EPSILON;
// Smallest positive normalized double precision number
const double fpngl_d_lambda = DBL_MIN;
// Smallest positive double precision number
const double fpngl_d_mu = DBL_MIN*DBL_EPSILON;
const double fpngl_d_NaN = 0.0/0.0;
const double fpngl_d_infinity = 1.0/0.0;
const double fpngl_d_max = DBL_MAX;
#endif // __constants_h__
