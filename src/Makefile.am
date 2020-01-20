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

AM_CFLAGS = -Wall
lib_LTLIBRARIES = libfpnglib.la
libfpnglib_la_SOURCES = fpu.c rng_t.c uirange.c utilities.c \
	mt19937ar.c mt19937-64.c lcg.c

libfpnglib_la_CPPFLAGS = -I$(top_srcdir)/src
pkginclude_HEADERS = fpngl_config.h constants32.h constants64.h fpnglib.h fpu.h \
	rng_t.h uirange.h utilities.h \
	mt19937ar.h mt19937-64.h \
	lcg.h
libfpnglib_la_LDFLAGS = -version-info $(LT_VERSION_INFO)
