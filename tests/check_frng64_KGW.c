/* Unit tests for frng64_KGW.c

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
#include <fpnglib/frng64_KGW.h>
#include <fpnglib/lcg.h>
#include "tests_frng64.h"

const uint64_t seed = 42;

const double KGW_T[] = {0x1.555755525559dp-3,
												0x1.00003fffd0002p-2,
												0x1.31eca7c176739p-1,
												0x1.92ccf14f49d89p-1,
												0x1.aaa0033de6a46p-2,
												0x1.965c18a8e6148p-1,
												0x1.78f5c0504cd5cp-1,
												0x1.133574e48fdb5p-1,
												0x1.92d94001ecb3p-2,
												0x1.fe1333f4d026ap-1};

fpngl_irng_t *irng;

TESTING_FRNG64(KGW,seed,irng);

Suite *frng64_KGW_suite(void)
{
  Suite *s;
  TCase *tc_core;

	irng = fpngl_irng_new64(fpngl_randu64(seed));

	s = suite_create("frng64_KGW");
  
  /* Core test case */
  tc_core = tcase_create("Core");
	ADD_TEST_FRNG64(KGW);
  suite_add_tcase(s, tc_core);
  
  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;
  
	s = frng64_KGW_suite();
  sr = srunner_create(s);
  
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

