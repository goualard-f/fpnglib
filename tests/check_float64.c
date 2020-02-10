/* Unit tests for float64.c

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

#include <config.h>
#include <stdlib.h>
#include <check.h>
#include <math.h>
#include <fpnglib/float64.h>
#include <fpnglib/constants64.h>
#include <fpnglib/mt19937ar.h>
#include <fpnglib/irng_t.h>

const uint32_t seed = 42;

START_TEST(test_nextafter64)
{
	ck_assert(fpngl_nextafter64(1.0,2) == nextafter(nextafter(1.0,
																														fpngl_infinity64),
																									fpngl_infinity64));
	ck_assert(fpngl_nextafter64(-1.0,2) == nextafter(nextafter(-1.0,
																														 fpngl_infinity64),
																									 fpngl_infinity64));
	ck_assert(fpngl_nextafter64(fpngl_max64,2) == fpngl_infinity64);
	ck_assert(fpngl_nextafter64(-fpngl_infinity64,1) == -fpngl_max64);
	ck_assert(fpngl_nextafter64(0.0,2) == nextafter(fpngl_mu64,
																									fpngl_infinity64));
	ck_assert(fpngl_nextafter64(-0.0,2) == nextafter(fpngl_mu64,
																									 fpngl_infinity64));
}
END_TEST

START_TEST(test_previous64)
{
	ck_assert(fpngl_previous64(1.0,2) == nextafter(nextafter(1.0,
																													 -fpngl_infinity64),
																								 -fpngl_infinity64));
	ck_assert(fpngl_previous64(-1.0,2) == nextafter(nextafter(-1.0,
																														 -fpngl_infinity64),
																									 -fpngl_infinity64));
	ck_assert(fpngl_previous64(-fpngl_max64,2) == -fpngl_infinity64);
	ck_assert(fpngl_previous64(fpngl_infinity64,1) == fpngl_max64);
	ck_assert(fpngl_previous64(0.0,2) == nextafter(-fpngl_mu64,
																									-fpngl_infinity64));
	ck_assert(fpngl_previous64(-0.0,2) == nextafter(-fpngl_mu64,
																									 -fpngl_infinity64));
}
END_TEST

fpngl_irng_t *irng;

START_TEST(test_denormal64)
{
	ck_assert(fpclassify(fpngl_denormal64(irng)) == FP_SUBNORMAL);
}
END_TEST

START_TEST(test_zero64)
{
	ck_assert(fpngl_zero64(irng) == 0.0);
}
END_TEST

START_TEST(test_inf64)
{
	ck_assert_double_infinite(fpngl_inf64(irng));
}
END_TEST

START_TEST(test_normal64)
{
	ck_assert(isnormal(fpngl_normal64(irng)));
}
END_TEST

START_TEST(test_nan64)
{
	ck_assert(isnan(fpngl_nan64(irng)));
}
END_TEST

START_TEST(test_float64)
{
	double x0 = fpngl_float64(irng,fpngl_positive,
														0,0,
														0x0000000000000000, 0x000fffffffffffff,
														0xffffffffffffffff, 0x0000000000000000);
	ck_assert(x0 >= 0 && fpclassify(x0) == FP_SUBNORMAL);
	x0 = fpngl_float64(irng,fpngl_negative,
										 0,0,
										 0x0000000000000000, 0x000fffffffffffff,
										 0xffffffffffffffff, 0x0000000000000000);
	ck_assert(x0 <= 0 && fpclassify(x0) == FP_SUBNORMAL);
	x0 = fpngl_float64(irng,fpngl_whatever,
										 1023,1024,
										 0x0000000000000000, 0x000fffffffffffff,
										 0xffffffffffffffff, 0x0000000000000000);
	ck_assert((x0> -4 && x0 <= -1) || (x0 >= 1 && x0 < 4));
}
END_TEST

START_TEST(test_float64_distrib)
{
	const uint32_t niters = 100000;
	const double T[5] = {0.5, 0.125, 0.125, 0.125, 0.125};
	fpngl_ddistribution_t *dd = fpngl_class_float64_new(irng,T);
	uint32_t hist[5] = {0, 0, 0, 0, 0};
	for (uint32_t i = 0; i < niters; ++i) {
		int classd = fpclassify(fpngl_float64_distrib(dd));
		switch (classd) {
		case FP_ZERO:
			++hist[0];
			break;
		case FP_SUBNORMAL:
			++hist[1];
			break;
		case FP_NORMAL:
			++hist[2];
			break;
		case FP_INFINITE:
			++hist[3];
			break;
		case FP_NAN:
			++hist[4];
		}
	}
	for (uint32_t i = 0; i < 5; ++i) {
		ck_assert_double_eq_tol(hist[i]/(double)niters,T[i],1e-3);
	}
}
END_TEST

START_TEST(test_distance_float64)
{
	ck_assert(fpngl_distance_float64(1.0,nextafter(1.0,fpngl_infinity64)) == 2);
}
END_TEST

START_TEST(test_signed_distance_float64)
{
	ck_assert(fpngl_signed_distance_float64(1.0,nextafter(1.0,fpngl_infinity64)) == 2);
	ck_assert(fpngl_signed_distance_float64(nextafter(1.0,fpngl_infinity64),1.0) == -2);
}
END_TEST

Suite *float64_suite(void)
{
  Suite *s;
  TCase *tc_core;

	irng = fpngl_irng_new32(fpngl_mt19937v32(seed));
	
  s = suite_create("float64");
  
  /* Core test case */
  tc_core = tcase_create("Core");
  
  tcase_add_test(tc_core, test_nextafter64);
  tcase_add_test(tc_core, test_previous64);
  tcase_add_test(tc_core, test_denormal64);
  tcase_add_test(tc_core, test_zero64);
  tcase_add_test(tc_core, test_inf64);
  tcase_add_test(tc_core, test_normal64);
  tcase_add_test(tc_core, test_nan64);
  tcase_add_test(tc_core, test_float64);
  tcase_add_test(tc_core, test_float64_distrib);
  tcase_add_test(tc_core, test_distance_float64);
  tcase_add_test(tc_core, test_signed_distance_float64);
  suite_add_tcase(s, tc_core);
  
  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;
  
  s = float64_suite();
  sr = srunner_create(s);
  
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

