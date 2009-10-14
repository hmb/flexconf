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

#ifndef Generator_h
#define Generator_h

#ifdef _MSC_VER
  #pragma warning(disable: 4786 4996)
#endif

#include <string>
#include <list>
#include <map>



class CGenerator
{
public:
  CGenerator();
  virtual ~CGenerator();

  enum EOutputFile
  {
    eCommonHdr,             // header file common to both serializer and deserializer
    eCommonImp,             // implementation file common to both serializer and deserializer
    eSerializerHdr,         // header file for serializer
    eSerializerImp,         // implementation file for serializer
    eDeserializerHdr,       // header file for deserializer
    eDeserializerImp,       // implementation file for deserializer
    eFileCount
  };

  enum EGeneratorString
  {
    eProlog,
    ePrologFile,

    ePrologStruct,
    eVarDecl,
    eVarDeclVector,
    eVarDeclSetList,
    eVarDeclMap,
    eEpilogStruct,

    eEpilogFile,
    eEpilog,

    eStringCount
  };

  void SetOutputFileName(EOutputFile fileid, const char * filename);
  void SetOutputFileName(EOutputFile fileid, const std::string & filename);

  // add header files to process
  void AddSourceFile(const char * pszFilename);

  // generate output files by parsing header files
  int Generate();

  // reset generator to do more processing
  void Reset();

  // names of variables filled by framework
  static const char * const VAR_PACKAGE;      // name of package
  static const char * const VAR_BUGREPORT;    // address for bugreports
  static const char * const VAR_HEADERFILE;   // name of headerfile being processed
  // names of variables filled by c++
  static const char * const VAR_TYPE;         // type of a member declaration
  static const char * const VAR_NAME;         // name of the declared member
  static const char * const VAR_SIZE;         // size of declared member, if declared as array
//  static const char * const VAR_COUNT;        // number of valid elements in an array
  // names of variables filled by tags
  static const char * const VAR_ALIAS;        // alias given by tag
  static const char * const VAR_ITEM;         // item name for sets and lists
  static const char * const VAR_ID;           // id name for map elements

  // variable handling
  bool IsVariableSet(const std::string & strName);
//  const std::string & GetVariable(const std::string & strName);
  void SetVariable(const std::string & strName, const std::string & strValue);
  void ClearVariable(const std::string & strName);

  // called by yyparse
  void BeginStruct();
  void VarDecl();
  void VarDeclVector();
  void VarDeclSetList();
  void VarDeclMap();
  void EndStruct();

protected:
  // replace variables and write resulting string to file
  void writeRep(const std::string & strSource, EOutputFile fileid);
  // write string of non replaced vars
  void writeStr(const char * pszSource, EOutputFile fileid);

private:
  // virtual functions to write headers
  virtual int header()                = 0;
  virtual int headerfile()            = 0;

  // virtual functions called by the parser to generate de/serializers
  virtual void writeStructBegin()     = 0;
  virtual void writeVarDecl()         = 0;
  virtual void writeVarDeclVector()   = 0;
  virtual void writeVarDeclSetList()  = 0;
  virtual void writeVarDeclMap()      = 0;
  virtual void writeStructEnd()       = 0;

  // virtual functions to write footers
  virtual int footerfile()            = 0;
  virtual int footer()                = 0;

  // replace all $(varname) vars with values from map
  int replaceVariables(const std::string & strSource, std::string & rstrReplace);
  // replace variables and write resulting string to file
  void writeRep(const std::string & strSource, FILE * fWrite);
  // write string of non replaced vars
  void writeStr(const char * pszSource, FILE * fWrite);

  // container types for variables in form of $(varname)
  typedef std::map<std::string, std::string>  ContVariableType;
  typedef ContVariableType::iterator          ContVariableItrType;
  typedef ContVariableType::const_iterator    ContVariableCtrType;
  // container for variables in form of $(varname)
  ContVariableType  mcontVariables;

  // file names for output files
  std::string mFileNames[eFileCount];
  FILE *      mOutputFiles[eFileCount];

  // list of source files to process
  typedef std::list<std::string>              lstSourceFilesType;
  typedef lstSourceFilesType::iterator        lstSourceFilesItrType;
  typedef lstSourceFilesType::const_iterator  lstSourceFilesCtrType;

  lstSourceFilesType  mlstSourceFiles;

  // defaults for flexconf flags
  static const char * const mpszItem;
  static const char * const mpszId;
};


#endif // Generator_h
