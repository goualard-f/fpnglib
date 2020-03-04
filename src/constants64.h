/* Useful double precision constants.

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
#ifndef __fpngl_constants64_h__
#define __fpngl_constants64_h__

#include <fpnglib/fpngl_config.h>
#include <stdint.h>
#include <float.h>

/*
  Defining constants according to:
  Accuracy and Stability of Numerical Algorithms. 
  Nicholas J. Higham. SIAM
 */

// Double precision format **************************************
// **************************************************************
// Number of bits in the significand of a double precision number
static const uint32_t fpngl_t64 = 53;
// Smallest unbiased exponent of a double precision number
static const int32_t fpngl_emin64 = -1022;
// Largest unbiased exponent of a double precision number
static const int32_t fpngl_emax64 = 1023;
// Unit roundoff for a double precision number
static const double fpngl_u64 = 0.5*DBL_EPSILON;
// Smallest positive normal double precision number
static const double fpngl_lambda64 = DBL_MIN;
// Smallest positive double precision number
static const double fpngl_mu64 = DBL_MIN*DBL_EPSILON;
static const double fpngl_NaN64 = 0.0/0.0;
static const double fpngl_infinity64 = 1.0/0.0;
// Largest positive finite double precision number
static const double fpngl_max64 = DBL_MAX;

/*
	Constants used in defining constraints on floating-point numbers
 */
// Minimum fractional part in a 64 bits float
static const uint64_t fpngl_minfrac64 = 0x0000000000000000;
// Maximum fractional part in a 64 bits float
static const uint64_t fpngl_maxfrac64 = 0x000fffffffffffff;
// No AND mask on the fractional part of a 64 bits float
static const uint64_t fpngl_noand64 = 0xffffffffffffffff;
// No OR mask on the fractional part of a 64 bits float
static const uint64_t fpngl_noor64 = 0x0000000000000000;


#endif // __fpngl_constants64_h__
