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



int main(int argc, char * argv[])
{
  std::cout << PACKAGE " - " PACKAGE_STRING << std::endl;

  std::auto_ptr<CGenerator>   pGenerator;
  int                         nFileStart = 1;

  if (argc>=2 && 0==strcmp(argv[1], "-c"))
  {
    std::cout << "found -c, using custom generator" << std::endl;
    CGeneratorCustom * pCust = new CGeneratorCustom;
    pCust->Load("../genxml.src");
    auto_ptr_assign(pGenerator, CGenerator, pCust);
    ++nFileStart;
  }
  else if (argc>=2 && 0==strcmp(argv[1], "-r"))
  {
    std::cout << "found -r, using registry generator" << std::endl;
    auto_ptr_assign(pGenerator, CGenerator, new CGeneratorReg);
    ++nFileStart;
  }
  else if (argc>=2 && 0==strcmp(argv[1], "-x"))
  {
    std::cout << "found -x, using xml generator" << std::endl;
    auto_ptr_assign(pGenerator, CGenerator, new CGeneratorXml);
    ++nFileStart;
  }
  else
  {
    std::cout << "no generation option given, defaulting to xml generator" << std::endl;
    auto_ptr_assign(pGenerator, CGenerator, new CGeneratorXml);
  }

  /*
  Generator.SetHeaderFilename(argv[nFile]);
  Generator.SetSerializerFilename(argv[nFile]);
  Generator.SetDeserializerFilename(argv[nFile]);
  */
  if (nFileStart==argc)
  {
    std::cout << "input files missing" << std::endl;
    return 1;
  }

  for (int nFile=nFileStart; nFile<argc; nFile++)
  {
    std::cout << "adding input files :" << argv[nFile] << std::endl;
    pGenerator->AddSourceFile(argv[nFile]);
  }
  pGenerator->Generate();

  return 0;
}
