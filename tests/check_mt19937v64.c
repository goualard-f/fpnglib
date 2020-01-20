/* Unit tests for mt19937-64.c

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
#include <fpnglib/irng64_t.h>
#include <fpnglib/irng_t.h>
#include <fpnglib/mt19937-64.h>

typedef struct fpngl_mt19937v64_state_t fpngl_mt19937v64_state_t;
fpngl_mt19937v64_state_t *fpngl_init_mt19937v64_by_array64(uint64_t init_key[],
																													 uint64_t key_length);

uint64_t fpngl_mt19937v64_next64(fpngl_mt19937v64_state_t *state);
void fpngl_free_mt19937v64(fpngl_mt19937v64_state_t *state);

// Ten first values with array init[4] (see below) as seed.
const uint64_t mt19937v64_10[10] = {7266447313870364031ULL,
																		4946485549665804864ULL,
																		16945909448695747420ULL,
																		16394063075524226720ULL,
																		4873882236456199058ULL,
																		14877448043947020171ULL,
																		6740343660852211943ULL,
																		13857871200353263164ULL,
																		5249110015610582907ULL,
																		10205081126064480383ULL};

// Ten first values generated with seed `42`.
const uint64_t mt19937_10b[] = {13930160852258120406ULL,
																11788048577503494824ULL,
																13874630024467741450ULL,
																2513787319205155662ULL,
																16662371453428439381ULL,
																1735254072534978428ULL,
																10598951352238613536ULL,
																6878563960102566144ULL,
																5052085463162682550ULL,
																7199227068870524257ULL};


fpngl_mt19937v64_state_t *mt19937v64(void)
{
	uint64_t init[4]={0x12345ULL, 0x23456ULL, 0x34567ULL, 0x45678ULL}, length=4;
	return fpngl_init_mt19937v64_by_array64(init, length);
}

START_TEST(test_generate_1)
{
	fpngl_mt19937v64_state_t *state = mt19937v64();
	ck_assert(fpngl_mt19937v64_next64(state) == 7266447313870364031ULL);
	fpngl_free_mt19937v64(state);
}
END_TEST

START_TEST(test_generate_5)
{
	fpngl_mt19937v64_state_t *state = mt19937v64();
	for (int i=0; i<10; i++) {
		ck_assert(mt19937v64_10[i] == fpngl_mt19937v64_next64(state));
	}
	fpngl_free_mt19937v64(state);
}
END_TEST

START_TEST(test_construction)
{
	fpngl_irng64_t *rng = fpngl_new_mt19937v64_64(42);
	for (int i = 0; i < 10; ++i) {
		ck_assert(fpngl_irng64_next64(rng) == mt19937_10b[i]);
	}
	fpngl_delete_irng64(rng);
}
END_TEST

START_TEST(test_next64)
{
	fpngl_irng_t *rng = fpngl_new_mt19937v64(42);
	for (int i = 0; i < 10; ++i) {
		ck_assert(fpngl_irng_next64(rng) == mt19937_10b[i]);
	}
	fpngl_delete_irng(rng);
}
END_TEST

START_TEST(test_next32)
{
	fpngl_irng_t *rng = fpngl_new_mt19937v64(42);
	for (int i = 0; i < 10; ++i) {
		ck_assert(fpngl_irng_next32(rng) == (mt19937_10b[i] >> 32));
	}
	fpngl_delete_irng(rng);
}
END_TEST

START_TEST(test_seed)
{
	fpngl_irng_t *rng = fpngl_new_mt19937v64(42);
	ck_assert(fpngl_irng_seed(rng) == 42);
}
END_TEST

START_TEST(test_name)
{
	fpngl_irng_t *rng = fpngl_new_mt19937v64(42);
	ck_assert(!strcmp(fpngl_irng_name(rng),"mt19937-64"));
}
END_TEST

START_TEST(test_array64)
{
	fpngl_irng_t *rng = fpngl_new_mt19937v64(42);
	uint64_t T[10];
	fpngl_irng_array64(rng,T,10);
	for (int i = 0; i < 10; ++i) {
		ck_assert(T[i] == mt19937_10b[i]);
	}
	fpngl_delete_irng(rng);
}
END_TEST

START_TEST(test_array32)
{
	fpngl_irng_t *rng = fpngl_new_mt19937v64(42);
	uint32_t T[20];
	fpngl_irng_array32(rng,T,20);
	for (int i = 0,j=0; i < 10; i+=2,++j) {
		ck_assert(T[i] == (mt19937_10b[j] & 0x00000000ffffffff));
		ck_assert(T[i+1] == (mt19937_10b[j] >> 32));
	}
	fpngl_delete_irng(rng);
}
END_TEST

START_TEST(test_next_k)
{
	fpngl_irng_t *rng = fpngl_new_mt19937v64(42);
	uint64_t v = fpngl_irng_nextk(rng,13);
	ck_assert(v == 0x182a);
	fpngl_delete_irng(rng);
}
END_TEST

Suite *mt19937_64_suite(void)
{
  Suite *s;
  TCase *tc_core;
  
  s = suite_create("mt19937-64");
  
  /* Core test case */
  tc_core = tcase_create("Core");
  
  tcase_add_test(tc_core, test_generate_1);
  tcase_add_test(tc_core, test_generate_5);
  tcase_add_test(tc_core, test_construction);
  tcase_add_test(tc_core, test_next64);
  tcase_add_test(tc_core, test_next32);
  tcase_add_test(tc_core, test_seed);
  tcase_add_test(tc_core, test_name);
  tcase_add_test(tc_core, test_array64);
	tcase_add_test(tc_core, test_array32);
	tcase_add_test(tc_core, test_next_k);
  suite_add_tcase(s, tc_core);
  
  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;
  
  s = mt19937_64_suite();
  sr = srunner_create(s);
  
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
