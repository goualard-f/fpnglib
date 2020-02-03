/* Unit tests for frng64_rationalLCG10.c

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
#include <fpnglib/frng64_rationalLCG10.h>
#include <fpnglib/lcg.h>
#include "tests_frng64.h"

const uint64_t seed = 42;

const double rationalLCG10_T[] = {0x1.a96998b18febcp-1,
																	0x1.5d5e1570a72a3p-1,
																	0x1.7f78a1cc84cfp-1,
																	0x1.b17d2fd688a0fp-1,
																	0x1.1c2a06ac42122p-3,
																	0x1.68b27c729d49bp-1,
																	0x1.97c9bcee6b9c8p-1,
																	0x1.1c406852ba926p-2,
																	0x1.4dbac208abcc6p-1,
																	0x1.13a613f9aa628p-3};

TESTING_FRNG64(rationalLCG10,seed);

Suite *frng64_rationalLCG10_suite(void)
{
  Suite *s;
  TCase *tc_core;

  s = suite_create("frng64_rationalLCG10");
  
  /* Core test case */
  tc_core = tcase_create("Core");
	ADD_TEST_FRNG64(rationalLCG10);
  suite_add_tcase(s, tc_core);
  
  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;
  
  s = frng64_rationalLCG10_suite();
  sr = srunner_create(s);
  
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

