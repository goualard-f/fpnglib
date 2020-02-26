/* Simplest example of use of the library: generation of one random integer.

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
#include <fpnglib/mt19937ar.h>

const uint32_t seed = 13;

int main(void)
{
	fpngl_irng32_t *irng32 = fpngl_mt19937v32(seed);
	printf("%u\n",fpngl_irng32_next32(irng32));
	printf("%lu\n",fpngl_irng32_next64(irng32));
	fpngl_irng32_delete(irng32);
}
