// Created by camilo on 2022-11-01 23:04 <3ThomasBorregaardSorensen!!
#include "framework.h"
// #include "acme/primitive/string/string.h"
#include "acme/_operating_system.h"

string idn_to_punycode(const ::string & str)
{

   wstring wstr(str);

   int iSize = IdnToAscii(IDN_RAW_PUNYCODE, wstr, (int)wstr.length(), nullptr, 0);

   wstring wstrTarget;

   WCHAR * pwszTarget = wstrTarget.get_buffer(iSize);

   IdnToAscii(IDN_RAW_PUNYCODE, wstr, (int)wstr.length(), pwszTarget, iSize);

   wstrTarget.release_buffer();

   string strTarget = wstrTarget;

   return strTarget;

}


string idn_from_punycode(const ::string & str)
{

   wstring wstrSource(str);

   int iSize = IdnToUnicode(IDN_RAW_PUNYCODE, wstrSource, (int)wstrSource.length(), nullptr, 0);

   wstring wstrTarget;

   auto pwszTarget = wstrTarget.get_buffer(iSize);

   IdnToUnicode(IDN_RAW_PUNYCODE, wstrSource, (int)wstrSource.length(), pwszTarget, iSize);

   wstrTarget.release_buffer(iSize);

   string strTarget = wstrTarget;

   return strTarget;


}



