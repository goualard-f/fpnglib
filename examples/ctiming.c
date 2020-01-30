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

#include "ctiming.h"

#if defined(HAVE_GETRUSAGE)
// ************* getrusage() *****************************************
#include <sys/time.h>
#include <sys/resource.h>

long get_usertime(void)
{
	struct rusage timing;
	getrusage(RUSAGE_SELF,&timing);
	return timing.ru_utime.tv_sec*1000 + timing.ru_utime.tv_usec/1000;
}
 
#elif defined(HAVE_CLOCK)
// ************* clock() *****************************************

long get_usertime(void)
{
	return long((1000.*clock())/CLOCKS_PER_SEC);
}

#else
// ************* ??????? *****************************************
#error "No timing function available."

#endif
