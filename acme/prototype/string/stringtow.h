#pragma once


//#include "string.h"


class CLASS_DECL_ACME stringtow
{
public:


   wstring *      m_pwstring;
   ::string       m_str;
   char *         m_pszBuffer;


   stringtow(wstring & str, int iAllocCount = 0);
   ~stringtow();


   inline operator const_char_pointer () { return m_str; }
   inline operator char* () { return m_pszBuffer; }

};
