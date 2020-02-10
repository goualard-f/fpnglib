/* Creation of double precision floating-point number with some properties

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

#include <global.h>
#include <math.h>
#include <fpnglib/constants64.h>
#include <fpnglib/float64.h>
#include <fpnglib/irange.h>
#include <fpnglib/types.h>


// Random sign
static inline uint64_t randsign(fpngl_irng_t *rng)
{
  return fpngl_ubound32(rng,2);
}

// Random exponent
static inline uint64_t randexp(fpngl_irng_t *rng)
{
  return fpngl_ubound32(rng,2048);
}

// Random exponent in the domain [min, max]
static inline uint64_t randexp2(fpngl_irng_t *rng, uint32_t min, uint32_t max)
{
  return fpngl_range32(rng,(int32_t)min,(int32_t)(max+1));
}

// Random exponent (normal or denormal, but not infinite)
static inline uint64_t randnumexp(fpngl_irng_t *rng)
{
  return fpngl_ubound32(rng,2047);
}

// Random normal exponent
static inline uint64_t randnormexp(fpngl_irng_t *rng)
{
  return fpngl_ubound32(rng,2046) + 1;
}

// Random fractional part (52 bits)
static inline uint64_t randfrac(fpngl_irng_t *rng)
{
  return fpngl_n_bits64(fpngl_irng_next64(rng),52);
}

// Random fractional part in the domain [min, max]
static inline uint64_t randfrac2(fpngl_irng_t *rng, uint64_t min, uint64_t max)
{
  return fpngl_range64(rng,min,max+1);
}


double fpngl_nextafter64(double v, uint64_t n)
{
	assert(n >= 1 && n <= 0x7fe0000000000000);
  if (isnan(v)) {
	 return v;
  }
  if (n == 1) {
	 return nextafter(v,fpngl_infinity64);
  }
  if (n == 0) {
	 return v;
  }
  fpngl_uintf64_t vi = {.d = v};
  if (v > 0) { // We shall not enter that branch if v == 0.0
	 if (0x7ff0000000000000 - n > vi.ui) { // We will not go beyond +oo when adding n to v?
		vi.ui += n;
		return vi.d;
	 } else {
		return fpngl_infinity64;
	 }
  } else { // v < 0?
	 vi.ui &= 0x7fffffffffffffff; // vi.i <- abs(vi.i)
	 if (vi.ui >= n) { // We will not create a positive number by adding n to v?
		vi.ui -= n;
		return -vi.d;
	 } else {
		vi.ui=(n - vi.ui);
		return vi.d;
	 }
  }
}

double fpngl_previous64(double v, uint64_t n)
{
  if (isnan(v)) {
	 return v;
  }
  if (n == 1) {
	 return nextafter(v,-fpngl_infinity64);
  }
  if (n == 0) {
	 return v;
  }
  return -fpngl_nextafter64(-v,n);
}

double fpngl_denormal64(fpngl_irng_t *rng)
{
  fpngl_uintf64_t dui;
  
  uint64_t sign = randsign(rng);
  uint64_t exponent = 0; // Characteristics of denormal numbers
  uint64_t fract = randfrac(rng);
  
  dui.ui = (sign << 63) | (exponent << 52) | fract;
  return dui.d;
}


double fpngl_zero64(fpngl_irng_t *rng)
{
  return (randsign(rng)-1)*0.0;
}


double fpngl_inf64(fpngl_irng_t *rng)
{
  return (randsign(rng)) ? fpngl_infinity64 : -fpngl_infinity64;
}

double fpngl_normal64(fpngl_irng_t *rng)
{
  fpngl_uintf64_t di;
  uint64_t sign = randsign(rng);
  uint64_t exponent = randnormexp(rng); // Exponent shall not be zero or 
                                        // 2047 to avoid denormal and 
                                        // infinite numbers

  uint64_t fract = randfrac(rng);
  
  di.ui = (sign << 63) | (exponent << 52) | fract;
  return di.d;
}

double fpngl_nan64(fpngl_irng_t *rng)
{
  fpngl_uintf64_t di;
  uint64_t sign = randsign(rng);
  uint64_t fract = randfrac(rng);
  
  di.ui = (sign << 63) | ((uint64_t)0x7ff << 52) | fract;
  return di.d;
  
}

double fpngl_float64(fpngl_irng_t *rng,
										 fpngl_sign_t s,
										 uint32_t minexp, uint32_t maxexp, 
										 uint64_t minfrac, uint64_t maxfrac, 
										 uint64_t andmask,
										 uint64_t ormask)
{
  fpngl_uintf64_t di;

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
  
  di.ui = (((sign << 63) | (exponent << 52) | fract) & andmask) | ormask; 
  return di.d;
}


fpngl_ddistribution_t *fpngl_class_float64_new(fpngl_irng_t *irng,
																							 const double P[static 5])
{
	return fpngl_ddistribution_new(irng,P,5);
}


double fpngl_float64_distrib(fpngl_ddistribution_t *fpd)
{
	typedef double (*realfun_t)(fpngl_irng_t *);
  static realfun_t createv[] = { fpngl_zero64,
																 fpngl_denormal64,
																 fpngl_normal64,
																 fpngl_inf64,
																 fpngl_nan64 };
  return createv[fpngl_ddistribution_next32(fpd)](fpngl_ddistribution_rng(fpd));

}

uint64_t fpngl_distance_float64(double a, double b)
{
  if (isinf(a) || isinf(b) || isnan(a) || isnan(b)) {
	 return 0; // Error
  }
  
  if (a == b) {
	 return 1;
  }
  
  fpngl_uintf64_t dia = {.d = fabs(a)};
  fpngl_uintf64_t dib = {.d = fabs(b)};
  
  if (a <= 0.0 && b >= 0.0) { // The tests have to be not strict to take into account -0.0
	 return dia.ui + dib.ui + 1;
  } else {
	 if (a >= 0.0) {
		return dib.ui - dia.ui + 1;
	 } else {
		return dia.ui - dib.ui + 1;
	 }
  }
}

int64_t fpngl_signed_distance_float64(double a, double b)
{
  if (a > b) {
	 return -fpngl_distance_float64(b,a);
  } else {
	 return fpngl_distance_float64(a,b);
  }
}
