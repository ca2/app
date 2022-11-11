//
//  simple_string_base.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 08/06/22.
//  Copyright © 2022 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//
#pragma once


#include "acme/memory/string_memory_allocator.h"
#include "string_meta_data.h"


template < typename TYPE_CHAR >
class simple_string_base :
   public natural_pointer < string_meta_data < TYPE_CHAR >, string_memory_allocator >
{
public:

   using NATURAL_POINTER = natural_pointer < string_meta_data < TYPE_CHAR >, string_memory_allocator >;

   using NATURAL_META_DATA = typename NATURAL_POINTER::NATURAL_META_DATA;

   using NATURAL_POINTER::NATURAL_POINTER;

   simple_string_base(e_char_count, strsize iCharCount)
   {

      this->m_pdata = NATURAL_META_DATA::to_data(this->create_meta_data(sizeof(TYPE_CHAR) * (iCharCount + 1)));

   }

   simple_string_base(e_byte_count, memsize iMemSize)
   {

      this->m_pdata = NATURAL_META_DATA::to_data(this->create_meta_data(((iMemSize + sizeof(TYPE_CHAR) + sizeof(TYPE_CHAR) - 1) / sizeof(TYPE_CHAR)) * sizeof(TYPE_CHAR)));

   }


   operator TYPE_CHAR * () { return this->m_pdata; }
   operator const TYPE_CHAR * () const { return this->m_pdata; }


   inline auto length() { return this->metadata()->length(); }
   inline auto memsize() { return this->metadata()->memsize(); }


};





