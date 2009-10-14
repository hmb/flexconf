/*
  flexconf - flexible configuration generator
  Copyright (C) 2008 Holger Böhnke

  This file is part of flexconf.

  Flexconf is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GeneratorCustom_h
#define GeneratorCustom_h

#include "../genstrngrepl.h"



class CGeneratorCustom : public CGeneratorStringReplace
{
public:
  CGeneratorCustom();
  virtual ~CGeneratorCustom();

  bool Load(const char * filename);
  bool Save(const char * filename);
  bool SaveSource(const char * filename);

private:
  virtual const char * const getSourceFileProlog();
  virtual const char * const getGlobalProlog();
  virtual const char * const getGeneratorString(EOutputFile fileid, EGeneratorString stringid);

  std::string   mSourceFileProlog;
  std::string   mGlobalProlog;
  std::string   mGeneratorString[eFileCount][eStringCount];

  static const char * const mTagGlobalProlog;
  static const char * const mTagSections[eFileCount * eStringCount];
  static const char * const mTagEnd;
};


#endif // GeneratorCustom_h
