#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.67])

AC_INIT(libcgeneric, 0.4.2, villmow@gmail.com)
AM_INIT_AUTOMAKE(libcgeneric, 0.4.2)

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([src/binary_tree.c], [src/conversions.c], [src/deque.c], [src/hashtable.c], [src/heap.c], [src/list.c], [src/node.c], [src/priority_queue.c], [src/queue.c], [src/stack.c], [src/vector.c])

AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_INSTALL

AC_PROG_LIBTOOL
AC_PROG_RANLIB
# Checks for libraries.
PKG_CHECK_MODULES([CHECK], [check >= 0.9.4])

# Checks for header files.
AC_CHECK_HEADERS([limits.h stddef.h stdint.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset])

AC_CONFIG_FILES([Makefile
	doc/Makefile
	m4/Makefile
	lib/Makefile
	src/Makefile
	tests/Makefile
  units/Makefile])
AC_OUTPUT

