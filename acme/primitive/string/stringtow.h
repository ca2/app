#pragma once


#include "string.h"


class CLASS_DECL_ACME stringtow :
   public string
{
public:

   wstring * m_pwstring;

   stringtow(wstring & str, i32 iAllocCount = 0);
   ~stringtow();


   using string::operator = ;

   inline operator const char * () { return c_str(); }
   inline operator char * () { return (char *) c_str(); }

};
