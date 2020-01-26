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

#include <config.h>
#include <stdlib.h>
#include <string.h>
#include <check.h>
#include <fpnglib/lcg.h>

const uint64_t minstd_T64[] = {705894ULL,
															 1126542223ULL,
															 1579310009ULL,
															 565444343ULL,
															 807934826ULL,
															 421520601ULL,
															 2095673201ULL,
															 1100194760ULL,
															 1139130650ULL,
															 552121545ULL};
const uint32_t minstd_T32[] = {705894UL,
															 1126542219UL,
															 1579233965UL,
															 1434844124UL,
															 1331308677UL,
															 672805828UL,
															 1346144477UL,
															 909993260UL,
															 2025663413UL,
															 1266710548UL};

START_TEST(test_lcg64)
{
	fpngl_irng64_t *rng = fpngl_new_lcg64(42,"minstd",(1UL<<31)-1,16807,0);

	ck_assert(fpngl_irng64_seed(rng) == 42);
	ck_assert(!strcmp(fpngl_irng64_name(rng),"minstd"));
	ck_assert(fpngl_irng64_min(rng) == 0);
	ck_assert(fpngl_irng64_max(rng) == 0xffffffffffffffff);

	for (uint32_t i = 0; i < 10; ++i) {
		ck_assert(fpngl_irng64_next64(rng)==minstd_T64[i]);
	}
	fpngl_delete_irng64(rng);
}
END_TEST

START_TEST(test_lcg)
{
	fpngl_irng_t *rng = fpngl_new_lcg(42,"minstd",(1UL<<31)-1,16807,0);

	ck_assert(fpngl_irng_seed(rng) == 42);
	ck_assert(!strcmp(fpngl_irng_name(rng),"minstd"));
	ck_assert(fpngl_irng_min(rng) == 0);
	ck_assert(fpngl_irng_max(rng) == 0xffffffffffffffff);

	for (uint32_t i = 0; i < 10; ++i) {
		ck_assert(fpngl_irng_next64(rng)==minstd_T64[i]);
	}
	fpngl_delete_irng(rng);
}
END_TEST

START_TEST(test_minstd_next64)
{
	fpngl_irng_t *rng = fpngl_minstd(42);

	for (uint32_t i = 0; i < 10; ++i) {
		ck_assert(fpngl_irng_next64(rng)==minstd_T64[i]);
	}
	fpngl_delete_irng(rng);
}
END_TEST

START_TEST(test_minstd_next32)
{
	fpngl_irng_t *rng = fpngl_minstd(42);

	ck_assert(fpngl_irng_seed(rng) == 42);
	ck_assert(!strcmp(fpngl_irng_name(rng),"minstd"));
	ck_assert(fpngl_irng_min(rng) == 0);
	ck_assert(fpngl_irng_max(rng) == 0xffffffffffffffff);
	
	for (uint32_t i = 0; i < 10; ++i) {
		ck_assert(fpngl_irng_next32(rng) == minstd_T32[i]);
	}
	fpngl_delete_irng(rng);
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
  tcase_add_test(tc_core, test_lcg);
  tcase_add_test(tc_core, test_minstd_next64);
  tcase_add_test(tc_core, test_minstd_next32);
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

