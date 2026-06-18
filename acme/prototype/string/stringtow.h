#pragma once


//#include "string.h"


class CLASS_DECL_ACME stringtow
{
public:


   wstring *      m_pwstring;
   ::string       m_str;
   char_pointer m_pszBuffer;


   stringtow(wstring & str, ::i32 iAllocCount = 0);
   ~stringtow();


   inline operator const_char_pointer () { return m_str; }
   inline operator char_pointer () { return m_pszBuffer; }

};
