# High-level Makefile
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

AM_CFLAGS = -Wall -O3
lib_LTLIBRARIES = libfpnglib.la
libfpnglib_la_SOURCES = fpu.c irng32_t.c irng64_t.c irng_t.c irange.c \
	utilities.c \
	mt19937ar.c mt19937-64.c lcg.c \
	frng64_t.c frng64_division_fc.c frng64_division_ff.c \
	frng64_fields.c \
	irng32_vnm.c

libfpnglib_la_CPPFLAGS = -I$(top_srcdir)/src
pkginclude_HEADERS = fpngl_config.h constants32.h constants64.h fpnglib.h fpu.h \
	irng32_t.h irng64_t.h irng_t.h irange.h utilities.h debug.h\
	mt19937ar.h mt19937-64.h \
	lcg.h \
	frng64_t.h frng64_division_fc.h frng64_division_ff.c \
	frng64_fields.h irng32_vnm.h
libfpnglib_la_LDFLAGS = -version-info $(LT_VERSION_INFO)
