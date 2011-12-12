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

# include "libxml2Com.h"
# include "libxml2Ser.h"
# include "libxml2Des.h"



void serialize(CWriteXml & writer, const CData & rObject, const char * pszTag, bool fRoot,
  const char * pszIdTag, const std::string * pstrIdValue)
{
  serialize(writer, static_cast<const SData&>(rObject), pszTag, fRoot, pszIdTag, pstrIdValue);
}

void deserialize(xmlNode * reader, CData & rObject, const char * pszTag, bool fRoot,
  const char * pszIdTag, std::string * pstrIdValue)
{
  deserialize(reader, static_cast<SData&>(rObject), pszTag, fRoot, pszIdTag, pstrIdValue);
}



int main(int argc, char *argv[])
{
  std::string strXmlFirst;
  STest       testFirst;

  initTest(testFirst);

#if 0
  {
    std::cerr << "+----------------------------------------------------------------+" << std::endl;
    std::cerr << "| write xml to a string                                          |" << std::endl;
    std::cerr << "+----------------------------------------------------------------+" << std::endl;

    CWriteXmlString writeString(strXmlFirst);
    serialize(writeString, testFirst);
    std::cerr << strXmlFirst << std::endl;
  }

  {
    std::cerr << "+----------------------------------------------------------------+" << std::endl;
    std::cerr << "| read xml back from the same string...                          |" << std::endl;

    STest sTest;

    CReadXmlPChar readPChar(strXmlFirst.c_str());
    deserialize(readPChar, sTest);

    std::cerr << "| ...and rewrite again to a new string                           |" << std::endl;
    std::cerr << "+----------------------------------------------------------------+" << std::endl;

    std::string strXmlSecond;

    CWriteXmlString writeString(strXmlSecond);
    serialize(writeString, sTest);
    std::cerr << strXmlSecond << std::endl;

    std::cerr << "+----------------------------------------------------------------+" << std::endl;
    std::cerr << "| compare both strings                                           |" << std::endl;
    std::cerr << "+----------------------------------------------------------------+" << std::endl;
    winloose(strXmlFirst == strXmlSecond);
    std::cerr << "+----------------------------------------------------------------+" << std::endl;

    std::cerr << "+----------------------------------------------------------------+" << std::endl;
    std::cerr << "| compare both objects                                           |" << std::endl;
    std::cerr << "+----------------------------------------------------------------+" << std::endl;
    winloose(testFirst == sTest);
    std::cerr << "+----------------------------------------------------------------+" << std::endl;
  }
#endif

  for (int nArg=1; nArg<argc; nArg++)
  {
    std::cerr << "+----------------------------------------------------------------+" << std::endl;
    std::cerr << "| read xml from a file                                           |" << std::endl;

    STest sTest;

    if (Libxml2Load(argv[nArg], sTest, 0, "TEST"))
    {
      std::cerr << "+----------------------------------------------------------------+" << std::endl;
      std::cerr << "| compare both objects                                           |" << std::endl;
      std::cerr << "+----------------------------------------------------------------+" << std::endl;
      winloose(testFirst == sTest);
      std::cerr << "+----------------------------------------------------------------+" << std::endl;

      std::string strXmlSecond;

      CWriteXmlString writeString(strXmlSecond);
      serialize(writeString, sTest);
      std::cout << strXmlSecond << std::endl;

/*
      std::cerr << "+----------------------------------------------------------------+" << std::endl;
      std::cerr << "| compare with first string                                      |" << std::endl;
      std::cerr << "+----------------------------------------------------------------+" << std::endl;
      winloose(readFile.GetData() == strXmlFirst);
      std::cerr << "+----------------------------------------------------------------+" << std::endl;
      std::cerr << "| compare with second string                                     |" << std::endl;
      std::cerr << "+----------------------------------------------------------------+" << std::endl;
      winloose(readFile.GetData() == strXmlSecond);
      std::cerr << "+----------------------------------------------------------------+" << std::endl;
*/
    }
    else
    {
      std::cerr << "| ...error reading file ???                                      |" << std::endl;
      std::cerr << "+----------------------------------------------------------------+" << std::endl;
    }
  }

  return 0;
}
