/* Unit tests for walker_vose.c

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
#include <check.h>
#include <fpnglib/debug.h>
#include <fpnglib/discrete_distribution.h>
#include <fpnglib/mt19937ar.h>

const uint32_t seed = 42;

START_TEST(test_distribution)
{
	const double P[4] = {0.5, 0.125, 0.25, 0.125}; 
	const uint32_t ndraws = 10;

	fpngl_irng_t *irng = fpngl_irng_new32(fpngl_mt19937v32(seed));
	fpngl_ddistribution_t *dd = fpngl_ddistribution_new(irng, P, 4);
	uint32_t occurrences[4] = { 0, 0, 0, 0};

	for (uint32_t i = 0; i < ndraws; ++i) {
		uint32_t drawn = fpngl_ddistribution_next32(dd);
		FPNGL_DEBUG("Drawn: %u\n",drawn);
		++occurrences[drawn];
	}

	for (uint32_t j = 0; j < 4; ++j) {
		//ck_assert_double_eq_tol(P[j],occurrences[j]/(double)ndraws);
		FPNGL_DEBUG("%g ",occurrences[j]/(double)ndraws);
	}
	FPNGL_DEBUG("\n");
	fpngl_ddistribution_delete(dd);
}
END_TEST

Suite *walker_vose_suite(void)
{
  Suite *s;
  TCase *tc_core;
  
  s = suite_create("walker_vose");
  
  /* Core test case */
  tc_core = tcase_create("Core");
  
  tcase_add_test(tc_core, test_distribution);
  suite_add_tcase(s, tc_core);
  
  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;
  
  s = walker_vose_suite();
  sr = srunner_create(s);
  
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

