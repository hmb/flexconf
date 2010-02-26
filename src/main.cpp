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
#include "gencust/gencust.h"
#include <iostream>
#include <memory>

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
  bool            mExtOut;      // -e <filename>
  std::string     mExtFile;     // -e <filename>
  bool            mIntOut;      // -i <filename>
  std::string     mIntFile;     // -i <filename>
  std::string     mBasename;    // -b <filename>
};



SOptions::SOptions()
  :
  mGenType(eGenTypXmlconf),
  mGenFile("flexconf.src"),
  mExtOut(false),
  mExtFile("external"),
  mIntOut(false),
  mIntFile("internal")
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
      std::cout << "ERR: internal registry generation currently disabled. "
        "Use the custom generator with 'winreg.src'" << std::endl;
      return false;
      break;

    case 'x':
      options.mGenType = eGenTypXmlconf;
      break;

    case 'e':
      if (!getoptionparam(argc, argv, n, options.mExtFile))
      {
        std::cout << "ERR: missing external filename for option: '-" << argv[n][1] << '\'' << std::endl;
        return false;
      }
      options.mExtOut = true;
      break;

    case 'i':
      if (!getoptionparam(argc, argv, n, options.mIntFile))
      {
        std::cout << "ERR: missing internal filename for option: '-" << argv[n][1] << '\'' << std::endl;
        return false;
      }
      options.mIntOut = true;
      break;

    case 'b':
      if (!getoptionparam(argc, argv, n, options.mBasename))
      {
        std::cout << "ERR: missing basename for option: '-" << argv[n][1] << '\'' << std::endl;
        return false;
      }
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

  std::auto_ptr<CGenerator> pGenerator;

  switch (options.mGenType)
  {
  case eGenTypCustom:
    {
      std::cout << "using custom generator" << std::endl;
      CGeneratorCustom * pCust = new CGeneratorCustom;
      if (!pCust->Load(options.mGenFile))
      {
        std::cout << "ERR: could not load custom generator file" << std::endl;
        return 1;
      }

      if (options.mExtOut)
      {
        pCust->Save(options.mExtFile);
      }
      if (options.mIntOut)
      {
        pCust->SaveSource(options.mIntFile);
      }

      auto_ptr_assign(pGenerator, CGenerator, pCust);
    }
    break;

/*
  case eGenTypRegistry:
    std::cout << "using registry generator" << std::endl;
    auto_ptr_assign(pGenerator, CGenerator, new CGeneratorReg);
    break;
*/

  case eGenTypXmlconf:
    {
      std::cout << "using xml generator" << std::endl;
      CGeneratorXml * pXml = new CGeneratorXml;

/*
      if (options.mExtOut)
      {
        pXml->Save(options.mExtFile);
      }
      if (options.mIntOut)
      {
        pXml->SaveSource(options.mIntFile);
      }
*/

      auto_ptr_assign(pGenerator, CGenerator, pXml);
    }
    break;

  default:
    std::cout << "ERR: no generation option given" << std::endl;
    return 1;
    // break;
  }

  if (files.empty())
  {
    std::cout << "WARNING: no input files" << std::endl;
    return 0;
  }

  if (!options.mBasename.empty())
  {
    pGenerator->SetOutputFileBasename(options.mBasename);
  }

  for (std::list<std::string>::const_iterator ctr=files.begin(); ctr!=files.end(); ++ctr)
  {
    std::cout << "adding input files :" << *ctr << std::endl;
    pGenerator->AddSourceFile(ctr->c_str());
  }

  return pGenerator->Generate();
}
