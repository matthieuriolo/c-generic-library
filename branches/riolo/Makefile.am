ACLOCAL_AMFLAGS=-I m4
EXTRA_DIST = reconf

SUBDIRS = m4 doc src lib

if enable_tests
SUBDIRS += tests
endif

if enable_units
SUBDIRS += units
endif

INCLUDES = -I$(top_srcdir)/src
LDFLAGS = -L$(top_srcdir)/lib
LDADD = -lcgeneric
