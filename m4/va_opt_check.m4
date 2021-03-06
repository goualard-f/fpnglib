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

# @synopsis VA_OPT_CHECK
# @summary check whether the __VA_OPT__ macro is supported by the C compiler.
# Define the automake conditional  HAVE_VA_OPT to `true` if the macro is
# available and to `false` otherwise. The macro can be used in Makefile.am
#  That macro should be available in GCC 8 and above, and in Clang 6 and above.
# C code taken from:
# https://stackoverflow.com/questions/48045470/portably-detect-va-opt-support
#

AC_DEFUN([VA_OPT_CHECK],
[dnl,
AC_LANG_PUSH([C])
AC_MSG_CHECKING([whether __VA_OPT__ macro is supported])
AC_RUN_IFELSE([AC_LANG_SOURCE([#define PP_THIRD_ARG(a,b,c,...) c
#define VA_OPT_SUPPORTED_I(...) PP_THIRD_ARG(__VA_OPT__(,),0,1,)
#define VA_OPT_SUPPORTED VA_OPT_SUPPORTED_I(?)
int main(void) { return VA_OPT_SUPPORTED;}])],[have_va_opt=yes;AC_MSG_RESULT([yes])],[have_va_opt=no;AC_MSG_RESULT([no])])
AM_CONDITIONAL(HAVE_VA_OPT,[test x${have_va_opt} = xyes])
AC_LANG_POP([C])
])
