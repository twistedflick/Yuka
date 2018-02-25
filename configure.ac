## Copyright 2018 Mo McRoberts.
##
##  Licensed under the Apache License, Version 2.0 (the "License");
##  you may not use this file except in compliance with the License.
##  You may obtain a copy of the License at
##
##      http://www.apache.org/licenses/LICENSE-2.0
##
##  Unless required by applicable law or agreed to in writing, software
##  distributed under the License is distributed on an "AS IS" BASIS,
##  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
##  See the License for the specific language governing permissions and
##  limitations under the License.

#############################################################################
## Initialise Autoconf and Automake with project-specific information      ##
#############################################################################

AC_INIT([Yuka],[develop])
AC_CONFIG_AUX_DIR([BuildScripts])
AC_CONFIG_MACRO_DIR([M4])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AM_MAINTAINER_MODE
AC_CONFIG_HEADER([config.h])

# AC_PROG_C and AC_PROG_CXX violate automake's normal rules for historical
# reasons and will modify CFLAGS and CXXFLAGS if the compiler is determined
# to be GCC (or compatible). Because user flags (CXXFLAGS) always come after
# our own flags (AM_CXXFLAGS), this has the effect of potentially reversing
# flags that we supply even when the user didn't ask us to.
#
# To counteract this, we save copies of CFLAGS and CXXFLAGS early and
# restore them after performing basic compiler tests. We only do this in
# the case of GCC, in the event hat AC_PROG_CXX() needs to update CXXFLAGS
# for more critical reasons (which it ought not to, but we should be
# conservative and deal only with cases we know about -- the scope can be
# expanded necessary if needed).
AS_VAR_SET([original_CFLAGS], ["$CFLAGS"])
AS_VAR_SET([original_CXXFLAGS], ["$CXXFLAGS"])

#############################################################################
## Check for basic system utilities and build tools (e.g., compilers)      ##
#############################################################################

AC_PROG_LN_S
AC_PROG_CXX([clang++ g++ c++])

if test x"$GXX" = x"yes" ; then
	AS_VAR_SET([CFLAGS], ["$original_CFLAGS"])
	AS_VAR_SET([CXXFLAGS], ["$original_CXXFLAGS"])
fi

LT_INIT

if test x"$GXX" = x"yes" ; then
	AS_VAR_APPEND([AM_CXXFLAGS], ['-W -Wall '])
	AS_VAR_APPEND([AM_CXXFLAGS], ['-fvisibility=hidden '])
	AS_VAR_APPEND([AM_CXXFLAGS], ['-O0 '])
	AS_VAR_APPEND([AM_CXXFLAGS], ['-g '])
	AS_VAR_APPEND([AM_CXXFLAGS], ['-std=c++11 '])
fi

AS_VAR_APPEND([AM_CPPFLAGS], ['-I${top_srcdir}/PrivateHeaders '])
AS_VAR_APPEND([AM_CPPFLAGS], ['-I${top_builddir}/PrivateHeaders '])

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
PrivateHeaders/Makefile
Headers/Makefile
Headers/Yuka/Makefile
Headers/Yuka/Traits/Makefile
Headers/Yuka/Intrinsics/Makefile
Headers/Yuka/Props/Makefile
Headers/Yuka/Behaviours/Makefile
Headers/Yuka/Lights/Makefile
Sources/Makefile
Examples/Makefile
])

AC_OUTPUT
