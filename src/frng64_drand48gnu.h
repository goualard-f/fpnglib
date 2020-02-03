/*  Generation of a random double precision number by using the implementation
	 of rand48t() in GNU C.

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

#ifndef __fpngl_frng64_drand48gnu_h__
#define __fpngl_frng64_drand48gnu_h__

#include <fpnglib/fpngl_config.h>
#include <stdint.h>
#include <fpnglib/frng64_t.h>

#ifdef __cplusplus
extern "C" {
#endif

	/*
    The POSIX drand48() function as implemented in GNU gcc. 
		Returns a floating-point number in ``[0,1)`` with only 48 bits of entropy.
    *Source*: [IEEE Std 1003.1-2017](http://pubs.opengroup.org/onlinepubs/9699919799/functions/drand48.html) and https://github.com/lattera/glibc/blob/master/stdlib/erand48_r.c
	 */
	fpngl_frng64_t *fpngl_drand48gnu(uint64_t seed);
	
#ifdef __cplusplus
}
#endif

#endif // __fpngl_frng64_drand48gnu_h__
