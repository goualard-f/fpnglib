/* Unit tests for uirange.c

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
#include <stdint.h>
#include <check.h>
#include <fpnglib/uirange.h>

START_TEST(test_n_bits32)
{
	ck_assert(fpngl_n_bits32(0x10000000,7) == 0x8);
	ck_assert(fpngl_n_bits32(0x80000000,7) == 0x40);
	ck_assert(fpngl_n_bits32(0xf0000f00,3) == 0x7);
}
END_TEST

START_TEST(test_n_bits64)
{
	ck_assert(fpngl_n_bits64(0x1000000000000000,7) == 0x8);
	ck_assert(fpngl_n_bits64(0x8000000000000000,7) == 0x40);
	ck_assert(fpngl_n_bits64(0xf0000f0000000000,3) == 0x7);
}
END_TEST

Suite *uirange_suite(void)
{
  Suite *s;
  TCase *tc_core;
  
  s = suite_create("uirange");
  
  /* Core test case */
  tc_core = tcase_create("Core");
  
  tcase_add_test(tc_core, test_n_bits32);
  tcase_add_test(tc_core, test_n_bits64);
  suite_add_tcase(s, tc_core);
  
  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;
  
  s = uirange_suite();
  sr = srunner_create(s);
  
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

