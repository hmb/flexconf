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
# define your output targets here

noinst_PROGRAMS = \
  testxmlconf \
  testlibxml2



#---------------------------------------------------------------------------------
# sources needed for the the targets defined above

testxmlconf_SOURCES = \
  xmlconfCom.cpp \
  xmlconfSer.cpp \
  xmlconfDes.cpp \
  test.cpp \
  testxmlconf.cpp

#nodist_testxmlconf_SOURCES = \
  xmlconfCom.cpp \
  xmlconfSer.cpp \
  xmlconfDes.cpp

#EXTRA_DIST = \
  test.h

testlibxml2_SOURCES = \
  libxml2Com.cpp \
  libxml2Ser.cpp \
  libxml2Des.cpp \
  test.cpp \
  testlibxml2.cpp



#---------------------------------------------------------------------------------
# compiler flags needed for the the targets defined above

testxmlconf_CXXFLAGS = -g

testlibxml2_CXXFLAGS = -g -I/usr/include/libxml2



#---------------------------------------------------------------------------------
# remember autoconf adds AC_CHECK_LIB libraries automatically

#testxmlconf_LIBADD =

testlibxml2_LDADD = -lxml2


#---------------------------------------------------------------------------------
# linker flags needed for the the targets defined above

#testxmlconf_LDFLAGS =



#---------------------------------------------------------------------------------
# generate the cpp files from test.h

FCSOURCES   = test.h

%Com.cpp: ../flexconf ../gencust/%.src $(FCSOURCES)
	../flexconf -c ../gencust/$*.src -b $* $(FCSOURCES)



#---------------------------------------------------------------------------------
# add cleanup

distclean-local:
	rm -f *Com.h *Ser.h *Des.h *Com.cpp *Ser.cpp *Des.cpp
