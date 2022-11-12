// Created by camilo on 2022-11-11 17:14 <3ThomasBorregaardSorensen!!
#pragma once


template < primitive_character CHARACTER, strsize m_sizeMaximumLength >
class inline_string
{
public:


   CHARACTER m_sz[m_sizeMaximumLength + 1];
   int m_iLength;

   
   inline_string()
   {
      
      memset(this, 0, sizeof(*this));

   }


   inline_string(const CHARACTER* psz)
   {

      auto len = string_safe_length(psz, 7);

      ::i32 i = 0;

      for (; i < len; i++)
      {

         m_sz[i] = psz[i];

      }

      m_sz[i] = '\0';

      m_iLength = i;

   }


   inline_string(const inline_string& inlinestring)
   {

      for (int i = 0; i < m_sizeMaximumLength; i++)
      {

         m_sz[i] = inlinestring.m_sz[i];

      }

      m_iLength = inlinestring.m_iLength;

   }



   operator const CHARACTER* () const { return m_sz; }
   operator CHARACTER* () { return m_sz; }


};



using inline_number_string = inline_string < char, 64 >;




