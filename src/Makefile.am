lib_LTLIBRARIES = libspacetime.la

libspacetime_la_SOURCES = earth.c \
    earth.h \
    mars/mars.h \
    mars/mars_time.c \
    mars/__mars_tm_to_secs.c \
    mars/diffmarstime.c \
    mars/mkmarstime.c \
    mars/ammarstime.c \
    mars/strfmarstime.c \
    mars/strpmarstime.c

libspacetime_la_includedir=$(includedir)/libspacetime
libspacetime_la_include_HEADERS = earth.h \
    mars/mars.h

pkgconfigdir=$(libdir)/pkgconfig
pkgconfig_DATA=libspacetime.pc

EXTRADIST = libspacetime.pc
CLEANFILES = libspacetime.pc
