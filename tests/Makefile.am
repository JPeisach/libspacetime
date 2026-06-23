# TODO: subfolders for tests
check_PROGRAMS = mars_time \
    mars_diffmarstime_onesol \
    mars_important_dates_mariner9_enter_orbit \
    mars_important_dates_perseverance_landing \
    mars_mkmarstime_darian_leap_day_y210 \
    mars_mkmarstime_gregorian_leap_day_2004 \
    mars_mkmarstime_msd0 \
    mars_mkmarstime_unixepoch \
    mars_mkmarstime_y2k \
    mars_mkmarstime_y2038 \
    mars_mkmarstime_y2038_post \
    mars_mkmarstime_y2038_pre

mars_time_SOURCES = mars/time.c

mars_diffmarstime_onesol_SOURCES = mars/diffmarstime/onesol.c

mars_important_dates_mariner9_enter_orbit_SOURCES = mars/important_dates/mariner9_enter_orbit.c
mars_important_dates_perseverance_landing_SOURCES = mars/important_dates/perseverance_landing.c

mars_mkmarstime_darian_leap_day_y210_SOURCES = mars/mkmarstime/darian_leap_day_y210.c
mars_mkmarstime_gregorian_leap_day_2004_SOURCES = mars/mkmarstime/gregorian_leap_day_2004.c
mars_mkmarstime_msd0_SOURCES = mars/mkmarstime/msd0.c
mars_mkmarstime_unixepoch_SOURCES = mars/mkmarstime/unixepoch.c

mars_mkmarstime_y2k_SOURCES = mars/mkmarstime/y2k.c

mars_mkmarstime_y2038_SOURCES = mars/mkmarstime/y2038.c
mars_mkmarstime_y2038_post_SOURCES = mars/mkmarstime/y2038_post.c
mars_mkmarstime_y2038_pre_SOURCES = mars/mkmarstime/y2038_pre.c

LDADD = $(top_srcdir)/src/libspacetime.la

# Below is taken from the autotools docs
$(srcdir)/package.m4: $(top_srcdir)/configure.ac
		:;{ \
		  echo '# Signature of the current package.' && \
		  echo 'm4_define([AT_PACKAGE_NAME],' && \
		  echo '  [$(PACKAGE_NAME)])' && \
		  echo 'm4_define([AT_PACKAGE_TARNAME],' && \
		  echo '  [$(PACKAGE_TARNAME)])' && \
		  echo 'm4_define([AT_PACKAGE_VERSION],' && \
		  echo '  [$(PACKAGE_VERSION)])' && \
		  echo 'm4_define([AT_PACKAGE_STRING],' && \
		  echo '  [$(PACKAGE_STRING)])' && \
		  echo 'm4_define([AT_PACKAGE_BUGREPORT],' && \
		  echo '  [$(PACKAGE_BUGREPORT)])'; \
		  echo 'm4_define([AT_PACKAGE_URL],' && \
		  echo '  [$(PACKAGE_URL)])'; \
		} >'$(srcdir)/package.m4'

EXTRA_DIST = testsuite.at $(srcdir)/package.m4 $(TESTSUITE) atlocal.in
TESTSUITE = $(srcdir)/testsuite

check-local: atconfig atlocal $(TESTSUITE)
	$(SHELL) '$(TESTSUITE)' $(TESTSUITEFLAGS)

installcheck-local: atconfig atlocal $(TESTSUITE)
	$(SHELL) '$(TESTSUITE)' AUTOTEST_PATH='$(bindir)' \
	$(TESTSUITEFLAGS)

clean-local:
	test ! -f '$(TESTSUITE)' || \
		$(SHELL) '$(TESTSUITE)' --clean

AUTOTEST = $(AUTOM4TE) --language=autotest
$(TESTSUITE): $(srcdir)/testsuite.at $(srcdir)/package.m4
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $@.at
	mv $@.tmp $@
