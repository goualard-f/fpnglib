/* Unit tests for frng64_drand48gnu.c

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
#include <fpnglib/debug.h>
#include <fpnglib/irng64_t.h>
#include <fpnglib/frng64_drand48gnu.h>

// Ten first values with array init[4] (see below) as seed.
const double drand48gnu[10] = {0x1.ed25bb9bdap-9,
															 0x1.673c57df37e8p-1,
															 0x1.d76eb0253ddep-1,
															 0x1.0fb40218cb9cp-1,
															 0x1.a6004e99b304p-2,
															 0x1.196106fb687p-1,
															 0x1.e46d00805f18p-3,
															 0x1.7548c18e0364p-1,
															 0x1.f4afd8b349aap-1,
															 0x1.b6175a7a32fp-2};

START_TEST(test_nextf64)
{
	fpngl_frng64_t *frng = fpngl_drand48gnu(42);
	for (uint32_t i = 0; i < 10; ++i) {
		ck_assert(fpngl_frng64_nextf64(frng) == drand48gnu[i]);
	}
	fpngl_frng64_delete(frng);
}
END_TEST

START_TEST(test_next_arrayf64)
{
	fpngl_frng64_t *frng = fpngl_drand48gnu(42);
	double T[10];
	fpngl_frng64_next_arrayf64(frng,T,10);
	for (uint32_t i = 0; i < 10; ++i) {
		ck_assert(T[i] == drand48gnu[i]);
	}
	fpngl_frng64_delete(frng);
}
END_TEST

START_TEST(test_seed)
{
	fpngl_frng64_t *frng = fpngl_drand48gnu(42);
	ck_assert(fpngl_frng64_seed(frng) == 42);
	fpngl_frng64_delete(frng);
}
END_TEST

START_TEST(test_name)
{
	fpngl_frng64_t *frng = fpngl_drand48gnu(42);
	ck_assert(!strcmp(fpngl_frng64_name(frng),"drand48gnu"));
	fpngl_frng64_delete(frng);
}
END_TEST
		
Suite *drand48gnu_suite(void)
{
  Suite *s;
  TCase *tc_core;
  
  s = suite_create("drand48 gnu");
  
  /* Core test case */
  tc_core = tcase_create("Core");
  
  tcase_add_test(tc_core, test_nextf64);
  tcase_add_test(tc_core, test_next_arrayf64);
  tcase_add_test(tc_core, test_seed);
  tcase_add_test(tc_core, test_name);
  suite_add_tcase(s, tc_core);
  
  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;
  
  s = drand48gnu_suite();
  sr = srunner_create(s);
  
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

