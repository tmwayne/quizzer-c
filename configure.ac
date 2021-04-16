#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
# If the project has a wildly different structure, use autoscan
# to generate an appropriate configure.ac

AC_PREREQ([2.69])
AC_INIT([Quizzer], [1.0], [tylerwayne3@gmail.com])
AM_INIT_AUTOMAKE

AC_CONFIG_SRCDIR([src/quizzer.c])
AC_CONFIG_HEADERS([config.h])

LT_PREREQ([2.2.])
LT_INIT([dlopen])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
# AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([
  Makefile
  common/Makefile
  src/Makefile])

AC_OUTPUT
