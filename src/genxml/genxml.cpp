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
  writeRep(pszDisclaimer, eCommonHdr);
  writeRep(pszHdrProlog,  eCommonHdr);
  writeStr(pszTypes,      eCommonHdr);
  // write serializer
  writeRep(pszDisclaimer, eSerializerImp);
  writeRep(pszSerProlog,  eSerializerImp);
  // write deserializer
  writeRep(pszDisclaimer, eDeserializerImp);
  writeRep(pszDesProlog,  eDeserializerImp);
  return 0;
}



int CGeneratorXml::headerfile()
{
  writeRep(pszHdrFile, eCommonHdr);
  return 0;
}



void CGeneratorXml::writeStructBegin()
{
  // declarations
  writeRep(pszHdrStruct, eCommonHdr);
  // start of struct serialize function
  writeRep(pszSerStructBegin, eSerializerImp);
  // start of struct deserialize function
  writeRep(pszDesStructBegin, eDeserializerImp);
}



void CGeneratorXml::writeVarDecl()
{
  // write serializer
  writeRep(pszSerStructVarDecl, eSerializerImp);
  // write deserializer
  writeRep(pszDesStructVarDecl, eDeserializerImp);
}



void CGeneratorXml::writeVarDeclVector()
{
  // write serializer
  writeRep(pszSerStructVarDeclVector, eSerializerImp);
  // write deserializer
  writeRep(pszDesStructVarDeclVector, eDeserializerImp);
}



void CGeneratorXml::writeVarDeclSetList()
{
  // write serializer
  writeRep(pszSerStructVarDeclList, eSerializerImp);
  // write deserializer
  writeRep(pszDesStructVarDeclList, eDeserializerImp);
}



void CGeneratorXml::writeVarDeclMap()
{
  // write serializer
  writeRep(pszSerStructVarDeclMap, eSerializerImp);
  // write deserializer
  writeRep(pszDesStructVarDeclMap, eDeserializerImp);
}



void CGeneratorXml::writeStructEnd()
{
  // end of struct serialize function
  writeRep(pszSerStructEnd, eSerializerImp);
  // end of struct deserialize function
  writeRep(pszDesStructEnd, eDeserializerImp);
}



int CGeneratorXml::footerfile()
{
  return 0;
}



int CGeneratorXml::footer()
{
  // write header
  writeStr(pszHeader,       eCommonHdr);
  writeStr(pszHdrEpilog,    eCommonHdr);
  // write serializer
  writeStr(pszSerialize,    eSerializerImp);
  // write deserializer
  writeStr(pszDeserialize,  eDeserializerImp);
  return 0;
}
