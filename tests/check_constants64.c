/* Unit tests for double precision constants

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
#include <fpnglib/constants64.h>

START_TEST(test_constants)
{
  ck_assert_double_eq(fpngl_u64,ldexp(1.0,-fpngl_t64));
  ck_assert_double_eq(fpngl_lambda64,ldexp(1.0,fpngl_emin64));
  ck_assert_double_eq(fpngl_mu64,ldexp(1.0,fpngl_emin64-fpngl_t64+1));
  ck_assert_double_eq(fpngl_max64,nextafter(fpngl_infinity64,-fpngl_infinity64));
  ck_assert_double_nan(fpngl_NaN64);
  ck_assert_double_infinite(fpngl_infinity64);
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
