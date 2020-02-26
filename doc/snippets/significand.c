/* Example of use of fpngl_t{32,64}

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
#include <math.h>
#include <fpnglib/constants32.h>
#include <fpnglib/constants64.h>

int main(void)
{
	printf("Number of digits with single precision: %u\n",
				 (uint32_t)trunc(fpngl_t32*log10(2)));
	printf("Number of digits with double precision: %u\n",
				 (uint32_t)trunc(fpngl_t64*log10(2)));
}
