/* Unit tests for mt19937ar.c

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
#include <fpnglib/irng_t.h>
#include <fpnglib/irng32_t.h>
#include <fpnglib/mt19937ar.h>

// Ten first numbers generated with an array seed of {0x123, 0x234, 0x345, 0x456}
const uint32_t mt19937v32_array[10] = {1067595299UL,
																			 955945823UL,
																			 477289528UL,
																			 4107218783UL,
																			 4228976476UL,
																			 3344332714UL,
																			 3355579695UL,
																			 227628506UL,
																			 810200273UL,
																			 2591290167UL};

// Ten first number generated with a seed of 42
const uint32_t mt19937v32_42[10] = {0x5fe1dc66UL,
																		0xcbea3db3UL,
																		0xf362035cUL,
																		0x2ef5950eUL,
																		0xbb63f46aUL,
																		0xc799d447UL,
																		0x9941aebcUL,
																		0x98cb2c14UL,
																		0x27f0d666UL,
																		0x72221879UL};

START_TEST(test_new_by_array)
{
	uint32_t init[4]={0x123, 0x234, 0x345, 0x456}, length=4;
	fpngl_irng32_t *irng = fpngl_mt19937v32_by_array(init,length);
	for (uint32_t i = 0; i < 10; ++i) {
		ck_assert(fpngl_irng32_next32(irng) == mt19937v32_array[i]);
	}
	fpngl_irng32_delete(irng);
}
END_TEST

START_TEST(test_new_by_seed32)
{
	fpngl_irng32_t *irng = fpngl_mt19937v32(42);
	for (uint32_t i = 0; i < 10; ++i) {
		ck_assert(fpngl_irng32_next32(irng) == mt19937v32_42[i]);
	}
	fpngl_irng32_delete(irng);
}
END_TEST

START_TEST(test_new_by_seed64)
{
	fpngl_irng32_t *irng = fpngl_mt19937v32(42);
	for (uint32_t i = 0; i < 10; ++i) {
		ck_assert(fpngl_irng32_next32(irng) == mt19937v32_42[i]);
	}
	fpngl_irng32_delete(irng);
}
END_TEST

START_TEST(test_characteristics)
{
	fpngl_irng32_t *irng = fpngl_mt19937v32(42);
	ck_assert(fpngl_irng32_seed(irng) == 42);
	ck_assert(!strcmp(fpngl_irng32_name(irng),"mt19937v32"));
	ck_assert(fpngl_irng32_min(irng) == 0);
	ck_assert(fpngl_irng32_max(irng) == 0xffffffff);
	fpngl_irng32_delete(irng);
}
END_TEST

START_TEST(test_next_array32)
{
	fpngl_irng32_t *irng = fpngl_mt19937v32(42);
	uint32_t T[10];
	fpngl_irng32_array32(irng,T,10);
	for (uint32_t i = 0; i < 10; ++i) {
		ck_assert(T[i] == mt19937v32_42[i]);
	}
	fpngl_irng32_delete(irng);
}
END_TEST

START_TEST(test_next_array64)
{
	fpngl_irng32_t *irng = fpngl_mt19937v32(42);
	uint64_t T[5];
	fpngl_irng32_array64(irng,T,5);
	uint32_t j = 0;
	for (uint32_t i = 0; i < 5; ++i,j+=2) {
		ck_assert(T[i] == (uint64_t)((((uint64_t)mt19937v32_42[j]) << 32) | (uint64_t)mt19937v32_42[j+1]));
	}
	fpngl_irng32_delete(irng);
}
END_TEST

START_TEST(test_nextk)
{
	fpngl_irng32_t *irng = fpngl_mt19937v32(42);
	for (uint32_t i = 1; i < 10; ++i) {
		ck_assert(fpngl_irng32_nextk(irng,i) == (((uint64_t)(mt19937v32_42[i-1])) >> (32-i)));
	}
	fpngl_irng32_delete(irng);
}
END_TEST


Suite *mt19937_32_suite(void)
{
  Suite *s;
  TCase *tc_core;
  
  s = suite_create("mt19937-32");
  
  /* Core test case */
  tc_core = tcase_create("Core");
  
	tcase_add_test(tc_core, test_new_by_array);
	tcase_add_test(tc_core, test_characteristics);
	tcase_add_test(tc_core, test_new_by_seed32);
	tcase_add_test(tc_core, test_new_by_seed64);
  tcase_add_test(tc_core, test_next_array32);
  tcase_add_test(tc_core, test_next_array64);
  tcase_add_test(tc_core, test_nextk);
  suite_add_tcase(s, tc_core);
  
  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;
  
  s = mt19937_32_suite();
  sr = srunner_create(s);
  
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

