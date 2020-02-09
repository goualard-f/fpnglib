/* Unit tests for uistack.c

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
#include <fpnglib/uistack.h>

START_TEST(test_push_pop_simple)
{
	fpngl_uistack_t *stack = fpngl_uistack_new();
	ck_assert(fpngl_uistack_empty(stack));
	for (int32_t i = 0; i < 10; ++i) {
		fpngl_uistack_push(stack,i+17);
	}
	ck_assert(!fpngl_uistack_empty(stack));
	for (int32_t i = 9; i >= 0; --i) {
		ck_assert(fpngl_uistack_pop(stack) == i+17);
	}
	ck_assert(fpngl_uistack_empty(stack));
	fpngl_uistack_delete(stack);
}
END_TEST


START_TEST(test_push_pop_realloc)
{
	fpngl_uistack_t *stack = fpngl_uistack_new();
	ck_assert(fpngl_uistack_empty(stack));
	for (int32_t i = 0; i < 40; ++i) {
		fpngl_uistack_push(stack,i+17);
	}
	ck_assert(!fpngl_uistack_empty(stack));
	for (int32_t i = 39; i >= 0; --i) {
		ck_assert(fpngl_uistack_pop(stack) == i+17);
	}
	ck_assert(fpngl_uistack_empty(stack));
	fpngl_uistack_delete(stack);
}
END_TEST

Suite *uistack_suite(void)
{
  Suite *s;
  TCase *tc_core;
  
  s = suite_create("uistack");
  
  /* Core test case */
  tc_core = tcase_create("Core");
  
  tcase_add_test(tc_core, test_push_pop_simple);
  tcase_add_test(tc_core, test_push_pop_realloc);
  suite_add_tcase(s, tc_core);
  
  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;
  
  s = uistack_suite();
  sr = srunner_create(s);
  
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

