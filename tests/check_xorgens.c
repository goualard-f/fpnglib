/* Unit tests for xorgens.c

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
#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include <fpnglib/xorgens.h>

const uint32_t seed = 13;

START_TEST(test_xor4096iv32)
{
	ck_assert(xor4096iv32(seed) == 3576136620);
	ck_assert(xor4096iv32(0) == 759735156);
}
END_TEST

START_TEST(test_xor4096iv64)
{
	ck_assert(xor4096iv64(seed) == 13509119958973590113UL);
	ck_assert(xor4096iv64(0) == 1262759457436996418UL);
}
END_TEST

START_TEST(test_xor4096rv32)
{
	ck_assert(xor4096rv32(seed) == 0x1.aa4f06p-1);
	ck_assert(xor4096rv32(0) == 0x1.6a4518p-3);
}
END_TEST

START_TEST(test_xor4096rv64)
{
	ck_assert(xor4096rv64(seed) == 0x1.76f4120e7d855p-1);
	ck_assert(xor4096rv64(0) == 0x1.1863909414c1p-4);
}
END_TEST

Suite *xorgens_suite(void)
{
  Suite *s;
  TCase *tc_core;
  
  s = suite_create("xorgens");
  
  /* Core test case */
  tc_core = tcase_create("Core");
  
  tcase_add_test(tc_core, test_xor4096iv32);
  tcase_add_test(tc_core, test_xor4096iv64);
  tcase_add_test(tc_core, test_xor4096rv32);
  tcase_add_test(tc_core, test_xor4096rv64);
  suite_add_tcase(s, tc_core);
  
  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;
  
  s = xorgens_suite();
  sr = srunner_create(s);
  
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

