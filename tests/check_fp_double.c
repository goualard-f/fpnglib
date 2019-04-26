/* Unit tests for fp_double.c

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
#include <stdlib.h>
#include <check.h>
#include <fpnglib/fp_double.h>
#include <fpnglib/constants.h>

START_TEST(test_next_float)
{
  // Case  n == 0
  ck_assert_double_eq(fpngl_next_float(1.0,0), 1.0);
  ck_assert_double_nan(fpngl_next_float(fpngl_d_NaN,0));
  ck_assert_double_infinite(fpngl_next_float(fpngl_d_infinity,0));

  // Case n == 1
  ck_assert_double_eq(fpngl_next_float(1.0,1), nextafter(1.0,HUGE_VAL));
  ck_assert_double_eq(fpngl_next_float(-1.0,1), nextafter(-1.0,HUGE_VAL));
  ck_assert_double_nan(fpngl_next_float(fpngl_d_NaN,1));
  ck_assert_double_infinite(fpngl_next_float(fpngl_d_infinity,1));
  ck_assert_double_eq(fpngl_next_float(-fpngl_d_infinity,1),-fpngl_d_max);

  // Case n >= 1
  ck_assert_double_eq(fpngl_next_float(1.0,3),
							 nextafter(nextafter(nextafter(1.0,HUGE_VAL),
														HUGE_VAL),
										  HUGE_VAL));
  ck_assert_double_nan(fpngl_next_float(fpngl_d_NaN,3));
  ck_assert_double_infinite(fpngl_next_float(fpngl_d_infinity,3));
  double largeval = nextafter(fpngl_d_max,-fpngl_d_infinity);
  ck_assert_double_infinite(fpngl_next_float(largeval,4));
  ck_assert_double_eq(fpngl_next_float(-fpngl_d_mu,2),fpngl_d_mu);
}
END_TEST


START_TEST(test_previous_float)
{
  ck_assert_double_eq(fpngl_previous_float(1.0,0),1.0);
  ck_assert_double_eq(fpngl_next_float(fpngl_previous_float(1.0,1),1),1.0);
}
END_TEST


Suite *fp_double_suite(void)
{
  Suite *s;
  TCase *tc_core;
  
  s = suite_create("fp_double");
  
  /* Core test case */
  tc_core = tcase_create("Core");
  
  tcase_add_test(tc_core, test_next_float);
  tcase_add_test(tc_core, test_previous_float);
  suite_add_tcase(s, tc_core);
  
  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;
  
  s = fp_double_suite();
  sr = srunner_create(s);
  
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
