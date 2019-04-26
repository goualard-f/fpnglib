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

TESTS = check_constants check_fp_double
check_PROGRAMS = check_constants check_fp_double
LDADD = $(top_builddir)/src/libfpnglib.la @CHECK_LIBS@ -lm

check_fp_double_SOURCES = check_fp_double.c $(top_builddir)/fpnglib/fp_double.h
check_fp_double_CFLAGS = -I.. @CHECK_CFLAGS@

check_constants_SOURCES = check_constants.c $(top_builddir)/fpnglib/constants.h
check_constants_CFLAGS = -I.. @CHECK_CFLAGS@


