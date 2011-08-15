ACLOCAL_AMFLAGS=-I m4
EXTRA_DIST = reconf


#used to install the headers with the subfolder (without nobase_ the folder won't be copied one be one - including the subfolders)
#automake does not remove the ../ out of the path, so the files are copied to /usr/local/include/../libcgeneric -> /usr/local/libcgeneric
#the problem above is the reason why we have to put it here (and not inside lib/ or include)
incDIR=./libcgeneric
srcHEADERS=$(incDIR)/libcgeneric.h $(incDIR)/binary_tree.h $(incDIR)/deque.h $(incDIR)/heap.h $(incDIR)/node.h $(incDIR)/queue.h $(incDIR)/vector.h $(incDIR)/comparisons.h $(incDIR)/hashtable.h $(incDIR)/list.h $(incDIR)/priority_queue.h $(incDIR)/stack.h $(incDIR)/gen/access_macros.h $(incDIR)/gen/control_macros.h $(incDIR)/gen/error_macros.h $(incDIR)/gen/function_signatures.h $(incDIR)/gen/stdint.h $(incDIR)/gen/control_arr_macros.h $(incDIR)/gen/data_types.h $(incDIR)/gen/function_macros.h $(incDIR)/gen/gen_macros.h
libincludedir=$(includedir)
nobase_libinclude_HEADERS=$(srcHEADERS)

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
