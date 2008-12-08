//   flexconf - flexible configuration generator
//   Copyright (C) 2008 Holger Böhnke
//
//   This file is part of flexconf.
//
//   Flexconf is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//
//
const int IDENT_WIDTH = 2;

class CWriteXml
{
public:
  virtual ~CWriteXml()
  {
  }

  void StartTag(const char * pszTag, bool fRoot)
  {
    startTag(pszTag, fRoot);
  }

  void EndTag(const char * pszTag)
  {
    endTag(pszTag);
  }

  void PutData(const char * pszData, int nDataLen = 0x7FFF)
  {
    putData(pszData, nDataLen);
  }

private:
  virtual void startTag(const char * pszTag, bool fRoot)            = 0;
  virtual void endTag(const char * pszTag)                          = 0;
  virtual void putData(const char * pszData, int nDataLen = 0x7FFF) = 0;
};

class CWriteXmlString : public CWriteXml
{
public:
  CWriteXmlString(std::string & strWrite) :
    mstrWrite(strWrite),
    mnDepth(0),
    mfStartTag(false),
    mfLf(false)
  {
  }

  void startTag(const char * pszTag, bool fRoot)
  {
    if (fRoot)
    {
      mstrWrite += "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n";
      mfLf      = true;
    }

    if (mfStartTag)
    {
      mstrWrite += '\n';
      mfLf = true;
    }

    indent();
    mstrWrite += '<';
    mstrWrite += pszTag;
    mstrWrite += '>';
    mfStartTag = true;
    mnDepth++;
  }

  void endTag(const char * pszTag)
  {
    mnDepth--;
    indent();
    mstrWrite += "</";
    mstrWrite += pszTag;
    mstrWrite += ">\n";
    mfLf      = true;
    mfStartTag  = false;
  }

  void putData(const char * pszData, int nDataLen)
  {
    const char *  pszPos  = pszData;

    while (*pszPos && pszPos-pszData < nDataLen)
    {
      if ('<' == *pszPos)
      {
        mstrWrite += "&lt;";
        pszPos++;
        continue;
      }

      if ('>' == *pszPos)
      {
        mstrWrite += "&gt;";
        pszPos++;
        continue;
      }

      if ('&' == *pszPos)
      {
        mstrWrite += "&amp;";
        pszPos++;
        continue;
      }

      if ('"' == *pszPos)
      {
        mstrWrite += "&quot;";
        pszPos++;
        continue;
      }

      if ('\'' == *pszPos)
      {
        mstrWrite += "&apos;";
        pszPos++;
        continue;
      }

      const char *  pszEnd  = pszPos;

      // find end or entity
      while ( pszEnd-pszData < nDataLen   &&
              0   != *pszEnd    &&
              '<' != *pszEnd    &&
              '>' != *pszEnd    &&
              '"' != *pszEnd    &&
              '\''!= *pszEnd    &&
              '&' != *pszEnd )
      {
        pszEnd++;
      }

      mstrWrite.append(pszPos, pszEnd-pszPos);
      pszPos = pszEnd;
    }

    mfStartTag  = false;
  }

  void indent()
  {
    if (mfLf)
    {
      mstrWrite.append(mnDepth*IDENT_WIDTH, ' ');
      mfLf = false;
    }
  }

private:
  std::string & mstrWrite;
  int           mnDepth;
  bool          mfStartTag;
  bool          mfLf;
};

