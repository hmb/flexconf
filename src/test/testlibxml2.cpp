/*
  flexconf - flexible configuration generator
  Copyright (c) 2008-2009 Holger Böhnke

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

#ifdef _MSC_VER
  #pragma warning( disable : 4786 4996 )
#endif

# include "xmlconfCom.h"
# include "xmlconfSer.h"
# include "xmlconfDes.h"

# include <iostream>



void serialize(CWriteXml & rWriteXml, const CData & rObject, const char * pszTag, bool fRoot,
  const char * pszIdTag, const std::string * pstrIdValue)
{
  serialize(rWriteXml, static_cast<const SData&>(rObject), pszTag, fRoot, pszIdTag, pstrIdValue);
}



void deserialize(CReadXml & rReadXml, CData & rObject, const char * pszTag, bool fRoot,
  const char * pszIdTag, std::string * pstrIdValue)
{
  deserialize(rReadXml, static_cast<SData&>(rObject), pszTag, fRoot, pszIdTag, pstrIdValue);
}



int main(int argc, char *argv[])
{
  std::string strXmlFirst;
  STest       testFirst;

  initTest(testFirst);

  {
    std::cout << "+----------------------------------------------------------------+" << std::endl;
    std::cout << "| write xml to a string                                          |" << std::endl;
    std::cout << "+----------------------------------------------------------------+" << std::endl;

    CWriteXmlString writeString(strXmlFirst);
    serialize(writeString, testFirst);
    std::cout << strXmlFirst << std::endl;
  }

  {
    std::cout << "+----------------------------------------------------------------+" << std::endl;
    std::cout << "| read xml back from the same string...                          |" << std::endl;

    STest sTest;

    CReadXmlPChar readPChar(strXmlFirst.c_str());
    deserialize(readPChar, sTest);

    std::cout << "| ...and rewrite again to a new string                           |" << std::endl;
    std::cout << "+----------------------------------------------------------------+" << std::endl;

    std::string strXmlSecond;

    CWriteXmlString writeString(strXmlSecond);
    serialize(writeString, sTest);
    std::cout << strXmlSecond << std::endl;

    std::cout << "+----------------------------------------------------------------+" << std::endl;
    std::cout << "| compare both strings                                           |" << std::endl;
    std::cout << "+----------------------------------------------------------------+" << std::endl;
    winloose(strXmlFirst == strXmlSecond);
    std::cout << "+----------------------------------------------------------------+" << std::endl;

    std::cout << "+----------------------------------------------------------------+" << std::endl;
    std::cout << "| compare both objects                                           |" << std::endl;
    std::cout << "+----------------------------------------------------------------+" << std::endl;
    winloose(testFirst == sTest);
    std::cout << "+----------------------------------------------------------------+" << std::endl;
  }

  for (int nArg=1; nArg<argc; nArg++)
  {
    std::cout << "+----------------------------------------------------------------+" << std::endl;
    std::cout << "| read xml from a file                                           |" << std::endl;

    STest sTest;

    CReadXmlFile readFile;
    if (readFile.UseFile(argv[nArg]))
    {
#if 0
      try
      {
        readFile.EnableExceptions();
#endif
        deserialize(readFile, sTest);
#if 0
        if (CReadXmlFile::readFile.GetStatus());
      }
      catch (CReadXmlFile::EStatus /*eStatus*/)
      {
        std::cout << "error parsing file at line " << readFile.GetLine() << ", " << readFile.GetColumn() << std::endl;
        return 1;
      }
#endif
      std::cout << "| ...and rewrite again to a new string                           |" << std::endl;
      std::cout << "+----------------------------------------------------------------+" << std::endl;

      std::string strXmlSecond;

      CWriteXmlString writeString(strXmlSecond);
      serialize(writeString, sTest);
      std::cout << strXmlSecond << std::endl;

      std::cout << "+----------------------------------------------------------------+" << std::endl;
      std::cout << "| compare with first string                                      |" << std::endl;
      std::cout << "+----------------------------------------------------------------+" << std::endl;
      winloose(readFile.GetData() == strXmlFirst);
      std::cout << "+----------------------------------------------------------------+" << std::endl;
      std::cout << "| compare with second string                                     |" << std::endl;
      std::cout << "+----------------------------------------------------------------+" << std::endl;
      winloose(readFile.GetData() == strXmlSecond);
      std::cout << "+----------------------------------------------------------------+" << std::endl;
    }
    else
    {
      std::cout << "| ...error reading file ???                                      |" << std::endl;
      std::cout << "+----------------------------------------------------------------+" << std::endl;
    }
  }

  return 0;
}
