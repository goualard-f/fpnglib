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
#include <fpnglib/frng64_division.h>
#include <fpnglib/lcg.h>
#include "tests_frng64.h"

const uint64_t seed = 42;

const double matlabp5_T[] = {0x1.58accp-12,
														 0x1.0c96ae3cp-1,
														 0x1.78896ee4p-1,
														 0x1.0d9ff7b8p-2,
														 0x1.8140db5p-2,
														 0x1.91fe4d9p-3,
														 0x1.f3a5bdc4p-1,
														 0x1.064e8f2p-1,
														 0x1.0f970468p-1,
														 0x1.0745a648p-2};

const double drand48bsd_T[] = {0x1.ed25bb9bdap-9,
															 0x1.673c57df37e8p-1,
															 0x1.d76eb0253ddep-1,
															 0x1.0fb40218cb9cp-1,
															 0x1.a6004e99b304p-2,
															 0x1.196106fb687p-1,
															 0x1.e46d00805f18p-3,
															 0x1.7548c18e0364p-1,
															 0x1.f4afd8b349aap-1,
															 0x1.b6175a7a32fp-2};

const double mupad_T[] = {0x1.e73b8950c7853p-1,
													0x1.94d5687fdc7d6p-1,
													0x1.cfae5e9ba0302p-2,
													0x1.53c37c3d37d83p-1,
													0x1.3a3f0b3e4423dp-1,
													0x1.a392a222d588bp-1,
													0x1.e56c080a47138p-2,
													0x1.9afc8d07780bfp-2,
													0x1.f2c6f8782b675p-4,
													0x1.c1579efde7d3p-1};

const double div53_T[] = {0x1.5p-43,
													0x1.f8p-41,
													0x1.1b8p-38,
													0x1.1b808p-36,
													0x1.09c88p-34,
													0x1.bcd1cp-34,
													0x1.14dd8p-34,
													0x1.b3a18p-35,
													0x1.5f1a6p-34,
													0x1.248e8p-35};

fpngl_irng_t *irngdiv53;

TESTING_FRNG64(div53,seed,irngdiv53);
TESTING_FRNG64(matlabp5,seed);
TESTING_FRNG64(drand48bsd,seed);
TESTING_FRNG64(mupad,seed);

Suite *frng64_division_suite(void)
{
  Suite *s;
  TCase *tc_core;

	irngdiv53 = fpngl_irng_new64(fpngl_randu64(seed));
	
  s = suite_create("frng64_division");
  
  /* Core test case */
  tc_core = tcase_create("Core");
  ADD_TEST_FRNG64(div53);
  ADD_TEST_FRNG64(matlabp5);
  ADD_TEST_FRNG64(drand48bsd);
	ADD_TEST_FRNG64(mupad);
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

