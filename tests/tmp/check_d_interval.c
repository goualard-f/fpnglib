/* Unit tests for d_interval.c

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
#include <stdint.h>
#include <stdlib.h>
#include <check.h>
#include <fpnglib/d_interval.h>
#include <fpnglib/fp_double.h>

fpngl_rng_t *rng;

START_TEST(test_d_interval)
{
  const uint32_t niter = 10000;
  const double T[] = { 0.1, 0.1, 0.7, 0.1 };
  fpngl_fp_distribution_t *dd = fpngl_new_fp_distribution(rng,T);
  size_t noccur[] = { 0, 0, 0, 0, 0 };
  for (uint32_t i = 0; i < niter; ++i) {
	 double l, r;
	 fpngl_d_interval(dd,&l,&r);
	 switch (fpclassify(l)) {
	 case FP_ZERO:
		++noccur[0];
		break;
	 case FP_SUBNORMAL:
		++noccur[1];
		break;
	 case FP_NORMAL:
		++noccur[2];
		break;
	 case FP_INFINITE:
		++noccur[3];
		break;
	 case FP_NAN:
		++noccur[4];
	 }
	 switch (fpclassify(r)) {
	 case FP_ZERO:
		++noccur[0];
		break;
	 case FP_SUBNORMAL:
		++noccur[1];
		break;
	 case FP_NORMAL:
		++noccur[2];
		break;
	 case FP_INFINITE:
		++noccur[3];
		break;
	 case FP_NAN:
		++noccur[4];
	 }
  }
  ck_assert(fabs(noccur[0]/(2.0*niter) - 0.1) < 3e-3);
  ck_assert(fabs(noccur[1]/(2.0*niter) - 0.1) < 4e-3);
  ck_assert(fabs(noccur[2]/(2.0*niter) - 0.7) < 3e-3);
  ck_assert(fabs(noccur[3]/(2.0*niter) - 0.1) < 4e-3);
  ck_assert_uint_eq(noccur[4],0); // No NaN should be produced
  
  fpngl_delete_fp_distribution(dd);
}
END_TEST

START_TEST(test_d_interval_by_size)
{
  const uint32_t niter = 10000;
  const uint32_t min = 10;
  const uint32_t max = 34040;
  const double T[] = { 0.1, 0.2, 0.7, 0.0 };
  fpngl_fp_distribution_t *dd = fpngl_new_fp_distribution(rng,T);
  for (uint32_t i = 0; i < niter; ++i) {
	 double l, r;
	 fpngl_d_interval_by_size(dd,min,max,&l,&r);
	 uint64_t nfp = fpngl_d_unfp(l,r);
	 ck_assert(nfp >= min && nfp<= max);
  }
  fpngl_delete_fp_distribution(dd);
}
END_TEST


Suite *fp_suite(void)
{
  Suite *s;
  TCase *tc_core;
  
  s = suite_create("d_interval");
  
  tc_core = tcase_create("Core");
  
  tcase_add_test(tc_core, test_d_interval);
  tcase_add_test(tc_core, test_d_interval_by_size);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;

  rng = fpngl_create_rng(0);
  
  s = fp_suite();
  sr = srunner_create(s);
  
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  fpngl_delete_rng(rng);
	 
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
