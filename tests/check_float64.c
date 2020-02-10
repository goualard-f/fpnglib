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

Suite *float64_suite(void)
{
  Suite *s;
  TCase *tc_core;
  
  s = suite_create("float64");
  
  /* Core test case */
  tc_core = tcase_create("Core");
  
  tcase_add_test(tc_core, test_nextafter64);
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

