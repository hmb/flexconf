#include "struct.h"



void serialize(CWriteXml & rWriteXml, const SData & rObject, const char * pszTag, bool fRoot,
  const char * pszIdTag, const std::string * pstrIdValue)
{
  if (!pszTag)
    pszTag="data";
  rWriteXml.StartTag(pszTag, fRoot);
  if (pszIdTag && pstrIdValue)
  {
    serialize(rWriteXml, *pstrIdValue, pszIdTag, false);
  }
  serialize(rWriteXml, rObject.nInt, "int", false);
  serialize(rWriteXml, rObject.dblDouble, "double", false);
  serialize(rWriteXml, rObject.strString, "string", false);
  rWriteXml.EndTag(pszTag);
}



void serialize(CWriteXml & rWriteXml, const STestBase & rObject, const char * pszTag, bool fRoot,
  const char * pszIdTag, const std::string * pstrIdValue)
{
  if (!pszTag)
    pszTag="TEST";
  rWriteXml.StartTag(pszTag, fRoot);
  if (pszIdTag && pstrIdValue)
  {
    serialize(rWriteXml, *pstrIdValue, pszIdTag, false);
  }
  serialize(rWriteXml, rObject.nShort, "nShort", false);
  serialize(rWriteXml, rObject.nuShort, "nuShort", false);
  serialize(rWriteXml, rObject.nInt, "nInt", false);
  serialize(rWriteXml, rObject.nuInt, "nuInt", false);
  serialize(rWriteXml, rObject.nLong, "nLong", false);
  serialize(rWriteXml, rObject.nuLong, "nuLong", false);
  serialize(rWriteXml, rObject.nuLongX, "nuLongX", false);
  serialize(rWriteXml, rObject.fltFloat, "fltFloat", false);
  serialize(rWriteXml, rObject.dblDouble, "dblDouble", false);
  serialize(rWriteXml, rObject.strString, "strString", false);
  serialize(rWriteXml, rObject.datData, "datData", false);
  serialize(rWriteXml, rObject.datData2, "Data", false);
  rWriteXml.StartTag("vecData", false);
  {for (int n=0; n<4; n++)
  {
    serialize(rWriteXml, rObject.vecData[n], "DataElement", false);
  }}
  rWriteXml.EndTag("vecData");
  serialize(rWriteXml, rObject.setData, "setdata", "text", false);
  serialize(rWriteXml, rObject.setDataL, "setlong", "long", false);
  serialize(rWriteXml, rObject.mlstData, "ListData", "DataItem", false);
  serialize(rWriteXml, rObject.mlstString, "ListString", "StringItem", false);
  serialize(rWriteXml, rObject.mapDataL, "maplong", "app", "longid", false);
  rWriteXml.EndTag(pszTag);
}



void serialize(CWriteXml & rWriteXml, const std::string & rObject, const char * pszTag, bool fRoot)
{
  rWriteXml.StartTag(pszTag, fRoot);
  rWriteXml.PutData(rObject.data(), rObject.length());
  rWriteXml.EndTag(pszTag);
}



