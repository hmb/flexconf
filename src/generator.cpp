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

#include "generator.h"



// defaults for structxml flags
const char * const CGenerator::mpszItem   = "_item";
const char * const CGenerator::mpszId     = "_id";



CGenerator::CGenerator()
  :
  mfHeader(0),
  mfSerialize(0),
  mfDeserialize(0),
  mstrHeader("struct.h"),
  mstrSerialize("structSer.cpp"),
  mstrDeserialize("structDes.cpp")
{
}



CGenerator::~CGenerator()
{
}





void CGenerator::SetHeaderFilename(const char * pszFilename)
{
  mstrHeader = pszFilename;
}



void CGenerator::SetSerializerFilename(const char * pszFilename)
{
  mstrSerialize = pszFilename;
}



void CGenerator::SetDeserializerFilename(const char * pszFilename)
{
  mstrDeserialize = pszFilename;
}



void CGenerator::AddSourceFile(const char * pszFilename)
{
  mlstSourceFiles.push_back(pszFilename);
}



// :TODO: put into a more appropriate place
extern CGenerator * spGenerator;
void yyrestart(FILE *);
int yyparse(void);

void CGenerator::Generate()
{
  // init file pointers for output files
  mfHeader      = fopen(mstrHeader.c_str(),       "w");
  mfSerialize   = fopen(mstrSerialize.c_str(),    "w");
  mfDeserialize = fopen(mstrDeserialize.c_str(),  "w");

  // write header
  header();

  // write per file headers
  {for (lstSourceFilesCtrType ctr=mlstSourceFiles.begin(); ctr!=mlstSourceFiles.end(); ctr++)
  {
    SetVariable(VAR_HEADERFILE, ctr->c_str());
    headerfile();
  }}
  ClearVariable(VAR_HEADERFILE);

  // :TODO: parser internal, put this into the parser
  // init this to the default, if no alias is set
  SetVariable(CGenerator::VAR_ITEM, mpszItem);
  SetVariable(CGenerator::VAR_ID,   mpszId);
  // :TODO: pass this as param to yyparse
  spGenerator = this;

  // parse files and create the main work
  {for (lstSourceFilesCtrType ctr=mlstSourceFiles.begin(); ctr!=mlstSourceFiles.end(); ctr++)
  {
    SetVariable(VAR_HEADERFILE, ctr->c_str());
    int nRetVal = 0;
    #if YYDEBUG
      yydebug   = 1;
    #endif

    FILE * fParse = fopen(ctr->c_str(), "r");
    if (fParse)
    {
      yyrestart(fParse);
      nRetVal = yyparse();
      fclose(fParse);
    }
    else
    {
      printf("error: could not open file %s\n", ctr->c_str());
      nRetVal = -1;
    }

    if (0!=nRetVal)
    {
      break;
    }
  }}
  ClearVariable(VAR_HEADERFILE);

  // remove the parsers pointer to the generator
  spGenerator = NULL;

  // write per file footers
  {for (lstSourceFilesCtrType ctr=mlstSourceFiles.begin(); ctr!=mlstSourceFiles.end(); ctr++)
  {
    SetVariable(VAR_HEADERFILE, ctr->c_str());
    footerfile();
  }}
  ClearVariable(VAR_HEADERFILE);

  // write footer
  footer();

  // close files
  fclose(mfHeader);
  fclose(mfSerialize);
  fclose(mfDeserialize);

  // reset file pointers
  mfHeader      = 0;
  mfSerialize   = 0;
  mfDeserialize = 0;
}



void CGenerator::Reset()
{
  // empty list of source files
  mlstSourceFiles.clear();
}






// names of variables filled by framework
const char * const CGenerator::VAR_HEADERFILE     = "headerfile";
// names of variables filled by c++
const char * const CGenerator::VAR_TYPE           = "type";
const char * const CGenerator::VAR_NAME           = "name";
const char * const CGenerator::VAR_SIZE           = "size";
// const char * const CGenerator::VAR_COUNT          = "count";
// names of variables filled by tags
const char * const CGenerator::VAR_ALIAS          = "alias";
const char * const CGenerator::VAR_ITEM           = "item";
const char * const CGenerator::VAR_ID             = "id";



bool CGenerator::IsVariableSet(const std::string & strName)
{
  return mcontVariables.find(strName) != mcontVariables.end();
}

/*
const std::string & CGenerator::GetVariable(const std::string & strName)
{
  return mcontVariables[strName];
}
*/

void CGenerator::SetVariable(const std::string & strName, const std::string & strValue)
{
  mcontVariables[strName] = strValue;
}

void CGenerator::ClearVariable(const std::string & strName)
{
  ContVariableItrType ctr = mcontVariables.find(strName);
  if (ctr != mcontVariables.end())
  {
    mcontVariables.erase(ctr);
  }
}






void CGenerator::BeginStruct()
{
  // verbose output
  writeRep("struct $(name)\n", stdout);
  writeStr("{\n", stdout);
  // do the work
  writeStructBegin();
}



void CGenerator::VarDecl()
{
  // verbose output
  writeRep("  $(type) $(name); // $(alias)\n", stdout);
  // do the work
  writeVarDecl();
}



void CGenerator::VarDeclVector()
{
  // verbose output
  writeRep("  $(type) $(name)[$(size)]; // $(alias) (vector)\n", stdout);
  // do the work
  writeVarDeclVector();
  // reset item to standard
  SetVariable(CGenerator::VAR_ITEM, mpszItem);
}



void CGenerator::VarDeclSetList()
{
  // verbose output
  writeRep("  $(type) $(name); // $(alias) (set/list)\n", stdout);
  // do the work
  // write set / list declaration
  writeVarDeclSetList();
  // reset item to standard
  SetVariable(CGenerator::VAR_ITEM, mpszItem);
}



void CGenerator::VarDeclMap()
{
  // verbose output
  writeRep("  $(type) $(name); // $(alias) (map)\n", stdout);
  // do the work
  // write map declaration
  writeVarDeclMap();
  // reset item and id to standard
  SetVariable(CGenerator::VAR_ITEM, mpszItem);
  SetVariable(CGenerator::VAR_ID,   mpszId);
}



void CGenerator::EndStruct()
{
  // verbose output
  writeStr("};\n\n", stdout);
  // do the work
  writeStructEnd();
}






int CGenerator::replaceVariables(const std::string & strSource, std::string & rstrReplace)
{
  int nReplaced = 0;

  std::string::size_type ctrPos     = 0;
  std::string::size_type ctrDollar  = 0;

  for (ctrPos=0; std::string::npos!=(ctrDollar=strSource.find('$', ctrPos)); ctrPos=ctrDollar)
  {
    // append the part of the string preceeding the found dollar
    rstrReplace.append(strSource.substr(ctrPos, ctrDollar-ctrPos));

    // no space left for '(...)'
    if (strSource.size() < ctrDollar+3)
      break;

    switch (strSource[ctrDollar+1])
    {
    case '(':
      // skip character and '('
      ctrPos    = ctrDollar + 2;
      ctrDollar = strSource.find(')', ctrPos);
      if (std::string::npos != ctrDollar)
      {
        // :TODO: use find_not_first_of or sth. like while (isalpha())...
        ContVariableCtrType fnd = mcontVariables.find(strSource.substr(ctrPos, ctrDollar-ctrPos));
        if (fnd != mcontVariables.end())
        {
          rstrReplace.append(fnd->second);
          nReplaced++;
        }
        // skip trailing ')'
        ctrDollar++;
      }
      else
      {
        // error, could not find closing bracket
        return -1;
      }
      break;

    case '$':
      // append the character found
      rstrReplace.append(1, strSource[ctrDollar]);
      // skip found character and second dollar
      ctrDollar += 2;
      break;

    default:
      // append the character found
      rstrReplace.append(1, strSource[ctrDollar]);
      // skip character
      ctrDollar++;
      break;
    };
  }

  // append the rest of the string 'as is'
  if (std::string::npos != ctrPos)
    rstrReplace.append(strSource.substr(ctrPos));

  return nReplaced;
}



void CGenerator::writeRep(const std::string & strSource, FILE * fWrite)
{
  std::string strWrite;
  replaceVariables(strSource, strWrite);
  fputs(strWrite.c_str(), fWrite);
}



void CGenerator::writeStr(const char * pszSource, FILE * fWrite)
{
  fputs(pszSource, fWrite);
}
