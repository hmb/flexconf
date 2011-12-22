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
  testlibxml2 \
  testjson



#---------------------------------------------------------------------------------
# sources needed for the the targets defined above

XMLCONF_TARGETS = \
  xmlconfCom.cpp \
  xmlconfSer.cpp \
  xmlconfDes.cpp

testxmlconf_SOURCES = \
  $(XMLCONF_TARGETS) \
  test.cpp \
  testxmlconf.cpp



LIBXML2_TARGETS = \
  libxml2Com.cpp \
  libxml2Ser.cpp \
  libxml2Des.cpp

testlibxml2_SOURCES = \
  $(LIBXML2_TARGETS) \
  test.cpp \
  testlibxml2.cpp



JSON_TARGETS = \
  jsonCom.cpp \
  jsonSer.cpp \
  jsonDes.cpp

testjson_SOURCES = \
  $(JSON_TARGETS) \
  test.cpp \
  testjson.cpp



#---------------------------------------------------------------------------------
# compiler flags needed for the the targets defined above

testxmlconf_CXXFLAGS = -g -W -Wno-unused-parameter -Wall

testlibxml2_CXXFLAGS = -g -I/usr/include/libxml2 -W -Wno-unused-parameter -Wall

testjson_CXXFLAGS = -g -W -Wno-unused-parameter -Wall



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

$(XMLCONF_TARGETS): ../flexconf ../gencust/xmlconf.src $(FCSOURCES)
	../flexconf -c ../gencust/xmlconf.src -b xmlconf $(FCSOURCES)

$(LIBXML2_TARGETS): ../flexconf ../gencust/libxml2.src $(FCSOURCES)
	../flexconf -c ../gencust/libxml2.src -b libxml2 $(FCSOURCES)

$(JSON_TARGETS): ../flexconf ../gencust/json.src $(FCSOURCES)
	../flexconf -c ../gencust/json.src -b json $(FCSOURCES)



#---------------------------------------------------------------------------------
# add cleanup

distclean-local:
	rm -f *Com.h *Ser.h *Des.h *Com.cpp *Ser.cpp *Des.cpp
