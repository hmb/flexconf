#   flexconf - flexible configuration generator
#   Copyright (C) 2008 Holger Böhnke
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

# SUBDIRS =



#---------------------------------------------------------------------------------
# define your output targets here

# programs installed in bin
noinst_PROGRAMS = testread

# static libraries
noinst_LIBRARIES = libgenxml.a



#---------------------------------------------------------------------------------
# sources needed for the the targets defined above

testread_SOURCES = \
  testread.cpp

libgenxml_a_SOURCES = \
  progstr.cxx \
  genxml.cpp



#---------------------------------------------------------------------------------

testread_LDADD = \
  libgenxml.a

#---------------------------------------------------------------------------------
# other files needed to be in the distribution

EXTRA_DIST = \
  deserialize.cpp \
  deserialize.h \
  genxml.h \
  readxml.h \
  serialize.cpp \
  serialize.h \
  writexml.h



#---------------------------------------------------------------------------------
# compiler flags needed for the the targets defined above

AM_CXXFLAGS = -g



#---------------------------------------------------------------------------------
# add serializer and xmlreader/writer as string to binary

progstr.cxx: disclaimer.h types.h writexml.h readxml.h serialize.h deserialize.h serialize.cpp deserialize.cpp strcode.pl
	perl -w strcode.pl pszDisclaimer disclaimer.h > $@
	perl -w strcode.pl pszTypes types.h >> $@
	perl -w strcode.pl pszHeader writexml.h readxml.h serialize.h deserialize.h >> $@
	perl -w strcode.pl pszSerialize serialize.cpp >> $@
	perl -w strcode.pl pszDeserialize deserialize.cpp >> $@


#---------------------------------------------------------------------------------
# add cleanup

distclean-local:
	rm -f progstr.cxx
