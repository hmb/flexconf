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

# include "test.h"
# include <iostream>



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



void initTest(STest & test)
{
  test.nShort      = -234;
  test.nuShort     = 5645;
  test.nInt        = -48142;
  test.nuInt       = 900;
  test.nLong       = -45456644;
  test.nuLong      = 89890;
  test.nuLongX     = 0x1010;
  test.fltFloat    = 797.987f;
  test.dblDouble   = 47.11;
  test.strString   = "siebenundvierzigelf -\"'<>&- siebenundvierzigelf";

  test.setData.insert("asdf");
  test.setData.insert("jklö");

  test.setDataL.insert(545);
  test.setDataL.insert(789);
  test.setDataL.insert(123);
  test.setDataL.insert(9315);
  test.setDataL.insert(852);

  SData data;
  data.nInt                 = 45;
  data.dblDouble            = 54456456.564565;
  data.strString            = "ldksfl";

  test.vecData[0].nInt = 465;
  test.vecData[3].nInt = 78;

  test.mlstData.push_back(data);
  test.mlstData.push_back(data);
  test.mlstData.push_back(data);

  test.mlstString.push_back("Hallo");
  test.mlstString.push_back("Hallo");
  test.mlstString.push_back("Hallo");
  test.mlstString.push_back("Welt");

//  test.mapData["asdfg"]    = data;
  test.mapDataL[5]         = data;

  data.nInt                 = 546;
  data.dblDouble            = 45456.54;
  data.strString            = "sdalkds";
//  test.mapData["kllkrew"]  = data;
  test.mapDataL[6]         = data;

  data.nInt                 = 458;
  data.dblDouble            = 123287.65;
  data.strString            = "iurewiou";
//  test.mapData["eropw"]    = data;
  test.mapDataL[79]        = data;

  // multimap long
  data.strString = "1001-1";
  test.mmapDataL.insert(std::pair<long, SData>(1001, data));
  data.strString = "1001-2";
  test.mmapDataL.insert(std::pair<long, SData>(1001, data));

  data.strString = "1002";
  test.mmapDataL.insert(std::pair<long, SData>(1002, data));
  data.strString = "1003";
  test.mmapDataL.insert(std::pair<long, SData>(1003, data));

  data.strString = "2002-1";
  test.mmapDataL.insert(std::pair<long, SData>(2002, data));
  data.strString = "2002-2";
  test.mmapDataL.insert(std::pair<long, SData>(2002, data));

  data.strString = "2004-1";
  test.mmapDataL.insert(std::pair<long, SData>(2004, data));
  data.strString = "2004-2";
  test.mmapDataL.insert(std::pair<long, SData>(2004, data));
  data.strString = "2004-3";
  test.mmapDataL.insert(std::pair<long, SData>(2004, data));
  data.strString = "2004-4";
  test.mmapDataL.insert(std::pair<long, SData>(2004, data));

  // map string
  data.strString = "key: asdfg";
  test.mapDataStr["asdfg"]    = data;
  data.strString = "key: kllkrew";
  test.mapDataStr["kllkrew"]  = data;
  data.strString = "key: eropw";
  test.mapDataStr["eropw"]    = data;

  // multimap string
  data.strString = "multi key: test1-1";
  test.mmapDataStr.insert(std::pair<std::string, SData>("test1", data));
  data.strString = "multi key: test1-2";
  test.mmapDataStr.insert(std::pair<std::string, SData>("test1", data));

  data.strString = "multi key: test2";
  test.mmapDataStr.insert(std::pair<std::string, SData>("test2", data));
  data.strString = "multi key: test3";
  test.mmapDataStr.insert(std::pair<std::string, SData>("test3", data));

  data.strString = "multi key: test4-1";
  test.mmapDataStr.insert(std::pair<std::string, SData>("test4", data));
  data.strString = "multi key: test4-2";
  test.mmapDataStr.insert(std::pair<std::string, SData>("test4", data));
  data.strString = "multi key: test4-3";
  test.mmapDataStr.insert(std::pair<std::string, SData>("test4", data));
  data.strString = "multi key: test4-4";
  test.mmapDataStr.insert(std::pair<std::string, SData>("test4", data));
}
