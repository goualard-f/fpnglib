/* Unit tests for frng64_golang.c

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
#include <fpnglib/frng64_golang.h>
#include <fpnglib/lcg.h>
#include <fpnglib/irng_t.h>
#include "tests_frng64.h"

const uint64_t seed = 42;

const double golang_T[] = {0x1.58accp-45,
													 0x1.0c96ae38p-34,
													 0x1.78896eep-34,
													 0x1.0d9ff7bp-35,
													 0x1.8140db5p-35,
													 0x1.91fe4d8p-36,
													 0x1.f3a5bdcp-34,
													 0x1.064e8f2p-34,
													 0x1.0f970468p-34,
													 0x1.0745a64p-35};

fpngl_irng_t *irng;

TESTING_FRNG64(golang,seed,irng);

Suite *frng64_golang_suite(void)
{
  Suite *s;
  TCase *tc_core;

	irng = fpngl_irng_new64(fpngl_minstd64(seed));
	
  s = suite_create("frng64_golang");
  
  /* Core test case */
  tc_core = tcase_create("Core");
	ADD_TEST_FRNG64(golang);
  suite_add_tcase(s, tc_core);
  
  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;
  
  s = frng64_golang_suite();
  sr = srunner_create(s);
  
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

