# Makefile for examples
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

noinst_LTLIBRARIES = libctiming.la
libctiming_la_SOURCES = ctiming.c
libctiming_la_CPPFLAGS = -I$(top_srcdir)

noinst_PROGRAMS = timing_mt19937v32 timing_mt19937v64 pi biased ddistribution coin \
	penney_game

LDADD= $(top_builddir)/src/libfpnglib.la -lm -lctiming $(LIBS)
AM_CFLAGS = -I.. -Wall -O3 -std=c99 

$(noinst_PROGRAMS): libctiming.la
