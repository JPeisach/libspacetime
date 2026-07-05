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

AC_CONFIG_FILES([Makefile src/Makefile po/Makefile.in])
AC_CONFIG_FILES([src/libspacetime.pc])

# Testing
AC_CONFIG_TESTDIR([tests])
AC_CONFIG_FILES([tests/Makefile tests/atlocal])
AM_MISSING_PROG([AUTOM4TE], [autom4te])

AC_OUTPUT
AC_OUTPUT
