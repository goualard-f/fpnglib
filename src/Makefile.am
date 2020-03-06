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

AM_CFLAGS = -Wall -O3 -std=c99 
lib_LTLIBRARIES = libfpnglib.la
libfpnglib_la_SOURCES = fpu.c irng32_t.c irng64_t.c irng_t.c irange.c \
	utilities.c uistack.c walker_vose.c float64.c \
	mt19937ar.c mt19937-64.c lcg.c \
	frng64_t.c frng64_division.c frng64_division_k.c \
	frng64_drand48gnu.c frng64_java.c frng64_golang.c \
	frng64_lecuyer_simard.c frng64_rationalLCG10.c \
	frng64_KGW.c frng64_fog97.c frng64_fog05.c xorgens.c \
	frng32_t.c \
	irng32_vnm.c

libfpnglib_la_CPPFLAGS = -I$(top_srcdir)/src
pkginclude_HEADERS = fpngl_config.h constants32.h constants64.h fpnglib.h fpu.h \
	irng32_t.h irng64_t.h irng_t.h irange.h utilities.h debug.h uistack.h\
	discrete_distribution.h float64.h \
	mt19937ar.h mt19937-64.h \
	lcg.h \
	frng64_t.h frng64_division.h frng64_division_k.h \
	frng64_drand48gnu.h frng64_java.h frng64_golang.h \
	frng64_lecuyer_simard.h frng64_rationalLCG10.h \
	frng64_KGW.h frng64_fog97.h frng64_fog05.h xorgens.h \
	frng32_t.h \
	irng32_vnm.h
libfpnglib_la_LDFLAGS = -version-info $(LT_VERSION_INFO)
