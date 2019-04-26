/* Floating-point number generation (double precision format)

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

#ifndef __fp_double_h__
#define __fp_double_h__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

  typedef union {
	 double d;
	 uint64_t i;
  } fpngl_dui_t;
  
  /*
	 Return a float that is n floating-point numbers after v.
	 
	 The parameter n must be in the interval [1, 0x7fe0000000000000].
  */
  double fpngl_next_float(double v, uint64_t n);
  
  /*
	 Return a float that is n floating-point numbers before v.
  */
  double fpngl_previous_float(double v, uint64_t n);
  
  /*
	 Return the "unit in the first place" of x 
	 See: Accurate floating-point summation part I: faithful rounding. S. M. Rump, 
	 T. Ogita, S. Oishi. SIAM J. Sci. Comput. 31(1), pp. 189--224, 2008.
	 \pre x shall not be an infinity or a NaN	 
  */
  double fpngl_ufp(double x);

  /*
	 Return the "unit in the first place" of x with the sign of x.
	 \pre x shall not be an infinity or a NaN	 
  */
  double fpngl_signed_ufp(double x);

  
#ifdef __cplusplus
}
#endif

#endif // __fp_double_h__
