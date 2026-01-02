//
//  _string_base_meta_data.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 08/06/22.
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//  as _impl_string_meta_data.h from _impl_string_base.h by
//  camilo on 2023-03-07 15:05 BRT <3ThomasBorregaardSorensen!!
//
#pragma once


//template < prototype_character CHARACTER >
//inline void string_heap_data < CHARACTER > ::raw_set_character_count(::character_count countData)
//{
//
//   if (this->natural_is_shared())
//   {
//
//      throw_exception(error_wrong_state, "invalid state");
//
//   }
//
//   auto storageCharacterCount = this->storage_character_count();
//
//   if (countData > storageCharacterCount)
//   {
//
//      throw_exception(error_bad_argument, "count in bytes of character count exceeds storage size");
//
//   }
//
//   this->m_countData = countData;
//
//}


//template < prototype_character CHARACTER >
//inline void string_heap_data < CHARACTER > ::set_character_count(::character_count countData)
//{
//
//   raw_set_character_count(countData);
//
//}




//template < prototype_character CHARACTER >
//inline ::memsize string_heap_data < CHARACTER>::character_count_in_bytes() const
//{
//
//   return character_count_to_byte_length(&this->begin()[0], this->m_countData);
//
//}
//

//template < prototype_character CHARACTER >
//inline ::memsize string_heap_data < CHARACTER>::null_terminated_character_count_in_bytes() const
//{
//
//   return this->character_count_in_bytes() + sizeof(CHARACTER);
//
//}
//

