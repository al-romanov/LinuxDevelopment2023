AC_PREREQ([2.69])
AC_INIT([Wonderful Guess Game], [1.0], [raa_2001@mail.ru], [guess])
DX_INIT_DOXYGEN([guess])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([src/guess.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([libintl.h locale.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([setlocale])

AC_CONFIG_FILES([Makefile src/Makefile po/Makefile Doxyfile])
AC_OUTPUT
