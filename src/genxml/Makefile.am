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

progstr.cxx: types.h writexml.h readxml.h serialize.h deserialize.h serialize.cpp deserialize.cpp
	awk 'BEGIN { BS = "\\\\";  print "const char * pszTypes =" }       { gsub(/\\/,BS); } { gsub(/\t/,"\\t"); } { gsub(/\"/,"\\\""); } { print "  \"" $$0 "\\n\"" } END { print ";" }' types.h > $@
	awk 'BEGIN { BS = "\\\\";  print "const char * pszHeader =" }      { gsub(/\\/,BS); } { gsub(/\t/,"\\t"); } { gsub(/\"/,"\\\""); } { print "  \"" $$0 "\\n\"" } END { print ";" }' writexml.h readxml.h serialize.h deserialize.h >> $@
	awk 'BEGIN { BS = "\\\\";  print "const char * pszSerialize =" }   { gsub(/\\/,BS); } { gsub(/\t/,"\\t"); } { gsub(/\"/,"\\\""); } { print "  \"" $$0 "\\n\"" } END { print ";" }' serialize.cpp >> $@
	awk 'BEGIN { BS = "\\\\";  print "const char * pszDeserialize =" } { gsub(/\\/,BS); } { gsub(/\t/,"\\t"); } { gsub(/\"/,"\\\""); } { print "  \"" $$0 "\\n\"" } END { print ";" }' deserialize.cpp >> $@


#---------------------------------------------------------------------------------
# add cleanup

distclean-local:
	rm -f progstr.cxx
