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

# include "jsonCom.h"
# include "jsonSer.h"
# include "jsonDes.h"

# include <iostream>
# include <inttypes.h>



void serialize(CWriter & writer, const CData & rObject, const char * pszTag,
  const char * pszIdTag, const std::string * pstrIdValue)
{
  serialize(writer, static_cast<const SData&>(rObject), pszTag, pszIdTag, pstrIdValue);
}

void deserialize(CReader & reader, CData & rObject, const char * pszTag, bool fRoot,
  const char * pszIdTag, std::string * pstrIdValue)
{
  deserialize(reader, static_cast<SData&>(rObject), pszTag, fRoot, pszIdTag, pstrIdValue);
}

const char * tkn2str(int token)
{
  const char * string = "<unknown>";

  switch (token)
  {
    case CReader::CURLY_BRACKET_LEFT:        string = "{"; break;
    case CReader::CURLY_BRACKET_RIGHT:       string = "}"; break;
    case CReader::SQUARE_BRACKET_LEFT:       string = "["; break;
    case CReader::SQUARE_BRACKET_RIGHT:      string = "]"; break;
    case CReader::COLON:                     string = ":"; break;
    case CReader::COMMA:                     string = ","; break;
    case CReader::STRING:                    string = "STRING"; break;
    case CReader::NUMBER:                    string = "NUMBER"; break;
    case CReader::END:                       string = "END"; break;
    case CReader::ERROR:                     string = "ERROR"; break;
  }

  return string;
}

void tokenize(CReader & reader)
{
  std::string text;
  int token;

  while ((token=reader.getToken(text)) != CReader::END)
  {
    std::cout << tkn2str(token);
    if (token != CReader::ERROR)
    {
      std::cout << " -> '" << text << '\'' << std::endl;
    }
    else
    {
      std::cout << std::endl;
      break;
    }
  }
}



template <class T>
void writeStructure(bool pretty)
{
  std::string serialized;
  CWriterJsonString writer(serialized);

  if (pretty)
    writer.SetPretty();
  else
    writer.SetCondensed();

//   writer.SetNewline(false);
//   writer.SetIndentation(0);
//   writer.SetAlignmentObj(0);
//   writer.SetAlignmentElem(0);
//   writer.SetColonWhitespace(false);

  T dat;
  serialize(writer, dat);
  std::cout << serialized << std::endl;
}



int main(int argc, char *argv[])
{
  const char * json =
    "{\n"
    "  \"int\" : 451,\n"
    "  \"double\" : 2.000234000,\n"
    "  \"string\" : \"foobar\"\n"
    "}\n";

  std::cout << json;

  STest       testFirst;
  initTest(testFirst);
  SData dat;

  {
    CReaderCharPointer reader(json);
    tokenize(reader);
  }

  {
    CReaderCharPointer reader(json);
    deserialize(reader, dat);
  }

  std::string serialized;
  {
    std::cerr << "+----------------------------------------------------------------+" << std::endl;
    std::cerr << "| write xml to a string                                          |" << std::endl;
    std::cerr << "+----------------------------------------------------------------+" << std::endl;

    CWriterJsonString writer(serialized);

//    writer.SetCondensed();
    writer.SetPretty();

//     writer.SetNewline(false);
//     writer.SetIndentation(0);
//     writer.SetAlignmentObj(0);
//     writer.SetAlignmentElem(0);
//     writer.SetColonWhitespace(false);

/*
    serialize(writer, testFirst);
/*/
    serialize(writer, dat);
//    serialize(writer, dat, "sepp");
//*/
    std::cout << serialized << std::endl;
  }

#if 0
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

  for (int nArg=1; nArg<argc; nArg++)
  {
    std::cerr << "+----------------------------------------------------------------+" << std::endl;
    std::cerr << "| read xml from a file                                           |" << std::endl;

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
        std::cerr << "error parsing file at line " << readFile.GetLine() << ", " << readFile.GetColumn() << std::endl;
        return 1;
      }
#endif
      std::cerr << "| ...and rewrite again to a new string                           |" << std::endl;
      std::cerr << "+----------------------------------------------------------------+" << std::endl;

      std::string strXmlSecond;

      CWriteXmlString writeString(strXmlSecond);
      serialize(writeString, sTest);
      std::cout << strXmlSecond << std::endl;

      std::cerr << "+----------------------------------------------------------------+" << std::endl;
      std::cerr << "| compare with first string                                      |" << std::endl;
      std::cerr << "+----------------------------------------------------------------+" << std::endl;
      winloose(readFile.GetData() == strXmlFirst);
      std::cerr << "+----------------------------------------------------------------+" << std::endl;
      std::cerr << "| compare with second string                                     |" << std::endl;
      std::cerr << "+----------------------------------------------------------------+" << std::endl;
      winloose(readFile.GetData() == strXmlSecond);
      std::cerr << "+----------------------------------------------------------------+" << std::endl;
    }
    else
    {
      std::cerr << "| ...error reading file ???                                      |" << std::endl;
      std::cerr << "+----------------------------------------------------------------+" << std::endl;
    }
  }
#endif

  return 0;
}
