// Created by camilo on 2022-11-10 22:40 <3ThomasBorregaardSorensen!!
#pragma once


#include "inline_string.h"


class CLASS_DECL_ACME utf8_character :
   public inline_string < ::ansi_character, 8 >
{
public:


   mutable long long m_llIndex = -1;


   utf8_character() {}
   utf8_character(long long ch);


   character_count get_next(const character_range < const_char_pointer >& range, character_count charactercount);


   long long index() const;

   bool operator == (ansi_character ansicharacter) const
   {

      if (ansicharacter < 0)
      {

         throw ::exception(error_bad_argument);

      }

      auto llIndex = index();

      return ansicharacter == llIndex;
      
   }

   
   ansi_character ansi_lower() const
   {

      auto llIndex = index();

      if (llIndex >= 128)
      {

         throw ::exception(error_wrong_state, "not an ansi character");

      }

      return character_tolower((ansi_character)llIndex);

   }


   ansi_character ansi_uppwer() const
   {

      auto llIndex = index();

      if (llIndex >= 128)
      {

         throw ::exception(error_wrong_state, "not an ansi character");

      }

      return character_toupper((ansi_character)llIndex);

   }

   bool is_space() const
   {
      
      return wd32_char_isspace((wd32_character) index());

   }

   bool is_ansi_space() const
   {

      auto llIndex = index();

      if (llIndex >= 128)
      {

         return false;

      }

      return character_isspace((ansi_character)llIndex);

   }
   
   
   bool is_ansi_alpha() const
   {

      auto llIndex = index();

      if (llIndex >= 128)
      {

         return false;

      }

      return character_isalpha((ansi_character)llIndex);

   }


   bool is_ansi_digit() const
   {

      auto llIndex = index();

      if (llIndex >= 128)
      {

         return false;

      }

      return character_isdigit((ansi_character)llIndex);

   }

   bool is_ansi_alpha_or_digit() const
   {

      auto llIndex = index();

      if (llIndex >= 128)
      {

         return false;

      }

      return character_isalpha((ansi_character)llIndex)
         || character_isdigit((ansi_character)llIndex);
   }

};


class CLASS_DECL_ACME utf8_character_range :
   public utf8_character
{
public:


   character_range < const_char_pointer >& m_range;

   character_count m_i;

   character_count m_iNext;

   utf8_character_range(const utf8_character_range& range) :
      m_range(range.m_range),
      m_i(range.m_i),
      m_iNext(range.m_i)
   {
      this->m_begin = range.m_begin;
      this->m_end = range.m_end;
      this->m_erange = range.m_erange;
      this->m_llIndex = -1;
      memory_copy(m_sz, range.m_sz, sizeof(m_sz));


   }

   utf8_character_range(character_range < const_char_pointer >& range, character_count i = 0) :
      m_range(range)
   {

      m_i = i;

      this->m_llIndex = -1;

      get();

   }

   utf8_character_range& get()
   {

      if (m_llIndex < 0)
      {
         
         m_iNext = ::utf8_character::get_next(m_range, m_i);
         
         this->index();

      }

      return *this;

   }


   utf8_character_range& operator++()
   {
      
      m_i = m_iNext;

      m_llIndex = -1;
      
      get();

      return *this;

   }


   utf8_character_range operator++(int)
   {

      utf8_character_range ret = *this;

      ++(*this);

      return ret;

   }


   utf8_character_range & operator+=(character_count count)
   {

      auto c = count;

      while (c > 0)
      {

         ++(*this);

         c--;

      }

      return *this;

   }


   utf8_character_range& ansi_add(character_count count)
   {

      m_i += count;

      m_llIndex = -1;

      this->get();

      return *this;

   }



  


   utf8_character_range next() const
   {

      return { m_range, m_iNext };

   }



   using utf8_character::operator == ;



};