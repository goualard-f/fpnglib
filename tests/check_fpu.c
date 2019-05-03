/* Unit tests for fpu.c

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

#include <stdlib.h>
#include <check.h>
#include <fpnglib/fp_double.h>
#include <fpnglib/fpu.h>

START_TEST(test_inexact)
{
  double a = 1.0;
  double b = 10.0;
  fpngl_clear_inexact();
  double c = a/b;
  ck_assert(fpngl_inexact());
  a = 1.0;
  b = 2.0;
  fpngl_clear_inexact();
  c = a/b;
  ck_assert(!fpngl_inexact());
}
END_TEST

Suite *fpu_suite(void)
{
  Suite *s;
  TCase *tc_core;
  
  s = suite_create("fpu");
  
  /* Core test case */
  tc_core = tcase_create("Core");
  
  tcase_add_test(tc_core, test_inexact);
  suite_add_tcase(s, tc_core);
  
  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;
  
  s = fpu_suite();
  sr = srunner_create(s);
  
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

