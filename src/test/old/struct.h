#ifndef _Struct_h_
#define _Struct_h_

#ifdef _MSC_VER
#define snprintf _snprintf
#pragma warning(disable: 4786)
#endif



#include <string>
#include <list>
#include <set>
#include <map>
#include <stdio.h>



class CReadXml;
class CWriteXml;



struct SLongHex
{
  SLongHex() { }
  SLongHex(unsigned long ulHex) : mulHex(ulHex) { }

  unsigned long mulHex;

  bool operator == (const SLongHex & cmp) const { return mulHex == cmp.mulHex; }
  bool operator >= (const SLongHex & cmp) const { return mulHex >= cmp.mulHex; }
  bool operator <= (const SLongHex & cmp) const { return mulHex <= cmp.mulHex; }
  bool operator <  (const SLongHex & cmp) const { return mulHex >  cmp.mulHex; }
  bool operator >  (const SLongHex & cmp) const { return mulHex <  cmp.mulHex; }
  bool operator != (const SLongHex & cmp) const { return mulHex != cmp.mulHex; }

  unsigned long operator = (unsigned long ulHex) { return mulHex=ulHex; }
  operator unsigned long () const { return mulHex; }
};



#include "test.h"
void serialize(CWriteXml & rWriteXml, const SData & rObject, const char * pszTag = 0, bool fRoot = true,
  const char * pszIdTag = 0, const std::string * pstrIdValue = 0);
void deserialize(CReadXml & rReadXml, SData & rObject, const char * pszTag =0, bool fRoot = true,
  const char * pszIdTag = 0, std::string * pstrIdValue = 0);

void serialize(CWriteXml & rWriteXml, const STestBase & rObject, const char * pszTag = 0, bool fRoot = true,
  const char * pszIdTag = 0, const std::string * pstrIdValue = 0);
void deserialize(CReadXml & rReadXml, STestBase & rObject, const char * pszTag =0, bool fRoot = true,
  const char * pszIdTag = 0, std::string * pstrIdValue = 0);



const int IDENT_WIDTH = 2;

class CWriteXml
{
public:
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



class CReadXml
{
public:
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
    return getData(pszData, nDataLen);
  }

  void SkipTag()
  {
    skipTag();
  }


private:
  virtual bool isEof()                                            = 0;
  virtual bool isStartTag(const char * pszTag, bool fRoot)        = 0;
  virtual bool isEndTag(const char * pszTag)                      = 0;
  virtual bool getData(const char * & pszData, int & nDataLen)    = 0;
  virtual void skipTag()                                          = 0;
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
        return false;
      mpszXml += 6;
      while ( *mpszXml && '?' != *mpszXml++);
      if ( '>' != *mpszXml++)
        return false;

      // <!DOCTYPE ...
      eatws();
      if (0==strncmp(mpszXml, "<!DOCTYPE ", 10))
      {
        mpszXml += 10;
        while ( *mpszXml && '>' != *mpszXml++);
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
    mpszXml += nTagLen+2;
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
    mpszXml += nTagLen+3;
    return true;
  }

  bool getData(const char * & pszData, int & nDataLen)
  {
    if ('&' == *mpszXml)
    {
      // skip ampersand
      mpszXml++;

      if (0==strncmp(mpszXml, "gt;", 3))
      {
        pszData =   ">";
        mpszXml +=  3;
      }
      else if (0==strncmp(mpszXml, "lt;", 3))
      {
        pszData =   "<";
        mpszXml +=  3;
      }
      else if (0==strncmp(mpszXml, "amp;", 4))
      {
        pszData =   "&";
        mpszXml +=  4;
      }
      else if (0==strncmp(mpszXml, "quot;", 5))
      {
        pszData =   "\"";
        mpszXml +=  5;
      }
      else if (0==strncmp(mpszXml, "apos;", 5))
      {
        pszData =   "'";
        mpszXml +=  5;
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
      pszNext++;
    }

    pszData   = mpszXml;
    nDataLen  = pszNext - mpszXml;
    mpszXml   = pszNext;

    return '&' != *pszNext;
  }

  void skipTag()
  {
    // not eof then skip over the '<', if we are on one else skip non '<'
    // skip over the '<'
    if (*mpszXml)
      mpszXml++;

    // find next start or end tag
    while (  0 != *mpszXml   &&   '<' != *mpszXml  )
    {
      mpszXml++;
    }
  }

  void eatws()
  {
    while ( 0 != *mpszXml &&
            (
              ' '   == *mpszXml ||
              '\t'  == *mpszXml ||
              '\n'  == *mpszXml ||
              '\r'  == *mpszXml
            )
          )
    {
      mpszXml++;
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



inline void serialize(char * pBuffer, int nBufSize, const bool & rObject)
{
  snprintf(pBuffer, nBufSize, rObject? "1" : "0");
}

inline void serialize(char * pBuffer, int nBufSize, const short & rObject)
{
  snprintf(pBuffer, nBufSize, "%hd", rObject);
}

inline void serialize(char * pBuffer, int nBufSize, const unsigned short & rObject)
{
  snprintf(pBuffer, nBufSize, "%hu", rObject);
}

inline void serialize(char * pBuffer, int nBufSize, const int & rObject)
{
  snprintf(pBuffer, nBufSize, "%d", rObject);
}

inline void serialize(char * pBuffer, int nBufSize, const unsigned int & rObject)
{
  snprintf(pBuffer, nBufSize, "%u", rObject);
}

inline void serialize(char * pBuffer, int nBufSize, const long & rObject)
{
  snprintf(pBuffer, nBufSize, "%ld", rObject);
}

inline void serialize(char * pBuffer, int nBufSize, const unsigned long & rObject)
{
  snprintf(pBuffer, nBufSize, "%lu", rObject);
}

inline void serialize(char * pBuffer, int nBufSize, const float & rObject)
{
  snprintf(pBuffer, nBufSize, "%f", rObject);
}

inline void serialize(char * pBuffer, int nBufSize, const double & rObject)
{
  snprintf(pBuffer, nBufSize, "%lf", rObject);
}

inline void serialize(char * pBuffer, int nBufSize, const SLongHex & rObject)
{
  snprintf(pBuffer, nBufSize, "%lX", rObject.mulHex);
}



// serialize a std::string object
void serialize(CWriteXml & rWriteXml, const std::string &     rObject, const char * pszTag, bool fRoot = true);

// serialize any of the objects for that an above function is defined
template <class _T>
void serialize(CWriteXml & rWriteXml, const _T & rObject, const char * pszTag, bool fRoot = true)
{
  rWriteXml.StartTag(pszTag, fRoot);
  char szBuffer[80];
  serialize(szBuffer, 80, rObject);
  rWriteXml.PutData(szBuffer);
  rWriteXml.EndTag(pszTag);
}



// serialize any set object for witch a key serialize function exists
template <class _K>
void serialize(
  CWriteXml & rWriteXml, const std::set<_K> & rObject,
  const char * pszTag, const char * pszTagItem, bool fRoot = true)
{
  rWriteXml.StartTag(pszTag, fRoot);
  for (std::set<_K>::const_iterator itr=rObject.begin(); itr!=rObject.end(); itr++)
  {
    // serialize the key object
    serialize(rWriteXml, *itr, pszTagItem, false);
  }
  rWriteXml.EndTag(pszTag);
}



// serialize any list object for witch a serialize function exists
template <class _T>
void serialize(
  CWriteXml & rWriteXml, const std::list<_T> & rObject,
  const char * pszTag, const char * pszTagItem, bool fRoot = true)
{
  rWriteXml.StartTag(pszTag, fRoot);
  for (std::list<_T>::const_iterator itr=rObject.begin(); itr!=rObject.end(); itr++)
  {
    // serialize the key object
    serialize(rWriteXml, *itr, pszTagItem, false);
  }
  rWriteXml.EndTag(pszTag);
}



// serialize a std::map<std::string, _T> object
template <class _T>
void serialize(
  CWriteXml & rWriteXml, const std::map<std::string, _T> & rObject,
  const char * pszTag, const char * pszTagItem, const char * pszTagId,
  bool fRoot = true)
{
  rWriteXml.StartTag(pszTag, fRoot);
  for (std::map<std::string, _T>::const_iterator itr=rObject.begin(); itr!=rObject.end(); itr++)
  {
    serialize(rWriteXml, itr->second, pszTagItem, false, pszTagId, &itr->first);
  }
  rWriteXml.EndTag(pszTag);
}



// serialize any other map object for witch a key serialize function exists
template <class _K, class _T>
void serialize(
  CWriteXml & rWriteXml, const std::map<_K, _T> & rObject,
  const char * pszTag, const char * pszTagItem, const char * pszTagId,
  bool fRoot = true)
{
  rWriteXml.StartTag(pszTag, fRoot);
  for (std::map<_K, _T>::const_iterator itr=rObject.begin(); itr!=rObject.end(); itr++)
  {
    // first serialize the key to a string
    char szBuffer[80];
    serialize(szBuffer, 80, itr->first);
    std::string strBuffer(szBuffer);
    // serialize the object with a string key
    serialize(rWriteXml, itr->second, pszTagItem, false, pszTagId, &strBuffer);
  }
  rWriteXml.EndTag(pszTag);
}



inline void deserialize(const char * pBuffer, bool & rObject)
{
  rObject =
    0==strncmp(pBuffer, "true", 4) ||
    0==strncmp(pBuffer, "yes", 3) ||
    0==strncmp(pBuffer, "on", 2) ||
    0==strncmp(pBuffer, "1", 1);
}

inline void deserialize(const char * pBuffer, short & rObject)
{
  rObject = strtol(pBuffer, 0, 10);
}

inline void deserialize(const char * pBuffer, unsigned short & rObject)
{
  rObject = strtoul(pBuffer, 0, 10);
}

inline void deserialize(const char * pBuffer, int & rObject)
{
  rObject = strtol(pBuffer, 0, 10);
}

inline void deserialize(const char * pBuffer, unsigned int & rObject)
{
  rObject = strtoul(pBuffer, 0, 10);
}

inline void deserialize(const char * pBuffer, long & rObject)
{
  rObject = strtol(pBuffer, 0, 10);
}

inline void deserialize(const char * pBuffer, unsigned long & rObject)
{
  rObject = strtoul(pBuffer, 0, 10);
}

inline void deserialize(const char * pBuffer, float & rObject)
{
  rObject = atof(pBuffer);
}

inline void deserialize(const char * pBuffer, double & rObject)
{
  rObject = atof(pBuffer);
}

inline void deserialize(const char * pBuffer, SLongHex & rObject)
{
  rObject.mulHex = strtoul(pBuffer, 0, 16);
}



void deserialize(CReadXml & rReadXml, std::string & rObject, const char * pszTag, bool fRoot = true);

// deserialize types without a base or ordinal integers in decimal system
template <class _T>
void deserialize(CReadXml & rReadXml, _T & rObject, const char * pszTag, bool fRoot = true)
{
  if (fRoot)
  {
    if (!rReadXml.IsStartTag(pszTag, fRoot))
      return;
  }
  const char *  pszText   = 0;
  int           nLen      = 0;
  rReadXml.GetData(pszText, nLen);
  deserialize(pszText, rObject);
  if (!rReadXml.IsEndTag(pszTag))
    return;
}



template <class _K>
void deserialize(
  CReadXml & rReadXml, std::set<_K> & rObject,
  const char * pszTag, const char * pszTagItem, bool fRoot = true)
{
  if (fRoot)
  {
    if (!rReadXml.IsStartTag(pszTag, fRoot))
      return;
  }
  while (!rReadXml.IsEof() && !rReadXml.IsEndTag(pszTag))
  {
    if (rReadXml.IsStartTag(pszTagItem, false))
    {
      _K _k;
      deserialize(rReadXml, _k, pszTagItem, false);
      rObject.insert(_k);
      continue;
    }
    rReadXml.SkipTag();
  } // while (!rReadXml.IsEndTag(...))
}



template <class _T>
void deserialize(
  CReadXml & rReadXml, std::list<_T> & rObject,
  const char * pszTag, const char * pszTagItem, bool fRoot = true)
{
  if (fRoot)
  {
    if (!rReadXml.IsStartTag(pszTag, fRoot))
      return;
  }
  while (!rReadXml.IsEof() && !rReadXml.IsEndTag(pszTag))
  {
    if (rReadXml.IsStartTag(pszTagItem, false))
    {
      _T _t;
      deserialize(rReadXml, _t, pszTagItem, false);
      rObject.push_back(_t);
      continue;
    }
    rReadXml.SkipTag();
  } // while (!rReadXml.IsEndTag(...))
}



template <class _T>
void deserialize(
  CReadXml & rReadXml, std::map<std::string, _T> & rObject,
  const char * pszTag, const char * pszTagItem, const char * pszTagId,
  bool fRoot = true)
{
  if (fRoot)
  {
    if (!rReadXml.IsStartTag(pszTag, fRoot))
      return;
  }
  while (!rReadXml.IsEof() && !rReadXml.IsEndTag(pszTag))
  {
    if (rReadXml.IsStartTag(pszTagItem, false))
    {
      std::string strKey;
      _T _t;
      deserialize(rReadXml, _t, pszTagItem, false, pszTagId, &strKey);
      rObject[strKey] = _t;
      continue;
    }
    rReadXml.SkipTag();
  } // while (!rReadXml.IsEndTag(...))
}



template <class _K, class _T>
void deserialize(
  CReadXml & rReadXml, std::map<_K, _T> & rObject,
  const char * pszTag, const char * pszTagItem, const char * pszTagId,
  bool fRoot = true)
{
  if (fRoot)
  {
    if (!rReadXml.IsStartTag(pszTag, fRoot))
      return;
  }
  while (!rReadXml.IsEof() && !rReadXml.IsEndTag(pszTag))
  {
    if (rReadXml.IsStartTag(pszTagItem, false))
    {
      std::string strKey;
      _T _t;
      deserialize(rReadXml, _t, pszTagItem, false, pszTagId, &strKey);
      _K _k;
      deserialize(strKey.c_str(), _k);
      rObject[_k] = _t;
      continue;
    }
    rReadXml.SkipTag();
  } // while (!rReadXml.IsEndTag(...))
}



#endif // _Struct_h_
