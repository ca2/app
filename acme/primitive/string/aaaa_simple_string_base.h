//
//  simple_string_base.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 08/06/22.
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#pragma once

//
//#include "acme/memory/string_memory_allocator.h"
//#include "string_meta_data.h"
//#include "acme/primitive/collection/array_range.h"
//#include "acme/primitive/collection/comparable_range.h"
//
//
//
//template < typename CHARACTER_TYPE >
//class simple_string_base :
//   public string_natural_pointer < CHARACTER_TYPE >
//{
//public:
//
//
//   using NATURAL_POINTER = string_natural_pointer < CHARACTER_TYPE >;
//
//   using NATURAL_META_DATA = typename NATURAL_POINTER::NATURAL_META_DATA;
//
//   using NATURAL_POINTER::NATURAL_POINTER;
//
//   simple_string_base(e_char_count, strsize iCharCount)
//   {
//
//      this->m_pdata = NATURAL_META_DATA::to_data(this->create_meta_data(sizeof(CHARACTER_TYPE) * (iCharCount + 1)));
//
//   }
//
//   simple_string_base(e_byte_count, memsize iMemSize)
//   {
//
//      this->m_pdata = NATURAL_META_DATA::to_data(this->create_meta_data(((iMemSize + sizeof(CHARACTER_TYPE) + sizeof(CHARACTER_TYPE) - 1) / sizeof(CHARACTER_TYPE)) * sizeof(CHARACTER_TYPE)));
//
//   }
//
//
//   operator CHARACTER_TYPE * () { return this->m_pdata; }
//   operator const CHARACTER_TYPE * () const { return this->m_pdata; }
//
//
//   inline auto length() { return this->metadata()->length(); }
//   inline auto memsize() { return this->metadata()->memsize(); }
//
//
//};
//
//
//
//

