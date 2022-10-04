//
//  string_natural_pointer.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 08/06/22.
//  Copyright © 2022 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//
#pragma once


template < typename TYPE_CHAR >
class string_natural_pointer :
   public natural_pointer < string_meta_data < TYPE_CHAR >, string_memory_allocator >
{
public:

   using NATURAL_POINTER = natural_pointer < string_meta_data < TYPE_CHAR >, string_memory_allocator >;

   using NATURAL_META_DATA = typename NATURAL_POINTER::NATURAL_META_DATA;

   using NATURAL_POINTER::NATURAL_POINTER;

   string_natural_pointer(e_char_count, strsize iCharCount)
   {

      this->m_pdata = NATURAL_META_DATA::to_data(this->create_meta_data(sizeof(TYPE_CHAR) * (iCharCount + 1)));

   }

   string_natural_pointer(e_byte_count, memsize iMemSize)
   {

      this->m_pdata = NATURAL_META_DATA::to_data(this->create_meta_data(((iMemSize + sizeof(TYPE_CHAR) + sizeof(TYPE_CHAR) - 1) / sizeof(TYPE_CHAR)) * sizeof(TYPE_CHAR)));

   }


   operator TYPE_CHAR * () { return this->m_pdata; }
   operator const TYPE_CHAR * () const { return this->m_pdata; }


   inline auto length() { return this->metadata()->length(); }
   inline auto memsize() { return this->metadata()->memsize(); }


};



using natural_ansistring = string_natural_pointer < ansichar >;
using natural_wd16string = string_natural_pointer < wd16char >;
using natural_wd32string = string_natural_pointer < wd32char >;
using natural_widestring = string_natural_pointer < widechar >;

typedef natural_ansistring natural_string;
typedef natural_widestring natural_wstring;



