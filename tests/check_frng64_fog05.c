/* Unit tests for frng64_fog97.c

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
#include <stdio.h>
#include <fpnglib/frng64_fog05.h>
#include <fpnglib/lcg.h>
#include "tests_frng64.h"

const uint64_t seed = 42;

const double fog05_T[] = {0x1.5p-43,
													0x1.f8p-41,
													0x1.1b8p-38,
													0x1.1b808p-36,
													0x1.09c88p-34,
													0x1.bcd1cp-34,
													0x1.14dd8p-34,
													0x1.b3a18p-35,
													0x1.5f1a6p-34,
													0x1.248e8p-35};


fpngl_irng_t *irng;

TESTING_FRNG64(fog05,seed,irng);

Suite *frng64_fog05_suite(void)
{
  Suite *s;
  TCase *tc_core;

	irng = fpngl_irng_new64(fpngl_randu64(seed));

	s = suite_create("frng64_fog05");
  
  /* Core test case */
  tc_core = tcase_create("Core");
	ADD_TEST_FRNG64(fog05);
  suite_add_tcase(s, tc_core);
  
  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;
  
	s = frng64_fog05_suite();
  sr = srunner_create(s);
  
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

