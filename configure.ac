#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(nss_exfiles, 0.1, nss_exfiles-bugs@nakedape.cc)
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR(config)
AM_INIT_AUTOMAKE([-Wall])
AC_CONFIG_SRCDIR([src/])
AC_CONFIG_HEADER([config.h])

AC_SUBST(AM_CFLAGS, "-Wall")
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

#skip detection of Fortran
m4_undefine([AC_PROG_F77])
m4_defun([AC_PROG_F77],[])
m4_undefine([AC_PROG_FC])
m4_defun([AC_PROG_FC],[])


# Checks for programs.
AC_PROG_LIBTOOL
AC_PROG_CC

# Checks for libraries.
PKG_CHECK_MODULES([CHECK], [check >= 0.9.4])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([limits.h pwd.h stdlib.h string.h])

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
AM_PROG_CC_C_O
