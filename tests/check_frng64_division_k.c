/* Unit tests for frng64_division.c

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
#include <fpnglib/frng64_t.h>
#include <fpnglib/frng64_division_k.h>
#include <fpnglib/lcg.h>
#include "tests_frng64.h"

const uint64_t seed = 42;

const double div53_T[] = {0x1.5003fp-32,
													0x1.f802f4p-30,
													0x1.1b811b8p-27,
													0x1.1b80d4ap-25,
													0x1.09c89f78p-23,
													0x1.bcd1de68p-23,
													0x1.14dd9b38p-23,
													0x1.b3a1a35p-24,
													0x1.5f1a74f8p-23,
													0x1.248ebddp-24};

fpngl_irng_t *irngdiv53;

TESTING_FRNG64_NOSEED(div53,irngdiv53);

Suite *frng64_division_suite(void)
{
  Suite *s;
  TCase *tc_core;

	irngdiv53 = fpngl_irng_new64(fpngl_randu64(seed));
	
  s = suite_create("frng64_division");
  
  /* Core test case */
  tc_core = tcase_create("Core");
  ADD_TEST_FRNG64_NOSEED(div53);
  suite_add_tcase(s, tc_core);
  
  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;
  
  s = frng64_division_suite();
  sr = srunner_create(s);
  
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

