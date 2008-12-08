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
#ifdef _MSC_VER
  #define snprintf _snprintf
#endif

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
  bool operator >  (const SLongHex & cmp) const { return mulHex >  cmp.mulHex; }
  bool operator <  (const SLongHex & cmp) const { return mulHex <  cmp.mulHex; }
  bool operator != (const SLongHex & cmp) const { return mulHex != cmp.mulHex; }

  unsigned long operator = (unsigned long ulHex) { return mulHex=ulHex; }
  operator unsigned long () const { return mulHex; }
};

