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

#include <list>
#include <string>
#include <stdio.h>
#include "code/readxml.h"


static const char szXml[] =
{
  "<?xml encoding=\"kldsja\"  ?>     "
  "<!DOCTYPE balah laber fasel>      "
  "<test>    "
  "f kljdf kl &gt; jsdfhk"
  "</test>"
};












int main(int argc, const char * argv[])
{
  CReadXmlPChar xmlReader(szXml);

  if (xmlReader.IsStartTag("test", true))
  {
    printf("start tag\n");

    const char  * pszData = 0;
    int           nLen    = 0;

    while (!xmlReader.GetData(pszData, nLen))
      printf("%.*s\n", nLen, pszData);

    if (xmlReader.IsEndTag("test"))
      printf("end tag\n");
    else
      printf("no end tag\n");
  }
  else
    printf("no start tag\n");

  return 0;
}
