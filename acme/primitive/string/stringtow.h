#pragma once


//#include "string.h"


class CLASS_DECL_ACME stringtow
{
public:


   wstring *      m_pwstring;
   ::string       m_str;
   char *         m_pszBuffer;


   stringtow(wstring & str, i32 iAllocCount = 0);
   ~stringtow();


   inline operator const char * () { return m_str; }
   inline operator char* () { return m_pszBuffer; }

};
