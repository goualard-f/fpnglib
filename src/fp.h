/* Floating-point number generation

	Copyright 2019 University of Nantes, France.

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

#ifndef __fpngl_fp_h__
#define __fpngl_fp_h__

#include <stdint.h>
#include <fpnglib/random.h>

#ifdef __cplusplus
extern "C" {
#endif


  typedef enum {
	 fpngl_positive,
	 fpngl_negative,
	 fpngl_whatever
  } fpngl_sign_t;

  //Return an integer randomly chosen in the interval [min,max]
  int64_t fpngl_create_integer(fpngl_rng_t *rng, int64_t min, int64_t max);
  
#ifdef __cplusplus
}
#endif


#endif // __fpgnl_fp_h__
