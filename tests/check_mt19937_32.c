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
#include <check.h>
#include <fpnglib/rng_t.h>
#include <fpnglib/mt19937ar.h>

const uint32_t mt19937_32_10[10] = {1067595299UL,
																		955945823UL,
																		477289528UL,
																		4107218783UL,
																		4228976476UL,
																		3344332714UL,
																		3355579695UL,
																		227628506UL,
																		810200273UL,
																		2591290167UL};


fpngl_mt19937_32_state_t *mt19937_32(void)
{
	uint32_t init[4]={0x123, 0x234, 0x345, 0x456}, length=4;
	return fpngl_init_mt19937_32_by_array32(init, length);
}

uint32_t generate_one_uint32(fpngl_irng32_t *rng)
{
	return rng->next(rng->state);
}


START_TEST(test_generate_1)
{
	fpngl_mt19937_32_state_t *state = mt19937_32();
	fpngl_irng32_t *mt19937 = malloc(sizeof(fpngl_irng32_t));
	mt19937->state = state;
	mt19937->next = (uint32_t (*)(void*))fpngl_mt19937_32_next;
	ck_assert(generate_one_uint32(mt19937) == 1067595299UL);
	fpngl_free_mt19937_32(state);
}
END_TEST

START_TEST(test_generate_5)
{
	fpngl_mt19937_32_state_t *state = mt19937_32();
	for (int i=0; i<10; i++) {
		ck_assert(mt19937_32_10[i] == fpngl_mt19937_32_next(state));
	}
	fpngl_free_mt19937_32(state);
}
END_TEST

Suite *mt19937_32_suite(void)
{
  Suite *s;
  TCase *tc_core;
  
  s = suite_create("mt19937-32");
  
  /* Core test case */
  tc_core = tcase_create("Core");
  
  tcase_add_test(tc_core, test_generate_1);
  tcase_add_test(tc_core, test_generate_5);
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

