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

#ifndef Registry_h
#define Registry_h

// disable exeption warning
#pragma warning( disable : 4290 )


#include <string>


class CRegExeption
{
public:
  CRegExeption(LONG lRetVal);
  ~CRegExeption();

  LONG GetReturnValue() const;

private:
  LONG  mlRetVal;
};



class CRegKey
{
public:
  CRegKey()   throw ();
  ~CRegKey()  throw ();

  void Create(
    const CRegKey         & rkParent,
    LPCTSTR                 pszKeyName,
    REGSAM                  samDesired  = KEY_ALL_ACCESS,
    DWORD                   dwOptions   = REG_OPTION_NON_VOLATILE,
    LPSECURITY_ATTRIBUTES   lpSecurityAttributes = NULL,
    LPTSTR                  lpClass     = ""
  )           throw (CRegExeption);

  void Open(
    const CRegKey   & rkParent,
    LPCTSTR           pszKeyName,
    REGSAM            samDesired  = KEY_ALL_ACCESS,
    ULONG             ulOptions   = 0
  )           throw (CRegExeption);

  void Close()
    throw (CRegExeption);

  void Delete(
    LPCTSTR pszKeyName
  ) const     throw (CRegExeption);

  void Flush() const      throw (CRegExeption);



  /* not implemented by overloded member functions
    REG_NONE
    REG_DWORD_LITTLE_ENDIAN
    REG_DWORD_BIG_ENDIAN
    REG_QWORD
    REG_QWORD_LITTLE_ENDIAN
    REG_MULTI_SZ
    REG_EXPAND_SZ
    REG_LINK
    REG_RESOURCE_LIST
    REG_BINARY
  */

  void QueryValue(
    LPCTSTR   pszValueName,
    bool    & rfValue
  ) const     throw (CRegExeption);

  void QueryValue(
    LPCTSTR   pszValueName,
    SHORT   & rsValue
  ) const     throw (CRegExeption);

  void QueryValue(
    LPCTSTR   pszValueName,
    WORD    & rwValue
  ) const     throw (CRegExeption);

  void QueryValue(
    LPCTSTR   pszValueName,
    INT     & rnValue
  ) const     throw (CRegExeption);

  void QueryValue(
    LPCTSTR   pszValueName,
    UINT    & runValue
  ) const     throw (CRegExeption);

  void QueryValue(
    LPCTSTR   pszValueName,
    LONG    & rlValue
  ) const     throw (CRegExeption);

  void QueryValue(
    LPCTSTR   pszValueName,
    DWORD   & rdwValue
  ) const     throw (CRegExeption);

  void QueryValue(
    LPCTSTR   pszValueName,
    float   & rfValue
  ) const     throw (CRegExeption);

  void QueryValue(
    LPCTSTR   pszValueName,
    double  & rdValue
  ) const     throw (CRegExeption);

  void QueryValue(
    LPCTSTR   pszValueName,
    LPTSTR    pszValue,
    DWORD   & rdwSize
  ) const     throw (CRegExeption);

  void QueryValue(
    LPCTSTR   pszValueName,
    std::string & strValue
  ) const     throw (CRegExeption);



  void SetValue(
    LPCTSTR   pszValueName,
    bool      fValue
  ) const     throw (CRegExeption);

  void SetValue(
    LPCTSTR   pszValueName,
    SHORT     sValue
  ) const     throw (CRegExeption);

  void SetValue(
    LPCTSTR   pszValueName,
    WORD      wValue
  ) const     throw (CRegExeption);

  void SetValue(
    LPCTSTR   pszValueName,
    INT       nValue
  ) const     throw (CRegExeption);

  void SetValue(
    LPCTSTR   pszValueName,
    UINT      unValue
  ) const     throw (CRegExeption);

  void SetValue(
    LPCTSTR   pszValueName,
    LONG      lValue
  ) const     throw (CRegExeption);

  void SetValue(
    LPCTSTR   pszValueName,
    DWORD     dwValue
  ) const     throw (CRegExeption);

  void SetValue(
    LPCTSTR   pszValueName,
    float     fValue
  ) const     throw (CRegExeption);

  void SetValue(
    LPCTSTR   pszValueName,
    double    dValue
  ) const     throw (CRegExeption);

  void SetValue(
    LPCTSTR   pszValueName,
    LPCTSTR   pszValue,
    DWORD     dwSize = -1
  ) const     throw (CRegExeption);

  void SetValue(
    LPCTSTR   pszValueName,
    const std::string & strValue
  ) const     throw (CRegExeption);



  void DeleteValue(
    LPCTSTR   pszValueName
  ) const     throw (CRegExeption);

private:
  HKEY  mhKey;

private:
  CRegKey(HKEY hKey)              throw ();
  CRegKey(const & CRegKey)        throw ();
  operator = (const & CRegKey)    throw ();
  LONG close()                    throw ();

public:
  static const CRegKey HKCU;  // HKEY_CURRENT_USER
  static const CRegKey HKLM;  // HKEY_LOCAL_MACHINE
  static const CRegKey HKCC;  // HKEY_CURRENT_CONFIG
  static const CRegKey HKCR;  // HKEY_CLASSES_ROOT
  static const CRegKey HKUS;  // HKEY_USERS
};






inline void CRegKey::QueryValue(
  LPCTSTR   pszValueName,
  bool    & rfValue
) const     throw (CRegExeption)
{
  DWORD dwValue;
  QueryValue(pszValueName, dwValue);
  rfValue = 0!=dwValue;
}



inline void CRegKey::QueryValue(
  LPCTSTR   pszValueName,
  SHORT   & rsValue
) const     throw (CRegExeption)
{
  DWORD dwValue;
  QueryValue(pszValueName, dwValue);
  rsValue = static_cast<SHORT>(dwValue);
}



inline void CRegKey::QueryValue(
  LPCTSTR   pszValueName,
  WORD    & rwValue
) const     throw (CRegExeption)
{
  DWORD dwValue;
  QueryValue(pszValueName, dwValue);
  rwValue = static_cast<WORD>(dwValue);
}



inline void CRegKey::QueryValue(
  LPCTSTR   pszValueName,
  INT     & rnValue
) const     throw (CRegExeption)
{
  DWORD dwValue;
  QueryValue(pszValueName, dwValue);
  rnValue = static_cast<INT>(dwValue);
}



inline void CRegKey::QueryValue(
  LPCTSTR   pszValueName,
  UINT    & runValue
) const     throw (CRegExeption)
{
  DWORD dwValue;
  QueryValue(pszValueName, dwValue);
  runValue = static_cast<UINT>(dwValue);
}



inline void CRegKey::QueryValue(
  LPCTSTR   pszValueName,
  LONG    & rlValue
) const     throw (CRegExeption)
{
  DWORD dwValue;
  QueryValue(pszValueName, dwValue);
  rlValue = static_cast<LONG>(dwValue);
}






inline void CRegKey::SetValue(
  LPCTSTR   pszValueName,
  bool      fValue
) const     throw (CRegExeption)
{
  SetValue(pszValueName, static_cast<DWORD>(fValue));
}



inline void CRegKey::SetValue(
  LPCTSTR   pszValueName,
  SHORT     sValue
) const     throw (CRegExeption)
{
  SetValue(pszValueName, static_cast<DWORD>(sValue));
}



inline void CRegKey::SetValue(
  LPCTSTR   pszValueName,
  WORD      wValue
) const     throw (CRegExeption)
{
  SetValue(pszValueName, static_cast<DWORD>(wValue));
}



inline void CRegKey::SetValue(
  LPCTSTR   pszValueName,
  INT       nValue
) const     throw (CRegExeption)
{
  SetValue(pszValueName, static_cast<DWORD>(nValue));
}



inline void CRegKey::SetValue(
  LPCTSTR   pszValueName,
  UINT      unValue
) const     throw (CRegExeption)
{
  SetValue(pszValueName, static_cast<DWORD>(unValue));
}



inline void CRegKey::SetValue(
  LPCTSTR   pszValueName,
  LONG      lValue
) const     throw (CRegExeption)
{
  SetValue(pszValueName, static_cast<DWORD>(lValue));
}



inline void CRegKey::SetValue(
  LPCTSTR   pszValueName,
  const std::string & strValue
) const     throw (CRegExeption)
{
  SetValue(pszValueName, strValue.c_str());
}


#endif // Registry_h
