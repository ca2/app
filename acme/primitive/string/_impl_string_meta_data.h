//
//  _string_base_meta_data.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 08/06/22.
//  Copyright © 2022 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//  as _impl_string_meta_data.h from _impl_string_base.h by
//  camilo on 2023-03-07 15:05 BRT <3ThomasBorregaardSorensen!!
//
#pragma once


template < primitive_character CHARACTER >
inline void string_meta_data < CHARACTER > ::raw_set_character_count(::strsize countData)
{

   if (this->natural_is_shared())
   {

      throw_exception(error_wrong_state, "invalid state");

   }

   auto storageCharacterCount = this->storage_character_count();

   if (countData > storageCharacterCount)
   {

      throw_exception(error_bad_argument, "count in bytes of character count exceeds storage size");

   }

   this->m_countData = countData;

}


template < primitive_character CHARACTER >
inline void string_meta_data < CHARACTER > ::set_character_count(::strsize countData)
{

   raw_set_character_count(countData);

}


template < primitive_character CHARACTER >
inline ::strsize string_meta_data < CHARACTER>::storage_character_count() const
{

   return (::strsize)byte_length_to_character_count(&this->begin()[0], (::strsize)this->m_sizeStorageInBytes);

}


template < primitive_character CHARACTER >
inline ::memsize string_meta_data < CHARACTER>::character_count_in_bytes() const
{

   return character_count_to_byte_length(&this->begin()[0], this->m_countData);

}



