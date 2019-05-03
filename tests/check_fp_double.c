/* Unit tests for fp_double.c

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

#include <math.h>
#include <stdlib.h>
#include <check.h>
#include <fpnglib/fp_double.h>
#include <fpnglib/constants.h>
#include <fpnglib/random.h>

fpngl_rng_t *rng;

START_TEST(test_d_next)
{
  // Case  n == 0
  ck_assert_double_eq(fpngl_d_next(1.0,0), 1.0);
  ck_assert_double_nan(fpngl_d_next(fpngl_d_NaN,0));
  ck_assert_double_infinite(fpngl_d_next(fpngl_d_infinity,0));

  // Case n == 1
  ck_assert_double_eq(fpngl_d_next(1.0,1), nextafter(1.0,HUGE_VAL));
  ck_assert_double_eq(fpngl_d_next(-1.0,1), nextafter(-1.0,HUGE_VAL));
  ck_assert_double_nan(fpngl_d_next(fpngl_d_NaN,1));
  ck_assert_double_infinite(fpngl_d_next(fpngl_d_infinity,1));
  ck_assert_double_eq(fpngl_d_next(-fpngl_d_infinity,1),-fpngl_d_max);

  // Case n >= 1
  ck_assert_double_eq(fpngl_d_next(1.0,3),
							 nextafter(nextafter(nextafter(1.0,HUGE_VAL),
														HUGE_VAL),
										  HUGE_VAL));
  ck_assert_double_nan(fpngl_d_next(fpngl_d_NaN,3));
  ck_assert_double_infinite(fpngl_d_next(fpngl_d_infinity,3));
  double largeval = nextafter(fpngl_d_max,-fpngl_d_infinity);
  ck_assert_double_infinite(fpngl_d_next(largeval,4));
  ck_assert_double_eq(fpngl_d_next(-fpngl_d_mu,2),fpngl_d_mu);
}
END_TEST


START_TEST(test_d_previous)
{
  ck_assert_double_eq(fpngl_d_previous(1.0,0),1.0);
  ck_assert_double_eq(fpngl_d_next(fpngl_d_previous(1.0,1),1),1.0);
}
END_TEST

START_TEST(test_create_denormal)
{
  for (uint32_t i = 0; i < 100000; ++i) {
	 ck_assert(fpclassify(fpngl_d_create_denormal(rng)) == FP_SUBNORMAL);
  }
}
END_TEST

START_TEST(test_create_zero)
{
  for (uint32_t i = 0; i < 10000; ++i) {
	 ck_assert_double_eq(fpngl_d_create_zero(rng),0.0);
  }
}
END_TEST

START_TEST(test_create_inf)
{
  for (uint32_t i = 0; i < 10000; ++i) {
	 ck_assert_double_infinite(fpngl_d_create_inf(rng));
  }
}
END_TEST

START_TEST(test_create_normal)
{
  for (uint32_t i = 0; i < 100000; ++i) {
	 ck_assert(isnormal(fpngl_d_create_normal(rng)));
  }
}
END_TEST

START_TEST(test_create_by_field)
{
  for (uint32_t i = 0; i < 100; ++i) {
	 double v = fpngl_d_create_by_field(rng,fpngl_whatever,0,0,
												 0x0000000000000000,0x000fffffffffffff,
												 0xffffffffffffffff,0x0000000000000000);
	 ck_assert(fpclassify(v)==FP_SUBNORMAL);
  }
  for (uint32_t i = 0; i < 100; ++i) {
	 double v = fpngl_d_create_by_field(rng,fpngl_whatever,1,2046,
												 0x0000000000000000,0x000fffffffffffff,
												 0xffffffffffffffff,0x0000000000000000);
	 ck_assert(isnormal(v));
  }
  for (uint32_t i = 0; i < 100; ++i) {
	 double v = fpngl_d_create_by_field(rng,fpngl_whatever,2047,2047,
												 0x0000000000000000,0x0000000000000000,
												 0xffffffffffffffff,0x0000000000000000);
	 ck_assert(isinf(v));
  }
  for (uint32_t i = 0; i < 100; ++i) {
	 double v = fpngl_d_create_by_field(rng,fpngl_whatever,2047,2047,
												 0x0000000000000001,0x000fffffffffffff,
												 0xffffffffffffffff,0x0000000000000000);
	 ck_assert(isnan(v));
  }
  ck_assert(fpngl_d_create_by_field(rng,fpngl_positive,0,2046,
												 0x0000000000000000,0x000fffffffffffff,
											 0xffffffffffffffff,0x0000000000000000)>=0);
  ck_assert(fpngl_d_create_by_field(rng,fpngl_negative,0,2046,
												 0x0000000000000000,0x000fffffffffffff,
											 0xffffffffffffffff,0x0000000000000000)<=0);
}
END_TEST


START_TEST(test_create_by_distrib)
{
  const uint32_t niter = 10000;
  const double T[] = { 0.1, 0.1, 0.7, 0.1 };
  fpngl_fp_distribution_t *dd = fpngl_new_fp_distribution(rng,T);
  size_t noccur[] = { 0, 0, 0, 0, 0 };
  for (uint32_t i = 0; i < niter; ++i) {
	 double v = fpngl_d_create_by_distrib(dd);
	 switch (fpclassify(v)) {
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
  ck_assert(fabs(noccur[0]/(double)niter - 0.1) < 3e-3);
  ck_assert(fabs(noccur[1]/(double)niter - 0.1) < 4e-3);
  ck_assert(fabs(noccur[2]/(double)niter - 0.7) < 3e-3);
  ck_assert(fabs(noccur[3]/(double)niter - 0.1) < 4e-3);
  ck_assert_uint_eq(noccur[4],0); // No NaN should be produced
  
  fpngl_delete_fp_distribution(dd);

}
END_TEST



START_TEST(test_fpngl_d_unfp)
{
  ck_assert_uint_eq(fpngl_d_unfp(1,fpngl_d_next(1.0,1)),2);
  ck_assert_uint_eq(fpngl_d_unfp(fpngl_d_previous(0.0,2),fpngl_d_next(0.0,1)),4);
  ck_assert_uint_eq(fpngl_d_unfp(-1,fpngl_d_next(-1.0,1)),2);
  ck_assert_uint_eq(fpngl_d_unfp(0.0,fpngl_d_NaN),0);
  ck_assert_uint_eq(fpngl_d_unfp(0.0,fpngl_d_infinity),0);
  ck_assert_uint_eq(fpngl_d_unfp(fpngl_d_NaN,1.0),0);
  ck_assert_uint_eq(fpngl_d_unfp(0.0,fpngl_d_infinity),0);
}
END_TEST

START_TEST(test_fpngl_d_nfp)
{
  ck_assert_int_eq(fpngl_d_nfp(fpngl_d_next(1.0,1),1.0),-2);
}
END_TEST


Suite *fp_double_suite(void)
{
  Suite *s;
  TCase *tc_core;
  TCase *tc_random1;
  TCase *tc_auxiliary;
  
  s = suite_create("fp_double");
  
  tc_core = tcase_create("Core");
  tc_random1 = tcase_create("Uniform Random FP");
  tc_auxiliary = tcase_create("Auxiliary functions");
  
  
  tcase_add_test(tc_core, test_d_next);
  tcase_add_test(tc_core, test_d_previous);
  suite_add_tcase(s, tc_core);

  tcase_add_test(tc_random1, test_create_denormal);
  tcase_add_test(tc_random1, test_create_zero);
  tcase_add_test(tc_random1, test_create_inf);
  tcase_add_test(tc_random1, test_create_normal);
  tcase_add_test(tc_random1, test_create_by_field);
  tcase_add_test(tc_random1, test_create_by_distrib);
  suite_add_tcase(s, tc_random1);

  tcase_add_test(tc_auxiliary, test_fpngl_d_unfp);
  tcase_add_test(tc_auxiliary, test_fpngl_d_nfp);
  suite_add_tcase(s, tc_auxiliary);

  
  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;

  rng = fpngl_create_rng(0);
  
  s = fp_double_suite();
  sr = srunner_create(s);
  
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  fpngl_delete_rng(rng);
	 
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
