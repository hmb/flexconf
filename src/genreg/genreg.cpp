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
  writeStr("#ifndef _Struct_h_\n", mfCommonHdr);
  writeStr("#define _Struct_h_\n\n", mfCommonHdr);
  writeStr("#ifdef _MSC_VER\n", mfCommonHdr);
  writeStr("#define snprintf _snprintf\n", mfCommonHdr);
  writeStr("#pragma warning(disable: 4786)\n", mfCommonHdr);
  writeStr("#endif\n", mfCommonHdr);
  writeStr("\n\n\n", mfCommonHdr);
  writeStr("#include <string>\n", mfCommonHdr);
  writeStr("#include <list>\n", mfCommonHdr);
  writeStr("#include <set>\n", mfCommonHdr);
  writeStr("#include <map>\n", mfCommonHdr);
  writeStr("#include <windows.h>\n", mfCommonHdr);
  writeStr("#include <amalib/Registry.h>\n", mfCommonHdr);
  writeStr("\n\n\n", mfCommonHdr);

  writeStr("template <class _T>\n", mfCommonHdr);
  writeStr("void serialize(const amalib::CRegKey & rkeyStruct, const _T & rObject, const char * pszKeyName)\n", mfCommonHdr);
  writeStr("{\n", mfCommonHdr);
  writeStr("  rkeyStruct.SetValue(pszKeyName, rObject);\n", mfCommonHdr);
  writeStr("}\n", mfCommonHdr);
  writeStr("\n", mfCommonHdr);

  writeStr("template <class _T>\n", mfCommonHdr);
  writeStr("void serialize(const amalib::CRegKey & rkeyStruct, const _T arObject[], int nCount, const char * pszKeyName, const char * pszItemName)\n", mfCommonHdr);
  writeStr("{\n", mfCommonHdr);
  writeStr("  amalib::CRegKey keyArray;\n", mfCommonHdr);
  writeStr("  keyArray.Create(rkeyStruct, pszKeyName);\n", mfCommonHdr);
  writeStr("  for (int n=0; n<nCount; n++)\n", mfCommonHdr);
  writeStr("  {\n", mfCommonHdr);
  writeStr("    const int BUFSIZE   = 200;\n", mfCommonHdr);
  writeStr("    char szBuffer[BUFSIZE];\n", mfCommonHdr);
  writeStr("    snprintf(szBuffer, BUFSIZE, \"%.150s%d\", pszItemName, n);\n", mfCommonHdr);
  writeStr("    serialize(keyArray, arObject[n], szBuffer);\n", mfCommonHdr);
  writeStr("  } // for\n", mfCommonHdr);
  writeStr("}\n", mfCommonHdr);
  writeStr("\n\n\n", mfCommonHdr);

  writeStr("template <class _T>\n", mfCommonHdr);
  writeStr("void deserialize(const amalib::CRegKey & rkeyStruct, _T & rObject, const char * pszKeyName)\n", mfCommonHdr);
  writeStr("{\n", mfCommonHdr);
  writeStr("  rkeyStruct.QueryValue(pszKeyName, rObject);\n", mfCommonHdr);
  writeStr("}\n", mfCommonHdr);
  writeStr("\n\n\n", mfCommonHdr);

  writeStr("template <class _T>\n", mfCommonHdr);
  writeStr("void deserialize(const amalib::CRegKey & rkeyStruct, _T arObject[], int nCount, const char * pszKeyName, const char * pszItemName)\n", mfCommonHdr);
  writeStr("{\n", mfCommonHdr);
  writeStr("  amalib::CRegKey keyArray;\n", mfCommonHdr);
  writeStr("  keyArray.Create(rkeyStruct, pszKeyName);\n", mfCommonHdr);
  writeStr("  for (int n=0; n<nCount; n++)\n", mfCommonHdr);
  writeStr("  {\n", mfCommonHdr);
  writeStr("    const int BUFSIZE   = 200;\n", mfCommonHdr);
  writeStr("    char szBuffer[BUFSIZE];\n", mfCommonHdr);
  writeStr("    snprintf(szBuffer, BUFSIZE, \"%.150s%d\", pszItemName, n);\n", mfCommonHdr);
  writeStr("    deserialize(keyArray, arObject[n], szBuffer);\n", mfCommonHdr);
  writeStr("  } // for\n", mfCommonHdr);
  writeStr("\n\n\n", mfCommonHdr);
  writeStr("}\n", mfCommonHdr);

  // write serializer
  writeStr("#include \"struct.h\"\n", mfSerializeImp);

  // write deserializer
  writeStr("#include \"struct.h\"\n", mfDeserializeImp);

  return 0;
}



int CGeneratorReg::headerfile()
{
  writeRep("#include \"$(headerfile)\"\n", mfCommonHdr);
  return 0;
}






void CGeneratorReg::writeStructBegin()
{
  writeRep("void serialize(const amalib::CRegKey & rkeyParent, const $(name) & rObject, const char * pszKeyName = 0,\n", mfCommonHdr);
  writeStr("  const char * pszIdTag = 0, const std::string * pstrIdValue = 0);\n", mfCommonHdr);
  writeRep("void deserialize(const amalib::CRegKey & rkeyParent, $(name) & rObject, const char * pszKeyName = 0,\n", mfCommonHdr);
  writeStr("  const char * pszIdTag = 0, std::string * pstrIdValue = 0);\n\n", mfCommonHdr);

  /* start of struct serialize function */
  writeStr("\n\n\n", mfSerializeImp);
  writeRep("void serialize(const amalib::CRegKey & rkeyParent, const $(name) & rObject, const char * pszKeyName,\n", mfSerializeImp);
  writeStr("  const char * pszIdTag, const std::string * pstrIdValue)\n", mfSerializeImp);
  writeStr("{\n", mfSerializeImp);
  writeStr("  if (!pszKeyName)\n", mfSerializeImp);
  writeRep("    pszKeyName=\"$(alias)\";\n", mfSerializeImp);
  writeStr("  amalib::CRegKey keyStruct;\n", mfSerializeImp);
  writeStr("  keyStruct.Create(rkeyParent, pszKeyName);\n", mfSerializeImp);
  writeStr("  if (pszIdTag && pstrIdValue)\n", mfSerializeImp);
  writeStr("  {\n", mfSerializeImp);
  writeStr("    return; // :TODO: not yet implemented\n", mfSerializeImp);
  writeStr("  //  serialize(rWriteXml, *pstrIdValue, pszIdTag);\n", mfSerializeImp);
  writeStr("  }\n", mfSerializeImp);

  /* start of struct deserialize function */
  writeStr("\n\n\n", mfDeserializeImp);
  writeRep("void deserialize(const amalib::CRegKey & rkeyParent, $(name) & rObject, const char * pszKeyName,\n", mfDeserializeImp);
  writeStr("  const char * pszIdTag, std::string * pstrIdValue)\n", mfDeserializeImp);
  writeStr("{\n", mfDeserializeImp);
  writeStr("  if (!pszKeyName)\n", mfDeserializeImp);
  writeRep("    pszKeyName=\"$(alias)\";\n", mfDeserializeImp);
  writeStr("  amalib::CRegKey keyStruct;\n", mfDeserializeImp);
  writeStr("  keyStruct.Open(rkeyParent, pszKeyName);\n", mfDeserializeImp);
  writeStr("  if (pszIdTag && pstrIdValue)\n", mfDeserializeImp);
  writeStr("  {\n", mfDeserializeImp);
  writeStr("    return; // :TODO: not yet implemented\n", mfDeserializeImp);
  writeStr("    //  deserialize(rReadXml, *pstrIdValue, pszIdTag);\n", mfDeserializeImp);
  writeStr("  }\n", mfDeserializeImp);
}



void CGeneratorReg::writeVarDecl()
{
  // write serializer
  writeRep("  serialize(keyStruct, rObject.$(name), \"$(alias)\");\n", mfSerializeImp);
  // write deserializer
  writeRep("  deserialize(keyStruct, rObject.$(name), \"$(alias)\");\n", mfDeserializeImp);
}



void CGeneratorReg::writeVarDeclVector()
{
  // write serializer
  writeRep("  serialize(keyStruct, rObject.$(name), $(size), \"$(alias)\", \"$(item)\");\n", mfSerializeImp);
  // write deserializer
  writeRep("  deserialize(keyStruct, rObject.$(name), $(size), \"$(alias)\", \"$(item)\");\n", mfDeserializeImp);
}



void CGeneratorReg::writeVarDeclSetList()
{
  // write serializer
  writeRep("  // :TODO: serialize(keyStruct, rObject.$(name), \"$(alias)\", \"$(item)\");\n", mfSerializeImp);
  // write deserializer
  writeRep("  // :TODO: deserialize(keyStruct, rObject.$(name), \"$(alias)\", \"$(item)\");\n", mfDeserializeImp);
}



void CGeneratorReg::writeVarDeclMap()
{
  // write serializer
  writeRep("  // :TODO: serialize(keyStruct, rObject.$(name), \"$(alias)\", \"$(item)\", \"$(id)\");\n", mfSerializeImp);
  // write deserializer
  writeRep("  // :TODO: deserialize(keyStruct, rObject.$(name), \"$(alias)\", \"$(item)\", \"$(id)\");\n", mfDeserializeImp);
}



void CGeneratorReg::writeStructEnd()
{
  // write serializer
  writeStr("}\n", mfSerializeImp);
  // write deserializer
  writeStr("}\n", mfDeserializeImp);
}






int CGeneratorReg::footerfile()
{
  return 0;
}



int CGeneratorReg::footer()
{
  // write header
  writeStr("\n\n", mfCommonHdr);
  writeStr("#endif // _Struct_h_\n", mfCommonHdr);

  // write serializer
  writeStr("\n\n\n", mfSerializeImp);

  // write deserializer
  writeStr("\n\n\n", mfDeserializeImp);

  return 0;
}
