/* Macros to help define the tests for 64 bits integer RNGs.

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

#ifndef __fpngl_tests_irng64_h__
#define __fpngl_tests_irng64_h__

#include <fpnglib/fpngl_config.h>

#define TESTING_IRNG64(name,modulo, seed, ...)						\
	START_TEST(test_##name##_next64)												\
	{																												\
	  fpngl_irng64_t *rng = fpngl_##name(__VA_ARGS__ __VA_OPT__(,) seed);	\
																													\
		ck_assert(fpngl_irng64_seed(rng) == seed);							\
		ck_assert(!strcmp(fpngl_irng64_name(rng),#name));				\
		ck_assert(fpngl_irng64_min(rng) == 0);									\
		ck_assert(fpngl_irng64_max(rng) == ((modulo)-1));				\
																													\
		for (uint32_t i = 0; i < 10; ++i) {										\
			ck_assert(fpngl_irng64_next64(rng) == name##_T64[i]);	\
		}																											\
		fpngl_irng64_delete(rng);															\
	}																												\
	END_TEST																								\
																													\
	START_TEST(test_##name##_nextk)																				\
	{																																			\
		fpngl_irng64_t *rng = fpngl_##name(__VA_ARGS__ __VA_OPT__(,) seed);	\
		uint32_t k = 5;																											\
		for (uint32_t i = 0; i < 10; ++i,k+=2) {														\
			ck_assert(fpngl_irng64_nextk(rng,k) == (name##_T64[i] >> (32-k))); \
		}																																		\
		fpngl_irng64_delete(rng);																						\
	}																																			\
	END_TEST																															\
	START_TEST(test_##name##_array64)																			\
	{																																			\
		fpngl_irng64_t *rng = fpngl_##name(__VA_ARGS__ __VA_OPT__(,) seed);	\
		uint64_t T[10];																											\
		fpngl_irng64_array64(rng,T,10);																			\
		for (uint32_t i = 0; i < 10; ++i) {																	\
			ck_assert(T[i] == name##_T64[i]);																	\
		}																																		\
		fpngl_irng64_delete(rng);																						\
	}																																			\
	END_TEST



#define ADD_TEST_IRNG64(name)												\
	do {																							\
		tcase_add_test(tc_core, test_##name##_next64);	\
		tcase_add_test(tc_core, test_##name##_nextk);		\
		tcase_add_test(tc_core, test_##name##_array64);	\
	} while(0)


#define TESTING_IRNG64_32(name,seed,...)																\
	START_TEST(test_##name##_next32)																			\
	{																																			\
		fpngl_irng64_t *rng = fpngl_##name(__VA_ARGS__ __VA_OPT__(,) seed);	\
																																				\
		for (uint32_t i = 0; i < 10; ++i) {																	\
			ck_assert(fpngl_irng64_next32(rng) == name##_T32[i]);							\
		}																																		\
		fpngl_irng64_delete(rng);																						\
	}																																			\
	END_TEST																															\
																																				\
	START_TEST(test_##name##_array32)																			\
	{																																			\
		fpngl_irng64_t *rng = fpngl_##name(__VA_ARGS__ __VA_OPT__(,) seed);	\
		uint32_t T[10];																											\
		fpngl_irng64_array32(rng,T,10);																			\
		uint32_t j = 0;																											\
		for (uint32_t i = 0; i < 10; i+=2,++j) {														\
			ck_assert(T[i] == (name##_T64[j] & 0x00000000ffffffff));					\
			ck_assert(T[i+1] == (name##_T64[j]>> 32));												\
		}																																		\
		fpngl_irng64_delete(rng);																						\
	}																																			\
	END_TEST

#define ADD_TEST_IRNG64_32(name)											\
	do {																								\
		tcase_add_test(tc_core, test_##name##_next32);		\
		tcase_add_test(tc_core, test_##name##_array32);		\
	} while(0)


	
#endif // __fpngl_tests_irng64_h__


	
