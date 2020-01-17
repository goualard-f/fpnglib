# Makefile for tests
#
#	Copyright 2019 University of Nantes, France.
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

TESTS = check_constants64 check_fpu check_mt19937_32 check_mt19937_64 check_uirange \
	check_lcg check_utilities
check_PROGRAMS = $(TESTS)
LDADD = $(top_builddir)/src/libfpnglib.la @CHECK_LIBS@ -lm $(LIBS)
AM_CFLAGS = -I.. -Wall @CHECK_CFLAGS@



check_constants64_SOURCES = check_constants64.c $(top_builddir)/fpnglib/constants64.h

check_fpu_SOURCES = check_fpu.c $(top_builddir)/fpnglib/fpu.h
check_fpu_CFLAGS = -frounding-math

check_mt19937_32_SOURCES = check_mt19937_32.c $(top_builddir)/fpnglib/mt19937ar.h

check_mt19937_64_SOURCES = check_mt19937_64.c $(top_builddir)/fpnglib/mt19937-64.h

check_uirange_SOURCES = check_uirange.c $(top_builddir)/fpnglib/uirange.h

check_lcg_SOURCES = check_lcg.c $(top_builddir)/fpnglib/lcg.h

check_utilities_SOURCES = check_utilities.c $(top_builddir)/fpnglib/utilities.h
