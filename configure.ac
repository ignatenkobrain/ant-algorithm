AC_INIT([Ant algorithm], [0.0.1],
        [Igor Gnatenko <i.gnatenko.brain@gmail.com>],
        [ant_alg], [https://github.com/ignatenkobrain/ant_alg])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([-Wall])
AC_PROG_CC
AC_PROG_INSTALL
PKG_CHECK_MODULES(GLIB, glib-2.0)
AC_ARG_ENABLE([debug],
    AS_HELP_STRING([--enable-debug], [Enable debug build]))
AS_IF([test "x$enable_debug" != "xyes"], [
  CFLAGS="-g"
])
AC_CONFIG_FILES([Makefile src/Makefile src/version.h])
AC_OUTPUT
