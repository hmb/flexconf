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

#include "gencust.h"

#define PRINTF  printf



const char * const CGeneratorCustom::mpszSeparator[CGeneratorCustom::eStringCount * CGeneratorCustom::eFileCount] =
{
  "********** HeaderDeSerHdr\n",
  "********** HeaderSerImp\n",
  "********** HeaderDesImp\n",

  "********** HeaderFileDeSerHdr\n",
  "********** HeaderFileSerImp\n",
  "********** HeaderFileDesImp\n",

  "********** StructBeginDeSerHdr\n",
  "********** StructBeginSerImp\n",
  "********** StructBeginDesImp\n",

  "********** VarDeclDeSerHdr\n",
  "********** VarDeclSerImp\n",
  "********** VarDeclDesImp\n",

  "********** VarDeclVectorDeSerHdr\n",
  "********** VarDeclVectorSerImp\n",
  "********** VarDeclVectorDesImp\n",

  "********** VarDeclSetListDeSerHdr\n",
  "********** VarDeclSetListSerImp\n",
  "********** VarDeclSetListDesImp\n",

  "********** VarDeclMapDeSerHdr\n",
  "********** VarDeclMapSerImp\n",
  "********** VarDeclMapDesImp\n",

  "********** StructEndDeSerHdr\n",
  "********** StructEndSerImp\n",
  "********** StructEndDesImp\n",

  "********** FooterFileDeSerHdr\n",
  "********** FooterFileSerImp\n",
  "********** FooterFileDesImp\n",

  "********** FooterDeSerHdr\n",
  "********** FooterSerImp\n",
  "********** FooterDesImp\n"

//  ,"" // too many initializer test
};



const char * const CGeneratorCustom::mpszEnd =
  "********** end\n";






CGeneratorCustom::CGeneratorCustom()
{
}



CGeneratorCustom::~CGeneratorCustom()
{
}






void CGeneratorCustom::Load(const char * pszStrings)
{
  FILE * fString = fopen(pszStrings, "r");
  if (fString)
  {
    std::string   * pstrRead  = 0;
    const int       BUFSIZE   = 256;
    char            szBuffer[BUFSIZE];

    while (NULL!=fgets(szBuffer, BUFSIZE, fString))
    {
      bool fSeparator = false;

      for (int n=0; n<eStringCount*eFileCount; n++)
      {
        if (0==strcmp(mpszSeparator[n], szBuffer))
        {
          pstrRead    = &mstrGeneratorString[n/eFileCount][n%eFileCount];
          fSeparator  = true;
          break;
        }
      }

      if (fSeparator)
        continue;

      if (0==strcmp(mpszEnd, szBuffer))
      {
        pstrRead = 0;
      }
      else if (0!=pstrRead)
      {
        pstrRead->append(szBuffer);
      }
    }

    fclose(fString);
  }
}






int CGeneratorCustom::output(EGeneratorString eString)
{
  writeRep(mstrGeneratorString[eString][eSerDeserHdr], mfHeader);
  writeRep(mstrGeneratorString[eString][eSerializerImp], mfSerialize);
  writeRep(mstrGeneratorString[eString][eDeserializerImp], mfDeserialize);
  return 0;
}






int CGeneratorCustom::header()
{
  return output(eHeader);
}

int CGeneratorCustom::headerfile()
{
  return output(eHeaderFile);
}



void CGeneratorCustom::writeStructBegin()
{
  output(eStructBegin);
}

void CGeneratorCustom::writeVarDecl()
{
  output(eVarDecl);
}

void CGeneratorCustom::writeVarDeclVector()
{
  output(eVarDeclVector);
}

void CGeneratorCustom::writeVarDeclSetList()
{
  output(eVarDeclSetList);
}

void CGeneratorCustom::writeVarDeclMap()
{
  output(eVarDeclMap);
}

void CGeneratorCustom::writeStructEnd()
{
  output(eStructEnd);
}



int CGeneratorCustom::footerfile()
{
  return output(eFooterFile);
}

int CGeneratorCustom::footer()
{
  return output(eFooter);
}
