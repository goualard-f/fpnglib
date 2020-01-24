/* Unit tests for frng64_division_fc.c

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
#include <stdio.h>
#include <string.h>
#include <check.h>
#include <fpnglib/frng64_t.h>
#include <fpnglib/frng64_division_fc.h>

const double matlabp5_T[] = {0x1.58accp-12,
														 0x1.0c96ae3cp-1,
														 0x1.78896ee4p-1,
														 0x1.0d9ff7b8p-2,
														 0x1.8140db5p-2,
														 0x1.91fe4d9p-3,
														 0x1.f3a5bdc4p-1,
														 0x1.064e8f2p-1,
														 0x1.0f970468p-1,
														 0x1.0745a648p-2};

START_TEST(test_matlabp5_nextf64)
{
	fpngl_frng64_t *frng = fpngl_new_matlabp5(42);
	for (uint32_t i = 0; i < 10; ++i) {
		ck_assert(fpngl_frng64_nextf64(frng) == matlabp5_T[i]);
	}
	fpngl_frng64_delete(frng);
}
END_TEST

START_TEST(test_matlabp5_nextarrayf64)
{
	fpngl_frng64_t *frng = fpngl_new_matlabp5(42);
	double T[10];
	fpngl_frng64_next_arrayf64(frng,T,10);
	for (uint32_t i = 0; i < 10; ++i) {
		ck_assert(T[i] == matlabp5_T[i]);
	}
	fpngl_frng64_delete(frng);
}
END_TEST

START_TEST(test_matlabp5_name)
{
	fpngl_frng64_t *frng = fpngl_new_matlabp5(42);
	ck_assert(!strcmp(fpngl_frng64_name(frng),"matlabp5"));
	fpngl_frng64_delete(frng);
}
END_TEST

START_TEST(test_matlabp5_seed)
{
	fpngl_frng64_t *frng = fpngl_new_matlabp5(42);
	ck_assert(fpngl_frng64_seed(frng) == 42);
	fpngl_frng64_delete(frng);
}
END_TEST

Suite *frng64_division_fc_suite(void)
{
  Suite *s;
  TCase *tc_core;
  
  s = suite_create("frng64_division_fc");
  
  /* Core test case */
  tc_core = tcase_create("Core");
  
  tcase_add_test(tc_core, test_matlabp5_nextf64);
  tcase_add_test(tc_core, test_matlabp5_nextarrayf64);
  tcase_add_test(tc_core, test_matlabp5_name);
  tcase_add_test(tc_core, test_matlabp5_seed);
  suite_add_tcase(s, tc_core);
  
  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;
  
  s = frng64_division_fc_suite();
  sr = srunner_create(s);
  
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

