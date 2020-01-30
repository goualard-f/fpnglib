#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
#
# Copyright 2019--2020 University of Nantes, France.
#
#	This file is part of the FPNGlib library.
#
#	The FPNGlib library is free software; you can redistribute it and/or modify
#	it under the terms of the GNU Lesser General Public License as published by the 
#	Free Software Foundation; either version 3 of the License, or (at your
#	option) any later version.
#	
#	The FPNGlib library is distributed in the hope that it will be useful, but
#	WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
#	or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
#	for more details.
#	
#	You should have received copies of the GNU General Public License and the
#	GNU Lesser General Public License along with the FPNGlib Library.  If not,
#	see https://www.gnu.org/licenses/. 	

AC_PREREQ([2.69])
AC_INIT([fpnglib],m4_esyscmd([tr -d '\n' < VERSION]),[frederic.goualard@univ-nantes.fr])
dnl For Automake
AM_INIT_AUTOMAKE([gnu 1.7 dist-bzip2])

PKG_CHECK_MODULES([CHECK], [check >= 0.11.0])

AC_CONFIG_SRCDIR([src/fpu.h])
AC_CONFIG_HEADERS([config.h src/fpngl_config.h])
AC_CONFIG_FILES([Makefile fpnglib/Makefile src/Makefile tests/Makefile doc/Makefile examples/Makefile])

dnl Libtool support
AC_CONFIG_MACRO_DIR([m4])
dnl Libtool revision system (from the Libtool manual)
dnl Here are a set of rules to help you update your library version information:
dnl    Start with version information of ‘0:0:0’ for each libtool library.
dnl    Update the version information only immediately before a public release of 
dnl    your software. More frequent updates are unnecessary, and only guarantee that 
dnl    the current interface number gets larger faster.
dnl    If the library source code has changed at all since the last update, then 
dnl    increment revision (‘c:r:a’ becomes ‘c:r+1:a’).
dnl    If any interfaces have been added, removed, or changed since the last update, 
dnl    increment current, and set revision to 0.
dnl    If any interfaces have been added since the last public release, then increment age.
dnl    If any interfaces have been removed or changed since the last public release, then set 
dnl    age to 0. 
LT_VERSION_INFO="0:0:0"
AC_SUBST(LT_VERSION_INFO)
LT_INIT


# Checks for programs.
AC_PROG_CC
AC_PROG_CC_STDC
if test "${ac_cv_prog_cc_stdc}" = "no"; then
	AC_MSG_ERROR([fpnglib must be compiled with a C99-compliant C compiler.])
fi
AC_PROG_LIBTOOL

# Checks for libraries.
AC_CHECK_LIB([m],[cos])

# Check for functions
AC_CHECK_FUNCS(getrusage clock)


# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([fenv.h stdint.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_TYPE_INT32_T
AC_TYPE_UINT32_T
AC_TYPE_INT64_T
AC_TYPE_UINT64_T

# Set default CFLAGS to nothing to avoid -O2 optimization in tests
CFLAGS=

AC_HEADER_ASSERT
# Checks for library functions.

AC_OUTPUT
