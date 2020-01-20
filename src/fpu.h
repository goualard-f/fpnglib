/* Routines to set/get information in the fpu.

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

#ifndef __fpngl_fpu_h__
#define __fpngl_fpu_h__

#include <fpnglib/fpngl_config.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

	
  /*
		Return FE_INEXACT if the FPU inexact flag was raised by previous computation, and
		0 otherwise.
	*/
  int fpngl_inexact(void);

  /*
		Clear the FPU inexact flag.
	 */
  void fpngl_clear_inexact(void);
 
  
#ifdef __cplusplus
}
#endif

#endif // __fpngl_fpu_h__
