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

#include "genxml.h"
#include "config.h"



// strings held in progstr.cxx, generated from parser files with perl
extern const char * pszDisclaimer;
extern const char * pszTypes;
extern const char * pszHeader;
extern const char * pszSerialize;
extern const char * pszDeserialize;



CGeneratorXml::CGeneratorXml()
{
}



CGeneratorXml::~CGeneratorXml()
{
}



int CGeneratorXml::header()
{
  // write header declarations
  writeRep(pszDisclaimer, mfHeader);
  writeStr("\n", mfHeader);
  writeStr("#ifndef _Struct_h_\n", mfHeader);
  writeStr("#define _Struct_h_\n\n", mfHeader);
  writeStr("#ifdef _MSC_VER\n", mfHeader);
  writeStr("#define snprintf _snprintf\n", mfHeader);
  writeStr("#pragma warning(disable: 4786 4996)\n", mfHeader);
  writeStr("#endif\n", mfHeader);
  writeStr("\n\n\n", mfHeader);
  writeStr("#include <string>\n", mfHeader);
  writeStr("#include <list>\n", mfHeader);
  writeStr("#include <set>\n", mfHeader);
  writeStr("#include <map>\n", mfHeader);
  writeStr("#include <stdio.h>\n", mfHeader);
  writeStr("\n\n\n", mfHeader);
  writeStr(pszTypes, mfHeader);

  // write serializer
  writeRep(pszDisclaimer, mfSerialize);
  writeStr("\n", mfSerialize);
  writeStr("#include \"struct.h\"\n", mfSerialize);
//  writeStr("#include <stdio.h>\n", mfSerialize);

  // write deserializer
  writeRep(pszDisclaimer, mfDeserialize);
  writeStr("\n", mfDeserialize);
  writeStr("#include \"struct.h\"\n", mfDeserialize);
  writeStr("#include <stdlib.h>\n", mfDeserialize);
  return 0;
}



int CGeneratorXml::headerfile()
{
  writeRep("#include \"$(headerfile)\"\n", mfHeader);
  return 0;
}






void CGeneratorXml::writeStructBegin()
{
  /* declarations */
  writeRep("void serialize(CWriteXml & rWriteXml, const $(name) & rObject, const char * pszTag = 0, bool fRoot = true,\n", mfHeader);
  writeStr("  const char * pszIdTag = 0, const std::string * pstrIdValue = 0);\n", mfHeader);
  writeRep("void deserialize(CReadXml & rReadXml, $(name) & rObject, const char * pszTag =0, bool fRoot = true,\n", mfHeader);
  writeStr("  const char * pszIdTag = 0, std::string * pstrIdValue = 0);\n\n", mfHeader);

  /* start of struct serialize function */
  writeStr("\n\n\n", mfSerialize);
  writeRep("void serialize(CWriteXml & rWriteXml, const $(name) & rObject, const char * pszTag, bool fRoot,\n", mfSerialize);
  writeStr("  const char * pszIdTag, const std::string * pstrIdValue)\n", mfSerialize);
  writeStr("{\n", mfSerialize);
  writeStr("  if (!pszTag)\n", mfSerialize);
  writeRep("    pszTag=\"$(alias)\";\n", mfSerialize);
  writeStr("  rWriteXml.StartTag(pszTag, fRoot);\n", mfSerialize);
  writeStr("  if (pszIdTag && pstrIdValue)\n", mfSerialize);
  writeStr("  {\n", mfSerialize);
  writeStr("    serialize(rWriteXml, *pstrIdValue, pszIdTag, false);\n", mfSerialize);
  writeStr("  }\n", mfSerialize);

  /* start of struct deserialize function */
  writeStr("\n\n\n", mfDeserialize);
  writeRep("void deserialize(CReadXml & rReadXml, $(name) & rObject, const char * pszTag, bool fRoot,\n", mfDeserialize);
  writeStr("  const char * pszIdTag, std::string * pstrIdValue)\n", mfDeserialize);
  writeStr("{\n", mfDeserialize);
  writeStr("  if (!pszTag)\n", mfDeserialize);
  writeRep("    pszTag=\"$(alias)\";\n", mfDeserialize);
  writeStr("  if (fRoot)\n", mfDeserialize);
  writeStr("  {\n", mfDeserialize);
  writeStr("    if (!rReadXml.IsStartTag(pszTag, fRoot))\n", mfDeserialize);
  writeStr("      return;\n", mfDeserialize);
  writeStr("  }\n", mfDeserialize);
  writeStr("  while (!rReadXml.IsEof() && !rReadXml.IsEndTag(pszTag))\n", mfDeserialize);
  writeStr("  {\n", mfDeserialize);
  writeStr("    if (pszIdTag && pstrIdValue && rReadXml.IsStartTag(pszIdTag, false))\n", mfDeserialize);
  writeStr("    {\n", mfDeserialize);
  writeStr("      deserialize(rReadXml, *pstrIdValue, pszIdTag, false);\n", mfDeserialize);
  writeStr("      continue;\n", mfDeserialize);
  writeStr("    }\n", mfDeserialize);
}



void CGeneratorXml::writeVarDecl()
{
  // write serializer
  writeRep("  serialize(rWriteXml, rObject.$(name), \"$(alias)\", false);\n", mfSerialize);

  // write deserializer
  writeRep("    if (rReadXml.IsStartTag(\"$(alias)\", false))\n", mfDeserialize);
  writeStr("    {\n", mfDeserialize);
  writeRep("      deserialize(rReadXml, rObject.$(name), \"$(alias)\", false);\n", mfDeserialize);
  writeStr("      continue;\n", mfDeserialize);
  writeStr("    }\n", mfDeserialize);
}



void CGeneratorXml::writeVarDeclVector()
{
  // write serializer
  writeRep("  rWriteXml.StartTag(\"$(alias)\", false);\n", mfSerialize);
  writeRep("  {for (int n=0; n<$(size); n++)\n", mfSerialize);
  writeStr("  {\n", mfSerialize);
  writeRep("    serialize(rWriteXml, rObject.$(name)[n], \"$(item)\", false);\n", mfSerialize);
  writeStr("  }}\n", mfSerialize);
  writeRep("  rWriteXml.EndTag(\"$(alias)\");\n", mfSerialize);

  // write deserializer
  writeRep("    if (rReadXml.IsStartTag(\"$(alias)\", false))\n", mfDeserialize);
  writeStr("    {\n", mfDeserialize);
  writeStr("      int     _n   = 0;\n", mfDeserialize);
  writeRep("      while (!rReadXml.IsEof() && !rReadXml.IsEndTag(\"$(alias)\"))\n", mfDeserialize);
  writeStr("      {\n", mfDeserialize);
  writeRep("        if (_n<$(size) && rReadXml.IsStartTag(\"$(item)\", false))\n", mfDeserialize);
  writeStr("        {\n", mfDeserialize);
  writeRep("          deserialize(rReadXml, rObject.$(name)[_n++], \"$(item)\", false);\n", mfDeserialize);
  writeStr("          continue;\n", mfDeserialize);
  writeStr("        }\n", mfDeserialize);
  writeStr("        rReadXml.SkipTag();\n", mfDeserialize);
  writeStr("      } // while (!rReadXml.IsEndTag(...))\n", mfDeserialize);
  writeStr("      continue;\n", mfDeserialize);
  writeStr("    }\n", mfDeserialize);
}



void CGeneratorXml::writeVarDeclSetList()
{
  // write serializer
  writeRep("  serialize(rWriteXml, rObject.$(name), \"$(alias)\", \"$(item)\", false);\n", mfSerialize);

  // write deserializer
  writeRep("    if (rReadXml.IsStartTag(\"$(alias)\", false))\n", mfDeserialize);
  writeStr("    {\n", mfDeserialize);
  writeRep("      deserialize(rReadXml, rObject.$(name), \"$(alias)\", \"$(item)\", false);\n", mfDeserialize);
  writeStr("      continue;\n", mfDeserialize);
  writeStr("    }\n", mfDeserialize);
}



void CGeneratorXml::writeVarDeclMap()
{
  // write serializer
  writeRep("  serialize(rWriteXml, rObject.$(name), \"$(alias)\", \"$(item)\", \"$(id)\", false);\n", mfSerialize);

  // write deserializer
  writeRep("    if (rReadXml.IsStartTag(\"$(alias)\", false))\n", mfDeserialize);
  writeStr("    {\n", mfDeserialize);
  writeRep("      deserialize(rReadXml, rObject.$(name), \"$(alias)\", \"$(item)\", \"$(id)\", false);\n", mfDeserialize);
  writeStr("      continue;\n", mfDeserialize);
  writeStr("    }\n", mfDeserialize);
}



void CGeneratorXml::writeStructEnd()
{
  /* end of struct serialize function */
  writeStr("  rWriteXml.EndTag(pszTag);\n", mfSerialize);
  writeStr("}\n", mfSerialize);

  /* end of struct deserialize function */
  writeStr("    rReadXml.SkipTag();\n", mfDeserialize);
  writeStr("  } // while (!rReadXml.IsEndTag(...))\n", mfDeserialize);
  writeStr("}\n", mfDeserialize);
}






int CGeneratorXml::footerfile()
{
  return 0;
}



int CGeneratorXml::footer()
{
  // write header
  writeStr("\n\n", mfHeader);
  writeStr(pszHeader, mfHeader);
  writeStr("#endif // _Struct_h_\n", mfHeader);

  // write serializer
  writeStr("\n\n\n", mfSerialize);
  writeStr(pszSerialize, mfSerialize);

  // write deserializer
  writeStr("\n\n\n", mfDeserialize);
  writeStr(pszDeserialize, mfDeserialize);
  return 0;
}
