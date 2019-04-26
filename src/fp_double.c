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

#include <math.h>
#include <fpnglib/constants.h>
#include <fpnglib/fp_double.h>

double fpngl_next_float(double v, uint64_t n)
{
  if (n == 1) {
	 return nextafter(v,fpngl_d_infinity);
  }
  if (n == 0) {
	 return v;
  }
  fpngl_dui_t vi = {.d = v};
  if (v > 0) { // We shall not enter that branch if v == 0.0
	 if (0x7ff0000000000000 - n > vi.i) { // We will not go beyond +oo when adding n to v?
		vi.i+=n;
		return vi.d;
	 } else {
		return fpngl_d_infinity;
	 }
  } else { // v < 0?
	 vi.i &= 0x7fffffffffffffff; // vi.i <- abs(vi.i)
	 if (vi.i >= n) { // We will not create a positive number by adding n to v?
		vi.i-=n;
		return -vi.d;
	 } else {
		vi.i=(n-vi.i);
		return vi.d;
	 }
  }
}

double fpngl_previous_float(double v, uint64_t n)
{
  if (n == 1) {
	 return nextafter(v,-fpngl_d_infinity);
  }
  if (n == 0) {
	 return v;
  }
  return -fpngl_next_float(-v,n);
}


double fpngl_ufp(double x)
{
  // TODO
}

double fpngl_signed_ufp(double x)
{
  // TODO
}
