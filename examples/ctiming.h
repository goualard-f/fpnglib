/* ctiming -- A small library to profile programs

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

#ifndef __ctiming_h__
#define __ctiming_h__

#include <fpnglib/global.h>

#ifdef __cplusplus
extern "C" {
#endif

	/*
		Return the time spent by a program since some epoch.
		Timing some code is done by calling this function at the beginning and end of the
		section to be profiled and subtracting the two results. The result is expressed
		in microseconds.
	*/
	long get_usertime(void);

#ifdef __cplusplus
}
#endif

#endif // __ctiming_h__
