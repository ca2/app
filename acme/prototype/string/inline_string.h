// Created by camilo on 2022-11-11 17:14 <3ThomasBorregaardSorensen!!
#pragma once


//#include "string_range.h"


template < primitive_character CHARACTER, character_count m_sizeMaximumLength >
class inline_string :
   //public ::range < CHARACTER * >
   public ::range < const CHARACTER * >
{
public:


   CHARACTER m_sz[m_sizeMaximumLength + 1];

   
   constexpr inline_string() :
      ::range < const CHARACTER * >(no_initialize_t{})
   {
      
      this->m_begin = m_sz;
      this->m_end = this->m_begin;
      m_sz[0] = '\0';

   }


   constexpr inline_string(const CHARACTER* psz) :
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


   constexpr inline_string(const inline_string & inlinestring)
   {
      memory_copy(m_sz, inlinestring.m_sz, sizeof(m_sz));
      this->m_begin = m_sz;
      this->m_end = m_sz + inlinestring.size();
      this->m_erange = inlinestring.m_erange;
   }


   //const CHARACTER* c_str() { return m_sz; }


   //operator const CHARACTER* () const { return m_sz; }
   //operator CHARACTER* () { return m_sz; }


   //const CHARACTER * data() const { return m_sz; }
   //CHARACTER * data() { return m_sz; }

   //const CHARACTER * begin() const { return data(); }
   //CHARACTER * begin() { return data(); }

   //const CHARACTER * end() const { return data() + size(); }
   //CHARACTER * end() { return data() + size(); }

   //character_count size() const { return ::maximum(0, m_iLength); }
   //character_count length_in_bytes() const { return size() * sizeof(CHARACTER); }

   //operator ::block() const { return { data(), size() }; }


};


template < primitive_number NUMBER >
inline string as_string(NUMBER number, const_char_pointer pszFormat);

// template < primitive_unsigned UNSIGNED >
// inline inline_number_string as_string(UNSIGNED u, int radix = 10, enum_digit_case edigitcase = e_digit_case_lower);

template < primitive_integral INTEGRAL >
inline inline_number_string as_string(INTEGRAL i, int radix = 10, enum_digit_case edigitcase = e_digit_case_lower);



