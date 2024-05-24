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

      get_buffer(iAllocCount);

   }


   ~wstring_adaptor()
   {

      m_stringCatcher = this->c_str();

   }


   inline operator const ::wide_character * () { return this->m_begin; }
   inline operator ::wide_character * () { return (::wide_character *) this->m_begin; }


};



