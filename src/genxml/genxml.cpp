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

#include "genxml.h"
#include "config.h"



// strings held in progstr.cxx, generated from parser files with perl
extern const char * pszDisclaimer;
extern const char * pszHdrProlog;
extern const char * pszTypes;
extern const char * pszHdrFile;
extern const char * pszHdrStruct;
extern const char * pszHeader;
extern const char * pszHdrEpilog;

extern const char * pszSerProlog;
extern const char * pszSerStructBegin;
extern const char * pszSerStructVarDecl;
extern const char * pszSerStructVarDeclVector;
extern const char * pszSerStructVarDeclList;
extern const char * pszSerStructVarDeclMap;
extern const char * pszSerStructEnd;
extern const char * pszSerialize;

extern const char * pszDesProlog;
extern const char * pszDesStructBegin;
extern const char * pszDesStructVarDecl;
extern const char * pszDesStructVarDeclVector;
extern const char * pszDesStructVarDeclList;
extern const char * pszDesStructVarDeclMap;
extern const char * pszDesStructEnd;
extern const char * pszDeserialize;



CGeneratorXml::CGeneratorXml()
{
}



CGeneratorXml::~CGeneratorXml()
{
}



int CGeneratorXml::header()
{
  // write header declarations
  writeRep(pszDisclaimer, mfHeader);
  writeRep(pszHdrProlog,  mfHeader);
  writeStr(pszTypes,      mfHeader);
  // write serializer
  writeRep(pszDisclaimer, mfSerialize);
  writeRep(pszSerProlog,  mfSerialize);
  // write deserializer
  writeRep(pszDisclaimer, mfDeserialize);
  writeRep(pszDesProlog,  mfDeserialize);
  return 0;
}



int CGeneratorXml::headerfile()
{
  writeRep(pszHdrFile, mfHeader);
  return 0;
}



void CGeneratorXml::writeStructBegin()
{
  // declarations
  writeRep(pszHdrStruct, mfHeader);
  // start of struct serialize function
  writeRep(pszSerStructBegin, mfSerialize);
  // start of struct deserialize function
  writeRep(pszDesStructBegin, mfDeserialize);
}



void CGeneratorXml::writeVarDecl()
{
  // write serializer
  writeRep(pszSerStructVarDecl, mfSerialize);
  // write deserializer
  writeRep(pszDesStructVarDecl, mfDeserialize);
}



void CGeneratorXml::writeVarDeclVector()
{
  // write serializer
  writeRep(pszSerStructVarDeclVector, mfSerialize);
  // write deserializer
  writeRep(pszDesStructVarDeclVector, mfDeserialize);
}



void CGeneratorXml::writeVarDeclSetList()
{
  // write serializer
  writeRep(pszSerStructVarDeclList, mfSerialize);
  // write deserializer
  writeRep(pszDesStructVarDeclList, mfDeserialize);
}



void CGeneratorXml::writeVarDeclMap()
{
  // write serializer
  writeRep(pszSerStructVarDeclMap, mfSerialize);
  // write deserializer
  writeRep(pszDesStructVarDeclMap, mfDeserialize);
}



void CGeneratorXml::writeStructEnd()
{
  // end of struct serialize function
  writeRep(pszSerStructEnd, mfSerialize);
  // end of struct deserialize function
  writeRep(pszDesStructEnd, mfDeserialize);
}



int CGeneratorXml::footerfile()
{
  return 0;
}



int CGeneratorXml::footer()
{
  // write header
  writeStr(pszHeader,       mfHeader);
  writeStr(pszHdrEpilog,    mfHeader);
  // write serializer
  writeStr(pszSerialize,    mfSerialize);
  // write deserializer
  writeStr(pszDeserialize,  mfDeserialize);
  return 0;
}
