#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([fpnglib],m4_esyscmd([tr -d '\n' < VERSION]),[frederic.goualard@univ-nantes.fr])
dnl For Automake
AM_INIT_AUTOMAKE([gnu 1.7 dist-bzip2])

PKG_CHECK_MODULES([CHECK], [check >= 0.12.0])

AC_CONFIG_SRCDIR([src/fpu.h])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile fpnglib/Makefile src/Makefile tests/Makefile])

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

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([fenv.h stdint.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_UINT64_T

CFLAGS="$CFLAGS -Wall"

# Checks for library functions.

AC_OUTPUT
