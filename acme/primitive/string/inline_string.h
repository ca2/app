// Created by camilo on 2022-11-11 17:14 <3ThomasBorregaardSorensen!!
#pragma once


#include "string_range.h"


template < primitive_character CHARACTER, strsize m_sizeMaximumLength >
class inline_string :
   public ::string_range < CHARACTER * >
{
public:


   CHARACTER m_sz[m_sizeMaximumLength + 1];

   
   constexpr inline_string() :
      ::string_range < CHARACTER * >(e_no_initialize)
   {
      
      this->m_begin = m_sz;
      this->m_end = this->m_begin;
      this->m_erange = e_range_null_terminated;
      m_sz[0] = 0;

   }


   inline_string(const CHARACTER* psz) :
      inline_string()
   {
      
      while (*psz && this->size() < m_sizeMaximumLength)
      {
         
         *this->m_end = *psz;
         
         this->m_end++;
         
         psz++;

      }

      *this->m_end = '\0';

   }


   inline_string(const inline_string & inlinestring) = default;


   //const CHARACTER* c_str() { return m_sz; }


   //operator const CHARACTER* () const { return m_sz; }
   //operator CHARACTER* () { return m_sz; }


   //const CHARACTER * data() const { return m_sz; }
   //CHARACTER * data() { return m_sz; }

   //const CHARACTER * begin() const { return data(); }
   //CHARACTER * begin() { return data(); }

   //const CHARACTER * end() const { return data() + size(); }
   //CHARACTER * end() { return data() + size(); }

   //strsize size() const { return ::maximum(0, m_iLength); }
   //strsize length_in_bytes() const { return size() * sizeof(CHARACTER); }

   //operator ::block() const { return { data(), size() }; }


};



using inline_number_string = inline_string < char, 64 >;




