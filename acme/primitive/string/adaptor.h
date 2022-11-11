#pragma once


#include "string.h"


template < typename STRING_CATCHER >
class wstring_adaptor :
   public wstring
{
public:


   STRING_CATCHER & m_stringCatcher;


   wstring_adaptor(STRING_CATCHER & stringCatcher, i32 iAllocCount) :
      m_stringCatcher(stringCatcher)
   {

      get_string_buffer(iAllocCount);

   }


   ~wstring_adaptor()
   {

      m_stringCatcher = m_pdata;

   }


   inline operator const widechar * () { return this->m_pdata; }
   inline operator widechar * () { return this->m_pdata; }


};



