/* Macros to help define the tests for single precision RNGs.

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

/*

	The following macros help write standard tests for the frng32 single precision
	FRNGs.

	Some assumptions are made:
	+ There exists an array of ten single precision values corresponding to the
	first 10 values generated by the FRNG with the seed `seed`. The name of 
	the array is <name>_T, where `<name>` is the name passed as argument to the
	macro;
	+ The seed is always the last parameter in the constructor for the FRNG.
 */

#ifndef __fpngl_tests_frng32_h__
#define __fpngl_tests_frng32_h__

#include <fpnglib/fpngl_config.h>

#define TESTING_FRNG32(name,seed,...)														 \
START_TEST(test_##name##_nextf32)																 \
{																																 \
	fpngl_frng32_t *frng = fpngl_##name(__VA_ARGS__ __VA_OPT__(,) seed);	\
	for (uint32_t i = 0; i < 10; ++i) {														 \
		ck_assert(fpngl_frng32_nextf32(frng) == name##_T[i]);				 \
	}																															 \
	fpngl_frng32_delete(frng);																		 \
}																																 \
END_TEST																												 \
																																 \
START_TEST(test_##name##_nextarrayf32)													 \
{																																 \
	fpngl_frng32_t *frng = fpngl_##name(__VA_ARGS__ __VA_OPT__(,) seed);	\
	float T[10];																									 \
	fpngl_frng32_next_arrayf32(frng,T,10);												 \
	for (uint32_t i = 0; i < 10; ++i) {														 \
		ck_assert(T[i] == name##_T[i]);															 \
	}																															 \
	fpngl_frng32_delete(frng);																		 \
}																																 \
END_TEST																												 \
START_TEST(test_##name##_name)																	 \
{																																 \
	fpngl_frng32_t *frng = fpngl_##name(__VA_ARGS__ __VA_OPT__(,) seed);	\
	ck_assert(!strcmp(fpngl_frng32_name(frng),#name));						 \
	fpngl_frng32_delete(frng);																		 \
}																																 \
END_TEST																												 \
																																 \
START_TEST(test_##name##_seed)																	 \
{																																 \
	fpngl_frng32_t *frng = fpngl_##name(__VA_ARGS__ __VA_OPT__(,) seed);	\
	ck_assert(fpngl_frng32_seed(frng) == seed);													\
	fpngl_frng32_delete(frng);																		 \
}																																 \
END_TEST

#define ADD_TEST_FRNG32(name)														\
	tcase_add_test(tc_core, test_##name##_nextf32);				\
  tcase_add_test(tc_core, test_##name##_nextarrayf32);	\
  tcase_add_test(tc_core, test_##name##_name);					\
  tcase_add_test(tc_core, test_##name##_seed);


#endif // __fpngl_tests_frng32_h__