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

#include "genreg.h"



CGeneratorReg::CGeneratorReg()
{
}



CGeneratorReg::~CGeneratorReg()
{
}



int CGeneratorReg::header()
{
  // write header
  writeStr("#ifndef _Struct_h_\n", mfHeader);
  writeStr("#define _Struct_h_\n\n", mfHeader);
  writeStr("#ifdef _MSC_VER\n", mfHeader);
  writeStr("#define snprintf _snprintf\n", mfHeader);
  writeStr("#pragma warning(disable: 4786)\n", mfHeader);
  writeStr("#endif\n", mfHeader);
  writeStr("\n\n\n", mfHeader);
  writeStr("#include <string>\n", mfHeader);
  writeStr("#include <list>\n", mfHeader);
  writeStr("#include <set>\n", mfHeader);
  writeStr("#include <map>\n", mfHeader);
  writeStr("#include <windows.h>\n", mfHeader);
  writeStr("#include <amalib/Registry.h>\n", mfHeader);
  writeStr("\n\n\n", mfHeader);

  writeStr("template <class _T>\n", mfHeader);
  writeStr("void serialize(const amalib::CRegKey & rkeyStruct, const _T & rObject, const char * pszKeyName)\n", mfHeader);
  writeStr("{\n", mfHeader);
  writeStr("  rkeyStruct.SetValue(pszKeyName, rObject);\n", mfHeader);
  writeStr("}\n", mfHeader);
  writeStr("\n", mfHeader);

  writeStr("template <class _T>\n", mfHeader);
  writeStr("void serialize(const amalib::CRegKey & rkeyStruct, const _T arObject[], int nCount, const char * pszKeyName, const char * pszItemName)\n", mfHeader);
  writeStr("{\n", mfHeader);
  writeStr("  amalib::CRegKey keyArray;\n", mfHeader);
  writeStr("  keyArray.Create(rkeyStruct, pszKeyName);\n", mfHeader);
  writeStr("  for (int n=0; n<nCount; n++)\n", mfHeader);
  writeStr("  {\n", mfHeader);
  writeStr("    const int BUFSIZE   = 200;\n", mfHeader);
  writeStr("    char szBuffer[BUFSIZE];\n", mfHeader);
  writeStr("    snprintf(szBuffer, BUFSIZE, \"%.150s%d\", pszItemName, n);\n", mfHeader);
  writeStr("    serialize(keyArray, arObject[n], szBuffer);\n", mfHeader);
  writeStr("  } // for\n", mfHeader);
  writeStr("}\n", mfHeader);
  writeStr("\n\n\n", mfHeader);

  writeStr("template <class _T>\n", mfHeader);
  writeStr("void deserialize(const amalib::CRegKey & rkeyStruct, _T & rObject, const char * pszKeyName)\n", mfHeader);
  writeStr("{\n", mfHeader);
  writeStr("  rkeyStruct.QueryValue(pszKeyName, rObject);\n", mfHeader);
  writeStr("}\n", mfHeader);
  writeStr("\n\n\n", mfHeader);

  writeStr("template <class _T>\n", mfHeader);
  writeStr("void deserialize(const amalib::CRegKey & rkeyStruct, _T arObject[], int nCount, const char * pszKeyName, const char * pszItemName)\n", mfHeader);
  writeStr("{\n", mfHeader);
  writeStr("  amalib::CRegKey keyArray;\n", mfHeader);
  writeStr("  keyArray.Create(rkeyStruct, pszKeyName);\n", mfHeader);
  writeStr("  for (int n=0; n<nCount; n++)\n", mfHeader);
  writeStr("  {\n", mfHeader);
  writeStr("    const int BUFSIZE   = 200;\n", mfHeader);
  writeStr("    char szBuffer[BUFSIZE];\n", mfHeader);
  writeStr("    snprintf(szBuffer, BUFSIZE, \"%.150s%d\", pszItemName, n);\n", mfHeader);
  writeStr("    deserialize(keyArray, arObject[n], szBuffer);\n", mfHeader);
  writeStr("  } // for\n", mfHeader);
  writeStr("\n\n\n", mfHeader);
  writeStr("}\n", mfHeader);

  // write serializer
  writeStr("#include \"struct.h\"\n", mfSerialize);

  // write deserializer
  writeStr("#include \"struct.h\"\n", mfDeserialize);

  return 0;
}



int CGeneratorReg::headerfile()
{
  writeRep("#include \"$(headerfile)\"\n", mfHeader);
  return 0;
}






void CGeneratorReg::writeStructBegin()
{
  writeRep("void serialize(const amalib::CRegKey & rkeyParent, const $(name) & rObject, const char * pszKeyName = 0,\n", mfHeader);
  writeStr("  const char * pszIdTag = 0, const std::string * pstrIdValue = 0);\n", mfHeader);
  writeRep("void deserialize(const amalib::CRegKey & rkeyParent, $(name) & rObject, const char * pszKeyName = 0,\n", mfHeader);
  writeStr("  const char * pszIdTag = 0, std::string * pstrIdValue = 0);\n\n", mfHeader);

  /* start of struct serialize function */
  writeStr("\n\n\n", mfSerialize);
  writeRep("void serialize(const amalib::CRegKey & rkeyParent, const $(name) & rObject, const char * pszKeyName,\n", mfSerialize);
  writeStr("  const char * pszIdTag, const std::string * pstrIdValue)\n", mfSerialize);
  writeStr("{\n", mfSerialize);
  writeStr("  if (!pszKeyName)\n", mfSerialize);
  writeRep("    pszKeyName=\"$(alias)\";\n", mfSerialize);
  writeStr("  amalib::CRegKey keyStruct;\n", mfSerialize);
  writeStr("  keyStruct.Create(rkeyParent, pszKeyName);\n", mfSerialize);
  writeStr("  if (pszIdTag && pstrIdValue)\n", mfSerialize);
  writeStr("  {\n", mfSerialize);
  writeStr("    return; // :TODO: not yet implemented\n", mfSerialize);
  writeStr("  //  serialize(rWriteXml, *pstrIdValue, pszIdTag);\n", mfSerialize);
  writeStr("  }\n", mfSerialize);

  /* start of struct deserialize function */
  writeStr("\n\n\n", mfDeserialize);
  writeRep("void deserialize(const amalib::CRegKey & rkeyParent, $(name) & rObject, const char * pszKeyName,\n", mfDeserialize);
  writeStr("  const char * pszIdTag, std::string * pstrIdValue)\n", mfDeserialize);
  writeStr("{\n", mfDeserialize);
  writeStr("  if (!pszKeyName)\n", mfDeserialize);
  writeRep("    pszKeyName=\"$(alias)\";\n", mfDeserialize);
  writeStr("  amalib::CRegKey keyStruct;\n", mfDeserialize);
  writeStr("  keyStruct.Open(rkeyParent, pszKeyName);\n", mfDeserialize);
  writeStr("  if (pszIdTag && pstrIdValue)\n", mfDeserialize);
  writeStr("  {\n", mfDeserialize);
  writeStr("    return; // :TODO: not yet implemented\n", mfDeserialize);
  writeStr("    //  deserialize(rReadXml, *pstrIdValue, pszIdTag);\n", mfDeserialize);
  writeStr("  }\n", mfDeserialize);
}



void CGeneratorReg::writeVarDecl()
{
  // write serializer
  writeRep("  serialize(keyStruct, rObject.$(name), \"$(alias)\");\n", mfSerialize);
  // write deserializer
  writeRep("  deserialize(keyStruct, rObject.$(name), \"$(alias)\");\n", mfDeserialize);
}



void CGeneratorReg::writeVarDeclVector()
{
  // write serializer
  writeRep("  serialize(keyStruct, rObject.$(name), $(size), \"$(alias)\", \"$(item)\");\n", mfSerialize);
  // write deserializer
  writeRep("  deserialize(keyStruct, rObject.$(name), $(size), \"$(alias)\", \"$(item)\");\n", mfDeserialize);
}



void CGeneratorReg::writeVarDeclSetList()
{
  // write serializer
  writeRep("  // :TODO: serialize(keyStruct, rObject.$(name), \"$(alias)\", \"$(item)\");\n", mfSerialize);
  // write deserializer
  writeRep("  // :TODO: deserialize(keyStruct, rObject.$(name), \"$(alias)\", \"$(item)\");\n", mfDeserialize);
}



void CGeneratorReg::writeVarDeclMap()
{
  // write serializer
  writeRep("  // :TODO: serialize(keyStruct, rObject.$(name), \"$(alias)\", \"$(item)\", \"$(id)\");\n", mfSerialize);
  // write deserializer
  writeRep("  // :TODO: deserialize(keyStruct, rObject.$(name), \"$(alias)\", \"$(item)\", \"$(id)\");\n", mfDeserialize);
}



void CGeneratorReg::writeStructEnd()
{
  // write serializer
  writeStr("}\n", mfSerialize);
  // write deserializer
  writeStr("}\n", mfDeserialize);
}






int CGeneratorReg::footerfile()
{
  return 0;
}



int CGeneratorReg::footer()
{
  // write header
  writeStr("\n\n", mfHeader);
  writeStr("#endif // _Struct_h_\n", mfHeader);

  // write serializer
  writeStr("\n\n\n", mfSerialize);

  // write deserializer
  writeStr("\n\n\n", mfDeserialize);

  return 0;
}
