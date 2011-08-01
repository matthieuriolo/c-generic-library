AM_LDFLAGS = -L../lib
LDADD = -lcgen @CHECK_LIBS@
INCLUDES = -I../include -I.

TESTS = check_basevector check_baselist
check_PROGRAMS = check_basevector check_baselist

check_basevector_SOURCES = check_basevector.c $(top_builddir)/src/basevector.h
check_basevector_CFLAGS = @CHECK_CFLAGS@

check_baselist_SOURCES = check_baselist.c $(top_builddir)/src/baselist.h
check_baselist_CFLAGS = @CHECK_CFLAGS@
