/* Testing the time needed to fill an array with MT19937v32

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

#include <stdio.h>
#include <stdint.h>
#include <fpnglib/mt19937ar.h>
#include "ctiming.h"

int main(void)
{
	fpngl_irng32_t *irng = fpngl_mt19937v32(53);
	const uint32_t szT = 1000000;
	uint32_t T[szT];
	long t0 = get_usertime();
	for (uint32_t i = 0; i < szT; ++i) {
		T[i] = fpngl_irng32_next32(irng);
	}
	long t1 = get_usertime();
	fpngl_irng32_array32(irng,T,szT);
	long t2 = get_usertime();
	printf("Loop with next32:  %ld μs\n",t1-t0);
	printf("With array32: %ld μs\n",t2-t1);
	fpngl_irng32_delete(irng);
	return 0;
}
