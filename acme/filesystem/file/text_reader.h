// Created by camilo on 2022-04-26 05:41 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/exception/parsing.h"
#include "acme/prototype/string/string_block.h"


class CLASS_DECL_ACME text_reader
{
public:


   const_char_pointer m_psz;


   text_reader() {}
   text_reader(const_char_pointer psz) : m_psz(psz) { }
   text_reader(const text_reader & textreader) :
      m_psz(textreader.m_psz)
   {

   }
   text_reader(text_reader && textreader) :
      m_psz(textreader.m_psz)
   {
      textreader.m_psz = nullptr;
   }
   ~text_reader()
   {

   }


   text_reader & operator >>(bool & b)
   {

      skip_whitespace(m_psz);

      auto word = read_word(m_psz);

      paired_trim(word, "\"'([{", "\"')]}");

      if (word == "0")
      {

         b = false;

      }
      else if (word == "1")
      {

         b = true;

      }
      else if (word.case_insensitive_order("false") == 0)
      {

         b = false;

      }
      else if (word.case_insensitive_order("true") == 0)
      {

         b = true;

      }
      else if (word.case_insensitive_order("no") == 0)
      {

         b = false;

      }
      else if (word.case_insensitive_order("yes") == 0)
      {

         b = true;

      }
      else
      {

         throw parsing_exception("text_reader::operator >> (bool &) invalid value for boolean : \"" + string(word) + "\"");

      }

      return *this;

   }


   text_reader & operator >>(char & ch)
   {

      ch = *m_psz++;

      return *this;

   }


   text_reader & operator >>(unsigned char & uch)
   {

      uch = *((unsigned char *)m_psz);

      m_psz++;

      return *this;

   }


#ifdef WINDOWS


   text_reader & operator >>(unichar & wch)
   {

      wch = ::consume_unicode_index(m_psz);

      return *this;

   }


#endif


   //text_reader & operator >>(char & i)
   //{

   //   i = *m_psz++;

   //   return *this;

   //}




   text_reader & operator >>(short & sh)
   {

      read_integer(sh, m_psz);

      return *this;

   }


   text_reader & operator >>(unsigned short & u)
   {

      read_natural(u, m_psz);

      return *this;

   }


   text_reader & operator >>(int & i)
   {

      read_integer(i, m_psz);

      return *this;

   }


   text_reader & operator >>(unsigned int & u)
   {

      read_natural(u, m_psz);

      return *this;

   }


   text_reader & operator >>(long long & i)
   {

      read_integer(i, m_psz);

      return *this;

   }


   text_reader & operator >>(unsigned long long & u)
   {

      read_natural(u, m_psz);

      return *this;

   }


   text_reader & operator >>(float & f)
   {

      read_float(f, m_psz);

      return *this;

   }


   text_reader & operator >>(double & d)
   {

      read_float(d, m_psz);

      return *this;

   }


   text_reader & operator >>(string & str)
   {

      str = read_line(m_psz);

      return *this;

   }


   text_reader & operator >>(::property_set & set)
   {

      set.parse_network_payload(m_psz);

      return *this;

   }


   static string read_line(const_char_pointer &psz)
   {

      if (::is_null(psz))
      {

         return "";

      }

      if (*psz == '\0')
      {

         return "";

      }

      auto pszStart = psz;

      while (*psz != '\r' && *psz != '\n' && *psz != '\0')
      {

         psz++;

      }

      auto pszEnd = psz;

      if (*psz == '\n' && *(psz - 1) == '\r')
      {

         psz++;

      }

      return { pszStart, pszEnd - pszStart };

   }


   static const_ansi_range read_word(const_char_pointer &psz)
   {

      if (::is_null(psz))
      {

         return {};

      }

      if (*psz == '\0')
      {

         return {};

      }

      auto pszStart = psz;

      while (!character_isspace(*psz) && *psz != '\0')
      {

         psz++;

      }

      auto pszEnd = psz;

      if (*psz == '\n' && *(psz - 1) == '\r')
      {

         psz++;

      }

      return { pszStart, pszEnd - pszStart };

   }


   template < typename TYPE >
   void read_natural(TYPE & t, const_char_pointer &psz)
   {

      skip_whitespace(psz);

      auto pszStart = psz;

      auto l = strtol(psz, (char **) & psz, 10);

      if (psz == pszStart || l < 0)
      {

         throw parsing_exception("cannot text_reader::read_natural from \"" + ellipsis(pszStart, 20) + "\"");

      }

      t = (TYPE)l;

   }


   template < typename TYPE >
   void read_integer(TYPE & t, const_char_pointer &psz)
   {

      skip_whitespace(psz);

      auto pszStart = psz;

      t = (TYPE)strtol(psz, (char **) & psz, 10);

      if (psz == pszStart)
      {

         throw parsing_exception("cannot text_reader::read_integer from \"" + ellipsis(pszStart, 20) + "\"");

      }

   }


   template < typename TYPE >
   void read_float(TYPE & t, const_char_pointer &psz)
   {

      skip_whitespace(psz);

      auto pszStart = psz;

      t = (TYPE)strtod(psz, (char **) & psz);

      if (psz == pszStart)
      {

         throw parsing_exception("cannot text_reader::read_float from \"" + ellipsis(pszStart, 32) + "\"");

      }

   }


   static void skip_whitespace(const_char_pointer &psz)
   {

      while (unicode_is_whitespace(*psz))
      {

         psz++;

      }

   }


   static void paired_trim(const_ansi_range & block, const_char_pointer pszBeg, const_char_pointer pszEnd)
   {

      const_char_pointer pszBegChar = pszBeg;
      const_char_pointer pszEndChar = pszEnd;

      for (;
         *pszBegChar != '\0' &&
         *pszEndChar != '\0';
         pszBegChar++,
         pszEndChar++
         )
      {

         if (*block.begin() == *pszBegChar && *(block.end() - 1) == *pszEndChar)
         {

            block.begin()++;
            block.end()--;

            pszBegChar = pszBeg;
            pszEndChar = pszEnd;

         }

      }

   }


   static string ellipsis(const_char_pointer psz, character_count maximum_length)
   {

      if (maximum_length < 3)
      {

         throw ::exception(error_bad_argument);

      }

      auto pszStart = psz;

      character_count i = 0;

      for (; i < maximum_length; i++, psz++)
      {

         if (*psz == '\0')
         {

            break;

         }

      }

      string str;

      auto pszBuffer = str.get_buffer(i);

      if (i == maximum_length && *psz != '\0')
      {

         memory_copy(pszBuffer, pszStart, maximum_length - 3);

         ansi_copy(pszBuffer + maximum_length - 3, "...");

      }
      else
      {

         memory_copy(pszBuffer, pszStart, i);

      }

      str.release_buffer(i);

      return ::transfer(str);

   }

};



