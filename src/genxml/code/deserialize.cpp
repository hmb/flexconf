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
void deserialize(CReadXml & rReadXml, std::string & rObject, const char * pszTag, bool fRoot)
{
  if (fRoot)
  {
    if (!rReadXml.IsStartTag(pszTag, fRoot))
      return;
  }

  const char *  pszText   = 0;
  int           nLen      = 0;
  bool          fMore     = false;

  rObject.erase();
  do
  {
    fMore = !rReadXml.GetData(pszText, nLen);
    rObject.append(pszText, nLen);
  } while (fMore);

  if (!rReadXml.IsEndTag(pszTag))
    return;
}

