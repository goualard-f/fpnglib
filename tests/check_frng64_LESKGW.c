/* Unit tests for frng64_LESKGW.c

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
#include <fpnglib/frng64_LESKGW.h>
#include <fpnglib/lcg.h>
#include "tests_frng64.h"

const uint64_t seed = 42;

const double LESKGW_T[] = {0x1.5003f00fc017ap-10,
													 0x1.1b811b88dc06ap-5,
													 0x1.09c89f7b79a3cp-1,
													 0x1.14dd9b39b3a1ap-1,
													 0x1.5f1a74f9248ecp-1,
													 0x1.15be1cbabbe4bp-1,
													 0x1.bffc09e293a84p-3,
													 0x1.fec7163a251a8p-1,
													 0x1.e93f1fe9b73acp-3,
													 0x1.f93c0f73f6486p-2};

fpngl_irng64_t *irng64;

TESTING_FRNG64(LESKGW,seed,irng64);

Suite *frng64_LESKGW_suite(void)
{
  Suite *s;
  TCase *tc_core;

	irng64 = fpngl_randu64(seed);
	
  s = suite_create("frng64_LESKGW");
  
  /* Core test case */
  tc_core = tcase_create("Core");
	ADD_TEST_FRNG64(LESKGW);
  suite_add_tcase(s, tc_core);
  
  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;
  
  s = frng64_LESKGW_suite();
  sr = srunner_create(s);
  
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

