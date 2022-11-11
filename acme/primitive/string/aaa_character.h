// Created by camilo from ch.h on 2022-06-06 22:20 <3ThomasBorregaardSorensen!!
// Changed to character by camilo on 2022-10-07 16:00 <3ThomasBorregaardSorensen!!
#pragma once


#include "_c_unicode.h"


class CLASS_DECL_ACME character
{
public:


   ::wd32char     m_wd32char;


   character(ansichar ansichar) { m_wd32char = (::wd32char) static_cast <byte> (ansichar); }
   character(wd16char wd16char) { wd16_to_wd32(&m_wd32char, &wd16char, 1); }
   character(wd32char wd32char) { m_wd32char = wd32char; }
   character(const char * pszUtf8) { m_wd32char= parse_utf8(pszUtf8); }


   static wd32char parse_utf8(const char * pszUtf8);


};



