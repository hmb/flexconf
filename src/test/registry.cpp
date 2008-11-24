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

#include <windows.h>
#include "Registry.h"



CRegExeption::CRegExeption(LONG lRetVal) :
  mlRetVal(lRetVal)
{
}



CRegExeption::~CRegExeption()
{
}



LONG CRegExeption::GetReturnValue() const
{
  return mlRetVal;
}






const CRegKey CRegKey::HKCU(HKEY_CURRENT_USER);
const CRegKey CRegKey::HKLM(HKEY_LOCAL_MACHINE);
const CRegKey CRegKey::HKCC(HKEY_CURRENT_CONFIG);
const CRegKey CRegKey::HKCR(HKEY_CLASSES_ROOT);
const CRegKey CRegKey::HKUS(HKEY_USERS);






CRegKey::CRegKey() :
  mhKey(NULL)
{
}

CRegKey::CRegKey(HKEY hKey) :
  mhKey(hKey)
{
}

CRegKey::~CRegKey()
{
  close();
}






void CRegKey::Create(
  const CRegKey         & rkParent,
  LPCTSTR                 pszKeyName,
  REGSAM                  samDesired,
  DWORD                   dwOptions,
  LPSECURITY_ATTRIBUTES   lpSecurityAttributes,
  LPTSTR                  lpClass
)
{
  if (NULL!=mhKey)
    throw CRegExeption(ERROR_SUCCESS);

  DWORD dwDisposition = 0L;
  LONG  lRetVal = RegCreateKeyEx(rkParent.mhKey, pszKeyName, 0L, lpClass, dwOptions,
    samDesired, lpSecurityAttributes, &mhKey, &dwDisposition);

  if ( ERROR_SUCCESS != lRetVal )
    throw CRegExeption(lRetVal);
}



void CRegKey::Open(
  const CRegKey   & rkParent,
  LPCTSTR           pszKeyName,
  REGSAM            samDesired,
  ULONG             ulOptions
)
{
  if (NULL!=mhKey)
    throw CRegExeption(ERROR_SUCCESS);

  LONG lRetVal = ::RegOpenKeyEx(rkParent.mhKey, pszKeyName, 0L, samDesired, &mhKey);

  if ( ERROR_SUCCESS != lRetVal )
    throw CRegExeption(lRetVal);
}



void CRegKey::Close()
{
  LONG lRetVal = close();

  if ( ERROR_SUCCESS != lRetVal )
    throw CRegExeption(lRetVal);

  mhKey = NULL;
}



LONG CRegKey::close()
{
  return NULL==mhKey?
    ERROR_SUCCESS :
    ::RegCloseKey(mhKey);
}



void CRegKey::Delete(
  LPCTSTR pszKeyName
) const throw (CRegExeption)
{
  LONG lRetVal = RegDeleteKey(mhKey, pszKeyName);

  if ( ERROR_SUCCESS != lRetVal )
    throw CRegExeption(lRetVal);
}






void CRegKey::QueryValue(
  LPCTSTR   pszValueName,
  DWORD   & rdwValue
) const     throw (CRegExeption)
{
  DWORD dwType  = REG_DWORD;
  DWORD dwSize  = sizeof(rdwValue);

  LONG lRetVal = RegQueryValueEx(mhKey, pszValueName, NULL, &dwType,
    reinterpret_cast<LPBYTE>(&rdwValue), &dwSize);

  if ( ERROR_SUCCESS != lRetVal )
    throw CRegExeption(lRetVal);
  if ( REG_DWORD != dwType )
    throw CRegExeption(-1);
}



void CRegKey::QueryValue(
  LPCTSTR   pszValueName,
  float   & rfValue
) const     throw (CRegExeption)
{
  DWORD dwType  = REG_BINARY;
  DWORD dwSize  = sizeof(rfValue);

  LONG lRetVal = RegQueryValueEx(mhKey, pszValueName, NULL, &dwType,
    reinterpret_cast<LPBYTE>(&rfValue), &dwSize);

  if ( ERROR_SUCCESS != lRetVal )
    throw CRegExeption(lRetVal);
  if ( REG_BINARY != dwType )
    throw CRegExeption(-1);
}



void CRegKey::QueryValue(
  LPCTSTR   pszValueName,
  double  & rdValue
) const     throw (CRegExeption)
{
  DWORD dwType  = REG_BINARY;
  DWORD dwSize  = sizeof(rdValue);

  LONG lRetVal = RegQueryValueEx(mhKey, pszValueName, NULL, &dwType,
    reinterpret_cast<LPBYTE>(&rdValue), &dwSize);

  if ( ERROR_SUCCESS != lRetVal )
    throw CRegExeption(lRetVal);
  if ( REG_BINARY != dwType )
    throw CRegExeption(-1);
}



void CRegKey::QueryValue(
  LPCTSTR   pszValueName,
  LPTSTR    pszValue,
  DWORD   & rdwSize
) const     throw (CRegExeption)
{
  DWORD dwType  = REG_SZ;

  LONG lRetVal = RegQueryValueEx(mhKey, pszValueName, NULL, &dwType,
    reinterpret_cast<LPBYTE>(pszValue), &rdwSize);

  if ( ERROR_SUCCESS != lRetVal )
    throw CRegExeption(lRetVal);
  if ( REG_SZ != dwType )
    throw CRegExeption(-1);
}



void CRegKey::QueryValue(
  LPCTSTR   pszValueName,
  std::string & strValue
) const     throw (CRegExeption)
{
  DWORD dwSize  = 0;
  RegQueryValueEx(mhKey, pszValueName, NULL, NULL, NULL, &dwSize);

  char * const szBuffer = new char[dwSize];
  DWORD dwType          = REG_SZ;

  LONG lRetVal = RegQueryValueEx(mhKey, pszValueName, NULL, &dwType,
                    reinterpret_cast<LPBYTE>(szBuffer), &dwSize);

  if ( ERROR_SUCCESS != lRetVal )
    throw CRegExeption(lRetVal);
  if ( REG_SZ != dwType )
    throw CRegExeption(-1);

  strValue = szBuffer;
  delete [] szBuffer;
}






void CRegKey::SetValue(
  LPCTSTR   pszValueName,
  DWORD     dwValue
) const     throw (CRegExeption)
{
  LONG lRetVal = RegSetValueEx(mhKey, pszValueName, 0L, REG_DWORD,
    reinterpret_cast<CONST BYTE *>(&dwValue), sizeof(dwValue));

  if ( ERROR_SUCCESS != lRetVal )
    throw CRegExeption(lRetVal);
}



void CRegKey::SetValue(
  LPCTSTR   pszValueName,
  float     fValue
) const     throw (CRegExeption)
{
  LONG lRetVal = RegSetValueEx(mhKey, pszValueName, 0L, REG_BINARY,
    reinterpret_cast<CONST BYTE *>(&fValue), sizeof(fValue));

  if ( ERROR_SUCCESS != lRetVal )
    throw CRegExeption(lRetVal);
}



void CRegKey::SetValue(
  LPCTSTR   pszValueName,
  double    dValue
) const     throw (CRegExeption)
{
  LONG lRetVal = RegSetValueEx(mhKey, pszValueName, 0L, REG_BINARY,
    reinterpret_cast<CONST BYTE *>(&dValue), sizeof(dValue));

  if ( ERROR_SUCCESS != lRetVal )
    throw CRegExeption(lRetVal);
}



void CRegKey::SetValue(
  LPCTSTR   pszValueName,
  LPCTSTR   pszValue,
  DWORD     dwSize
) const     throw (CRegExeption)
{
  if (-1==dwSize)
    dwSize = lstrlen(pszValue) +1;

  LONG lRetVal = RegSetValueEx(mhKey, pszValueName, 0L, REG_SZ,
    reinterpret_cast<CONST BYTE *>(pszValue), dwSize);

  if ( ERROR_SUCCESS != lRetVal )
    throw CRegExeption(lRetVal);
}






void CRegKey::DeleteValue(
  LPCTSTR pszValueName
) const throw (CRegExeption)
{
  LONG lRetVal = ::RegDeleteValue(mhKey, pszValueName);

  if ( ERROR_SUCCESS != lRetVal )
    throw CRegExeption(lRetVal);
}
