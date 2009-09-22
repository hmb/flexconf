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

#include "../generator.h"



class CGeneratorCustom : public CGenerator
{
public:
  CGeneratorCustom();
  virtual ~CGeneratorCustom();

  void Load(const char * pszStrings);

protected:
  // virtual functions to write headers
  virtual int header();
  virtual int headerfile();

  // virtual functions called by the parser to generate de/serializers
  virtual void writeStructBegin();
  virtual void writeVarDecl();
  virtual void writeVarDeclVector();
  virtual void writeVarDeclSetList();
  virtual void writeVarDeclMap();
  virtual void writeStructEnd();

  // virtual functions to write footers
  virtual int footerfile();
  virtual int footer();

  enum EGeneratorString
  {
    eHeader,
    eHeaderFile,

    eStructBegin,
    eVarDecl,
    eVarDeclVector,
    eVarDeclSetList,
    eVarDeclMap,
    eStructEnd,

    eFooterFile,
    eFooter,

    eStringCount
  };

  enum EOutputFile
  {
    eSerializerHdr,
    eDeserializerHdr,
    eSerializerImp,
    eDeserializerImp,
    eFileCount
  };

private:
  int output(EGeneratorString eString);

  std::string   mstrGeneratorString[eStringCount][eFileCount];

  std::string   mstrStructBegin;
  std::string   mstrVarDecl;
  std::string   mstrVarDeclSetList;
  std::string   mstrVarDeclMap;
  std::string   mstrStructEnd;

  static const char * const mpszSeparator[eStringCount * eFileCount];
  static const char * const mpszEnd;
};


#endif // GeneratorCustom_h
