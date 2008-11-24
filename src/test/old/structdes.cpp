#include "struct.h"
#include <stdlib.h>



void deserialize(CReadXml & rReadXml, SData & rObject, const char * pszTag, bool fRoot,
  const char * pszIdTag, std::string * pstrIdValue)
{
  if (!pszTag)
    pszTag="data";
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
    if (rReadXml.IsStartTag("int", false))
    {
      deserialize(rReadXml, rObject.nInt, "int", false);
      continue;
    }
    if (rReadXml.IsStartTag("double", false))
    {
      deserialize(rReadXml, rObject.dblDouble, "double", false);
      continue;
    }
    if (rReadXml.IsStartTag("string", false))
    {
      deserialize(rReadXml, rObject.strString, "string", false);
      continue;
    }
    rReadXml.SkipTag();
  } // while (!rReadXml.IsEndTag(...))
}



void deserialize(CReadXml & rReadXml, STestBase & rObject, const char * pszTag, bool fRoot,
  const char * pszIdTag, std::string * pstrIdValue)
{
  if (!pszTag)
    pszTag="TEST";
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
    if (rReadXml.IsStartTag("nShort", false))
    {
      deserialize(rReadXml, rObject.nShort, "nShort", false);
      continue;
    }
    if (rReadXml.IsStartTag("nuShort", false))
    {
      deserialize(rReadXml, rObject.nuShort, "nuShort", false);
      continue;
    }
    if (rReadXml.IsStartTag("nInt", false))
    {
      deserialize(rReadXml, rObject.nInt, "nInt", false);
      continue;
    }
    if (rReadXml.IsStartTag("nuInt", false))
    {
      deserialize(rReadXml, rObject.nuInt, "nuInt", false);
      continue;
    }
    if (rReadXml.IsStartTag("nLong", false))
    {
      deserialize(rReadXml, rObject.nLong, "nLong", false);
      continue;
    }
    if (rReadXml.IsStartTag("nuLong", false))
    {
      deserialize(rReadXml, rObject.nuLong, "nuLong", false);
      continue;
    }
    if (rReadXml.IsStartTag("nuLongX", false))
    {
      deserialize(rReadXml, rObject.nuLongX, "nuLongX", false);
      continue;
    }
    if (rReadXml.IsStartTag("fltFloat", false))
    {
      deserialize(rReadXml, rObject.fltFloat, "fltFloat", false);
      continue;
    }
    if (rReadXml.IsStartTag("dblDouble", false))
    {
      deserialize(rReadXml, rObject.dblDouble, "dblDouble", false);
      continue;
    }
    if (rReadXml.IsStartTag("strString", false))
    {
      deserialize(rReadXml, rObject.strString, "strString", false);
      continue;
    }
    if (rReadXml.IsStartTag("datData", false))
    {
      deserialize(rReadXml, rObject.datData, "datData", false);
      continue;
    }
    if (rReadXml.IsStartTag("Data", false))
    {
      deserialize(rReadXml, rObject.datData2, "Data", false);
      continue;
    }
    if (rReadXml.IsStartTag("vecData", false))
    {
      int     _n   = 0;
      while (!rReadXml.IsEof() && !rReadXml.IsEndTag("vecData"))
      {
        if (_n<4 && rReadXml.IsStartTag("DataElement", false))
        {
          deserialize(rReadXml, rObject.vecData[_n++], "DataElement", false);
          continue;
        }
        rReadXml.SkipTag();
      } // while (!rReadXml.IsEndTag(...))
      continue;
    }
    if (rReadXml.IsStartTag("setdata", false))
    {
      deserialize(rReadXml, rObject.setData, "setdata", "text", false);
      continue;
    }
    if (rReadXml.IsStartTag("setlong", false))
    {
      deserialize(rReadXml, rObject.setDataL, "setlong", "long", false);
      continue;
    }
    if (rReadXml.IsStartTag("ListData", false))
    {
      deserialize(rReadXml, rObject.mlstData, "ListData", "DataItem", false);
      continue;
    }
    if (rReadXml.IsStartTag("ListString", false))
    {
      deserialize(rReadXml, rObject.mlstString, "ListString", "StringItem", false);
      continue;
    }
    if (rReadXml.IsStartTag("maplong", false))
    {
      deserialize(rReadXml, rObject.mapDataL, "maplong", "app", "longid", false);
      continue;
    }
    rReadXml.SkipTag();
  } // while (!rReadXml.IsEndTag(...))
}



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



