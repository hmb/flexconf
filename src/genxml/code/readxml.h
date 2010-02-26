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
//#line 2 "../readxml.h"
#include <string.h>



class CReadXml
{
public:
  enum EStatus
  {
    eStatStart,
    eStatFinish,
    eStatXmlDeclTagstartMissing,      // the declaration tag start '<?xml...'is not found
    eStatXmlDeclTagendMissing,        // the declaration tag end '?>'is not found
    eStatIlleagalCharInTagName,       // a char other than alnum and '_' has been found in a tagname
    eStatIlleagalTextBetweenTags,     // text other than WS is found between closed value tags
    eStatIlleagalStarttag,            // an unexpected starttag has been found
    eStatMissingStarttag,             // there's no starttag where we expect one in a skip operation
    eStatMissingEndtag,               // the end tag for a value is missing
    eStatNonMatchingEndtag,           // an endtag is encountered, that does not match the nesting
    eStatSuperfluousEndtag,           // an endtag is encountered after the all enclosing tag has been closed
    eStatUnterminatedComment,         // a comment did not have the terminating '-->' tag
    eStatUnterminatedBegintag,        // a begintag did not have the terminating '>'
    eStatUnterminatedEndtag           // an endtag did not have the terminating '>'
  };

  bool IsEof()
  {
    return isEof();
  }

  bool IsStartTag(const char * pszTag, bool fRoot)
  {
    return isStartTag(pszTag, fRoot);
  }

  bool IsEndTag(const char * pszTag)
  {
    return isEndTag(pszTag);
  }

  bool GetData(const char * & pszData, int & nDataLen)
  {
    return getText(pszData, nDataLen);
  }

  void SkipTag()
  {
    if (mfStrict)
    {
      // skipping of unknown tags not allowed
      SetStatus(eStatIlleagalStarttag);
      return;
    }

    skipTag();
  }

  void EnableStrict(bool fEnable = true)
  {
    mfStrict = fEnable;
  }

/*
  bool Strict() const
  {
    return mfStrict;
  }
*/

  void EnableExceptions(bool fEnable = true)
  {
    mfExceptions = fEnable;
  }

/*
  bool Exceptions()
  {
    return mfExceptions;
  }
*/

  EStatus GetStatus() const
  {
    return meStatus;
  }

  void SetStatus(EStatus eStatus)
  {
    meStatus = eStatus;
    // :TODO: only if abortive status
    if (mfExceptions)
    {
      throw meStatus;
    }
  }

  int GetLine()
  {
    return mnLine;
  }

  int GetColumn()
  {
    return mnColumn;
  }

protected:
  CReadXml() :
    meStatus(eStatStart),
    mfStrict(false),
    mfExceptions(false),
    mnLine(1),
    mnColumn(1)
  {
  }

  virtual ~CReadXml()
  {
  }

  // dummy function that increases the line when '\n' is found
  bool incChar(char c)
  {
    if ('\n'==c)
    {
      mnLine++;
      mnColumn = 1;
    }
    else
    {
      mnColumn++;
    }

    return true;
  }

  // dummy function that increases the column
  int movChar(int n)
  {
    mnColumn +=n;
    return n;
  }

  void pushTag(const char * pszTag)
  {
    mstackTags.push_back(pszTag);
  }

  void pushTag(const char * pszTag, int nLen)
  {
    mstackTags.push_back(std::string(pszTag, nLen));
  }

  void popTag(const char * pszTag, unsigned int nLen = std::string::npos)
  {
    std::string strTag;

    if (std::string::npos == nLen)
      strTag = pszTag;
    else
      strTag.assign(pszTag, nLen);

    if (mstackTags.empty())
    {
      SetStatus(eStatSuperfluousEndtag);
    }
    else if (mstackTags.back() != strTag)
    {
      SetStatus(eStatNonMatchingEndtag);
    }
    mstackTags.pop_back();
  }

private:
  virtual bool isEof()                                            = 0;
  virtual bool isStartTag(const char * pszTag, bool fRoot)        = 0;
  virtual bool isEndTag(const char * pszTag)                      = 0;
  virtual bool getText(const char * & pszData, int & nDataLen)    = 0;
  virtual void skipTag()                                          = 0;

  EStatus   meStatus;
  bool      mfStrict;
  bool      mfExceptions;
  int       mnLine;
  int       mnColumn;
  std::list<std::string> mstackTags;
};

class CReadXmlPChar : public CReadXml
{
public:
  CReadXmlPChar(const char * pszXml) :
    mpszXml(pszXml)
  {
  }

  bool isEof()
  {
    return !*mpszXml;
  }

  bool isStartTag(const char * pszTag, bool fRoot)
  {
    if (fRoot)
    {
      // <?xml version="1.0" encoding="UTF-8" ?>
      if (0!=strncmp(mpszXml, "<?xml ", 6))
      {
        SetStatus(eStatXmlDeclTagstartMissing);
        return false;
      }
      mpszXml += movChar(6); // magic number: strlen("<?xml ")
      while ( *mpszXml && incChar(*mpszXml) && '?' != *mpszXml++);
      if ( incChar(*mpszXml) && '>' != *mpszXml++)
      {
        SetStatus(eStatXmlDeclTagendMissing);
        return false;
      }

      // <!DOCTYPE ...
      eatws();
      if (0==strncmp(mpszXml, "<!DOCTYPE ", 10))
      {
        mpszXml += movChar(10); // magic number: strlen("<!DOCTYPE ")
        while ( *mpszXml && incChar(*mpszXml) && '>' != *mpszXml++);
      }
    }

    eatws();

    int nTagLen = strlen(pszTag);

    if ('<' != mpszXml[0]                           ||
        0   != strncmp(mpszXml+1, pszTag, nTagLen)  ||
        '>' != mpszXml[nTagLen+1] )
    {
      return false;
    }
    mpszXml += movChar(nTagLen+2);
    pushTag(pszTag);
    return true;
  }

  bool isEndTag(const char * pszTag)
  {
    eatws();

    int nTagLen = strlen(pszTag);

    if ('<' != mpszXml[0]                           ||
        '/' != mpszXml[1]                           ||
        0   != strncmp(mpszXml+2, pszTag, nTagLen)  ||
        '>' != mpszXml[nTagLen+2] )
    {
      return false;
    }

    popTag(pszTag);
    mpszXml += movChar(nTagLen+3);
    return true;
  }

  bool getText(const char * & pszData, int & nDataLen)
  {
    if ('&' == *mpszXml)
    {
      // skip ampersand
      mpszXml++; movChar(1);

      if (0==strncmp(mpszXml, "gt;", 3))
      {
        pszData =   ">";
        mpszXml +=  movChar(3);
      }
      else if (0==strncmp(mpszXml, "lt;", 3))
      {
        pszData =   "<";
        mpszXml +=  movChar(3);
      }
      else if (0==strncmp(mpszXml, "amp;", 4))
      {
        pszData =   "&";
        mpszXml +=  movChar(4);
      }
      else if (0==strncmp(mpszXml, "quot;", 5))
      {
        pszData =   "\"";
        mpszXml +=  movChar(5);
      }
      else if (0==strncmp(mpszXml, "apos;", 5))
      {
        pszData =   "'";
        mpszXml +=  movChar(5);
      }
      else
      {
        // no known xml entity, use as plain text
        pszData =   "&";
      }
      nDataLen = 1;

      // finished, when new tag starts or string is at the end
      return  0   == *mpszXml     ||
              '<' == *mpszXml;
    }

    const char * pszNext = mpszXml;
    // find next delimiter
    while ( 0   != *pszNext &&
            '<' != *pszNext &&
            '&' != *pszNext )
    {
      incChar(*pszNext);
      pszNext++;
    }

    pszData   = mpszXml;
    nDataLen  = pszNext - mpszXml;
    mpszXml   = pszNext;

    return '&' != *pszNext;
  }

  void skipTag()
  {
/*
    int nStack = .size();
    if (!skipSingleTag(false))
    {
      // :TODO:
      return;
    }

    while (*mpszXml && nstack...
    {
      eatText();
      skipSingleTag();
    }
*/
  }

  bool skipSingleTag(bool fEndTag)
  {
    // not on the start of a tag ?
    if ('<' != *mpszXml)
    {
      SetStatus(eStatMissingStarttag);
      return false;
    }

    // skip over the '<'
    incChar(*mpszXml);
    mpszXml++;

    if (fEndTag && '/' != *mpszXml)
    {
      SetStatus(eStatMissingEndtag);
      return false;
    }
    else
    {
      // skip over the '/'
      incChar(*mpszXml);
      mpszXml++;
    }

    // remember start of tag
    const char * pszTag = mpszXml;

    // find end of tag
    while (  0 != *mpszXml   &&   '>' != *mpszXml  )
    {
      if (!isalnum(*mpszXml) && '_' != *mpszXml)
      {
        SetStatus(eStatIlleagalCharInTagName);
        return false;
      }

      incChar(*mpszXml);
      mpszXml++;
    }

    if (0 != *mpszXml)
    {
      SetStatus(eStatUnterminatedBegintag);
      return false;
    }

    if (fEndTag)
      popTag(pszTag, mpszXml-pszTag);
    else
      pushTag(pszTag, mpszXml-pszTag);
    return true;
  }

  void eatws()
  {
    do
    {
      // eat whitespace
      while (   ' '   == *mpszXml ||
                '\t'  == *mpszXml ||
                '\n'  == *mpszXml ||
                '\r'  == *mpszXml )
      {
        incChar(*mpszXml);
        mpszXml++;
      }
    } while (eatcomment());

    if (*mpszXml != '<')
      SetStatus(eStatIlleagalTextBetweenTags);
  }

  bool eatcomment()
  {
    // check start of comment
    if ( '<' == mpszXml[0]    &&
         '!' == mpszXml[1]    &&
         '-' == mpszXml[2]    &&
         '-' == mpszXml[3])
    {
      mpszXml += movChar(4);
    }
    else
      return false;

    for (;;)
    {
      // find end of comment
      while ( 0 != *mpszXml  &&  '-' != *mpszXml  &&  incChar(*mpszXml) )
        mpszXml++;

      // end of string
      if (!*mpszXml)
      {
        // unterminated comment
        SetStatus(eStatUnterminatedComment);
        return true;
      }

      incChar(*mpszXml);
      mpszXml++;

      // check end of comment
      if ( '-' == mpszXml[0]  &&
           '>' == mpszXml[1])
      {
        mpszXml += movChar(2);
        return true;
      }
    }
  }

protected:
  void setXml(const char * pszXml)
  {
    mpszXml = pszXml;
  }

private:
  const char * mpszXml;
};

class CReadXmlFile : public CReadXmlPChar
{
public:
  CReadXmlFile() :
    CReadXmlPChar(0)
  {
  }

  virtual ~CReadXmlFile()
  {
  }

  bool UseFile(const char * pszFilename)
  {
    setXml(0);
    mstrData.erase();

    FILE * f = fopen(pszFilename, "r");
    if (!f)
    {
      return false;
    }

    while (!feof(f))
    {
      const int BUFSIZE = 4096;
      char szBuffer[BUFSIZE];
      int nRead = fread(szBuffer, 1, BUFSIZE, f);
      mstrData.append(szBuffer, nRead);
    }

    fclose(f);
    setXml(mstrData.c_str());
    return true;
  }

  const std::string & GetData() { return mstrData; }

private:
  std::string mstrData;
};

