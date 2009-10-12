/*
  flexconf - flexible configuration generator
  Copyright (C) 2003-2008 Holger Böhnke

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

#include "config.h"
#include "grammar.h"
#include "genxml/genxml.h"
#include "genreg/genreg.h"
#include "gencust/gencust.h"
#include <iostream>

#if defined(_MSC_VER) && _MSC_VER <= 1200
  #define auto_ptr_assign(_ptr, _class, _value) _ptr = std::auto_ptr<_class>(_value)
#else
  #define auto_ptr_assign(_ptr, _class, _value) _ptr.reset(_value)
#endif


enum EGeneratorType
{
  eGenTypCustom,
  eGenTypRegistry,
  eGenTypXmlconf
};



struct SOptions
{
  SOptions();

  EGeneratorType  mGenType;     // -c <filename> | -r | -x
  std::string     mGenFile;     // -c <filename>
  bool            mDbgOut;      // -d <filename>
  std::string     mDbgFile;     // -d <filename>
};



SOptions::SOptions()
  :
  mGenType(eGenTypXmlconf),
  mGenFile("flexconf.src"),
  mDbgOut(false),
  mDbgFile("debug.src")
{
}



// ------------------------------------------------------------------------
// BEGIN TEMPORARY
/* This function is a temporary workaround to read the commandline options.
   It shall be replaced by flexconfs future own option generator.
*/
static bool getoptionparam(int argc, const char * argv[], int & n, std::string & param)
{
  if ( n == argc-1 )
  {
    return false;
  }

  param = argv[++n];
  return true;
}



static bool getoptions(int argc, const char * argv[], SOptions & options, std::list<std::string> & files)
{
  bool readoptions = true;

  for (int n=1; n<argc; ++n)
  {
    if ( !readoptions  ||  argv[n][0] != '-' )
    {
      files.push_back(argv[n]);
      continue;
    }

    if (argv[n][1] == '-')
    {
      if (argv[n][2] == 0) // parameter separator: "--"
      {
        readoptions = false;
      }
      else
      {
        std::cout << "INF: currently ignoring long options: '" << argv[n] << '\'' << std::endl;
      }

      continue;
    }

    if (argv[n][2] != 0)
    {
      std::cout << "ERR: trailing characters after option: '-" << argv[n][1] << '\'' << std::endl;
      return false;
    }

    switch (argv[n][1])
    {
    case 'c':
      if (!getoptionparam(argc, argv, n, options.mGenFile))
      {
        std::cout << "ERR: missing generator file for option: '-" << argv[n][1] << '\'' << std::endl;
        return false;
      }
      options.mGenType = eGenTypCustom;
      break;

    case 'r':
      options.mGenType = eGenTypRegistry;
      break;

    case 'x':
      options.mGenType = eGenTypXmlconf;
      break;

    case 'd':
      if (!getoptionparam(argc, argv, n, options.mDbgFile))
      {
        std::cout << "ERR: missing debug output file for option: '-" << argv[n][1] << '\'' << std::endl;
        return false;
      }
      options.mDbgOut = true;
      break;

    default:
      std::cout << "ERR: unknown option: '-" << argv[n][1] << '\'' << std::endl;
      return false;
      // break; // obsolete, due to the above return
    }
  }

  return true;
}
// END TEMPORARY
// ------------------------------------------------------------------------



int main(int argc, const char * argv[])
{
  std::cout << PACKAGE " - " PACKAGE_STRING << std::endl;

  SOptions                options;
  std::list<std::string>  files;

  if (!getoptions(argc, argv, options, files))
  {
    return 1;
  }

  if (files.empty())
  {
    std::cout << "ERR: no input files" << std::endl;
    return 1;
  }

  std::auto_ptr<CGenerator> pGenerator;

  switch (options.mGenType)
  {
  case eGenTypCustom:
    {
      std::cout << "using custom generator" << std::endl;
      CGeneratorCustom * pCust = new CGeneratorCustom;
      if (!pCust->Load(options.mGenFile.c_str()))
      {
        std::cout << "ERR: could not load custom generator file" << std::endl;
        return 1;
      }

      if (options.mDbgOut)
      {
        pCust->Save(options.mDbgFile.c_str());
      }

      auto_ptr_assign(pGenerator, CGenerator, pCust);
    }
    break;

  case eGenTypRegistry:
    std::cout << "using registry generator" << std::endl;
    auto_ptr_assign(pGenerator, CGenerator, new CGeneratorReg);
    break;

  case eGenTypXmlconf:
    std::cout << "using xml generator" << std::endl;
    auto_ptr_assign(pGenerator, CGenerator, new CGeneratorXml);
    break;

  default:
    std::cout << "ERR: no generation option given" << std::endl;
    return 1;
    // break;
  }

  /*
  SetFileComHdr(const char * pszFilename);
  SetFileComImp(const char * pszFilename);
  SetFileSerHdr(const char * pszFilename);
  SetFileSerImp(const char * pszFilename);
  SetFileDesHdr(const char * pszFilename);
  SetFileDesImp(const char * pszFilename);
  */

  for (std::list<std::string>::const_iterator ctr=files.begin(); ctr!=files.end(); ++ctr)
  {
    std::cout << "adding input files :" << *ctr << std::endl;
    pGenerator->AddSourceFile(ctr->c_str());
  }

  return pGenerator->Generate();
}
