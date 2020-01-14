/* Unit tests for fp.c

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
#include <fpnglib/fp.h>

fpngl_rng_t *rng;

START_TEST(test_create_integer)
{
  for (uint32_t i = 0; i < 10000; ++i) {
	 int64_t n = fpngl_create_integer(rng,3,100);
	 ck_assert(n>=3 && n<= 100);
  }
}
END_TEST


Suite *fp_suite(void)
{
  Suite *s;
  TCase *tc_core;
  
  s = suite_create("fp");
  
  tc_core = tcase_create("Core");
  
  tcase_add_test(tc_core, test_create_integer);
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
