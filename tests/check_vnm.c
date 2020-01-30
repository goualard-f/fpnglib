/* Unit tests for irng32_vnm.c

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
#include <fpnglib/irng32_vnm.h>

const uint32_t vnm_T32[] = {0x1623943UL,
														0xea226a1aUL,
														0xee97e2e1UL,
														0xc3f7ca80UL,
														0x6e57632eUL,
														0x371017b0UL,
														0xeb309831UL,
														0x40a362daUL,
														0x19b407c7UL,
														0xa81fce14UL};

START_TEST(test_next32)
{
	fpngl_irng32_t *irng = fpngl_von_neumann_metropolis(1233442);
	for (uint32_t i = 0; i < 10; ++i) {
		ck_assert(fpngl_irng32_next32(irng) == vnm_T32[i]);
	}
	fpngl_irng32_delete(irng);
}
END_TEST

START_TEST(test_characteristics)
{
	fpngl_irng32_t *irng = fpngl_von_neumann_metropolis(1233442);
	ck_assert(fpngl_irng32_seed(irng) == 1233442);
	ck_assert(!strcmp(fpngl_irng32_name(irng),"von neumann/metropolis"));
	ck_assert(fpngl_irng32_min(irng) == 0);
	ck_assert(fpngl_irng32_max(irng) == 0xffffffff);
	fpngl_irng32_delete(irng);
}
END_TEST



Suite *vnm_suite(void)
{
  Suite *s;
  TCase *tc_core;
  
  s = suite_create("von Neumann / Metropolis");
  
  /* Core test case */
  tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_next32);
	tcase_add_test(tc_core, test_characteristics);
  suite_add_tcase(s, tc_core);
  
  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;
  
  s = vnm_suite();
  sr = srunner_create(s);
  
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

