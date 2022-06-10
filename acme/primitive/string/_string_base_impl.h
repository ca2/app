//
//  _string_base_impl.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 08/06/22.
//  Copyright © 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


template < typename CHAR_TYPE >
inline void string_base < CHAR_TYPE >::get_string(CHAR_TYPE* psz) const noexcept { ::str().copy_chars(psz, this->m_pdata, length()); }


template < typename CHAR_TYPE >
CHAR_TYPE * string_base < CHAR_TYPE >::fork_string(strsize strsize)
{

   auto pOld = this->metadata();

   ASSERT(pOld->m_countReference >= 1);

   auto memsize = ::str().char_length_to_byte_length(this->m_pdata, strsize + 1);

   auto pNew = this->create_meta_data(memsize);

   if (::is_set(pOld))
   {

      auto memsizeOld = pOld->memsize();

      if (memsizeOld > 0)
      {

         auto memsizeCopy = minimum(memsizeOld, memsize);

         memcpy_dup(pNew->get_data(), pOld->get_data(), memsizeCopy);

      }

   }

   pNew->set_length(strsize);

   this->assign_natural_meta_data(pNew);

   //pNew->natural_dec_ref();

   return pNew->get_data();

}


template < typename CHAR_TYPE >
string_base < CHAR_TYPE > & string_base < CHAR_TYPE >::release_string_buffer(strsize nNewLength)
{

   if (nNewLength == -1)
   {

      nNewLength = ::str().string_safe_length(this->m_pdata);

   }

   this->metadata()->set_length(nNewLength);

   return *this;

}


template < typename CHAR_TYPE >
inline strsize string_base < CHAR_TYPE >::get_storage_length() { return (::strsize) ::str().byte_length_to_char_length(this->m_pdata, this->get_storage_size_in_bytes()); }


template < typename CHAR_TYPE >
inline memsize string_base < CHAR_TYPE >::get_length_in_bytes() const { return ::str().char_length_to_byte_length(this->m_pdata, (strsize) (this->metadata()->m_datasize)); }


template < typename CHAR_TYPE >
inline memsize string_base < CHAR_TYPE >::get_length_in_bytes_with_null_terminator() const { return ::str().char_length_to_byte_length(this->m_pdata, (strsize)(this->metadata()->m_datasize + 1)); }


template < typename CHAR_TYPE >
void string_base < CHAR_TYPE >::resize(strsize n, CHAR_TYPE c)
{

   strsize nOldSize = length();

   if (n < nOldSize)
   {

      this->truncate(n);

   }
   else
   {

      auto psz = this->get_string_buffer(n);

      ::str().flood_characters(psz + nOldSize, c, n - nOldSize);

      this->release_string_buffer(n);

   }

}


