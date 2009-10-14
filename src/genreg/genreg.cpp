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
  writeStr("#ifndef _Struct_h_\n", eCommonHdr);
  writeStr("#define _Struct_h_\n\n", eCommonHdr);
  writeStr("#ifdef _MSC_VER\n", eCommonHdr);
  writeStr("#define snprintf _snprintf\n", eCommonHdr);
  writeStr("#pragma warning(disable: 4786)\n", eCommonHdr);
  writeStr("#endif\n", eCommonHdr);
  writeStr("\n\n\n", eCommonHdr);
  writeStr("#include <string>\n", eCommonHdr);
  writeStr("#include <list>\n", eCommonHdr);
  writeStr("#include <set>\n", eCommonHdr);
  writeStr("#include <map>\n", eCommonHdr);
  writeStr("#include <windows.h>\n", eCommonHdr);
  writeStr("#include <amalib/Registry.h>\n", eCommonHdr);
  writeStr("\n\n\n", eCommonHdr);

  writeStr("template <class _T>\n", eCommonHdr);
  writeStr("void serialize(const amalib::CRegKey & rkeyStruct, const _T & rObject, const char * pszKeyName)\n", eCommonHdr);
  writeStr("{\n", eCommonHdr);
  writeStr("  rkeyStruct.SetValue(pszKeyName, rObject);\n", eCommonHdr);
  writeStr("}\n", eCommonHdr);
  writeStr("\n", eCommonHdr);

  writeStr("template <class _T>\n", eCommonHdr);
  writeStr("void serialize(const amalib::CRegKey & rkeyStruct, const _T arObject[], int nCount, const char * pszKeyName, const char * pszItemName)\n", eCommonHdr);
  writeStr("{\n", eCommonHdr);
  writeStr("  amalib::CRegKey keyArray;\n", eCommonHdr);
  writeStr("  keyArray.Create(rkeyStruct, pszKeyName);\n", eCommonHdr);
  writeStr("  for (int n=0; n<nCount; n++)\n", eCommonHdr);
  writeStr("  {\n", eCommonHdr);
  writeStr("    const int BUFSIZE   = 200;\n", eCommonHdr);
  writeStr("    char szBuffer[BUFSIZE];\n", eCommonHdr);
  writeStr("    snprintf(szBuffer, BUFSIZE, \"%.150s%d\", pszItemName, n);\n", eCommonHdr);
  writeStr("    serialize(keyArray, arObject[n], szBuffer);\n", eCommonHdr);
  writeStr("  } // for\n", eCommonHdr);
  writeStr("}\n", eCommonHdr);
  writeStr("\n\n\n", eCommonHdr);

  writeStr("template <class _T>\n", eCommonHdr);
  writeStr("void deserialize(const amalib::CRegKey & rkeyStruct, _T & rObject, const char * pszKeyName)\n", eCommonHdr);
  writeStr("{\n", eCommonHdr);
  writeStr("  rkeyStruct.QueryValue(pszKeyName, rObject);\n", eCommonHdr);
  writeStr("}\n", eCommonHdr);
  writeStr("\n\n\n", eCommonHdr);

  writeStr("template <class _T>\n", eCommonHdr);
  writeStr("void deserialize(const amalib::CRegKey & rkeyStruct, _T arObject[], int nCount, const char * pszKeyName, const char * pszItemName)\n", eCommonHdr);
  writeStr("{\n", eCommonHdr);
  writeStr("  amalib::CRegKey keyArray;\n", eCommonHdr);
  writeStr("  keyArray.Create(rkeyStruct, pszKeyName);\n", eCommonHdr);
  writeStr("  for (int n=0; n<nCount; n++)\n", eCommonHdr);
  writeStr("  {\n", eCommonHdr);
  writeStr("    const int BUFSIZE   = 200;\n", eCommonHdr);
  writeStr("    char szBuffer[BUFSIZE];\n", eCommonHdr);
  writeStr("    snprintf(szBuffer, BUFSIZE, \"%.150s%d\", pszItemName, n);\n", eCommonHdr);
  writeStr("    deserialize(keyArray, arObject[n], szBuffer);\n", eCommonHdr);
  writeStr("  } // for\n", eCommonHdr);
  writeStr("\n\n\n", eCommonHdr);
  writeStr("}\n", eCommonHdr);

  // write serializer
  writeStr("#include \"struct.h\"\n", eSerializerImp);

  // write deserializer
  writeStr("#include \"struct.h\"\n", eDeserializerImp);

  return 0;
}



int CGeneratorReg::headerfile()
{
  writeRep("#include \"$(headerfile)\"\n", eCommonHdr);
  return 0;
}






void CGeneratorReg::writeStructBegin()
{
  writeRep("void serialize(const amalib::CRegKey & rkeyParent, const $(name) & rObject, const char * pszKeyName = 0,\n", eCommonHdr);
  writeStr("  const char * pszIdTag = 0, const std::string * pstrIdValue = 0);\n", eCommonHdr);
  writeRep("void deserialize(const amalib::CRegKey & rkeyParent, $(name) & rObject, const char * pszKeyName = 0,\n", eCommonHdr);
  writeStr("  const char * pszIdTag = 0, std::string * pstrIdValue = 0);\n\n", eCommonHdr);

  /* start of struct serialize function */
  writeStr("\n\n\n", eSerializerImp);
  writeRep("void serialize(const amalib::CRegKey & rkeyParent, const $(name) & rObject, const char * pszKeyName,\n", eSerializerImp);
  writeStr("  const char * pszIdTag, const std::string * pstrIdValue)\n", eSerializerImp);
  writeStr("{\n", eSerializerImp);
  writeStr("  if (!pszKeyName)\n", eSerializerImp);
  writeRep("    pszKeyName=\"$(alias)\";\n", eSerializerImp);
  writeStr("  amalib::CRegKey keyStruct;\n", eSerializerImp);
  writeStr("  keyStruct.Create(rkeyParent, pszKeyName);\n", eSerializerImp);
  writeStr("  if (pszIdTag && pstrIdValue)\n", eSerializerImp);
  writeStr("  {\n", eSerializerImp);
  writeStr("    return; // :TODO: not yet implemented\n", eSerializerImp);
  writeStr("  //  serialize(rWriteXml, *pstrIdValue, pszIdTag);\n", eSerializerImp);
  writeStr("  }\n", eSerializerImp);

  /* start of struct deserialize function */
  writeStr("\n\n\n", eDeserializerImp);
  writeRep("void deserialize(const amalib::CRegKey & rkeyParent, $(name) & rObject, const char * pszKeyName,\n", eDeserializerImp);
  writeStr("  const char * pszIdTag, std::string * pstrIdValue)\n", eDeserializerImp);
  writeStr("{\n", eDeserializerImp);
  writeStr("  if (!pszKeyName)\n", eDeserializerImp);
  writeRep("    pszKeyName=\"$(alias)\";\n", eDeserializerImp);
  writeStr("  amalib::CRegKey keyStruct;\n", eDeserializerImp);
  writeStr("  keyStruct.Open(rkeyParent, pszKeyName);\n", eDeserializerImp);
  writeStr("  if (pszIdTag && pstrIdValue)\n", eDeserializerImp);
  writeStr("  {\n", eDeserializerImp);
  writeStr("    return; // :TODO: not yet implemented\n", eDeserializerImp);
  writeStr("    //  deserialize(rReadXml, *pstrIdValue, pszIdTag);\n", eDeserializerImp);
  writeStr("  }\n", eDeserializerImp);
}



void CGeneratorReg::writeVarDecl()
{
  // write serializer
  writeRep("  serialize(keyStruct, rObject.$(name), \"$(alias)\");\n", eSerializerImp);
  // write deserializer
  writeRep("  deserialize(keyStruct, rObject.$(name), \"$(alias)\");\n", eDeserializerImp);
}



void CGeneratorReg::writeVarDeclVector()
{
  // write serializer
  writeRep("  serialize(keyStruct, rObject.$(name), $(size), \"$(alias)\", \"$(item)\");\n", eSerializerImp);
  // write deserializer
  writeRep("  deserialize(keyStruct, rObject.$(name), $(size), \"$(alias)\", \"$(item)\");\n", eDeserializerImp);
}



void CGeneratorReg::writeVarDeclSetList()
{
  // write serializer
  writeRep("  // :TODO: serialize(keyStruct, rObject.$(name), \"$(alias)\", \"$(item)\");\n", eSerializerImp);
  // write deserializer
  writeRep("  // :TODO: deserialize(keyStruct, rObject.$(name), \"$(alias)\", \"$(item)\");\n", eDeserializerImp);
}



void CGeneratorReg::writeVarDeclMap()
{
  // write serializer
  writeRep("  // :TODO: serialize(keyStruct, rObject.$(name), \"$(alias)\", \"$(item)\", \"$(id)\");\n", eSerializerImp);
  // write deserializer
  writeRep("  // :TODO: deserialize(keyStruct, rObject.$(name), \"$(alias)\", \"$(item)\", \"$(id)\");\n", eDeserializerImp);
}



void CGeneratorReg::writeStructEnd()
{
  // write serializer
  writeStr("}\n", eSerializerImp);
  // write deserializer
  writeStr("}\n", eDeserializerImp);
}






int CGeneratorReg::footerfile()
{
  return 0;
}



int CGeneratorReg::footer()
{
  // write header
  writeStr("\n\n", eCommonHdr);
  writeStr("#endif // _Struct_h_\n", eCommonHdr);

  // write serializer
  writeStr("\n\n\n", eSerializerImp);

  // write deserializer
  writeStr("\n\n\n", eDeserializerImp);

  return 0;
}
