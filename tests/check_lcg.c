/* Unit tests for lcg.c

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
#include <fpnglib/lcg.h>
#include "tests_irng64.h"

const uint64_t seed = 42;

const uint64_t minstd64_T64[] = {705894ULL,
																 1126542223ULL,
																 1579310009ULL,
																 565444343ULL,
																 807934826ULL,
																 421520601ULL,
																 2095673201ULL,
																 1100194760ULL,
																 1139130650ULL,
																 552121545ULL};

const uint32_t minstd64_T32[] = {705894UL,
																 1126542219UL,
																 1579233965UL,
																 1434844124UL,
																 1331308677UL,
																 672805828UL,
																 1346144477UL,
																 909993260UL,
																 2025663413UL,
																 1266710548UL};

const uint64_t gnuc_lcg64_T64[] = {1250496027ULL,
																	 1116302264ULL,
																	 1000676753ULL,
																	 1668674806ULL,
																	 908095735ULL,
																	 71666532ULL,
																	 896336333ULL,
																	 1736731266ULL,
																	 1314989459ULL,
																	 1535244752ULL};


const uint32_t gnuc_lcg64_T32[] = {1250496027UL,
																	 1116302264UL,
																	 1000676753UL,
																	 1668674806UL,
																	 908095735UL,
																	 71666532UL,
																	 896336333UL,
																	 1736731266UL,
																	 1314989459UL,
																	 1535244752UL};

const uint64_t randu64_T64[] = {2752638ULL,
																16515450ULL,
																74318958ULL,
																297274698ULL,
																1114777566ULL,
																1865709466ULL,
																1161258702ULL,
																913585258ULL,
																1472634174ULL,
																613537722};

const uint32_t randu64_T32[] = {2752638UL,
																16515450UL,
																74318958UL,
																297274698UL,
																1114777566UL,
																1865709466UL,
																1161258702UL,
																913585258UL,
																1472634174UL,
																613537722Ul};

const uint64_t drand48_lcg64_T64[] = {1059025964525ULL,
																			197491923327988ULL,
																			259172689157871ULL,
																			149370390209998ULL,
																			115998806404289ULL,
																			154689748186168ULL,
																			66578973461475ULL,
																			205215161057714ULL,
																			275255534396629ULL,
																			120421598792892ULL};

const uint64_t mupad_lcg64_T64[] = {951626101589ULL,
																		790690675353ULL,
																		452813604587ULL,
																		663600809541ULL,
																		613762236923ULL,
																		819478098624ULL,
																		474044919607ULL,
																		401354030205ULL,
																		121771784384ULL,
																		877621620640ULL};
																	
START_TEST(test_lcg64)
{
	fpngl_irng64_t *rng = fpngl_lcg64_new(seed,"lcg64",(1UL<<31)-1,16807,0);

	ck_assert(fpngl_irng64_seed(rng) == seed);
	ck_assert(!strcmp(fpngl_irng64_name(rng),"lcg64"));
	ck_assert(fpngl_irng64_min(rng) == 0);
	ck_assert(fpngl_irng64_max(rng) == (1UL<<31)-2);

	for (uint32_t i = 0; i < 10; ++i) {
		ck_assert(fpngl_irng64_next64(rng)==minstd64_T64[i]);
	}
	fpngl_irng64_delete(rng);
}
END_TEST

TESTING_IRNG64(minstd64,(1UL << 31)-2,seed);
TESTING_IRNG64(gnuc_lcg64,(1UL << 31)-1,seed);
TESTING_IRNG64(randu64,(1UL << 31)-1,seed);
TESTING_IRNG64(drand48_lcg64,(1UL<<48)-1,seed);
TESTING_IRNG64(mupad_lcg64,0xe8d4a50ff4UL,seed);
TESTING_IRNG64_32(minstd64,seed);
TESTING_IRNG64_32(gnuc_lcg64,seed);
TESTING_IRNG64_32(randu64,seed);

Suite *lcg_suite(void)
{
  Suite *s;
  TCase *tc_core;
  
  s = suite_create("lcg");
  
  /* Core test case */
  tc_core = tcase_create("Core");
  
  tcase_add_test(tc_core, test_lcg64);
  ADD_TEST_IRNG64(minstd64);
  ADD_TEST_IRNG64_32(minstd64);
  ADD_TEST_IRNG64(gnuc_lcg64);
  ADD_TEST_IRNG64_32(gnuc_lcg64);
  ADD_TEST_IRNG64(randu64);
  ADD_TEST_IRNG64_32(randu64);
  ADD_TEST_IRNG64(drand48_lcg64);
  ADD_TEST_IRNG64(mupad_lcg64);
	suite_add_tcase(s, tc_core);
  
  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;
  
  s = lcg_suite();
  sr = srunner_create(s);
  
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

