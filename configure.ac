#----------------------------------------------------------------------------
# Process this file with autoconf to produce a configure script.
# This is a template file that can be used to create new projects.
# Go through this file and edit the :CHANGE_HERE: tags
#----------------------------------------------------------------------------



#----------------------------------------------------------------------------
# initialize autoconf with the package name, version, email and tarfilename
# the following macros and preprocessor symbols are now defined
# and can be used from now on
# AC_PACKAGE_NAME,      PACKAGE_NAME
# AC_PACKAGE_STRING,    PACKAGE_STRING
# AC_PACKAGE_VERSION,   PACKAGE_VERSION
# AC_PACKAGE_BUGREPORT, PACKAGE_BUGREPORT
# AC_PACKAGE_TARNAME,   PACKAGE_TARNAME

AC_INIT([flexible config generator], m4_normalize(esyscmd([ head -1 debian/changelog | cut -d"(" -f 2 | cut -d")" -f 1 ])), [holger.boehnke@amarin.de], [flexconf])

# make sure it is autoconf 2.53 or later that's used to build configure
AC_PREREQ(2.53)

# check for a file that is typically unique for the package (safety check)
AC_CONFIG_SRCDIR([src/main.cpp])

# AM_INIT_AUTOMAKE automatically gets it's parameters from AC_INIT
AM_INIT_AUTOMAKE([AC_PACKAGE_TARNAME], [AC_PACKAGE_VERSION])

# put macros defined by tests in config.h
AM_CONFIG_HEADER([config.h])
#AC_CONFIG_HEADERS



#----------------------------------------------------------------------------
# checks for programs needed for installation etc. and compilers etc.

# C compiler
AC_PROG_CC
# C++ compiler
AC_PROG_CXX

# lex/flex
AM_PROG_LEX
# yacc/bison
AC_PROG_YACC

# This is required if any libraries are built in the package.
AC_PROG_RANLIB

# libtool settings
# uncomment if you don't need static libs
#AC_DISABLE_STATIC
# uncomment if you don't need shared libs
#AC_DISABLE_SHARED
# uncomment if you don't need support for dlopen
#AC_LIBTOOL_DLOPEN
# Automake will turn on processing for libtool.
#AC_PROG_LIBTOOL

# include a portable install in your distribution
AC_PROG_INSTALL

# check for c file to code script
AC_ARG_VAR([STRCODE], [c file to code script])
AC_PATH_PROG([STRCODE], [strcode.pl], [no], [$(pwd)/script])
if test "$STRCODE" == "no"; then
  AC_MSG_ERROR([cannot find the c file to code script])
fi



#----------------------------------------------------------------------------
# add additional compiler flags

CXXFLAGS="$CXXFLAGS -O0 -Wall"
CFLAGS="-O0 $CFLAGS -Wall"



#----------------------------------------------------------------------------
# checks for AC_ARG_WITH
# here we check for custom packets and set the according variable
# you may duplicate the section used for stlport

AC_ARG_WITH( [stlport], AC_HELP_STRING([--with-stlport],
  [use the stlport library as C++ template library (default: no)]),
  [ac_cv_use_stlport="$withval"], [ac_cv_use_stlport=no])



#----------------------------------------------------------------------------
# checks for libraries

# shall we use stlport
if test "$ac_cv_use_stlport" != "no"; then
  # check for the stlport must be checked with C++ parameters
  AC_LANG_PUSH(C++)
  # check for the stlport library
  AC_CHECK_LIB(stlport, main)
  # go back to previous language
  AC_LANG_POP(C++)
fi



#----------------------------------------------------------------------------
# checks for AC_ARG_ENABLE
# here we check for custom options and set the according variable
# you may duplicate the section used for logging



#----------------------------------------------------------------------------
# check for header files

# check for stlport header files
if test "$ac_cv_use_stlport" != "no"; then
  # check for the stlport must be checked with C++ parameters
  AC_LANG_PUSH(C++)
  # check for some specific stlport header. if it is present
  # define HAVE_STLPORT to 1 and add stlport to include path
  # for preprocessor and (automatically) for compiler
  AC_CHECK_HEADER([stlport/stl/_abbrevs.h],
    [
      AC_DEFINE([HAVE_STLPORT], [], [ Define to 1 if you have the stlport header files. ])
      CPPFLAGS="-I/usr/include/stlport $CPPFLAGS"
    ],
    [
      AC_MSG_ERROR([ cannot find the stlport headers, try useing '--without-stlport' ])
    ] )
  # go back to previous language
  AC_LANG_POP(C++)
fi

# check for other headers later because the above blocks may
# have altered the include path

# check for standard headers
AC_HEADER_STDC

# :CHANGE_HERE: check for any other headers needed by your program
#AC_CHECK_HEADERS([])



#----------------------------------------------------------------------------
# checks for types
# :CHANGE_HERE: check for types needed by your program
#AC_TYPE_SIZE_T
#AC_HEADER_TIME
#AC_STRUCT_TM



#----------------------------------------------------------------------------
# checks for structures
# :CHANGE_HERE: check for structures needed by your program



#----------------------------------------------------------------------------
# checks for compiler characteristics
# :CHANGE_HERE: check for structures needed by your program
#AC_C_CONST



#----------------------------------------------------------------------------
# checks for library functions
# :CHANGE_HERE: check for library functions needed by your program
#AC_FUNC_MALLOC
#AC_FUNC_MKTIME
#AC_FUNC_STRFTIME
#AC_FUNC_STRTOD
#AC_CHECK_FUNCS([])



#----------------------------------------------------------------------------
#checks for system services



#----------------------------------------------------------------------------
# :CHANGE_HERE: put all makefiles to be generated here
AC_CONFIG_FILES([
  Makefile \
  src/Makefile \
  src/gencust/Makefile \
  src/genxml/Makefile \
  src/test/Makefile \
  ])

# it used to be that the makefiles files were parameters if AC_OUTPUT
# this changed they were moved to AC_CONFIG_FILES
AC_OUTPUT
