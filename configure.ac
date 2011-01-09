#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(FULL-PACKAGE-NAME, VERSION, BUG-REPORT-ADDRESS)
AC_CONFIG_AUX_DIR(config)
AM_INIT_AUTOMAKE(nss_exfiles, 1.0)
AC_CONFIG_SRCDIR([src/])
AC_CONFIG_HEADER([config.h])

AC_ARG_ENABLE(trace, 
              AS_HELP_STRING([--enable-trace],
                             [enable tracing (default is NO) ])
             )
dnl Tracing enabled?
if test -n "$enable_trace"; then
    enable_trace=${enable_trace_default-no}
fi
if test "$enable_trace" = no; then
    AC_DEFINE([ENABLE_TRACE], [], [Enable tracing])
fi


# Checks for programs.
AC_PROG_LIBTOOL
AC_PROG_YACC
AC_PROG_CC
AC_PROG_LEX

# Checks for libraries.
# FIXME: Replace `main' with a function in `-ll':
AC_CHECK_LIB([l], [main])
AC_CHECK_LIB([check], [main])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([limits.h netdb.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_UID_T
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([endpwent strdup])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 tests/Makefile])
AC_OUTPUT