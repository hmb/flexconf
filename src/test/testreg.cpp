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

#pragma warning( disable : 4786 )

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
    testOne.nShort      == testTwo.nShort       &&
    testOne.nuShort     == testTwo.nuShort      &&
    testOne.nInt        == testTwo.nInt         &&
    testOne.nuInt       == testTwo.nuInt        &&
    testOne.nLong       == testTwo.nLong        &&
    testOne.nuLong      == testTwo.nuLong       &&
    testOne.nuLongX     == testTwo.nuLongX      &&
    testOne.fltFloat    == testTwo.fltFloat     &&
    testOne.dblDouble   == testTwo.dblDouble    &&
    testOne.strString   == testTwo.strString    &&

    testOne.datData     == testTwo.datData      &&
    testOne.datData2    == testTwo.datData2     &&
    testOne.vecData[0]  == testTwo.vecData[0]   &&
    testOne.vecData[1]  == testTwo.vecData[1]   &&
    testOne.vecData[2]  == testTwo.vecData[2]   &&
    testOne.vecData[3]  == testTwo.vecData[3]   &&

    testOne.setData     == testTwo.setData      &&
    testOne.setDataL    == testTwo.setDataL     &&
    testOne.mlstData    == testTwo.mlstData     &&
    testOne.mlstString  == testTwo.mlstString   &&
    testOne.mapDataL    == testTwo.mapDataL     &&
//    testOne.mapNotags   == testTwo.mapNotags    &&
//    testOne.mapData     == testTwo.mapData      &&
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



int main()
{
  STest testFirst;

  {
    std::cout << "+----------------------------------------------------------------+" << std::endl;
    std::cout << "| write structure to registry                                    |" << std::endl;
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

    testFirst.datData.dblDouble = 1.0;
    testFirst.datData.nInt      = 12.0;
    testFirst.datData.strString = "Hänsel";

    testFirst.datData2.dblDouble  = 2.0;
    testFirst.datData2.nInt       = 24.0;
    testFirst.datData2.strString  = "Gretel";

    testFirst.vecData[0].nInt = 465;
    testFirst.vecData[3].nInt = 78;

/*
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
*/

    serialize(CRegKey::HKCU, static_cast<STestBase&>(testFirst), "Software\\Amarin Software\\flexconf-test");
  }

  {
    std::cout << "+----------------------------------------------------------------+" << std::endl;
    std::cout << "| read struct back from registry...                              |" << std::endl;
    std::cout << "+----------------------------------------------------------------+" << std::endl;

    STest sTest;
    deserialize(CRegKey::HKCU, static_cast<STestBase&>(sTest), "Software\\Amarin Software\\flexconf-test");

    std::cout << "+----------------------------------------------------------------+" << std::endl;
    std::cout << "| compare both objects                                           |" << std::endl;
    std::cout << "+----------------------------------------------------------------+" << std::endl;
    winloose(testFirst == sTest);
    std::cout << "+----------------------------------------------------------------+" << std::endl;
  }

  return 0;
}
