#############################################################################
## Initialise Autoconf and Automake with project-specific information      ##
#############################################################################

AC_INIT([scene],[develop])
AC_CONFIG_AUX_DIR([BuildScripts])
AC_CONFIG_MACRO_DIR([M4])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AM_MAINTAINER_MODE
AC_CONFIG_HEADER([config.h])

#############################################################################
## Check for basic system utilities and build tools (e.g., compilers)      ##
#############################################################################

AC_PROG_LN_S
AC_PROG_CXX([clang++ g++ c++])

LT_INIT

if test x"$GXX" = x"yes" ; then
	AS_VAR_APPEND([AM_CXXFLAGS], ['-W -Wall '])
	AS_VAR_APPEND([AM_CXXFLAGS], ['-fvisibility=hidden '])
	AS_VAR_APPEND([AM_CXXFLAGS], ['-O0 '])
	AS_VAR_APPEND([AM_CXXFLAGS], ['-g '])
fi

AS_VAR_APPEND([AM_CPPFLAGS], ['-I${top_srcdir}/Headers '])
AS_VAR_APPEND([AM_CPPFLAGS], ['-I${top_builddir}/Headers '])

AC_SUBST([LIBS])
AC_SUBST([AM_CPPFLAGS])
AC_SUBST([AM_CFLAGS])
AC_SUBST([AM_CXXFLAGS])
AC_SUBST([AM_LDFLAGS])

#############################################################################
## Project-specific compilation environment tests                          ##
#############################################################################

AM_PATH_XML2

#############################################################################
## Output files                                                            ##
#############################################################################

AC_CONFIG_FILES([
Makefile
Headers/Makefile
Sources/Makefile
])

AC_OUTPUT
