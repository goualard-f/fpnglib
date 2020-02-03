/* Unit tests for frng64_java.c

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
#include <fpnglib/frng64_java.h>

const double java_T[] = {0x1.ed25d9cf15fp-9,
												 0x1.d76eb043ed008p-1,
												 0x1.a6004e8cb0836p-2,
												 0x1.e46d017548c18p-3,
												 0x1.f4afd8b6c2eb4p-1,
												 0x1.f15f328438619p-1,
												 0x1.44a582ce800f6p-1,
												 0x1.c7c64b0ee725p-2,
												 0x1.d2310edd3d41cp-1,
												 0x1.b5a1e13b47104p-2};

#define TESTING(name)    																				 \
	START_TEST(test_##name##_nextf64)															 \
	{                                                              \
	  fpngl_frng64_t *frng = fpngl_##name(42);										 \
		for (uint32_t i = 0; i < 10; ++i) {												   \
			ck_assert(fpngl_frng64_nextf64(frng) == name##_T[i]);			 \
		}																														 \
		fpngl_frng64_delete(frng);																	 \
	}																															 \
	END_TEST																											 \
																																 \
	START_TEST(test_##name##_nextarrayf64)												 \
	{																															 \
	  fpngl_frng64_t *frng = fpngl_##name(42);										 \
		double T[10];																								 \
		fpngl_frng64_next_arrayf64(frng,T,10);											 \
		for (uint32_t i = 0; i < 10; ++i) {													 \
			ck_assert(T[i] == name##_T[i]);														 \
		}																														 \
		fpngl_frng64_delete(frng);																	 \
	}	  																													 \
  END_TEST																										   \
	START_TEST(test_##name##_name)																 \
	{																															 \
		fpngl_frng64_t *frng = fpngl_##name(42);										 \
		ck_assert(!strcmp(fpngl_frng64_name(frng),#name));					 \
		fpngl_frng64_delete(frng);																	 \
	}																															 \
	END_TEST																											 \
																																 \
	START_TEST(test_##name##_seed)																 \
	{																															 \
		fpngl_frng64_t *frng = fpngl_##name(42);										 \
		ck_assert(fpngl_frng64_seed(frng) == 42);										 \
		fpngl_frng64_delete(frng);																	 \
	}																															 \
	END_TEST

#define ADD_TEST(name)																	\
	tcase_add_test(tc_core, test_##name##_nextf64);				\
  tcase_add_test(tc_core, test_##name##_nextarrayf64);	\
  tcase_add_test(tc_core, test_##name##_name);					\
  tcase_add_test(tc_core, test_##name##_seed);
	
TESTING(java);

Suite *frng64_java_suite(void)
{
  Suite *s;
  TCase *tc_core;
  
  s = suite_create("frng64_java");
  
  /* Core test case */
  tc_core = tcase_create("Core");
	ADD_TEST(java);
  suite_add_tcase(s, tc_core);
  
  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;
  
  s = frng64_java_suite();
  sr = srunner_create(s);
  
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

