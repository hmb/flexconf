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

noinst_PROGRAMS = test



#---------------------------------------------------------------------------------
# sources needed for the the targets defined above

test_SOURCES = \
  test.cpp

nodist_test_SOURCES = \
  structCom.cpp \
  structSer.cpp \
  structDes.cpp

EXTRA_DIST = \
  test.h



#---------------------------------------------------------------------------------
# compiler flags needed for the the targets defined above

test_CXXFLAGS = -g



#---------------------------------------------------------------------------------
# remember autoconf adds AC_CHECK_LIB libraries automatically

#test_LIBADD =



#---------------------------------------------------------------------------------
# linker flags needed for the the targets defined above

#test_LDFLAGS =



#---------------------------------------------------------------------------------
# generate the cpp files from test.h

FCGENERATOR = ../gencust/xmlconf.src
FCSOURCES   = test.h

structCom.h structSer.h structDes.h structCom.cpp structSer.cpp structDes.cpp: ../flexconf $(FCGENERATOR) $(FCSOURCES)
	../flexconf -c $(FCGENERATOR) $(FCSOURCES)
#	../flexconf -x $(FCSOURCES)
#	../flexconf -r $(FCSOURCES)

# list dependencies of struct.h (cpp files that include struct.h)
test.cpp: test.h structCom.h structSer.h structDes.h


#---------------------------------------------------------------------------------
# add cleanup

distclean-local:
	rm -f structCom.h structSer.h structDes.h structCom.cpp structSer.cpp structDes.cpp
