const char * pszDisclaimer =
  "/*-------------------------------------------------------------------\n"
  "  This file is part of the structure de/serializer.\n"
  "  It has been automatically created by:\n"
  "\n"
  "  $(packagename)\n"
  "\n"
  "  !!! DO NOT MODIFY MANUALLY !!!\n"
  "\n"
  "  Bugreports to $(bugreport)\n"
  "  -------------------------------------------------------------------\n"
  "  flexconf - flexible configuration generator\n"
  "  Copyright (C) 2008 Holger Böhnke\n"
  "\n"
  "  This file is part of flexconf.\n"
  "\n"
  "  Flexconf is free software: you can redistribute it and/or modify\n"
  "  it under the terms of the GNU General Public License as published by\n"
  "  the Free Software Foundation, either version 3 of the License, or\n"
  "  (at your option) any later version.\n"
  "\n"
  "  This program is distributed in the hope that it will be useful,\n"
  "  but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
  "  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
  "  GNU General Public License for more details.\n"
  "\n"
  "  You should have received a copy of the GNU General Public License\n"
  "  along with this program.  If not, see <http://www.gnu.org/licenses/>.\n"
  "  -------------------------------------------------------------------\n"
  "  As a special exception, you may create a larger work that contains\n"
  "  part or all of the de/serializer functions and distribute that work\n"
  "  under terms of your choice, as long as that work itself does not\n"
  "  provide a functionality similar to flexconf.\n"
  "  Alternatively, if you modify or redistribute this file itself,\n"
  "  you may (at your option) remove this special exception, which will\n"
  "  cause the file to be licensed under the GNU General Public\n"
  "  License without this special exception.\n"
  "*/\n"
  "\n"
;
const char * pszTypes =
  "#ifdef _MSC_VER\n"
  "  #define snprintf _snprintf\n"
  "#endif\n"
  "\n"
  "class CReadXml;\n"
  "class CWriteXml;\n"
  "\n"
  "struct SLongHex\n"
  "{\n"
  "  SLongHex() { }\n"
  "  SLongHex(unsigned long ulHex) : mulHex(ulHex) { }\n"
  "\n"
  "  unsigned long mulHex;\n"
  "\n"
  "  bool operator == (const SLongHex & cmp) const { return mulHex == cmp.mulHex; }\n"
  "  bool operator >= (const SLongHex & cmp) const { return mulHex >= cmp.mulHex; }\n"
  "  bool operator <= (const SLongHex & cmp) const { return mulHex <= cmp.mulHex; }\n"
  "  bool operator >  (const SLongHex & cmp) const { return mulHex >  cmp.mulHex; }\n"
  "  bool operator <  (const SLongHex & cmp) const { return mulHex <  cmp.mulHex; }\n"
  "  bool operator != (const SLongHex & cmp) const { return mulHex != cmp.mulHex; }\n"
  "\n"
  "  unsigned long operator = (unsigned long ulHex) { return mulHex=ulHex; }\n"
  "  operator unsigned long () const { return mulHex; }\n"
  "};\n"
  "\n"
;
const char * pszHdrProlog =
  "#ifndef _Struct_h_\n"
  "#define _Struct_h_\n"
  "\n"
  "#ifdef _MSC_VER\n"
  "  #define snprintf _snprintf\n"
  "  #pragma warning(disable: 4786 4996)\n"
  "#endif\n"
  "\n"
  "#include <string>\n"
  "#include <list>\n"
  "#include <set>\n"
  "#include <map>\n"
  "#include <stdio.h>\n"
  "\n"
;
const char * pszHdrFile =
  "#include \"$(headerfile)\"\n"
;
const char * pszHdrStruct =
  "void serialize(CWriteXml & rWriteXml, const $(name) & rObject, const char * pszTag = 0, bool fRoot = true,\n"
  "  const char * pszIdTag = 0, const std::string * pstrIdValue = 0);\n"
  "void deserialize(CReadXml & rReadXml, $(name) & rObject, const char * pszTag =0, bool fRoot = true,\n"
  "  const char * pszIdTag = 0, std::string * pstrIdValue = 0);\n"
  "\n"
;
const char * pszHdrEpilog =
  "#endif // _Struct_h_\n"
;
const char * pszSerProlog =
  "#include \"structCom.h\"\n"
  "\n"
;
const char * pszSerStructBegin =
  "void serialize(CWriteXml & rWriteXml, const $(name) & rObject, const char * pszTag, bool fRoot,\n"
  "  const char * pszIdTag, const std::string * pstrIdValue)\n"
  "{\n"
  "  if (!pszTag)\n"
  "    pszTag=\"$(alias)\";\n"
  "  rWriteXml.StartTag(pszTag, fRoot);\n"
  "  if (pszIdTag && pstrIdValue)\n"
  "  {\n"
  "    serialize(rWriteXml, *pstrIdValue, pszIdTag, false);\n"
  "  }\n"
;
const char * pszSerStructVarDecl =
  "  serialize(rWriteXml, rObject.$(name), \"$(alias)\", false);\n"
;
const char * pszSerStructVarDeclVector =
  "  rWriteXml.StartTag(\"$(alias)\", false);\n"
  "  {for (int n=0; n<$(size); n++)\n"
  "  {\n"
  "    serialize(rWriteXml, rObject.$(name)[n], \"$(item)\", false);\n"
  "  }}\n"
  "  rWriteXml.EndTag(\"$(alias)\");\n"
;
const char * pszSerStructVarDeclList =
  "  serialize(rWriteXml, rObject.$(name), \"$(alias)\", \"$(item)\", false);\n"
;
const char * pszSerStructVarDeclMap =
  "  serialize(rWriteXml, rObject.$(name), \"$(alias)\", \"$(item)\", \"$(id)\", false);\n"
;
const char * pszSerStructEnd =
  "  rWriteXml.EndTag(pszTag);\n"
  "}\n"
  "\n"
;
const char * pszDesProlog =
  "#include \"structCom.h\"\n"
  "#include <stdlib.h>\n"
  "\n"
;
const char * pszDesStructBegin =
  "void deserialize(CReadXml & rReadXml, $(name) & rObject, const char * pszTag, bool fRoot,\n"
  "  const char * pszIdTag, std::string * pstrIdValue)\n"
  "{\n"
  "  if (!pszTag)\n"
  "    pszTag=\"$(alias)\";\n"
  "  if (fRoot)\n"
  "  {\n"
  "    if (!rReadXml.IsStartTag(pszTag, fRoot))\n"
  "      return;\n"
  "  }\n"
  "  while (!rReadXml.IsEof() && !rReadXml.IsEndTag(pszTag))\n"
  "  {\n"
  "    if (pszIdTag && pstrIdValue && rReadXml.IsStartTag(pszIdTag, false))\n"
  "    {\n"
  "      deserialize(rReadXml, *pstrIdValue, pszIdTag, false);\n"
  "      continue;\n"
  "    }\n"
;
const char * pszDesStructVarDecl =
  "    if (rReadXml.IsStartTag(\"$(alias)\", false))\n"
  "    {\n"
  "      deserialize(rReadXml, rObject.$(name), \"$(alias)\", false);\n"
  "      continue;\n"
  "    }\n"
;
const char * pszDesStructVarDeclVector =
  "    if (rReadXml.IsStartTag(\"$(alias)\", false))\n"
  "    {\n"
  "      int     _n   = 0;\n"
  "      while (!rReadXml.IsEof() && !rReadXml.IsEndTag(\"$(alias)\"))\n"
  "      {\n"
  "        if (_n<$(size) && rReadXml.IsStartTag(\"$(item)\", false))\n"
  "        {\n"
  "          deserialize(rReadXml, rObject.$(name)[_n++], \"$(item)\", false);\n"
  "          continue;\n"
  "        }\n"
  "        rReadXml.SkipTag();\n"
  "      } // while (!rReadXml.IsEndTag(...))\n"
  "      continue;\n"
  "    }\n"
;
const char * pszDesStructVarDeclList =
  "    if (rReadXml.IsStartTag(\"$(alias)\", false))\n"
  "    {\n"
  "      deserialize(rReadXml, rObject.$(name), \"$(alias)\", \"$(item)\", false);\n"
  "      continue;\n"
  "    }\n"
;
const char * pszDesStructVarDeclMap =
  "    if (rReadXml.IsStartTag(\"$(alias)\", false))\n"
  "    {\n"
  "      deserialize(rReadXml, rObject.$(name), \"$(alias)\", \"$(item)\", \"$(id)\", false);\n"
  "      continue;\n"
  "    }\n"
;
const char * pszDesStructEnd =
  "    rReadXml.SkipTag();\n"
  "  } // while (!rReadXml.IsEndTag(...))\n"
  "}\n"
  "\n"
;
const char * pszHeader =
  "const int IDENT_WIDTH = 2;\n"
  "\n"
  "class CWriteXml\n"
  "{\n"
  "public:\n"
  "  virtual ~CWriteXml()\n"
  "  {\n"
  "  }\n"
  "\n"
  "  void StartTag(const char * pszTag, bool fRoot)\n"
  "  {\n"
  "    startTag(pszTag, fRoot);\n"
  "  }\n"
  "\n"
  "  void EndTag(const char * pszTag)\n"
  "  {\n"
  "    endTag(pszTag);\n"
  "  }\n"
  "\n"
  "  void PutData(const char * pszData, int nDataLen = 0x7FFF)\n"
  "  {\n"
  "    putData(pszData, nDataLen);\n"
  "  }\n"
  "\n"
  "private:\n"
  "  virtual void startTag(const char * pszTag, bool fRoot)            = 0;\n"
  "  virtual void endTag(const char * pszTag)                          = 0;\n"
  "  virtual void putData(const char * pszData, int nDataLen = 0x7FFF) = 0;\n"
  "};\n"
  "\n"
  "class CWriteXmlString : public CWriteXml\n"
  "{\n"
  "public:\n"
  "  CWriteXmlString(std::string & strWrite) :\n"
  "    mstrWrite(strWrite),\n"
  "    mnDepth(0),\n"
  "    mfStartTag(false),\n"
  "    mfLf(false)\n"
  "  {\n"
  "  }\n"
  "\n"
  "  void startTag(const char * pszTag, bool fRoot)\n"
  "  {\n"
  "    if (fRoot)\n"
  "    {\n"
  "      mstrWrite += \"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\" ?>\\n\";\n"
  "      mfLf      = true;\n"
  "    }\n"
  "\n"
  "    if (mfStartTag)\n"
  "    {\n"
  "      mstrWrite += '\\n';\n"
  "      mfLf = true;\n"
  "    }\n"
  "\n"
  "    indent();\n"
  "    mstrWrite += '<';\n"
  "    mstrWrite += pszTag;\n"
  "    mstrWrite += '>';\n"
  "    mfStartTag = true;\n"
  "    mnDepth++;\n"
  "  }\n"
  "\n"
  "  void endTag(const char * pszTag)\n"
  "  {\n"
  "    mnDepth--;\n"
  "    indent();\n"
  "    mstrWrite += \"</\";\n"
  "    mstrWrite += pszTag;\n"
  "    mstrWrite += \">\\n\";\n"
  "    mfLf      = true;\n"
  "    mfStartTag  = false;\n"
  "  }\n"
  "\n"
  "  void putData(const char * pszData, int nDataLen)\n"
  "  {\n"
  "    const char *  pszPos  = pszData;\n"
  "\n"
  "    while (*pszPos && pszPos-pszData < nDataLen)\n"
  "    {\n"
  "      if ('<' == *pszPos)\n"
  "      {\n"
  "        mstrWrite += \"&lt;\";\n"
  "        pszPos++;\n"
  "        continue;\n"
  "      }\n"
  "\n"
  "      if ('>' == *pszPos)\n"
  "      {\n"
  "        mstrWrite += \"&gt;\";\n"
  "        pszPos++;\n"
  "        continue;\n"
  "      }\n"
  "\n"
  "      if ('&' == *pszPos)\n"
  "      {\n"
  "        mstrWrite += \"&amp;\";\n"
  "        pszPos++;\n"
  "        continue;\n"
  "      }\n"
  "\n"
  "      if ('\"' == *pszPos)\n"
  "      {\n"
  "        mstrWrite += \"&quot;\";\n"
  "        pszPos++;\n"
  "        continue;\n"
  "      }\n"
  "\n"
  "      if ('\\'' == *pszPos)\n"
  "      {\n"
  "        mstrWrite += \"&apos;\";\n"
  "        pszPos++;\n"
  "        continue;\n"
  "      }\n"
  "\n"
  "      const char *  pszEnd  = pszPos;\n"
  "\n"
  "      // find end or entity\n"
  "      while ( pszEnd-pszData < nDataLen   &&\n"
  "              0   != *pszEnd    &&\n"
  "              '<' != *pszEnd    &&\n"
  "              '>' != *pszEnd    &&\n"
  "              '\"' != *pszEnd    &&\n"
  "              '\\''!= *pszEnd    &&\n"
  "              '&' != *pszEnd )\n"
  "      {\n"
  "        pszEnd++;\n"
  "      }\n"
  "\n"
  "      mstrWrite.append(pszPos, pszEnd-pszPos);\n"
  "      pszPos = pszEnd;\n"
  "    }\n"
  "\n"
  "    mfStartTag  = false;\n"
  "  }\n"
  "\n"
  "  void indent()\n"
  "  {\n"
  "    if (mfLf)\n"
  "    {\n"
  "      mstrWrite.append(mnDepth*IDENT_WIDTH, ' ');\n"
  "      mfLf = false;\n"
  "    }\n"
  "  }\n"
  "\n"
  "private:\n"
  "  std::string & mstrWrite;\n"
  "  int           mnDepth;\n"
  "  bool          mfStartTag;\n"
  "  bool          mfLf;\n"
  "};\n"
  "\n"
  "#include <string.h>\n"
  "\n"
  "\n"
  "\n"
  "class CReadXml\n"
  "{\n"
  "public:\n"
  "  enum EStatus\n"
  "  {\n"
  "    eStatStart,\n"
  "    eStatFinish,\n"
  "    eStatXmlDeclTagstartMissing,      // the declaration tag start '<?xml...'is not found\n"
  "    eStatXmlDeclTagendMissing,        // the declaration tag end '?>'is not found\n"
  "    eStatIlleagalCharInTagName,       // a char other than alnum and '_' has been found in a tagname\n"
  "    eStatIlleagalTextBetweenTags,     // text other than WS is found between closed value tags\n"
  "    eStatIlleagalStarttag,            // an unexpected starttag has been found\n"
  "    eStatMissingStarttag,             // there's no starttag where we expect one in a skip operation\n"
  "    eStatMissingEndtag,               // the end tag for a value is missing\n"
  "    eStatNonMatchingEndtag,           // an endtag is encountered, that does not match the nesting\n"
  "    eStatSuperfluousEndtag,           // an endtag is encountered after the all enclosing tag has been closed\n"
  "    eStatUnterminatedComment,         // a comment did not have the terminating '-->' tag\n"
  "    eStatUnterminatedBegintag,        // a begintag did not have the terminating '>'\n"
  "    eStatUnterminatedEndtag           // an endtag did not have the terminating '>'\n"
  "  };\n"
  "\n"
  "  bool IsEof()\n"
  "  {\n"
  "    return isEof();\n"
  "  }\n"
  "\n"
  "  bool IsStartTag(const char * pszTag, bool fRoot)\n"
  "  {\n"
  "    return isStartTag(pszTag, fRoot);\n"
  "  }\n"
  "\n"
  "  bool IsEndTag(const char * pszTag)\n"
  "  {\n"
  "    return isEndTag(pszTag);\n"
  "  }\n"
  "\n"
  "  bool GetData(const char * & pszData, int & nDataLen)\n"
  "  {\n"
  "    return getText(pszData, nDataLen);\n"
  "  }\n"
  "\n"
  "  void SkipTag()\n"
  "  {\n"
  "    if (mfStrict)\n"
  "    {\n"
  "      // skipping of unknown tags not allowed\n"
  "      SetStatus(eStatIlleagalStarttag);\n"
  "      return;\n"
  "    }\n"
  "\n"
  "    skipTag();\n"
  "  }\n"
  "\n"
  "  void EnableStrict(bool fEnable = true)\n"
  "  {\n"
  "    mfStrict = fEnable;\n"
  "  }\n"
  "\n"
  "/*\n"
  "  bool Strict() const\n"
  "  {\n"
  "    return mfStrict;\n"
  "  }\n"
  "*/\n"
  "\n"
  "  void EnableExceptions(bool fEnable = true)\n"
  "  {\n"
  "    mfExceptions = fEnable;\n"
  "  }\n"
  "\n"
  "/*\n"
  "  bool Exceptions()\n"
  "  {\n"
  "    return mfExceptions;\n"
  "  }\n"
  "*/\n"
  "\n"
  "  EStatus GetStatus() const\n"
  "  {\n"
  "    return meStatus;\n"
  "  }\n"
  "\n"
  "  void SetStatus(EStatus eStatus)\n"
  "  {\n"
  "    meStatus = eStatus;\n"
  "    // :TODO: only if abortive status\n"
  "    if (mfExceptions)\n"
  "    {\n"
  "      throw meStatus;\n"
  "    }\n"
  "  }\n"
  "\n"
  "  int GetLine()\n"
  "  {\n"
  "    return mnLine;\n"
  "  }\n"
  "\n"
  "  int GetColumn()\n"
  "  {\n"
  "    return mnColumn;\n"
  "  }\n"
  "\n"
  "protected:\n"
  "  CReadXml() :\n"
  "    meStatus(eStatStart),\n"
  "    mfStrict(false),\n"
  "    mfExceptions(false),\n"
  "    mnLine(1),\n"
  "    mnColumn(1)\n"
  "  {\n"
  "  }\n"
  "\n"
  "  virtual ~CReadXml()\n"
  "  {\n"
  "  }\n"
  "\n"
  "  // dummy function that increases the line when '\\n' is found\n"
  "  bool incChar(char c)\n"
  "  {\n"
  "    if ('\\n'==c)\n"
  "    {\n"
  "      mnLine++;\n"
  "      mnColumn = 1;\n"
  "    }\n"
  "    else\n"
  "    {\n"
  "      mnColumn++;\n"
  "    }\n"
  "\n"
  "    return true;\n"
  "  }\n"
  "\n"
  "  // dummy function that increases the column\n"
  "  int movChar(int n)\n"
  "  {\n"
  "    mnColumn +=n;\n"
  "    return n;\n"
  "  }\n"
  "\n"
  "  void pushTag(const char * pszTag)\n"
  "  {\n"
  "    mstackTags.push_back(pszTag);\n"
  "  }\n"
  "\n"
  "  void pushTag(const char * pszTag, int nLen)\n"
  "  {\n"
  "    mstackTags.push_back(std::string(pszTag, nLen));\n"
  "  }\n"
  "\n"
  "  void popTag(const char * pszTag, unsigned int nLen = std::string::npos)\n"
  "  {\n"
  "    std::string strTag;\n"
  "\n"
  "    if (std::string::npos == nLen)\n"
  "      strTag = pszTag;\n"
  "    else\n"
  "      strTag.assign(pszTag, nLen);\n"
  "\n"
  "    if (mstackTags.empty())\n"
  "    {\n"
  "      SetStatus(eStatSuperfluousEndtag);\n"
  "    }\n"
  "    else if (mstackTags.back() != strTag)\n"
  "    {\n"
  "      SetStatus(eStatNonMatchingEndtag);\n"
  "    }\n"
  "    mstackTags.pop_back();\n"
  "  }\n"
  "\n"
  "private:\n"
  "  virtual bool isEof()                                            = 0;\n"
  "  virtual bool isStartTag(const char * pszTag, bool fRoot)        = 0;\n"
  "  virtual bool isEndTag(const char * pszTag)                      = 0;\n"
  "  virtual bool getText(const char * & pszData, int & nDataLen)    = 0;\n"
  "  virtual void skipTag()                                          = 0;\n"
  "\n"
  "  EStatus   meStatus;\n"
  "  bool      mfStrict;\n"
  "  bool      mfExceptions;\n"
  "  int       mnLine;\n"
  "  int       mnColumn;\n"
  "  std::list<std::string> mstackTags;\n"
  "};\n"
  "\n"
  "class CReadXmlPChar : public CReadXml\n"
  "{\n"
  "public:\n"
  "  CReadXmlPChar(const char * pszXml) :\n"
  "    mpszXml(pszXml)\n"
  "  {\n"
  "  }\n"
  "\n"
  "  bool isEof()\n"
  "  {\n"
  "    return !*mpszXml;\n"
  "  }\n"
  "\n"
  "  bool isStartTag(const char * pszTag, bool fRoot)\n"
  "  {\n"
  "    if (fRoot)\n"
  "    {\n"
  "      // <?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n"
  "      if (0!=strncmp(mpszXml, \"<?xml \", 6))\n"
  "      {\n"
  "        SetStatus(eStatXmlDeclTagstartMissing);\n"
  "        return false;\n"
  "      }\n"
  "      mpszXml += movChar(6); // magic number: strlen(\"<?xml \")\n"
  "      while ( *mpszXml && incChar(*mpszXml) && '?' != *mpszXml++);\n"
  "      if ( incChar(*mpszXml) && '>' != *mpszXml++)\n"
  "      {\n"
  "        SetStatus(eStatXmlDeclTagendMissing);\n"
  "        return false;\n"
  "      }\n"
  "\n"
  "      // <!DOCTYPE ...\n"
  "      eatws();\n"
  "      if (0==strncmp(mpszXml, \"<!DOCTYPE \", 10))\n"
  "      {\n"
  "        mpszXml += movChar(10); // magic number: strlen(\"<!DOCTYPE \")\n"
  "        while ( *mpszXml && incChar(*mpszXml) && '>' != *mpszXml++);\n"
  "      }\n"
  "    }\n"
  "\n"
  "    eatws();\n"
  "\n"
  "    int nTagLen = strlen(pszTag);\n"
  "\n"
  "    if ('<' != mpszXml[0]                           ||\n"
  "        0   != strncmp(mpszXml+1, pszTag, nTagLen)  ||\n"
  "        '>' != mpszXml[nTagLen+1] )\n"
  "    {\n"
  "      return false;\n"
  "    }\n"
  "    mpszXml += movChar(nTagLen+2);\n"
  "    pushTag(pszTag);\n"
  "    return true;\n"
  "  }\n"
  "\n"
  "  bool isEndTag(const char * pszTag)\n"
  "  {\n"
  "    eatws();\n"
  "\n"
  "    int nTagLen = strlen(pszTag);\n"
  "\n"
  "    if ('<' != mpszXml[0]                           ||\n"
  "        '/' != mpszXml[1]                           ||\n"
  "        0   != strncmp(mpszXml+2, pszTag, nTagLen)  ||\n"
  "        '>' != mpszXml[nTagLen+2] )\n"
  "    {\n"
  "      return false;\n"
  "    }\n"
  "\n"
  "    popTag(pszTag);\n"
  "    mpszXml += movChar(nTagLen+3);\n"
  "    return true;\n"
  "  }\n"
  "\n"
  "  bool getText(const char * & pszData, int & nDataLen)\n"
  "  {\n"
  "    if ('&' == *mpszXml)\n"
  "    {\n"
  "      // skip ampersand\n"
  "      mpszXml++; movChar(1);\n"
  "\n"
  "      if (0==strncmp(mpszXml, \"gt;\", 3))\n"
  "      {\n"
  "        pszData =   \">\";\n"
  "        mpszXml +=  movChar(3);\n"
  "      }\n"
  "      else if (0==strncmp(mpszXml, \"lt;\", 3))\n"
  "      {\n"
  "        pszData =   \"<\";\n"
  "        mpszXml +=  movChar(3);\n"
  "      }\n"
  "      else if (0==strncmp(mpszXml, \"amp;\", 4))\n"
  "      {\n"
  "        pszData =   \"&\";\n"
  "        mpszXml +=  movChar(4);\n"
  "      }\n"
  "      else if (0==strncmp(mpszXml, \"quot;\", 5))\n"
  "      {\n"
  "        pszData =   \"\\\"\";\n"
  "        mpszXml +=  movChar(5);\n"
  "      }\n"
  "      else if (0==strncmp(mpszXml, \"apos;\", 5))\n"
  "      {\n"
  "        pszData =   \"'\";\n"
  "        mpszXml +=  movChar(5);\n"
  "      }\n"
  "      else\n"
  "      {\n"
  "        // no known xml entity, use as plain text\n"
  "        pszData =   \"&\";\n"
  "      }\n"
  "      nDataLen = 1;\n"
  "\n"
  "      // finished, when new tag starts or string is at the end\n"
  "      return  0   == *mpszXml     ||\n"
  "              '<' == *mpszXml;\n"
  "    }\n"
  "\n"
  "    const char * pszNext = mpszXml;\n"
  "    // find next delimiter\n"
  "    while ( 0   != *pszNext &&\n"
  "            '<' != *pszNext &&\n"
  "            '&' != *pszNext )\n"
  "    {\n"
  "      incChar(*pszNext);\n"
  "      pszNext++;\n"
  "    }\n"
  "\n"
  "    pszData   = mpszXml;\n"
  "    nDataLen  = pszNext - mpszXml;\n"
  "    mpszXml   = pszNext;\n"
  "\n"
  "    return '&' != *pszNext;\n"
  "  }\n"
  "\n"
  "  void skipTag()\n"
  "  {\n"
  "/*\n"
  "    int nStack = .size();\n"
  "    if (!skipSingleTag(false))\n"
  "    {\n"
  "      // :TODO:\n"
  "      return;\n"
  "    }\n"
  "\n"
  "    while (*mpszXml && nstack...\n"
  "    {\n"
  "      eatText();\n"
  "      skipSingleTag();\n"
  "    }\n"
  "*/\n"
  "  }\n"
  "\n"
  "  bool skipSingleTag(bool fEndTag)\n"
  "  {\n"
  "    // not on the start of a tag ?\n"
  "    if ('<' != *mpszXml)\n"
  "    {\n"
  "      SetStatus(eStatMissingStarttag);\n"
  "      return false;\n"
  "    }\n"
  "\n"
  "    // skip over the '<'\n"
  "    incChar(*mpszXml);\n"
  "    mpszXml++;\n"
  "\n"
  "    if (fEndTag && '/' != *mpszXml)\n"
  "    {\n"
  "      SetStatus(eStatMissingEndtag);\n"
  "      return false;\n"
  "    }\n"
  "    else\n"
  "    {\n"
  "      // skip over the '/'\n"
  "      incChar(*mpszXml);\n"
  "      mpszXml++;\n"
  "    }\n"
  "\n"
  "    // remember start of tag\n"
  "    const char * pszTag = mpszXml;\n"
  "\n"
  "    // find end of tag\n"
  "    while (  0 != *mpszXml   &&   '>' != *mpszXml  )\n"
  "    {\n"
  "      if (!isalnum(*mpszXml) && '_' != *mpszXml)\n"
  "      {\n"
  "        SetStatus(eStatIlleagalCharInTagName);\n"
  "        return false;\n"
  "      }\n"
  "\n"
  "      incChar(*mpszXml);\n"
  "      mpszXml++;\n"
  "    }\n"
  "\n"
  "    if (0 != *mpszXml)\n"
  "    {\n"
  "      SetStatus(eStatUnterminatedBegintag);\n"
  "      return false;\n"
  "    }\n"
  "\n"
  "    if (fEndTag)\n"
  "      popTag(pszTag, mpszXml-pszTag);\n"
  "    else\n"
  "      pushTag(pszTag, mpszXml-pszTag);\n"
  "    return true;\n"
  "  }\n"
  "\n"
  "  void eatws()\n"
  "  {\n"
  "    do\n"
  "    {\n"
  "      // eat whitespace\n"
  "      while (   ' '   == *mpszXml ||\n"
  "                '\\t'  == *mpszXml ||\n"
  "                '\\n'  == *mpszXml ||\n"
  "                '\\r'  == *mpszXml )\n"
  "      {\n"
  "        incChar(*mpszXml);\n"
  "        mpszXml++;\n"
  "      }\n"
  "    } while (eatcomment());\n"
  "\n"
  "    if (*mpszXml != '<')\n"
  "      SetStatus(eStatIlleagalTextBetweenTags);\n"
  "  }\n"
  "\n"
  "  bool eatcomment()\n"
  "  {\n"
  "    // check start of comment\n"
  "    if ( '<' == mpszXml[0]    &&\n"
  "         '!' == mpszXml[1]    &&\n"
  "         '-' == mpszXml[2]    &&\n"
  "         '-' == mpszXml[3])\n"
  "    {\n"
  "      mpszXml += movChar(4);\n"
  "    }\n"
  "    else\n"
  "      return false;\n"
  "\n"
  "    for (;;)\n"
  "    {\n"
  "      // find end of comment\n"
  "      while ( 0 != *mpszXml  &&  '-' != *mpszXml  &&  incChar(*mpszXml) )\n"
  "        mpszXml++;\n"
  "\n"
  "      // end of string\n"
  "      if (!*mpszXml)\n"
  "      {\n"
  "        // unterminated comment\n"
  "        SetStatus(eStatUnterminatedComment);\n"
  "        return true;\n"
  "      }\n"
  "\n"
  "      incChar(*mpszXml);\n"
  "      mpszXml++;\n"
  "\n"
  "      // check end of comment\n"
  "      if ( '-' == mpszXml[0]  &&\n"
  "           '>' == mpszXml[1])\n"
  "      {\n"
  "        mpszXml += movChar(2);\n"
  "        return true;\n"
  "      }\n"
  "    }\n"
  "  }\n"
  "\n"
  "protected:\n"
  "  void setXml(const char * pszXml)\n"
  "  {\n"
  "    mpszXml = pszXml;\n"
  "  }\n"
  "\n"
  "private:\n"
  "  const char * mpszXml;\n"
  "};\n"
  "\n"
  "class CReadXmlFile : public CReadXmlPChar\n"
  "{\n"
  "public:\n"
  "  CReadXmlFile() :\n"
  "    CReadXmlPChar(0)\n"
  "  {\n"
  "  }\n"
  "\n"
  "  virtual ~CReadXmlFile()\n"
  "  {\n"
  "  }\n"
  "\n"
  "  bool UseFile(const char * pszFilename)\n"
  "  {\n"
  "    setXml(0);\n"
  "    mstrData.erase();\n"
  "\n"
  "    FILE * f = fopen(pszFilename, \"r\");\n"
  "    if (!f)\n"
  "    {\n"
  "      return false;\n"
  "    }\n"
  "\n"
  "    while (!feof(f))\n"
  "    {\n"
  "      const int BUFSIZE = 4096;\n"
  "      char szBuffer[BUFSIZE];\n"
  "      int nRead = fread(szBuffer, 1, BUFSIZE, f);\n"
  "      mstrData.append(szBuffer, nRead);\n"
  "    }\n"
  "\n"
  "    fclose(f);\n"
  "    setXml(mstrData.c_str());\n"
  "    return true;\n"
  "  }\n"
  "\n"
  "  const std::string & GetData() { return mstrData; }\n"
  "\n"
  "private:\n"
  "  std::string mstrData;\n"
  "};\n"
  "\n"
  "inline void serialize(char * pBuffer, int nBufSize, const bool & rObject)\n"
  "{\n"
  "  snprintf(pBuffer, nBufSize, rObject? \"1\" : \"0\");\n"
  "}\n"
  "\n"
  "inline void serialize(char * pBuffer, int nBufSize, const short & rObject)\n"
  "{\n"
  "  snprintf(pBuffer, nBufSize, \"%hd\", rObject);\n"
  "}\n"
  "\n"
  "inline void serialize(char * pBuffer, int nBufSize, const unsigned short & rObject)\n"
  "{\n"
  "  snprintf(pBuffer, nBufSize, \"%hu\", rObject);\n"
  "}\n"
  "\n"
  "inline void serialize(char * pBuffer, int nBufSize, const int & rObject)\n"
  "{\n"
  "  snprintf(pBuffer, nBufSize, \"%d\", rObject);\n"
  "}\n"
  "\n"
  "inline void serialize(char * pBuffer, int nBufSize, const unsigned int & rObject)\n"
  "{\n"
  "  snprintf(pBuffer, nBufSize, \"%u\", rObject);\n"
  "}\n"
  "\n"
  "inline void serialize(char * pBuffer, int nBufSize, const long & rObject)\n"
  "{\n"
  "  snprintf(pBuffer, nBufSize, \"%ld\", rObject);\n"
  "}\n"
  "\n"
  "inline void serialize(char * pBuffer, int nBufSize, const unsigned long & rObject)\n"
  "{\n"
  "  snprintf(pBuffer, nBufSize, \"%lu\", rObject);\n"
  "}\n"
  "\n"
  "inline void serialize(char * pBuffer, int nBufSize, const float & rObject)\n"
  "{\n"
  "  snprintf(pBuffer, nBufSize, \"%f\", static_cast<double>(rObject));\n"
  "}\n"
  "\n"
  "inline void serialize(char * pBuffer, int nBufSize, const double & rObject)\n"
  "{\n"
  "  snprintf(pBuffer, nBufSize, \"%f\", rObject);\n"
  "}\n"
  "\n"
  "inline void serialize(char * pBuffer, int nBufSize, const SLongHex & rObject)\n"
  "{\n"
  "  snprintf(pBuffer, nBufSize, \"%lX\", rObject.mulHex);\n"
  "}\n"
  "\n"
  "// serialize a std::string object\n"
  "void serialize(CWriteXml & rWriteXml, const std::string &     rObject, const char * pszTag, bool fRoot = true);\n"
  "\n"
  "// serialize any of the objects for that an above function is defined\n"
  "template <class _T>\n"
  "void serialize(CWriteXml & rWriteXml, const _T & rObject, const char * pszTag, bool fRoot = true)\n"
  "{\n"
  "  rWriteXml.StartTag(pszTag, fRoot);\n"
  "  char szBuffer[80];\n"
  "  serialize(szBuffer, 80, rObject);\n"
  "  rWriteXml.PutData(szBuffer);\n"
  "  rWriteXml.EndTag(pszTag);\n"
  "}\n"
  "\n"
  "// serialize any set object for witch a key serialize function exists\n"
  "template <class _K>\n"
  "void serialize(\n"
  "  CWriteXml & rWriteXml, const std::set<_K> & rObject,\n"
  "  const char * pszTag, const char * pszTagItem, bool fRoot = true)\n"
  "{\n"
  "  rWriteXml.StartTag(pszTag, fRoot);\n"
  "  for (typename std::set<_K>::const_iterator itr=rObject.begin(); itr!=rObject.end(); itr++)\n"
  "  {\n"
  "    // serialize the key object\n"
  "    serialize(rWriteXml, *itr, pszTagItem, false);\n"
  "  }\n"
  "  rWriteXml.EndTag(pszTag);\n"
  "}\n"
  "\n"
  "// serialize any list object for witch a serialize function exists\n"
  "template <class _T>\n"
  "void serialize(\n"
  "  CWriteXml & rWriteXml, const std::list<_T> & rObject,\n"
  "  const char * pszTag, const char * pszTagItem, bool fRoot = true)\n"
  "{\n"
  "  rWriteXml.StartTag(pszTag, fRoot);\n"
  "  for (typename std::list<_T>::const_iterator itr=rObject.begin(); itr!=rObject.end(); itr++)\n"
  "  {\n"
  "    // serialize the key object\n"
  "    serialize(rWriteXml, *itr, pszTagItem, false);\n"
  "  }\n"
  "  rWriteXml.EndTag(pszTag);\n"
  "}\n"
  "\n"
  "// serialize a std::map<std::string, _T> object\n"
  "template <class _T>\n"
  "void serialize(\n"
  "  CWriteXml & rWriteXml, const std::map<std::string, _T> & rObject,\n"
  "  const char * pszTag, const char * pszTagItem, const char * pszTagId,\n"
  "  bool fRoot = true)\n"
  "{\n"
  "  rWriteXml.StartTag(pszTag, fRoot);\n"
  "  for (typename std::map<std::string, _T>::const_iterator itr=rObject.begin(); itr!=rObject.end(); itr++)\n"
  "  {\n"
  "    serialize(rWriteXml, itr->second, pszTagItem, false, pszTagId, &itr->first);\n"
  "  }\n"
  "  rWriteXml.EndTag(pszTag);\n"
  "}\n"
  "\n"
  "// serialize any other map object for witch a key serialize function exists\n"
  "template <class _K, class _T>\n"
  "void serialize(\n"
  "  CWriteXml & rWriteXml, const std::map<_K, _T> & rObject,\n"
  "  const char * pszTag, const char * pszTagItem, const char * pszTagId,\n"
  "  bool fRoot = true)\n"
  "{\n"
  "  rWriteXml.StartTag(pszTag, fRoot);\n"
  "  for (typename std::map<_K, _T>::const_iterator itr=rObject.begin(); itr!=rObject.end(); itr++)\n"
  "  {\n"
  "    // first serialize the key to a string\n"
  "    const int BUFSIZE = 1024;\n"
  "    char szBuffer[BUFSIZE];\n"
  "    serialize(szBuffer, BUFSIZE, itr->first);\n"
  "    std::string strBuffer(szBuffer);\n"
  "    // serialize the object with a string key\n"
  "    serialize(rWriteXml, itr->second, pszTagItem, false, pszTagId, &strBuffer);\n"
  "  }\n"
  "  rWriteXml.EndTag(pszTag);\n"
  "}\n"
  "\n"
  "// serialize a std::multimap<std::string, _T> object\n"
  "template <class _T>\n"
  "void serialize(\n"
  "  CWriteXml & rWriteXml, const std::multimap<std::string, _T> & rObject,\n"
  "  const char * pszTag, const char * pszTagItem, const char * pszTagId,\n"
  "  bool fRoot = true)\n"
  "{\n"
  "  rWriteXml.StartTag(pszTag, fRoot);\n"
  "  for (typename std::multimap<std::string, _T>::const_iterator itr=rObject.begin(); itr!=rObject.end(); itr++)\n"
  "  {\n"
  "    serialize(rWriteXml, itr->second, pszTagItem, false, pszTagId, &itr->first);\n"
  "  }\n"
  "  rWriteXml.EndTag(pszTag);\n"
  "}\n"
  "\n"
  "// serialize any other multimap object for witch a key serialize function exists\n"
  "template <class _K, class _T>\n"
  "void serialize(\n"
  "  CWriteXml & rWriteXml, const std::multimap<_K, _T> & rObject,\n"
  "  const char * pszTag, const char * pszTagItem, const char * pszTagId,\n"
  "  bool fRoot = true)\n"
  "{\n"
  "  rWriteXml.StartTag(pszTag, fRoot);\n"
  "  for (typename std::multimap<_K, _T>::const_iterator itr=rObject.begin(); itr!=rObject.end(); itr++)\n"
  "  {\n"
  "    // first serialize the key to a string\n"
  "    const int BUFSIZE = 1024;\n"
  "    char szBuffer[BUFSIZE];\n"
  "    serialize(szBuffer, BUFSIZE, itr->first);\n"
  "    std::string strBuffer(szBuffer);\n"
  "    // serialize the object with a string key\n"
  "    serialize(rWriteXml, itr->second, pszTagItem, false, pszTagId, &strBuffer);\n"
  "  }\n"
  "  rWriteXml.EndTag(pszTag);\n"
  "}\n"
  "\n"
  "inline void deserialize(const char * pBuffer, bool & rObject)\n"
  "{\n"
  "  rObject =\n"
  "    0==strncmp(pBuffer, \"true\", 4) ||\n"
  "    0==strncmp(pBuffer, \"yes\", 3) ||\n"
  "    0==strncmp(pBuffer, \"on\", 2) ||\n"
  "    0==strncmp(pBuffer, \"1\", 1);\n"
  "}\n"
  "\n"
  "inline void deserialize(const char * pBuffer, short & rObject)\n"
  "{\n"
  "  rObject = static_cast<short>(strtol(pBuffer, 0, 10));\n"
  "}\n"
  "\n"
  "inline void deserialize(const char * pBuffer, unsigned short & rObject)\n"
  "{\n"
  "  rObject = static_cast<unsigned short>(strtoul(pBuffer, 0, 10));\n"
  "}\n"
  "\n"
  "inline void deserialize(const char * pBuffer, int & rObject)\n"
  "{\n"
  "  rObject = static_cast<int>(strtol(pBuffer, 0, 10));\n"
  "}\n"
  "\n"
  "inline void deserialize(const char * pBuffer, unsigned int & rObject)\n"
  "{\n"
  "  rObject = static_cast<unsigned int>(strtoul(pBuffer, 0, 10));\n"
  "}\n"
  "\n"
  "inline void deserialize(const char * pBuffer, long & rObject)\n"
  "{\n"
  "  rObject = strtol(pBuffer, 0, 10);\n"
  "}\n"
  "\n"
  "inline void deserialize(const char * pBuffer, unsigned long & rObject)\n"
  "{\n"
  "  rObject = strtoul(pBuffer, 0, 10);\n"
  "}\n"
  "\n"
  "inline void deserialize(const char * pBuffer, float & rObject)\n"
  "{\n"
  "  rObject = static_cast<float>(atof(pBuffer));\n"
  "}\n"
  "\n"
  "inline void deserialize(const char * pBuffer, double & rObject)\n"
  "{\n"
  "  rObject = atof(pBuffer);\n"
  "}\n"
  "\n"
  "inline void deserialize(const char * pBuffer, SLongHex & rObject)\n"
  "{\n"
  "  rObject.mulHex = strtoul(pBuffer, 0, 16);\n"
  "}\n"
  "\n"
  "void deserialize(CReadXml & rReadXml, std::string & rObject, const char * pszTag, bool fRoot = true);\n"
  "\n"
  "// deserialize types without a base or ordinal integers in decimal system\n"
  "template <class _T>\n"
  "void deserialize(CReadXml & rReadXml, _T & rObject, const char * pszTag, bool fRoot = true)\n"
  "{\n"
  "  if (fRoot)\n"
  "  {\n"
  "    if (!rReadXml.IsStartTag(pszTag, fRoot))\n"
  "      return;\n"
  "  }\n"
  "  const char *  pszText   = 0;\n"
  "  int           nLen      = 0;\n"
  "  rReadXml.GetData(pszText, nLen);\n"
  "  deserialize(pszText, rObject);\n"
  "  if (!rReadXml.IsEndTag(pszTag))\n"
  "  {\n"
  "    // we are done, this is an atomous value, with no subvalues\n"
  "    rReadXml.SetStatus(CReadXml::eStatMissingEndtag);\n"
  "  }\n"
  "}\n"
  "\n"
  "template <class _K>\n"
  "void deserialize(\n"
  "  CReadXml & rReadXml, std::set<_K> & rObject,\n"
  "  const char * pszTag, const char * pszTagItem, bool fRoot = true)\n"
  "{\n"
  "  if (fRoot)\n"
  "  {\n"
  "    if (!rReadXml.IsStartTag(pszTag, fRoot))\n"
  "      return;\n"
  "  }\n"
  "  while (!rReadXml.IsEof() && !rReadXml.IsEndTag(pszTag))\n"
  "  {\n"
  "    if (rReadXml.IsStartTag(pszTagItem, false))\n"
  "    {\n"
  "      _K _k;\n"
  "      deserialize(rReadXml, _k, pszTagItem, false);\n"
  "      rObject.insert(_k);\n"
  "      continue;\n"
  "    }\n"
  "\n"
  "    rReadXml.SetStatus(CReadXml::eStatIlleagalStarttag);\n"
  "    break;\n"
  "  } // while (!rReadXml.IsEndTag(...))\n"
  "}\n"
  "\n"
  "template <class _T>\n"
  "void deserialize(\n"
  "  CReadXml & rReadXml, std::list<_T> & rObject,\n"
  "  const char * pszTag, const char * pszTagItem, bool fRoot = true)\n"
  "{\n"
  "  if (fRoot)\n"
  "  {\n"
  "    if (!rReadXml.IsStartTag(pszTag, fRoot))\n"
  "      return;\n"
  "  }\n"
  "  while (!rReadXml.IsEof() && !rReadXml.IsEndTag(pszTag))\n"
  "  {\n"
  "    if (rReadXml.IsStartTag(pszTagItem, false))\n"
  "    {\n"
  "      _T _t;\n"
  "      deserialize(rReadXml, _t, pszTagItem, false);\n"
  "      rObject.push_back(_t);\n"
  "      continue;\n"
  "    }\n"
  "\n"
  "    rReadXml.SetStatus(CReadXml::eStatIlleagalStarttag);\n"
  "    break;\n"
  "  } // while (!rReadXml.IsEndTag(...))\n"
  "}\n"
  "\n"
  "template <class _T>\n"
  "void deserialize(\n"
  "  CReadXml & rReadXml, std::map<std::string, _T> & rObject,\n"
  "  const char * pszTag, const char * pszTagItem, const char * pszTagId,\n"
  "  bool fRoot = true)\n"
  "{\n"
  "  if (fRoot)\n"
  "  {\n"
  "    if (!rReadXml.IsStartTag(pszTag, fRoot))\n"
  "      return;\n"
  "  }\n"
  "  while (!rReadXml.IsEof() && !rReadXml.IsEndTag(pszTag))\n"
  "  {\n"
  "    if (rReadXml.IsStartTag(pszTagItem, false))\n"
  "    {\n"
  "      std::string strKey;\n"
  "      _T _t;\n"
  "      deserialize(rReadXml, _t, pszTagItem, false, pszTagId, &strKey);\n"
  "/*\n"
  "      rObject[strKey] = _t;\n"
  "/*/\n"
  "      typename std::map<std::string, _T>::iterator fnd = rObject.find(strKey);\n"
  "      if (fnd != rObject.end())\n"
  "      {\n"
  "        rObject.erase(fnd);\n"
  "      }\n"
  "      rObject.insert(std::pair<std::string, _T>(strKey, _t));\n"
  "//*/\n"
  "      continue;\n"
  "    }\n"
  "\n"
  "    rReadXml.SetStatus(CReadXml::eStatIlleagalStarttag);\n"
  "    break;\n"
  "  } // while (!rReadXml.IsEndTag(...))\n"
  "}\n"
  "\n"
  "template <class _K, class _T>\n"
  "void deserialize(\n"
  "  CReadXml & rReadXml, std::map<_K, _T> & rObject,\n"
  "  const char * pszTag, const char * pszTagItem, const char * pszTagId,\n"
  "  bool fRoot = true)\n"
  "{\n"
  "  if (fRoot)\n"
  "  {\n"
  "    if (!rReadXml.IsStartTag(pszTag, fRoot))\n"
  "      return;\n"
  "  }\n"
  "  while (!rReadXml.IsEof() && !rReadXml.IsEndTag(pszTag))\n"
  "  {\n"
  "    if (rReadXml.IsStartTag(pszTagItem, false))\n"
  "    {\n"
  "      std::string strKey;\n"
  "      _T _t;\n"
  "      deserialize(rReadXml, _t, pszTagItem, false, pszTagId, &strKey);\n"
  "      _K _k;\n"
  "      deserialize(strKey.c_str(), _k);\n"
  "/*\n"
  "      rObject[_k] = _t;\n"
  "/*/\n"
  "      typename std::map<_K, _T>::iterator fnd = rObject.find(_k);\n"
  "      if (fnd != rObject.end())\n"
  "      {\n"
  "        rObject.erase(fnd);\n"
  "      }\n"
  "      rObject.insert(std::pair<_K, _T>(_k, _t));\n"
  "//*/\n"
  "      continue;\n"
  "    }\n"
  "\n"
  "    rReadXml.SetStatus(CReadXml::eStatIlleagalStarttag);\n"
  "    break;\n"
  "  } // while (!rReadXml.IsEndTag(...))\n"
  "}\n"
  "\n"
  "template <class _T>\n"
  "void deserialize(\n"
  "  CReadXml & rReadXml, std::multimap<std::string, _T> & rObject,\n"
  "  const char * pszTag, const char * pszTagItem, const char * pszTagId,\n"
  "  bool fRoot = true)\n"
  "{\n"
  "  if (fRoot)\n"
  "  {\n"
  "    if (!rReadXml.IsStartTag(pszTag, fRoot))\n"
  "      return;\n"
  "  }\n"
  "  while (!rReadXml.IsEof() && !rReadXml.IsEndTag(pszTag))\n"
  "  {\n"
  "    if (rReadXml.IsStartTag(pszTagItem, false))\n"
  "    {\n"
  "      std::string strKey;\n"
  "      _T _t;\n"
  "      deserialize(rReadXml, _t, pszTagItem, false, pszTagId, &strKey);\n"
  "      rObject.insert(std::pair<std::string, _T>(strKey, _t));\n"
  "      continue;\n"
  "    }\n"
  "    rReadXml.SkipTag();\n"
  "  } // while (!rReadXml.IsEndTag(...))\n"
  "}\n"
  "\n"
  "template <class _K, class _T>\n"
  "void deserialize(\n"
  "  CReadXml & rReadXml, std::multimap<_K, _T> & rObject,\n"
  "  const char * pszTag, const char * pszTagItem, const char * pszTagId,\n"
  "  bool fRoot = true)\n"
  "{\n"
  "  if (fRoot)\n"
  "  {\n"
  "    if (!rReadXml.IsStartTag(pszTag, fRoot))\n"
  "      return;\n"
  "  }\n"
  "  while (!rReadXml.IsEof() && !rReadXml.IsEndTag(pszTag))\n"
  "  {\n"
  "    if (rReadXml.IsStartTag(pszTagItem, false))\n"
  "    {\n"
  "      std::string strKey;\n"
  "      _T _t;\n"
  "      deserialize(rReadXml, _t, pszTagItem, false, pszTagId, &strKey);\n"
  "      _K _k;\n"
  "      deserialize(strKey.c_str(), _k);\n"
  "      rObject.insert(std::pair<_K, _T>(_k, _t));\n"
  "      continue;\n"
  "    }\n"
  "    rReadXml.SkipTag();\n"
  "  } // while (!rReadXml.IsEndTag(...))\n"
  "}\n"
  "\n"
;
const char * pszSerialize =
  "void serialize(CWriteXml & rWriteXml, const std::string & rObject, const char * pszTag, bool fRoot)\n"
  "{\n"
  "  rWriteXml.StartTag(pszTag, fRoot);\n"
  "  rWriteXml.PutData(rObject.data(), rObject.length());\n"
  "  rWriteXml.EndTag(pszTag);\n"
  "}\n"
  "\n"
;
const char * pszDeserialize =
  "void deserialize(CReadXml & rReadXml, std::string & rObject, const char * pszTag, bool fRoot)\n"
  "{\n"
  "  if (fRoot)\n"
  "  {\n"
  "    if (!rReadXml.IsStartTag(pszTag, fRoot))\n"
  "      return;\n"
  "  }\n"
  "\n"
  "  const char *  pszText   = 0;\n"
  "  int           nLen      = 0;\n"
  "  bool          fMore     = false;\n"
  "\n"
  "  rObject.erase();\n"
  "  do\n"
  "  {\n"
  "    fMore = !rReadXml.GetData(pszText, nLen);\n"
  "    rObject.append(pszText, nLen);\n"
  "  } while (fMore);\n"
  "\n"
  "  if (!rReadXml.IsEndTag(pszTag))\n"
  "    return;\n"
  "}\n"
  "\n"
;
