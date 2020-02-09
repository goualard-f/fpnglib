/* Common types used in the library

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

#ifndef __fpngl_types_h__
#define __fpngl_types_h__

#include <fpnglib/fpngl_config.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

	/*
		Type used to access the fields of a double precision number.
	 */
	typedef union {
		double d;
		uint64_t ui;
	} fpngl_uintf64_t;

	/*
		Type used to access the fields of a single precision number.
	 */
	typedef union {
		float f;
		uint32_t ui;
	} fpngl_uintf32_t;

	// Sign expected for a random floating-point number.
	typedef enum {
			 fpngl_positive,
			 fpngl_negative,
			 fpngl_whatever
  } fpngl_sign_t;

	typedef struct fpngl_fp_distribution_t fpngl_fp_distribution_t;
	
#ifdef __cplusplus
}
#endif

#endif // __fpngl_types_h__
