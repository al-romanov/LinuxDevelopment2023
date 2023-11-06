#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CONFIG_SRCDIR([rhasher.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([rhash],[rhash_library_init],[],[AC_MSG_ERROR([couldn't find rhash_library_init symbol!])])
AC_ARG_WITH([readline],
    [AS_HELP_STRING([--without-readline], [disable readline])],
    [],
    [with_readline=yes])
AS_IF([test "x$with_readline" != xno],
    [AC_CHECK_LIB([readline], [readline],
        [
            AC_SUBST([rhasher_LDADD], ["-lreadline"])
            AC_DEFINE([READLINE], [1], [We want to use readline])
        ],
        [
            AC_MSG_FAILURE([Couldn't find readline (use --without-readline)])
        ])])
 
# Checks for header files.
AC_CHECK_HEADER([rhash.h])
AS_IF([test "x$with_readline" != xno],
    [AC_CHECK_HEADER([readline/readline.h])])


# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strerror strstr])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
