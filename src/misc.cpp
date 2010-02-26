/*
  flexconf - flexible configuration generator
  Copyright (C) 2003-2008 Holger Böhnke

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

#include "misc.h"
#include "config.h"
#include <string.h>



void replace(std::string & replace, const char * what, const char * with)
{
  std::string::size_type lenwhat = strlen(what);
  std::string::size_type lenwith = strlen(with);
  std::string::size_type pos = 0;

  while ( (pos=replace.find(what, pos)) != std::string::npos )
  {
    replace.replace(pos, lenwhat, with);
    pos += lenwith;
  }
}



/* TODO use these general function but write unittests first
int replaceVariables(
  const char              * source,
  const ContVariableType  & variables,
  std::string             & rstrReplace)
{
  int           nReplaced = 0;
  const char  * ctrPos    = source;
  const char  * ctrDollar = 0;
  const char  * ctrEnd    = source + strlen(source);

  for (; 0!=(ctrDollar=strchr(ctrPos, '$')); ctrPos=ctrDollar)
  {
    // append the part of the string preceeding the found dollar
    rstrReplace.append(ctrPos, ctrDollar-ctrPos);

    // no space left for '(...)'
    if (ctrEnd <= ctrDollar+3)
      break;

    switch (ctrDollar[1])
    {
    case '(':
      // skip character and '('
      ctrPos    = ctrDollar + 2;
      ctrDollar = strchr(ctrPos, ')');
      if (0 != ctrDollar)
      {
        // :TODO: use find_not_first_of or sth. like while (isalpha())...
        ContVariableCtrType fnd = variables.find(std::string(ctrPos, ctrDollar-ctrPos));
        if (fnd != variables.end())
        {
          rstrReplace.append(fnd->second);
          nReplaced++;
        }
        // skip trailing ')'
        ctrDollar++;
      }
      else
      {
        // error, could not find closing bracket
        return -1;
      }
      break;

    case '$':
      // append the character found
      rstrReplace.append(ctrDollar, 1);
      // skip found character and second dollar
      ctrDollar += 2;
      break;

    default:
      // append the character found
      rstrReplace.append(ctrDollar, 1);
      // skip character
      ctrDollar++;
      break;
    };
  }

  // append the rest of the string 'as is'
  if (0 != ctrPos)
    rstrReplace.append(ctrPos);

  return nReplaced;
}



int replaceVariables(
  const std::string       & source,
  const ContVariableType  & variables,
  std::string             & rstrReplace)
{
  int nReplaced = 0;

  std::string::size_type ctrPos     = 0;
  std::string::size_type ctrDollar  = 0;

  for (ctrPos=0; std::string::npos!=(ctrDollar=source.find('$', ctrPos)); ctrPos=ctrDollar)
  {
    // append the part of the string preceeding the found dollar
    rstrReplace.append(source.substr(ctrPos, ctrDollar-ctrPos));

    // no space left for '(...)'
    if (source.size() < ctrDollar+3)
      break;

    switch (source[ctrDollar+1])
    {
    case '(':
      // skip character and '('
      ctrPos    = ctrDollar + 2;
      ctrDollar = source.find(')', ctrPos);
      if (std::string::npos != ctrDollar)
      {
        // :TODO: use find_not_first_of or sth. like while (isalpha())...
        ContVariableCtrType fnd = variables.find(source.substr(ctrPos, ctrDollar-ctrPos));
        if (fnd != variables.end())
        {
          rstrReplace.append(fnd->second);
          nReplaced++;
        }
        // skip trailing ')'
        ctrDollar++;
      }
      else
      {
        // error, could not find closing bracket
        return -1;
      }
      break;

    case '$':
      // append the character found
      rstrReplace.append(1, source[ctrDollar]);
      // skip found character and second dollar
      ctrDollar += 2;
      break;

    default:
      // append the character found
      rstrReplace.append(1, source[ctrDollar]);
      // skip character
      ctrDollar++;
      break;
    };
  }

  // append the rest of the string 'as is'
  if (std::string::npos != ctrPos)
    rstrReplace.append(source.substr(ctrPos));

  return nReplaced;
}
*/
