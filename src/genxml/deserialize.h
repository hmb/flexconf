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
  rObject = static_cast<short>(strtol(pBuffer, 0, 10));
}

inline void deserialize(const char * pBuffer, unsigned short & rObject)
{
  rObject = static_cast<unsigned short>(strtoul(pBuffer, 0, 10));
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
  {
    // we are done, this is an atomous value, with no subvalues
    rReadXml.SetStatus(CReadXml::eStatMissingEndtag);
  }
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

    rReadXml.SetStatus(CReadXml::eStatIlleagalStarttag);
    break;
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

    rReadXml.SetStatus(CReadXml::eStatIlleagalStarttag);
    break;
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
/*
      rObject[strKey] = _t;
/*/
      typename std::map<std::string, _T>::iterator fnd = rObject.find(strKey);
      if (fnd != rObject.end())
      {
        rObject.erase(fnd);
      }
      rObject.insert(std::pair<std::string, _T>(strKey, _t));
//*/
      continue;
    }

    rReadXml.SetStatus(CReadXml::eStatIlleagalStarttag);
    break;
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
/*
      rObject[_k] = _t;
/*/
      typename std::map<_K, _T>::iterator fnd = rObject.find(_k);
      if (fnd != rObject.end())
      {
        rObject.erase(fnd);
      }
      rObject.insert(std::pair<_K, _T>(_k, _t));
//*/
      continue;
    }

    rReadXml.SetStatus(CReadXml::eStatIlleagalStarttag);
    break;
  } // while (!rReadXml.IsEndTag(...))
}



template <class _T>
void deserialize(
  CReadXml & rReadXml, std::multimap<std::string, _T> & rObject,
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
      rObject.insert(std::pair<std::string, _T>(strKey, _t));
      continue;
    }
    rReadXml.SkipTag();
  } // while (!rReadXml.IsEndTag(...))
}



template <class _K, class _T>
void deserialize(
  CReadXml & rReadXml, std::multimap<_K, _T> & rObject,
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
      rObject.insert(std::pair<_K, _T>(_k, _t));
      continue;
    }
    rReadXml.SkipTag();
  } // while (!rReadXml.IsEndTag(...))
}



