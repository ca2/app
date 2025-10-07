// Created by camilo on 2025-09-14 03:37 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "utf8_character.h"

// GitHub MightyPork / utf8_encode.c

utf8_character::utf8_character(long long i)
{

   auto& out = this->m_sz;
   this->m_begin = out;
   if (i <= 0x7F) {
      // Plain ASCII
      out[0] = (char)i;
      out[1] = 0;
      this->m_end = this->m_begin + 1;
   }
   else if (i <= 0x07FF) {
      // 2-unsigned char unicode
      out[0] = (char)(((i >> 6) & 0x1F) | 0xC0);
      out[1] = (char)(((i >> 0) & 0x3F) | 0x80);
      out[2] = 0;
      this->m_end = this->m_begin + 2;
   }
   else if (i <= 0xFFFF) {
      // 3-unsigned char unicode
      out[0] = (char)(((i >> 12) & 0x0F) | 0xE0);
      out[1] = (char)(((i >> 6) & 0x3F) | 0x80);
      out[2] = (char)(((i >> 0) & 0x3F) | 0x80);
      out[3] = 0;
      this->m_end = this->m_begin + 3;
   }
   else if (i <= 0x10FFFF) {
      // 4-unsigned char unicode
      out[0] = (char)(((i >> 18) & 0x07) | 0xF0);
      out[1] = (char)(((i >> 12) & 0x3F) | 0x80);
      out[2] = (char)(((i >> 6) & 0x3F) | 0x80);
      out[3] = (char)(((i >> 0) & 0x3F) | 0x80);
      out[4] = 0;
      this->m_end = this->m_begin + 4;
   }
   else {
      // error - use replacement character
      out[0] = (char)0xEF;
      out[1] = (char)0xBF;
      out[2] = (char)0xBD;
      out[3] = 0;
      this->m_end = this->m_begin + 3;
   }

}


character_count unicode_to_utf8_length(long long i)
{
   if (i < 0)
   {
      return -1;
   }
   else if (i <= 0x7F)
   {
      return 1;
   }
   else if (i <= 0x07FF)
   {
      return 2;
   }
   else if (i <= 0xFFFF)
   {
      return 3;
   }
   else if (i <= 0x10FFFF)
   {
      return 4;
   }
   else
   {
      return -1;
   }

}


long long utf8_character::index() const
{

   if (m_llIndex < 0)
   {

      m_llIndex = unicode_index(m_sz);

   }

   return m_llIndex;


}


character_count utf8_character::get_next(const character_range < const_char_pointer >& range, character_count charactercount)
{

   this->m_begin = m_sz;

   auto psz = range.m_begin + charactercount;

   m_llIndex = -1;

   character_count remaining = range.size() - charactercount;

   auto pszNext = unicode_next(psz, &remaining);

   character_count charactercountUtf8 = pszNext - psz;

   switch (charactercountUtf8)
   {
   case 0:
      m_llIndex = 0;
      break;
   case 1:
      m_sz[0] = psz[0];
      m_sz[1] = '\0';
      break;
   case 2:
      m_sz[0] = psz[0];
      m_sz[1] = psz[1];
      m_sz[2] = '\0';
      break;
   case 3:
      m_sz[0] = psz[0];
      m_sz[1] = psz[1];
      m_sz[2] = psz[2];
      m_sz[3] = '\0';
      break;
   case 4:
      m_sz[0] = psz[0];
      m_sz[1] = psz[1];
      m_sz[2] = psz[2];
      m_sz[3] = psz[3];
      m_sz[4] = '\0';
      break;
   case 5:
      m_sz[0] = psz[0];
      m_sz[1] = psz[1];
      m_sz[2] = psz[2];
      m_sz[3] = psz[3];
      m_sz[4] = psz[4];
      m_sz[5] = '\0';
      break;
   case 6:
      m_sz[0] = psz[0];
      m_sz[1] = psz[1];
      m_sz[2] = psz[2];
      m_sz[3] = psz[3];
      m_sz[4] = psz[4];
      m_sz[5] = psz[5];
      m_sz[6] = '\0';
      break;
   case 7:
      m_sz[0] = psz[0];
      m_sz[1] = psz[1];
      m_sz[2] = psz[2];
      m_sz[3] = psz[3];
      m_sz[4] = psz[4];
      m_sz[5] = psz[5];
      m_sz[6] = psz[6];
      m_sz[7] = '\0';
      break;

   }

   this->m_end = this->m_begin + charactercountUtf8;

   charactercount += charactercountUtf8;

   if (charactercount > range.size())
   {

      throw_encoding_exception("not enough characters");

   }

   return charactercount;

}