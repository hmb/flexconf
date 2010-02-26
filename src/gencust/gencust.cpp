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
#include "../misc.h"
#include <algorithm>
#include <string.h>

#define PRINTF  printf



CGeneratorCustom::CGeneratorCustom()
{
}



CGeneratorCustom::~CGeneratorCustom()
{
}



bool CGeneratorCustom::Load(const std::string & filename)
{
  FILE * fString = fopen(filename.c_str(), "r");

  if (!fString)
  {
    return false;
  }

  std::string   * pstrRead  = &mSourceFileProlog;
  const int       BUFSIZE   = 2048;
  char            szBuffer[BUFSIZE];

  while (NULL!=fgets(szBuffer, BUFSIZE, fString))
  {
    bool fSeparator = false;

    if (0==strcmp(mTagGlobalProlog, szBuffer))
    {
      pstrRead = &mGlobalProlog;
      continue;
    }

    for (int n=0; n<eFileCount*eStringCount; n++)
    {
      if (0==strcmp(mTagSections[n], szBuffer))
      {
        pstrRead    = &mGeneratorString[n/eStringCount][n%eStringCount];
        fSeparator  = true;
        break;
      }
    }

    if (fSeparator)
    {
      continue;
    }

    if (0==strcmp(mTagEnd, szBuffer))
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



bool CGeneratorCustom::Save(const std::string & filename)
{
  FILE * fString = fopen((filename+".src").c_str(), "w");

  if (!fString)
  {
    return false;
  }

  fputs(getSourceFileProlog(), fString);

  fputs(mTagGlobalProlog, fString);
  fputs(getGlobalProlog(), fString);
  fputs(mTagEnd, fString);

  char const * const sepstring  = "\n\n";
  char const * const sepfile    = "\n\n\n\n\n\n";
  const char * sepnext = sepfile;

  for (int nfile=0; nfile<eFileCount; ++nfile)
  {
    for (int nstring=0; nstring<eStringCount; ++nstring)
    {
      fputs(sepnext, fString);
      fputs(mTagSections[nfile * eStringCount + nstring], fString);
      fputs(getGeneratorString(static_cast<EOutputFile>(nfile),
        static_cast<EGeneratorString>(nstring)), fString);
      fputs(mTagEnd, fString);
      sepnext = sepstring;
    }
    sepnext = sepfile;
  }

  fclose(fString);

  return true;
}



static inline int isnonalpha(int c)
{
  return !isalpha(c);
}

static void mkvarname(std::string & varname)
{
  std::replace_if(varname.begin(), varname.end(), &isnonalpha, '_');
}

static void writeStringSource(char const * separator, std::string const & string,
  FILE * fString, std::string & array)
{
  std::string varname(separator);
  mkvarname(varname);
  fprintf(fString, "static char const * const %s =\n", varname.c_str());

  if (!array.empty())
    array += ",\n";
  array += "  ";
  array += varname;

  std::string::size_type start = 0;
  std::string::size_type end = std::string::npos;

  while (start != std::string::npos)
  {
    end = string.find('\n', start);

    if (end != std::string::npos)
    {
      if (end+1 == string.size())
        end = std::string::npos;
      else
        ++end;
    }

    std::string line = string.substr(start, end-start);

    replace(line, "\\", "\\\\");
    replace(line, "\n", "\\n");
    replace(line, "\r", "\\r");
    replace(line, "\t", "\\t");
    replace(line, "\"", "\\\"");

    fputs("  \"", fString);
    fputs(line.c_str(), fString);
    fputs("\"\n", fString);

    start = end;
  }

  fputs(";\n", fString);
}



bool CGeneratorCustom::SaveSource(const std::string & filename)
{
  FILE * fString = fopen((filename + ".h").c_str(), "w");
  if (!fString)
  {
    return false;
  }

  fprintf(fString, "#ifndef flexconf_source_%s_h\n", filename.c_str());
  fprintf(fString, "#define ifndef flexconf_source_%s_h\n", filename.c_str());
  fputs("\n", fString);
  fputs("\n", fString);
  fputs("\n", fString);
  fprintf(fString, "char const * const * const get_%s();\n", filename.c_str());
  fputs("\n", fString);
  fputs("\n", fString);
  fprintf(fString, "#endif // flexconf_source_%s_h\n", filename.c_str());
  fclose(fString);

  fString = fopen((filename + ".cpp").c_str(), "w");

  if (!fString)
  {
    return false;
  }

  std::string array;

  writeStringSource("SourceFileProlog", getSourceFileProlog(), fString, array);
  writeStringSource("GlobalProlog", getGlobalProlog(), fString, array);

  // the SourceFileProlog and the global prolog are not part of the infamous array
  array.clear();

  char const * const sepstring  = "\n\n";
  char const * const sepfile    = "\n\n\n\n\n\n";
  const char * sepnext = "";

  for (int nfile=0; nfile<eFileCount; ++nfile)
  {
    for (int nstring=0; nstring<eStringCount; ++nstring)
    {
      fputs(sepnext, fString);
      writeStringSource(
        mTagSections[nfile * eStringCount + nstring],
        getGeneratorString(static_cast<EOutputFile>(nfile),
        static_cast<EGeneratorString>(nstring)),
        fString, array);
      sepnext = sepstring;
    }
    sepnext = sepfile;
  }

  fprintf(fString, "\n\n\nstatic char const * const pointers[%d][%d] =\n{\n%s\n};\n",
    eFileCount, eStringCount, array.c_str());

  fputs("\n", fString);
  fputs("\n", fString);
  fputs("\n", fString);
  fprintf(fString, "char const * const * const get_%s()\n", filename.c_str());
  fputs("{\n", fString);
  fputs("  return pointers;\n", fString);
  fputs("}\n", fString);

  fclose(fString);

  return true;
}



const char * const CGeneratorCustom::getSourceFileProlog()
{
  return mSourceFileProlog.c_str();
}



const char * const CGeneratorCustom::getGlobalProlog()
{
  return mGlobalProlog.c_str();
}



const char * const CGeneratorCustom::getGeneratorString(EOutputFile fileid, EGeneratorString stringid)
{
  return mGeneratorString[fileid][stringid].c_str();
}



const char * const CGeneratorCustom::mTagSections[CGeneratorCustom::eFileCount * CGeneratorCustom::eStringCount] =
{
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



const char * const CGeneratorCustom::mTagGlobalProlog =
  "********** [GL] PROLOG\n";



const char * const CGeneratorCustom::mTagEnd =
  "********** [END]\n";
