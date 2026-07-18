AC_INIT
AT_INIT
LT_INIT

PACKAGE=libspacetime
VERSION=0.0.0

AM_INIT_AUTOMAKE($PACKAGE, $VERSION)
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

AC_CONFIG_MACRO_DIR([m4])

AC_SEARCH_LIBS(fmod, m, [], [])

AC_PROG_CC
PKG_PROG_PKG_CONFIG

AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.23.2])

case "$host_os" in
  darwin*)
    AC_DEFINE([MACOS], [1], [Define if building on macOS])
    ;;
esac

# Programs
AC_ARG_ENABLE([programs],
    [AS_HELP_STRING([--disable-programs], [Disables programs])],
    [enable_programs=$enableval],
    [enable_programs=yes])

AM_CONDITIONAL([PROGRAMS], [test "x$enable_programs" = "xyes"])

if test "$enable_programs" != no
then
AC_CONFIG_FILES([progs/Makefile])
fi

AC_CONFIG_FILES([Makefile src/Makefile po/Makefile.in])
AC_CONFIG_FILES([src/libspacetime.pc])

# Testing
AC_ARG_ENABLE([tests],
    [AS_HELP_STRING([--disable-tests], [Disables tests])],
    [enable_tests=$enableval],
    [enable_tests=yes])

AM_CONDITIONAL([TESTS], [test "x$enable_tests" = "xyes"])

if test "$enable_tests" != no
then
AC_CONFIG_TESTDIR([tests])
AC_CONFIG_FILES([tests/Makefile tests/atlocal])
AM_MISSING_PROG([AUTOM4TE], [autom4te])
fi

AC_OUTPUT
AC_OUTPUT

echo "libspacetime config:"
echo "Prefix: $prefix"
echo "Tests: $enable_tests"
echo "Programs: $enable_programs"
