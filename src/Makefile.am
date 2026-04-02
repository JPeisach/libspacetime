lib_LTLIBRARIES = libspacetime.la

libspacetime_la_SOURCES = earth.c \
    earth.h \
    mars.c \
    mars.h

libspacetime_la_includedir=$(includedir)/libspacetime
libspacetime_la_include_HEADERS = earth.h \
    mars.h

pkgconfigdir=$(libdir)/pkgconfig
pkgconfig_DATA=libspacetime.pc

EXTRADIST = libspacetime.pc
CLEANFILES = libspacetime.pc
