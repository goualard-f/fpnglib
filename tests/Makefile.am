# Makefile for tests
#
#	Copyright 2019--2020 University of Nantes, France.
#
#	This file is part of the FPNGlib library.
#
#	The FPNGlib library brary is free software; you can redistribute it and/or modify
#	it under the terms of the GNU Lesser General Public License as published by the 
#	Free Software Foundation; either version 3 of the License, or (at your
#	option) any later version.
#	
#	The FPNGlib Library is distributed in the hope that it will be useful, but
#	WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
#	or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
#	for more details.
#	
#	You should have received copies of the GNU General Public License and the
#	GNU Lesser General Public License along with the FPNGlib Library.  If not,
#	see https://www.gnu.org/licenses/. 	

# Tests performed only if the compiler supports the __VA_OPT__ macro.
if HAVE_VA_OPT
CONDTESTS = check_lcg check_frng64_division check_frng64_division_k check_frng64_fog05 \
	check_frng64_fog97 check_frng64_golang check_frng64_KGW check_frng64_lecuyer_simard \
	check_frng64_rationalLCG10
else
CONDTESTS =
endif

TESTS = check_constants32 check_constants64 check_fpu check_mt19937v32 check_mt19937v64 \
	check_irange check_utilities check_uistack check_walker_vose $(CONDTESTS)\
	check_float64 \
	check_frng64_java \
	check_vnm check_drand48gnu check_xorgens

check_PROGRAMS = $(TESTS)
LDADD = $(top_builddir)/src/libfpnglib.la @CHECK_LIBS@ -lm $(LIBS)
AM_CFLAGS = -I.. -std=c99 -Wall @CHECK_CFLAGS@

check_fpu_CFLAGS = -frounding-math -I.. -Wall @CHECK_CFLAGS@ -Wno-unused-but-set-variable

