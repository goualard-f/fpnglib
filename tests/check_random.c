/* Unit tests for random.c

	Copyright 2019 University of Nantes, France.

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

#include <stdio.h>

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <check.h>
#include <fpnglib/random.h>


START_TEST(test_fpngl_init_rng)
{
  {
	 fpngl_rng_t *r = fpngl_create_rng(57);
	 ck_assert_uint_eq(fpngl_get_seed(r),57);
	 fpngl_delete_rng(r);
  }
  {
	 fpngl_rng_t *r = fpngl_create_rng(0);
	 ck_assert_uint_eq(fpngl_get_seed(r),0);
	 fpngl_delete_rng(r);
  }
  {
	 putenv("GSL_RNG_SEED=3");
	 fpngl_rng_t *r = fpngl_create_rng(0);
	 ck_assert_uint_eq(fpngl_get_seed(r),3);
	 fpngl_delete_rng(r);
  }
}
END_TEST

START_TEST(test_fp_distribution)
{
  fpngl_rng_t *r = fpngl_create_rng(57);
  const double T[] = { 0.1, 0.1, 0.7, 0.1, 0.0 };
  fpngl_fp_distribution_t *dd = fpngl_new_fp_distribution(r,T);

  size_t noccur[] = { 0, 0, 0, 0, 0 };
  
  for (uint32_t i = 0; i < 10000; ++i) {
	 size_t v = fpngl_fp_distribution_value(dd);
	 ++noccur[v];
	 ck_assert(v <= 4);
  }
  ck_assert(fabs(noccur[0]/10000. - 0.1) < 3e-3);
  printf("AAA: %g\n",fabs(noccur[1]/10000. - 0.1));
  ck_assert(fabs(noccur[1]/10000. - 0.1) < 5e-3);
  ck_assert(fabs(noccur[2]/10000. - 0.7) < 3e-3);
  ck_assert(fabs(noccur[3]/10000. - 0.1) < 4e-3);
  ck_assert_uint_eq(noccur[4],0);
  
  fpngl_delete_fp_distribution(dd);
  fpngl_delete_rng(r);
}
END_TEST


Suite *fpu_suite(void)
{
  Suite *s;
  TCase *tc_core;
  
  s = suite_create("random");
  
  /* Core test case */
  tc_core = tcase_create("Core");
  
  tcase_add_test(tc_core, test_fpngl_init_rng);
  tcase_add_test(tc_core, test_fp_distribution);
  suite_add_tcase(s, tc_core);
  
  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;
  
  s = fpu_suite();
  sr = srunner_create(s);
  
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

