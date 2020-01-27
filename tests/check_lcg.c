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

const uint64_t minstd_T64[] = {705894ULL,
															 1126542223ULL,
															 1579310009ULL,
															 565444343ULL,
															 807934826ULL,
															 421520601ULL,
															 2095673201ULL,
															 1100194760ULL,
															 1139130650ULL,
															 552121545ULL};

const uint32_t minstd_T32[] = {705894UL,
															 1126542219UL,
															 1579233965UL,
															 1434844124UL,
															 1331308677UL,
															 672805828UL,
															 1346144477UL,
															 909993260UL,
															 2025663413UL,
															 1266710548UL};

const uint64_t gnuc_lcg_T64[] = {1250496027ULL,
																 1116302264ULL,
																 1000676753ULL,
																 1668674806ULL,
																 908095735ULL,
																 71666532ULL,
																 896336333ULL,
																 1736731266ULL,
																 1314989459ULL,
																 1535244752ULL};


const uint32_t gnuc_lcg_T32[] = {1250496027UL,
																 1116302264UL,
																 1000676753UL,
																 1668674806UL,
																 908095735UL,
																 71666532UL,
																 896336333UL,
																 1736731266UL,
																 1314989459UL,
																 1535244752UL};

const uint64_t randu_T64[] = {2752638ULL,
															16515450ULL,
															74318958ULL,
															297274698ULL,
															1114777566ULL,
															1865709466ULL,
															1161258702ULL,
															913585258ULL,
															1472634174ULL,
															613537722};

const uint32_t randu_T32[] = {2752638UL,
															16515450UL,
															74318958UL,
															297274698UL,
															1114777566UL,
															1865709466UL,
															1161258702UL,
															913585258UL,
															1472634174UL,
															613537722Ul};

const uint64_t drand48_lcg_T64[] = {1059025964525ULL,
																		197491923327988ULL,
																		259172689157871ULL,
																		149370390209998ULL,
																		115998806404289ULL,
																		154689748186168ULL,
																		66578973461475ULL,
																		205215161057714ULL,
																		275255534396629ULL,
																		120421598792892ULL};

const uint64_t mupad_lcg_T64[] = {951626101589ULL,
																	790690675353ULL,
																	452813604587ULL,
																	663600809541ULL,
																	613762236923ULL,
																	819478098624ULL,
																	474044919607ULL,
																	401354030205ULL,
																	121771784384ULL,
																	877621620640ULL};
																	


#define TESTING64(name)																		\
	START_TEST(test_##name##_next64)												\
	{																												\
	  fpngl_irng_t *rng = fpngl_##name(42);									\
																													\
		ck_assert(fpngl_irng_seed(rng) == 42);								\
		ck_assert(!strcmp(fpngl_irng_name(rng),#name));				\
		ck_assert(fpngl_irng_min(rng) == 0);									\
		ck_assert(fpngl_irng_max(rng) == 0xffffffffffffffff); \
																													\
		for (uint32_t i = 0; i < 10; ++i) {										\
			ck_assert(fpngl_irng_next64(rng) == name##_T64[i]);	\
		}																											\
		fpngl_delete_irng(rng);																\
	}																												\
	END_TEST																								\
																													\
	START_TEST(test_##name##_nextk)																				\
	{																																			\
		fpngl_irng_t *rng = fpngl_##name(42);																\
		uint32_t k = 5;																											\
		for (uint32_t i = 0; i < 10; ++i,k+=2) {														\
			ck_assert(fpngl_irng_nextk(rng,k) == (name##_T64[i] >> (32-k)));	\
		}																																		\
		fpngl_delete_irng(rng);																							\
	}																																			\
	END_TEST																															\
	START_TEST(test_##name##_array64)																			\
	{																																			\
		fpngl_irng_t *rng = fpngl_##name(42);																\
		uint64_t T[10];																											\
		fpngl_irng_array64(rng,T,10);																				\
		for (uint32_t i = 0; i < 10; ++i) {																	\
			ck_assert(T[i] == name##_T64[i]);																	\
		}																																		\
		fpngl_delete_irng(rng);																							\
	}																																			\
	END_TEST



#define ADD_TEST64(name)														\
	do {																							\
		tcase_add_test(tc_core, test_##name##_next64);	\
		tcase_add_test(tc_core, test_##name##_nextk);		\
		tcase_add_test(tc_core, test_##name##_array64);	\
	} while(0)


#define TESTING32(name)																									\
	START_TEST(test_##name##_next32)																			\
	{																																			\
		fpngl_irng_t *rng = fpngl_##name(42);																\
																																				\
		for (uint32_t i = 0; i < 10; ++i) {																	\
			ck_assert(fpngl_irng_next32(rng) == name##_T32[i]);								\
		}																																		\
		fpngl_delete_irng(rng);																							\
	}																																			\
	END_TEST																															\
																																				\
	START_TEST(test_##name##_array32)																			\
	{																																			\
		fpngl_irng_t *rng = fpngl_##name(42);																\
		uint32_t T[10];																											\
		fpngl_irng_array32(rng,T,10);																				\
		uint32_t j = 0;																											\
		for (uint32_t i = 0; i < 10; i+=2,++j) {														\
			ck_assert(T[i] == (name##_T64[j] & 0x00000000ffffffff));					\
			ck_assert(T[i+1] == (name##_T64[j]>> 32));												\
		}																																		\
		fpngl_delete_irng(rng);																							\
	}																																			\
	END_TEST

#define ADD_TEST32(name)															\
	do {																								\
		tcase_add_test(tc_core, test_##name##_next32);		\
		tcase_add_test(tc_core, test_##name##_array32);		\
	} while(0)


START_TEST(test_lcg64)
{
	fpngl_irng64_t *rng = fpngl_new_lcg64(42,"lcg64",(1UL<<31)-1,16807,0);

	ck_assert(fpngl_irng64_seed(rng) == 42);
	ck_assert(!strcmp(fpngl_irng64_name(rng),"lcg64"));
	ck_assert(fpngl_irng64_min(rng) == 0);
	ck_assert(fpngl_irng64_max(rng) == 0xffffffffffffffff);

	for (uint32_t i = 0; i < 10; ++i) {
		ck_assert(fpngl_irng64_next64(rng)==minstd_T64[i]);
	}
	fpngl_delete_irng64(rng);
}
END_TEST

START_TEST(test_lcg)
{
	fpngl_irng_t *rng = fpngl_new_lcg(42,"lcg",(1UL<<31)-1,16807,0);

	ck_assert(fpngl_irng_seed(rng) == 42);
	ck_assert(!strcmp(fpngl_irng_name(rng),"lcg"));
	ck_assert(fpngl_irng_min(rng) == 0);
	ck_assert(fpngl_irng_max(rng) == 0xffffffffffffffff);

	for (uint32_t i = 0; i < 10; ++i) {
		ck_assert(fpngl_irng_next64(rng)==minstd_T64[i]);
	}
	fpngl_delete_irng(rng);
}
END_TEST

TESTING64(minstd);
TESTING64(gnuc_lcg);
TESTING64(randu);
TESTING64(drand48_lcg);
TESTING64(mupad_lcg);
TESTING32(minstd);
TESTING32(gnuc_lcg);
TESTING32(randu);

Suite *lcg_suite(void)
{
  Suite *s;
  TCase *tc_core;
  
  s = suite_create("lcg");
  
  /* Core test case */
  tc_core = tcase_create("Core");
  
  tcase_add_test(tc_core, test_lcg64);
  tcase_add_test(tc_core, test_lcg);
  ADD_TEST64(minstd);
  ADD_TEST32(minstd);
  ADD_TEST64(gnuc_lcg);
  ADD_TEST32(gnuc_lcg);
  ADD_TEST64(randu);
  ADD_TEST32(randu);
  ADD_TEST64(drand48_lcg);
  ADD_TEST64(mupad_lcg);
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

