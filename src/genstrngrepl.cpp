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

#include "genstrngrepl.h"

#define PRINTF  printf



CGeneratorStringReplace::CGeneratorStringReplace()
{
}



CGeneratorStringReplace::~CGeneratorStringReplace()
{
}



int CGeneratorStringReplace::output(EGeneratorString stringid)
{
  writeRep(getGeneratorString(eCommonHdr, stringid),        eCommonHdr);
  writeRep(getGeneratorString(eCommonImp, stringid),        eCommonImp);
  writeRep(getGeneratorString(eSerializerHdr, stringid),    eSerializerHdr);
  writeRep(getGeneratorString(eSerializerImp, stringid),    eSerializerImp);
  writeRep(getGeneratorString(eDeserializerHdr, stringid),  eDeserializerHdr);
  writeRep(getGeneratorString(eDeserializerImp, stringid),  eDeserializerImp);

  return 0;
}



int CGeneratorStringReplace::header()
{
  const char * const global = getGlobalProlog();

  writeRep(global, eCommonHdr);
  writeRep(global, eCommonImp);
  writeRep(global, eSerializerHdr);
  writeRep(global, eSerializerImp);
  writeRep(global, eDeserializerHdr);
  writeRep(global, eDeserializerImp);

  return output(eProlog);
}

int CGeneratorStringReplace::headerfile()
{
  return output(ePrologFile);
}



void CGeneratorStringReplace::writeStructBegin()
{
  output(ePrologStruct);
}

void CGeneratorStringReplace::writeVarDecl()
{
  output(eVarDecl);
}

void CGeneratorStringReplace::writeVarDeclVector()
{
  output(eVarDeclVector);
}

void CGeneratorStringReplace::writeVarDeclSetList()
{
  output(eVarDeclSetList);
}

void CGeneratorStringReplace::writeVarDeclMap()
{
  output(eVarDeclMap);
}

void CGeneratorStringReplace::writeStructEnd()
{
  output(eEpilogStruct);
}



int CGeneratorStringReplace::footerfile()
{
  return output(eEpilogFile);
}

int CGeneratorStringReplace::footer()
{
  return output(eEpilog);
}
