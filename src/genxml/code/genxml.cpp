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
/* begin section: HdrProlog */
#ifndef _Struct_h_
#define _Struct_h_

#ifdef _MSC_VER
  #define snprintf _snprintf
  #pragma warning(disable: 4786 4996)
#endif

#include <string>
#include <list>
#include <set>
#include <map>
#include <stdio.h>

/* end section */



/* begin section: HdrFile */
#include "$(headerfile)"
/* end section */



/* begin section: HdrStruct */
void serialize(CWriteXml & rWriteXml, const $(name) & rObject, const char * pszTag = 0, bool fRoot = true,
  const char * pszIdTag = 0, const std::string * pstrIdValue = 0);
void deserialize(CReadXml & rReadXml, $(name) & rObject, const char * pszTag =0, bool fRoot = true,
  const char * pszIdTag = 0, std::string * pstrIdValue = 0);

/* end section */



/* begin section: HdrEpilog */
#endif // _Struct_h_
/* end section */






/* begin section: SerProlog */
#include "struct.h"

/* end section */



/* begin section: SerStructBegin */
void serialize(CWriteXml & rWriteXml, const $(name) & rObject, const char * pszTag, bool fRoot,
  const char * pszIdTag, const std::string * pstrIdValue)
{
  if (!pszTag)
    pszTag="$(alias)";
  rWriteXml.StartTag(pszTag, fRoot);
  if (pszIdTag && pstrIdValue)
  {
    serialize(rWriteXml, *pstrIdValue, pszIdTag, false);
  }
/* end section */



/* begin section: SerStructVarDecl */
  serialize(rWriteXml, rObject.$(name), "$(alias)", false);
/* end section */



/* begin section: SerStructVarDeclVector */
  rWriteXml.StartTag("$(alias)", false);
  {for (int n=0; n<$(size); n++)
  {
    serialize(rWriteXml, rObject.$(name)[n], "$(item)", false);
  }}
  rWriteXml.EndTag("$(alias)");
/* end section */



/* begin section: SerStructVarDeclList */
  serialize(rWriteXml, rObject.$(name), "$(alias)", "$(item)", false);
/* end section */



/* begin section: SerStructVarDeclMap */
  serialize(rWriteXml, rObject.$(name), "$(alias)", "$(item)", "$(id)", false);
/* end section */



/* begin section: SerStructEnd */
  rWriteXml.EndTag(pszTag);
}

/* end section */






/* begin section: DesProlog */
#include "struct.h"
#include <stdlib.h>

/* end section */



/* begin section: DesStructBegin */
void deserialize(CReadXml & rReadXml, $(name) & rObject, const char * pszTag, bool fRoot,
  const char * pszIdTag, std::string * pstrIdValue)
{
  if (!pszTag)
    pszTag="$(alias)";
  if (fRoot)
  {
    if (!rReadXml.IsStartTag(pszTag, fRoot))
      return;
  }
  while (!rReadXml.IsEof() && !rReadXml.IsEndTag(pszTag))
  {
    if (pszIdTag && pstrIdValue && rReadXml.IsStartTag(pszIdTag, false))
    {
      deserialize(rReadXml, *pstrIdValue, pszIdTag, false);
      continue;
    }
/* end section */



/* begin section: DesStructVarDecl */
    if (rReadXml.IsStartTag("$(alias)", false))
    {
      deserialize(rReadXml, rObject.$(name), "$(alias)", false);
      continue;
    }
/* end section */



/* begin section: DesStructVarDeclVector */
    if (rReadXml.IsStartTag("$(alias)", false))
    {
      int     _n   = 0;
      while (!rReadXml.IsEof() && !rReadXml.IsEndTag("$(alias)"))
      {
        if (_n<$(size) && rReadXml.IsStartTag("$(item)", false))
        {
          deserialize(rReadXml, rObject.$(name)[_n++], "$(item)", false);
          continue;
        }
        rReadXml.SkipTag();
      } // while (!rReadXml.IsEndTag(...))
      continue;
    }
/* end section */



/* begin section: DesStructVarDeclList */
    if (rReadXml.IsStartTag("$(alias)", false))
    {
      deserialize(rReadXml, rObject.$(name), "$(alias)", "$(item)", false);
      continue;
    }
/* end section */



/* begin section: DesStructVarDeclMap */
    if (rReadXml.IsStartTag("$(alias)", false))
    {
      deserialize(rReadXml, rObject.$(name), "$(alias)", "$(item)", "$(id)", false);
      continue;
    }
/* end section */



/* begin section: DesStructEnd */
    rReadXml.SkipTag();
  } // while (!rReadXml.IsEndTag(...))
}

/* end section */
