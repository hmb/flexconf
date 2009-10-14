# flexconf - flexible configuration generator
#   Copyright (C) 2003-2008 Holger Böhnke
#
#   This file is part of flexconf.
#
#   Flexconf is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.

#---------------------------------------------------------------------------------
# define subdirs to be made here

SUBDIRS = \
  gencust \
  genxml  \
  genreg  \
  . \
  test



#---------------------------------------------------------------------------------
# define your output targets here

# programs installed in bin
bin_PROGRAMS = flexconf



#---------------------------------------------------------------------------------
# sources needed for the the targets defined above

flexconf_SOURCES = \
  grammar.yxx \
  lexical.cxx \
  generator.cpp \
  genstrngrepl.cpp \
  misc.cpp \
  main.cpp



#---------------------------------------------------------------------------------
# sources needed for the the targets but not in the distribution

nodist_flexconf_SOURCES =



#---------------------------------------------------------------------------------
# other files needed to be in the distribution

EXTRA_DIST = \
  yystype.h



#--------------------------------------------------------------------------------
# when building a shared lib that should be installed include all headers
# needed to compile against the lib here

#pkginclude_HEADERS = \
#  header1.h



#---------------------------------------------------------------------------------
# compiler flags needed for the the targets defined above

#AM_CXXFLAGS = -g
AM_LFLAGS =
AM_YFLAGS = -d



#---------------------------------------------------------------------------------
# remember autoconf adds AC_CHECK_LIB libraries automatically

#flexconf_LIBADD =



#---------------------------------------------------------------------------------
# linker flags needed for the the targets defined above

#flexconf_LDFLAGS =



#---------------------------------------------------------------------------------
# additional libs needed for the the targets defined above

flexconf_LDADD = \
  gencust/libgencust.a \
  genxml/libgenxml.a \
  genreg/libgenreg.a



#---------------------------------------------------------------------------------
# patch the generated lexical file to fix bug under windows

lexical.cxx: lexical.lxx
	$(LEX) -o lexical.cxx lexical.lxx



#---------------------------------------------------------------------------------
# add cleanup

distclean-local:
	rm -f grammar.h grammar.cxx lexical.cxx
