/* Unit tests for irange.c

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
#include <fpnglib/irange.h>
#include <fpnglib/mt19937ar.h>
#include <fpnglib/mt19937-64.h>

START_TEST(test_ubound32)
{
	fpngl_irng_t *irng = fpngl_irng_new32(fpngl_mt19937v32(42));

	for (uint32_t i = 0; i < 100; ++i) {
		uint32_t v = fpngl_ubound32(irng,2);
		ck_assert(v == 0 || v == 1);
	}
	
	fpngl_irng_delete(irng);
}
END_TEST

START_TEST(test_ubound64)
{
	fpngl_irng_t *irng = fpngl_irng_new64(fpngl_mt19937v64(42));

	for (uint32_t i = 0; i < 100; ++i) {
		uint64_t v = fpngl_ubound64(irng,2);
		ck_assert(v == 0 || v == 1);
	}
	
	fpngl_irng_delete(irng);
}
END_TEST

START_TEST(test_range32)
{
	fpngl_irng_t *irng = fpngl_irng_new32(fpngl_mt19937v32(42));

	for (uint32_t i = 0; i < 10000; ++i) {
		int32_t v = fpngl_range32(irng,-1,2);
		ck_assert(v == -1 || v == 0 || v == 1);
	}
	for (uint32_t i = 0; i < 10000; ++i) {
		int64_t v = fpngl_range32(irng,-6,-2);
		ck_assert(v >= -6 && v < -2);
	}
	
	fpngl_irng_delete(irng);
}
END_TEST

START_TEST(test_range64)
{
	fpngl_irng_t *irng = fpngl_irng_new64(fpngl_mt19937v64(42));

	for (uint32_t i = 0; i < 10000; ++i) {
		int64_t v = fpngl_range64(irng,-1,2);
		ck_assert(v == -1 || v == 0 || v == 1);
	}
	for (uint32_t i = 0; i < 10000; ++i) {
		int64_t v = fpngl_range64(irng,-6,-2);
		ck_assert(v >= -6 && v < -2);
	}
	
	fpngl_irng_delete(irng);
}
END_TEST

Suite *irange_suite(void)
{
  Suite *s;
  TCase *tc_core;
  
  s = suite_create("irange");
  
  /* Core test case */
  tc_core = tcase_create("Core");
  
  tcase_add_test(tc_core, test_ubound32);
  tcase_add_test(tc_core, test_range32);
  tcase_add_test(tc_core, test_ubound64);
  tcase_add_test(tc_core, test_range64);
  suite_add_tcase(s, tc_core);
  
  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;
  
  s = irange_suite();
  sr = srunner_create(s);
  
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

