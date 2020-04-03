/* Useful single precision constants.

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
#ifndef __fpngl_constants32_h__
#define __fpngl_constants32_h__

#include <fpnglib/fpngl_config.h>
#include <stdint.h>
#include <float.h>

/*
  Defining constants according to:
  Accuracy and Stability of Numerical Algorithms. 
  Nicholas J. Higham. SIAM, 2002. ISBN: 978-0-89871-521-7
 */

// Double precision format **************************************
// **************************************************************
// Number of bits in the significand of a single precision number
static const uint32_t fpngl_t32 = 24;
// Smallest unbiased exponent of a single precision number
static const int32_t fpngl_emin32 = -126;
// Largest unbiased exponent of a single precision number
static const int32_t fpngl_emax32 = 127;
// Unit roundoff for a single precision number
static const float fpngl_u32 = 0.5f*FLT_EPSILON;
// Smallest positive normal single precision number
static const float fpngl_lambda32 = FLT_MIN;
// Smallest positive single precision number
static const float fpngl_mu32 = FLT_MIN*FLT_EPSILON;
static const float fpngl_NaN32 = 0.0f/0.0f;
static const float fpngl_infinity32 = 1.0f/0.0f;
// Largest positive finite float precision number
static const float fpngl_max32 = FLT_MAX;


#endif // __fpngl_constants32_h__
