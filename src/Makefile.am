# High-level Makefile
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

lib_LTLIBRARIES = libfpnglib.la
libfpnglib_la_SOURCES = fpu.c fp_double.c fp_float.c interval.c
libfpnglib_la_CPPFLAGS = -I$(top_srcdir)/srccd
pkginclude_HEADERS = constants.h fp_double.h fp_float.h fpnglib.h fpu.h interval.h
libfpnglib_la_LDFLAGS = -version-info $(LT_VERSION_INFO)
