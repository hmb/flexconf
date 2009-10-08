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
  "********** [GL] PROLOG\n",
  "********** [GL] FILE PROLOG\n",
  "********** [GL] STRUCT PROLOG\n",
  "********** [GL] GENERIC DECL\n",
  "********** [GL] VECTOR DECL\n",
  "********** [GL] SET/LIST DECL\n",
  "********** [GL] MAP DECL\n",
  "********** [GL] STRUCT EPILOG\n",
  "********** [GL] FILE EPILOG\n",
  "********** [GL] EPILOG\n",

  "********** [SH] PROLOG\n",
  "********** [SH] FILE PROLOG\n",
  "********** [SH] STRUCT PROLOG\n",
  "********** [SH] GENERIC DECL\n",
  "********** [SH] VECTOR DECL\n",
  "********** [SH] SET/LIST DECL\n",
  "********** [SH] MAP DECL\n",
  "********** [SH] STRUCT EPILOG\n",
  "********** [SH] FILE EPILOG\n",
  "********** [SH] EPILOG\n",

  "********** [DH] PROLOG\n",
  "********** [DH] FILE PROLOG\n",
  "********** [DH] STRUCT PROLOG\n",
  "********** [DH] GENERIC DECL\n",
  "********** [DH] VECTOR DECL\n",
  "********** [DH] SET/LIST DECL\n",
  "********** [DH] MAP DECL\n",
  "********** [DH] STRUCT EPILOG\n",
  "********** [DH] FILE EPILOG\n",
  "********** [DH] EPILOG\n",

  "********** [SI] PROLOG\n",
  "********** [SI] FILE PROLOG\n",
  "********** [SI] STRUCT PROLOG\n",
  "********** [SI] GENERIC DECL\n",
  "********** [SI] VECTOR DECL\n",
  "********** [SI] SET/LIST DECL\n",
  "********** [SI] MAP DECL\n",
  "********** [SI] STRUCT EPILOG\n",
  "********** [SI] FILE EPILOG\n",
  "********** [SI] EPILOG\n",

  "********** [DI] PROLOG\n",
  "********** [DI] FILE PROLOG\n",
  "********** [DI] STRUCT PROLOG\n",
  "********** [DI] GENERIC DECL\n",
  "********** [DI] VECTOR DECL\n",
  "********** [DI] SET/LIST DECL\n",
  "********** [DI] MAP DECL\n",
  "********** [DI] STRUCT EPILOG\n",
  "********** [DI] FILE EPILOG\n",
  "********** [DI] EPILOG\n"
//  ,"" // too many initializer test
};



const char * const CGeneratorCustom::mpszEnd =
  "********** [END]\n";






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
          pstrRead    = &mstrGeneratorString[n%eFileCount][n/eFileCount];
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
  writeRep(mstrGeneratorString[eGlobal][eString],           mfCommonHdr);
  writeRep(mstrGeneratorString[eGlobal][eString],           mfCommonImp);
  writeRep(mstrGeneratorString[eGlobal][eString],           mfSerializeHdr);
  writeRep(mstrGeneratorString[eGlobal][eString],           mfSerializeImp);
  writeRep(mstrGeneratorString[eGlobal][eString],           mfDeserializeHdr);
  writeRep(mstrGeneratorString[eGlobal][eString],           mfDeserializeImp);

  writeRep(mstrGeneratorString[eCommonHdr][eString],        mfCommonHdr);
  writeRep(mstrGeneratorString[eCommonImp][eString],        mfCommonImp);
  writeRep(mstrGeneratorString[eSerializerHdr][eString],    mfSerializeHdr);
  writeRep(mstrGeneratorString[eSerializerImp][eString],    mfSerializeImp);
  writeRep(mstrGeneratorString[eDeserializerHdr][eString],  mfDeserializeHdr);
  writeRep(mstrGeneratorString[eDeserializerImp][eString],  mfDeserializeImp);
  return 0;
}






int CGeneratorCustom::header()
{
  return output(eProlog);
}

int CGeneratorCustom::headerfile()
{
  return output(ePrologFile);
}



void CGeneratorCustom::writeStructBegin()
{
  output(ePrologStruct);
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
  output(eEpilogStruct);
}



int CGeneratorCustom::footerfile()
{
  return output(eEpilogFile);
}

int CGeneratorCustom::footer()
{
  return output(eEpilog);
}
