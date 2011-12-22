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

#ifndef Test_h
#define Test_h


/********************/
/** d **  ddd *************

***/
/* * d **  ddd *************** */

#include <string>
#include <set>
#include <list>
#include <map>
#include <iostream>


/* flexconf skip begin */

class CWriteXml;
class CReadXml;

struct _xmlNode;
typedef struct _xmlNode xmlNode;

namespace flexconfJson
{
class CWriter;
class CReader;
}


using namespace std;


// this is some hidden section
/////////////////////////////////////

//////////////* ddflexconf skip end */

//////////////* flexconf skip end */


//<!--
//#ifdef _MSC_VER
typedef unsigned long SHexNum;
//typedef SLongHex SHexNum;
//#endif
//-->



// flexconf alias data
struct SData
{
  int             nInt;       // xmlconf alias int
  double          dblDouble;  // flexconf alias double
  std::string     strString;  // flexconf alias string
//  int           & rnInt;      // flexconf alias ref_int

  SData();
};



//<!--
class CData;

namespace flexconfJson
{
void serialize(flexconfJson::CWriter & writer, const CData & rObject, const char * pszTag = 0,
  const char * pszIdTag = 0, const std::string * pstrIdValue = 0);

void deserialize(flexconfJson::CReader & reader, CData & rObject, const char * pszTag =0,
  const char * pszIdTag = 0, std::string * pstrIdValue = 0);
}

class CData : private SData
{
friend void flexconfJson::serialize(flexconfJson::CWriter & writer, const CData & rObject, const char * pszTag,
  const char * pszIdTag, const std::string * pstrIdValue);

friend void serialize(CWriteXml & writer, const CData & rObject, const char * pszTag = 0, bool fRoot = true,
  const char * pszIdTag = 0, const std::string * pstrIdValue = 0);


friend void flexconfJson::deserialize(flexconfJson::CReader & reader, CData & rObject, const char * pszTag,
  const char * pszIdTag, std::string * pstrIdValue);

friend void deserialize(CReadXml & reader, CData & rObject, const char * pszTag =0, bool fRoot = true,
  const char * pszIdTag = 0, std::string * pstrIdValue = 0);
  
friend void deserialize(xmlNode * reader, CData & rObject, const char * pszTag =0, bool fRoot = true,
  const char * pszIdTag = 0, std::string * pstrIdValue = 0);
};
//-->



// flexconf alias TEST
struct STestBase
{
  // one member for every ordinary type that's serializable
  short             nShort;
  unsigned short    nuShort;
  int               nInt;
  unsigned int      nuInt;
  long              nLong;
  unsigned long     nuLong;
  SHexNum           nuLongX;
  float             fltFloat;
  double            dblDouble;
  std::string       strString;
  std::string       strStringEmpty;

  SData             datData;
  SData             datData2;     // flexconf alias Data
  SData             vecData[4];   // flexconf alias sepp item DataElement
  CData             datDataDerived;

  // illeagal: maps with plain types as value are not allowed
  // std::map<std::string, int>    mapTesting;

  // testcase for a string set
  std::set<std::string>  setData; //flexconf alias setdata item text
  std::set<std::string>  setDataEmpty; //flexconf alias setdata_empty item text

  // testcase for a long set
  std::set<long>  setDataL; //flexconf alias setlong item long
  std::set<long>  setDataLEmpty; //flexconf alias setlong_empty item long

  // testcase for a data list
  std::list<SData> mlstData;  //flexconf alias ListData item DataItem
  std::list<SData> mlstDataEmpty;  //flexconf alias ListData_empty item DataItem

  // testcase for a data list
  std::list<std::string> mlstString;  //flexconf alias ListString item StringItem
  std::list<std::string> mlstStringEmpty;  //flexconf alias ListString_empty item StringItem

  std::map<long, SData>  mapDataL; //flexconf alias maplong item app id longid
  std::map<long, SData>  mapDataLEmpty; //flexconf alias maplong_empty item app id longid

  std::multimap<long, SData>  mmapDataL; //flexconf alias mmaplong item app id longid
  std::multimap<long, SData>  mmapDataLEmpty; //flexconf alias mmaplong_empty item app id longid

  std::map<std::string, SData>  mapDataStr; //flexconf alias mapstr item app id strid
  std::map<std::string, SData>  mapDataStrEmpty; //flexconf alias mapstr_empty item app id strid

  std::multimap<std::string, SData>  mmapDataStr; //flexconf alias mmapstr item app id strid
  std::multimap<std::string, SData>  mmapDataStrEmpty; //flexconf alias mmapstr_empty item app id strid

#ifndef _MSC_VER
//<!--
  // testcase for a map without tags
  map<std::string, SData>  mapNotags;

  // testcase for a string map
  std::map<std::string, SData>  mapData; //flexconf alias mapdata item app id strid
//-->
#endif

  // declare methods that shall be ignored by flexconf
  static unsigned int static_function(int some_int)    ;

  unsigned int some_function(int some_int) const ;
  unsigned int some_inline_function(int some_int)
  {
    return 879 * some_int;
  }

  virtual ~STestBase() {}
  virtual unsigned int abstract_function(int some_int) = 0;
  virtual unsigned int abstract_function(int some_int) const = 0  ;
};



/* flexconf skip begin */

struct STest : public STestBase
{
  virtual unsigned int abstract_function(int some_int)        { return 5 + some_int; }
  virtual unsigned int abstract_function(int some_int) const  { return 63 / some_int; }
};



// flexconf alias TEST
struct STestIgnored
{
  // one member for every ordinary type that's serializable
  short             nShort;
  unsigned short    nuShort;
  int               nInt;
  unsigned int      nuInt;
  long              nLong;
  unsigned long     nuLong;
  float             fltFloat;
  double            dblDouble;
  std::string       strString;

  // illeagal: maps with plain types as value are not allowed
  // std::map<std::string, int>    mapTesting;

  // testcase for a string map
  std::set<std::string>  setData; //flexconf alias setdata item text

  // testcase for a long map
  std::set<long>  setDataL; //flexconf alias setlong item long

  // testcase for a long map
  std::map<long, SData>  mapDataL; //flexconf alias maplong item app id longid

#ifndef _MSC_VER
  // testcase for a string map
  std::map<std::string, SData>  mapData; //flexconf alias mapdata item app id strid

  // testcase for a map without tags
  map<std::string, SData>  mapNotags;
#endif

  // declare methods that shall be ignored by flexconf
  static unsigned int static_function(int some_int);

  unsigned int some_function(int some_int) const;
  unsigned int some_inline_function(int some_int)
  {
    return some_int - 879;
  }

  virtual ~STestIgnored() {}
  virtual unsigned int abstract_function(int some_int)  const = 0 ;
};


bool operator == (const SData & testOne, const SData & testTwo);
bool operator == (const STest & testOne, const STest & testTwo);
void winloose(bool fWin, std::ostream & out = std::cerr);
void initTest(STest & test);

/* flexconf skip end */


#endif // Test_h
