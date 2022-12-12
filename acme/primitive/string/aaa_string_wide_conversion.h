#pragma once


#include "string.h"


template < typename STRING_CATCHER >
class CLASS_DECL_ACME catch_as_wstring :
   public wstring
{
public:


   STRING_CATCHER & m_stringCatcher;


   catch_as_wstring(STRING_CATCHER & stringCatcher, i32 iAllocCount) :
      m_stringCatcher(stringCatcher)
   {

      get_string_buffer(iAllocCount);

   }


   ~catch_as_wstring()
   {

      m_stringCatcher = m_pdata;

   }


   inline operator const ::wide_character * () { return this->m_pdata; }
   inline operator ::wide_character * () { return this->m_pdata; }


};



