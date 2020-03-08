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
#include "tests_irng32.h"
#include "tests_irng64.h"
#include "tests_frng32.h"
#include "tests_frng64.h"

const uint32_t seed = 13;

const uint32_t xor4096iv32_T32[] = {0xd52783ac,
																		0x2d48a374,
																		0x70b75afa,
																		0x3ea25ba4,
																		0x509d07cd,
																		0xa2c04c1b,
																		0x81cedc84,
																		0x980092ee,
																		0x68743233,
																		0xa722411a};

const float xor4096rv32_T[] = {0x1.aa4f06p-1,
																 0x1.6a4518p-3,
																 0x1.c2dd68p-2,
																 0x1.f512d8p-3,
																 0x1.42741cp-2,
																 0x1.458098p-1,
																 0x1.039db8p-1,
																 0x1.300124p-1,
																 0x1.a1d0c8p-2,
																 0x1.4e4482p-1};

const uint64_t xor4096iv64_T64[] = {0xbb7a09073ec2aa61,
																		0x11863909414c1342,
																		0x4f341f12aa3b9123,
																		0x39e1c7eeca4da368,
																		0x23e4ff0bb415a5c6,
																		0x2b00ebf7242c9d,
																		0x777ebb3eb1488c0e,
																		0xa90550789f084ecc,
																		0x96ea89d06ab50b81,
																		0x9e8cba4f9883d90d};
const double xor4096rv64_T[] = {0x1.76f4120e7d855p-1,
																	0x1.1863909414c1p-4,
																	0x1.3cd07c4aa8ee4p-2,
																	0x1.cf0e3f76526dp-3,
																	0x1.1f27f85da0adp-3,
																	0x1.58075fb9214p-11,
																	0x1.ddfaecfac5222p-2,
																	0x1.520aa0f13e109p-1,
																	0x1.2dd513a0d56a1p-1,
																	0x1.3d19749f3107bp-1};

TESTING_IRNG32(xor4096iv32,(1UL<<32)-1,seed);
TESTING_IRNG64(xor4096iv64,0xffffffffffffffff,seed);
TESTING_FRNG32(xor4096rv32,seed);
TESTING_FRNG64(xor4096rv64,seed);

Suite *xorgens_suite(void)
{
  Suite *s;
  TCase *tc_core;
  
  s = suite_create("xorgens");
  
  /* Core test case */
  tc_core = tcase_create("Core");

 	ADD_TEST_IRNG32(xor4096iv32);
	ADD_TEST_IRNG64(xor4096iv64);
	ADD_TEST_FRNG32(xor4096rv32);
	ADD_TEST_FRNG64(xor4096rv64);
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

