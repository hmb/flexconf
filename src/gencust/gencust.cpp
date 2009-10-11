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



const char * const CGeneratorCustom::mpszSeparator[CGeneratorCustom::eFileCount * CGeneratorCustom::eStringCount] =
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

  "********** [CH] PROLOG\n",
  "********** [CH] FILE PROLOG\n",
  "********** [CH] STRUCT PROLOG\n",
  "********** [CH] GENERIC DECL\n",
  "********** [CH] VECTOR DECL\n",
  "********** [CH] SET/LIST DECL\n",
  "********** [CH] MAP DECL\n",
  "********** [CH] STRUCT EPILOG\n",
  "********** [CH] FILE EPILOG\n",
  "********** [CH] EPILOG\n",

  "********** [CI] PROLOG\n",
  "********** [CI] FILE PROLOG\n",
  "********** [CI] STRUCT PROLOG\n",
  "********** [CI] GENERIC DECL\n",
  "********** [CI] VECTOR DECL\n",
  "********** [CI] SET/LIST DECL\n",
  "********** [CI] MAP DECL\n",
  "********** [CI] STRUCT EPILOG\n",
  "********** [CI] FILE EPILOG\n",
  "********** [CI] EPILOG\n",

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






bool CGeneratorCustom::Load(const char * filename)
{
  FILE * fString = fopen(filename, "r");

  if (!fString)
  {
    return false;
  }

  std::string   * pstrRead  = &mstrSourceFileProlog;
  const int       BUFSIZE   = 256;
  char            szBuffer[BUFSIZE];

  while (NULL!=fgets(szBuffer, BUFSIZE, fString))
  {
    bool fSeparator = false;

    for (int n=0; n<eFileCount*eStringCount; n++)
    {
      if (0==strcmp(mpszSeparator[n], szBuffer))
      {
        pstrRead    = &mstrGeneratorString[n/eStringCount][n%eStringCount];
        fSeparator  = true;
        break;
      }
    }

    if (fSeparator)
    {
      continue;
    }

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

  return true;
}



bool CGeneratorCustom::Save(const char * filename)
{
  FILE * fString = fopen(filename, "w");

  if (!fString)
  {
    return false;
  }

  fputs(mstrSourceFileProlog.c_str(), fString);

  char const * const sepstring  = "\n\n";
  char const * const sepfile    = "\n\n\n\n\n\n";
  const char * sepnext = "";

  for (int nfile=0; nfile<eFileCount; ++nfile)
  {
    for (int nstring=0; nstring<eStringCount; ++nstring)
    {
      fputs(sepnext, fString);
      fputs(mpszSeparator[nfile * eStringCount + nstring], fString);
      fputs(mstrGeneratorString[nfile][nstring].c_str(), fString);
      fputs(mpszEnd, fString);
      sepnext = sepstring;
    }
    sepnext = sepfile;
  }

  fclose(fString);

  return true;
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
