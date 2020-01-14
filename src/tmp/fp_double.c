/* Floating-point number generation (double precision format)

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

#include <math.h>
#include <fpnglib/constants.h>
#include <fpnglib/fp_double.h>

// Random sign
static inline unsigned long int randsign(fpngl_rng_t *rng)
{
  return fpngl_rand(rng) % 2;
}

// Random exponent
static inline unsigned long int randexp(fpngl_rng_t *rng)
{
  return fpngl_rand(rng) % 2048;
}

// Random exponent in the domain [min, max]
static inline unsigned long int randexp2(fpngl_rng_t *rng, uint32_t min, uint32_t max)
{
  return fpngl_rand(rng) % (max - min + 1) + min;
}

// Random exponent (normal or denormal, but not infinite)
static inline unsigned long int randnumexp(fpngl_rng_t *rng)
{
  return fpngl_rand(rng) % 2047;
}

// Random normal exponent
static inline unsigned long int randnormexp(fpngl_rng_t *rng)
{
  return fpngl_rand(rng) % 2046 + 1;
}

// Random fractional part (52 bits)
static inline unsigned long int randfrac(fpngl_rng_t *rng)
{
  return fpngl_rand(rng) % 0x10000000000000;
}

// Random fractional part in the domain [min, max]
static inline unsigned long int randfrac2(fpngl_rng_t *rng, uint64_t min, uint64_t max)
{
  return fpngl_rand(rng) % (max - min + 1) + min;
}


double fpngl_d_next(double v, uint64_t n)
{
  if (isnan(v)) {
	 return v;
  }
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

double fpngl_d_previous(double v, uint64_t n)
{
  if (isnan(v)) {
	 return v;
  }
  if (n == 1) {
	 return nextafter(v,-fpngl_d_infinity);
  }
  if (n == 0) {
	 return v;
  }
  return -fpngl_d_next(-v,n);
}

double fpngl_d_create_denormal(fpngl_rng_t *rng)
{
  fpngl_dui_t dui;
  
  unsigned long int sign = randsign(rng);
  unsigned long int exponent = 0; // Characteristics of denormal numbers
  unsigned long int fract = randfrac(rng);
  
  dui.i = (sign << 63) | (exponent << 52) | fract;
  return dui.d;
}


double fpngl_d_create_zero(fpngl_rng_t *rng)
{
  return (randsign(rng)-1)*0.0;
}


double fpngl_d_create_inf(fpngl_rng_t *rng)
{
  return (randsign(rng)) ? fpngl_d_infinity : -fpngl_d_infinity;
}

double fpngl_d_create_normal(fpngl_rng_t *rng)
{
  fpngl_dui_t di;
  uint64_t sign = randsign(rng);
  uint64_t exponent = randnormexp(rng); // Exponent shall not be zero or 
                                        // 2047 to avoid denormal and 
                                        // infinite numbers

  uint64_t fract = randfrac(rng);
  
  di.i = (sign << 63) | (exponent << 52) | fract;
  return di.d;
}

double fpngl_d_create_nan(fpngl_rng_t *rng)
{
  fpngl_dui_t di;
  uint64_t sign = randsign(rng);
  uint64_t fract = randfrac(rng);
  
  di.i = (sign << 63) | ((uint64_t)0x7ff << 52) | fract;
  return di.d;
  
}

double fpngl_d_create_by_field(fpngl_rng_t *rng,
										 fpngl_sign_t s, uint32_t minexp, uint32_t maxexp, 
										 uint64_t minfrac, uint64_t maxfrac, 
										 uint64_t andmask,
										 uint64_t ormask)
{
  fpngl_dui_t di;

  uint64_t sign;
  switch (s) {
  case fpngl_positive:
	 sign = 0;
	 break;
  case fpngl_negative:
	 sign = 1;
	 break;
  case fpngl_whatever:
  default:
	 sign = randsign(rng);
  }

  uint64_t exponent = randexp2(rng,minexp,maxexp);
  uint64_t fract = randfrac2(rng,minfrac,maxfrac);
  
  di.i = (((sign << 63) | (exponent << 52) | fract) & andmask) | ormask; 
  return di.d;
}


double fpngl_d_create_by_distrib(fpngl_fp_distribution_t *fpd)
{
  typedef double (*realfun)(fpngl_rng_t *);
  static realfun createv[] = {fpngl_d_create_zero, fpngl_d_create_denormal,
										fpngl_d_create_normal, fpngl_d_create_inf,
										fpngl_d_create_nan };
  return createv[fpngl_fp_distribution_value(fpd)](fpngl_get_rng(fpd));
}

uint64_t fpngl_d_unfp(double a, double b)
{
  if (isinf(a) || isinf(b) || isnan(a) || isnan(b)) {
	 return 0; // Error
  }
  
  if (a == b) {
	 return 1;
  }
  
  fpngl_dui_t dia = {.d = fabs(a)};
  fpngl_dui_t dib = {.d = fabs(b)};
  
  if (a <= 0.0 && b >= 0.0) { // The tests have to be not strict to take into account -0.0
	 return dia.i + dib.i + 1;
  } else {
	 if (a >= 0.0) {
		return dib.i - dia.i + 1;
	 } else {
		return dia.i - dib.i + 1;
	 }
  }
}

int64_t fpngl_d_nfp(double a, double b)
{
  if (a > b) {
	 return -fpngl_d_unfp(b,a);
  } else {
	 return fpngl_d_unfp(a,b);
  }
}
