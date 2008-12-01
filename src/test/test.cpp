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

#ifdef _MSC_VER
  #pragma warning( disable : 4786 4996 )
#endif

# include <iostream>
# include "struct.h"


SData::SData()
  :
  nInt(0),
  dblDouble(0.0)
{
}



bool operator == (const SData & testOne, const SData & testTwo)
{
  return
    testOne.nInt      == testTwo.nInt         &&
    testOne.dblDouble == testTwo.dblDouble    &&
    testOne.strString == testTwo.strString;
}


bool operator == (const STest & testOne, const STest & testTwo)
{
  return
    testOne.nShort        == testTwo.nShort       &&
    testOne.nuShort       == testTwo.nuShort      &&
    testOne.nInt          == testTwo.nInt         &&
    testOne.nuInt         == testTwo.nuInt        &&
    testOne.nLong         == testTwo.nLong        &&
    testOne.nuLong        == testTwo.nuLong       &&
    testOne.nuLongX       == testTwo.nuLongX      &&
    testOne.fltFloat      == testTwo.fltFloat     &&
    testOne.dblDouble     == testTwo.dblDouble    &&
    testOne.strString     == testTwo.strString    &&
    testOne.setData       == testTwo.setData      &&
    testOne.setDataL      == testTwo.setDataL     &&
    testOne.mlstData      == testTwo.mlstData     &&
    testOne.mlstString    == testTwo.mlstString   &&
    testOne.mapDataL      == testTwo.mapDataL     &&
    testOne.mapDataStr    == testTwo.mapDataStr   &&
    testOne.mmapDataL     == testTwo.mmapDataL    &&
    testOne.mmapDataStr   == testTwo.mmapDataStr  &&
//    testOne.mapData   == testTwo.mapData      &&
//    testOne.mapNotags == testTwo.mapNotags    &&
    true;
}



void winloose(bool fWin)
{
  if (fWin)
  {
    std::cout << "|     ____ ___ _   _  ____  ___                                  |" << std::endl;
    std::cout << "|    | __ )_ _| \\ | |/ ___|/ _ \\                                 |" << std::endl;
    std::cout << "|    |  _ \\| ||  \\| | |  _| | | |                                |" << std::endl;
    std::cout << "|    | |_) | || |\\  | |_| | |_| |                                |" << std::endl;
    std::cout << "|    |____/___|_| \\_|\\____|\\___/                                 |" << std::endl;
  }
  else
  {
    std::cout << "|     _     ___   ___  ____  _____                               |" << std::endl;
    std::cout << "|    | |   / _ \\ / _ \\/ ___|| ____|                              |" << std::endl;
    std::cout << "|    | |  | | | | | | \\___ \\|  _|                                |" << std::endl;
    std::cout << "|    | |__| |_| | |_| |___) | |___                               |" << std::endl;
    std::cout << "|    |_____\\___/ \\___/|____/|_____|                              |" << std::endl;
  }
}



int main(int argc, char *argv[])
{
  std::string strXmlFirst;
  STest       testFirst;

  {
    std::cout << "+----------------------------------------------------------------+" << std::endl;
    std::cout << "| write xml to a string                                          |" << std::endl;
    std::cout << "+----------------------------------------------------------------+" << std::endl;

    testFirst.nShort      = -234;
    testFirst.nuShort     = 5645;
    testFirst.nInt        = -48142;
    testFirst.nuInt       = 900;
    testFirst.nLong       = -45456644;
    testFirst.nuLong      = 89890;
    testFirst.nuLongX     = 0x1010;
    testFirst.fltFloat    = 797.987f;
    testFirst.dblDouble   = 47.11;
    testFirst.strString   = "siebenundvierzigelf -\"'<>&- siebenundvierzigelf";

    testFirst.setData.insert("asdf");
    testFirst.setData.insert("jklö");

    testFirst.setDataL.insert(545);
    testFirst.setDataL.insert(789);
    testFirst.setDataL.insert(123);
    testFirst.setDataL.insert(9315);
    testFirst.setDataL.insert(852);

    SData data;
    data.nInt                 = 45;
    data.dblDouble            = 54456456.564565;
    data.strString            = "ldksfl";

    testFirst.vecData[0].nInt = 465;
    testFirst.vecData[3].nInt = 78;

    testFirst.mlstData.push_back(data);
    testFirst.mlstData.push_back(data);
    testFirst.mlstData.push_back(data);

    testFirst.mlstString.push_back("Hallo");
    testFirst.mlstString.push_back("Hallo");
    testFirst.mlstString.push_back("Hallo");
    testFirst.mlstString.push_back("Welt");

//    testFirst.mapData["asdfg"]    = data;
    testFirst.mapDataL[5]         = data;

    data.nInt                 = 546;
    data.dblDouble            = 45456.54;
    data.strString            = "sdalkds";
//    testFirst.mapData["kllkrew"]  = data;
    testFirst.mapDataL[6]         = data;

    data.nInt                 = 458;
    data.dblDouble            = 123287.65;
    data.strString            = "iurewiou";
//    testFirst.mapData["eropw"]    = data;
    testFirst.mapDataL[79]        = data;

    // multimap long
    data.strString = "1001-1";
    testFirst.mmapDataL.insert(std::pair<long, SData>(1001, data));
    data.strString = "1001-2";
    testFirst.mmapDataL.insert(std::pair<long, SData>(1001, data));

    data.strString = "1002";
    testFirst.mmapDataL.insert(std::pair<long, SData>(1002, data));
    data.strString = "1003";
    testFirst.mmapDataL.insert(std::pair<long, SData>(1003, data));

    data.strString = "2002-1";
    testFirst.mmapDataL.insert(std::pair<long, SData>(2002, data));
    data.strString = "2002-2";
    testFirst.mmapDataL.insert(std::pair<long, SData>(2002, data));

    data.strString = "2004-1";
    testFirst.mmapDataL.insert(std::pair<long, SData>(2004, data));
    data.strString = "2004-2";
    testFirst.mmapDataL.insert(std::pair<long, SData>(2004, data));
    data.strString = "2004-3";
    testFirst.mmapDataL.insert(std::pair<long, SData>(2004, data));
    data.strString = "2004-4";
    testFirst.mmapDataL.insert(std::pair<long, SData>(2004, data));

    // map string
    data.strString = "key: asdfg";
    testFirst.mapDataStr["asdfg"]    = data;
    data.strString = "key: kllkrew";
    testFirst.mapDataStr["kllkrew"]  = data;
    data.strString = "key: eropw";
    testFirst.mapDataStr["eropw"]    = data;

    // multimap string
    data.strString = "multi key: test1-1";
    testFirst.mmapDataStr.insert(std::pair<std::string, SData>("test1", data));
    data.strString = "multi key: test1-2";
    testFirst.mmapDataStr.insert(std::pair<std::string, SData>("test1", data));

    data.strString = "multi key: test2";
    testFirst.mmapDataStr.insert(std::pair<std::string, SData>("test2", data));
    data.strString = "multi key: test3";
    testFirst.mmapDataStr.insert(std::pair<std::string, SData>("test3", data));

    data.strString = "multi key: test4-1";
    testFirst.mmapDataStr.insert(std::pair<std::string, SData>("test4", data));
    data.strString = "multi key: test4-2";
    testFirst.mmapDataStr.insert(std::pair<std::string, SData>("test4", data));
    data.strString = "multi key: test4-3";
    testFirst.mmapDataStr.insert(std::pair<std::string, SData>("test4", data));
    data.strString = "multi key: test4-4";
    testFirst.mmapDataStr.insert(std::pair<std::string, SData>("test4", data));



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
      try
      {
        readFile.EnableExceptions();
        deserialize(readFile, sTest);
//        if (CReadXmlFile::readFile.GetStatus());
      }
      catch (CReadXmlFile::EStatus /*eStatus*/)
      {
        std::cout << "error parsing file at line " << readFile.GetLine() << ", " << readFile.GetColumn() << std::endl;
        return 1;
      }
      std::cout << "| ...and rewrite again to a new string                           |" << std::endl;
      std::cout << "+----------------------------------------------------------------+" << std::endl;

      std::string strXmlSecond;

      CWriteXmlString writeString(strXmlSecond);
      serialize(writeString, sTest);
      std::cout << strXmlSecond << std::endl;

      std::cout << "+----------------------------------------------------------------+" << std::endl;
      std::cout << "| compare with first string                                      |" << std::endl;
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
