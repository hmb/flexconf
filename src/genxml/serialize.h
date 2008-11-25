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
  snprintf(pBuffer, nBufSize, "%f", static_cast<double>(rObject));
}

inline void serialize(char * pBuffer, int nBufSize, const double & rObject)
{
  snprintf(pBuffer, nBufSize, "%f", rObject);
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
  for (typename std::set<_K>::const_iterator itr=rObject.begin(); itr!=rObject.end(); itr++)
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
  for (typename std::list<_T>::const_iterator itr=rObject.begin(); itr!=rObject.end(); itr++)
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
  for (typename std::map<std::string, _T>::const_iterator itr=rObject.begin(); itr!=rObject.end(); itr++)
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
  for (typename std::map<_K, _T>::const_iterator itr=rObject.begin(); itr!=rObject.end(); itr++)
  {
    // first serialize the key to a string
    const int BUFSIZE = 1024;
    char szBuffer[BUFSIZE];
    serialize(szBuffer, BUFSIZE, itr->first);
    std::string strBuffer(szBuffer);
    // serialize the object with a string key
    serialize(rWriteXml, itr->second, pszTagItem, false, pszTagId, &strBuffer);
  }
  rWriteXml.EndTag(pszTag);
}



// serialize a std::multimap<std::string, _T> object
template <class _T>
void serialize(
  CWriteXml & rWriteXml, const std::multimap<std::string, _T> & rObject,
  const char * pszTag, const char * pszTagItem, const char * pszTagId,
  bool fRoot = true)
{
  rWriteXml.StartTag(pszTag, fRoot);
  for (typename std::multimap<std::string, _T>::const_iterator itr=rObject.begin(); itr!=rObject.end(); itr++)
  {
    serialize(rWriteXml, itr->second, pszTagItem, false, pszTagId, &itr->first);
  }
  rWriteXml.EndTag(pszTag);
}



// serialize any other multimap object for witch a key serialize function exists
template <class _K, class _T>
void serialize(
  CWriteXml & rWriteXml, const std::multimap<_K, _T> & rObject,
  const char * pszTag, const char * pszTagItem, const char * pszTagId,
  bool fRoot = true)
{
  rWriteXml.StartTag(pszTag, fRoot);
  for (typename std::multimap<_K, _T>::const_iterator itr=rObject.begin(); itr!=rObject.end(); itr++)
  {
    // first serialize the key to a string
    const int BUFSIZE = 1024;
    char szBuffer[BUFSIZE];
    serialize(szBuffer, BUFSIZE, itr->first);
    std::string strBuffer(szBuffer);
    // serialize the object with a string key
    serialize(rWriteXml, itr->second, pszTagItem, false, pszTagId, &strBuffer);
  }
  rWriteXml.EndTag(pszTag);
}



