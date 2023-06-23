// Created by camilo from ch.h on 2022-06-06 22:20 <3ThomasBorregaardSorensen!!
// Changed to character by camilo on 2022-10-07 16:00 <3ThomasBorregaardSorensen!!
#pragma once


#include "_c_unicode.h"


class CLASS_DECL_ACME character
{
public:


   ::wd32_character     m_wd32char;


   character(::ansi_character ::ansi_character) { m_wd32char = (::wd32_character) static_cast <::u8> (::ansi_character); }
   character(::wd16_character ::wd16_character) { wd16_to_wd32(&m_wd32char, &::wd16_character, 1); }
   character(::wd32_character ::wd32_character) { m_wd32char = ::wd32_character; }
   character(const ::scoped_string & scopedstrUtf8) { m_wd32char= parse_utf8(pszUtf8); }


   static ::wd32_character parse_utf8(const ::scoped_string & scopedstrUtf8);


};



