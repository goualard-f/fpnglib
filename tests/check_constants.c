/* Unit tests for constants

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

#include <stdlib.h>
#include <check.h>
#include <math.h>
#include <fpnglib/constants.h>

START_TEST(test_constants)
{
  ck_assert_double_eq(fpngl_d_u,ldexp(1.0,-fpngl_d_t));
  ck_assert_double_eq(fpngl_d_lambda,ldexp(1.0,fpngl_d_emin));
  ck_assert_double_eq(fpngl_d_mu,ldexp(1.0,fpngl_d_emin-fpngl_d_t+1));
  ck_assert_double_eq(fpngl_d_max,nextafter(fpngl_d_infinity,-fpngl_d_infinity));
  ck_assert_double_nan(fpngl_d_NaN);
  ck_assert_double_infinite(fpngl_d_infinity);
}
END_TEST

Suite *constants_suite(void)
{
  Suite *s;
  TCase *tc_core;
  
  s = suite_create("constants");
  
  /* Core test case */
  tc_core = tcase_create("Core");
  
  tcase_add_test(tc_core, test_constants);
  suite_add_tcase(s, tc_core);
  
  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;
  
  s = constants_suite();
  sr = srunner_create(s);
  
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
