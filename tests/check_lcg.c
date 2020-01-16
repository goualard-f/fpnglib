/* Unit tests for lcg.c

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

#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include <fpnglib/lcg.h>

const uint64_t minstd64T[] = {705894ULL,
															1126542223ULL,
															1579310009ULL,
															565444343ULL,
															807934826ULL,
															421520601ULL,
															2095673201ULL,
															1100194760ULL,
															1139130650ULL,
															552121545ULL};

START_TEST(test_lcg64)
{
	fpngl_lcg64_state_t *state = fpngl_init_lcg64(42,(1UL<<31)-1,16807,0);

	for (uint32_t i = 0; i < 10; ++i) {
		ck_assert(fpngl_lcg64_next(state)==minstd64T[i]);
	}
	fpngl_free_lcg64(state);
}
END_TEST

Suite *lcg_suite(void)
{
  Suite *s;
  TCase *tc_core;
  
  s = suite_create("lcg");
  
  /* Core test case */
  tc_core = tcase_create("Core");
  
  tcase_add_test(tc_core, test_lcg64);
  suite_add_tcase(s, tc_core);
  
  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;
  
  s = lcg_suite();
  sr = srunner_create(s);
  
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

