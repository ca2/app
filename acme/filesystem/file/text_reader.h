// Created by camilo on 2022-04-26 05:41 <3ThomasBorregaardS�rensen!!
#pragma once


#include "acme/exception/parsing.h"
#include "acme/primitive/string/string_block.h"


class CLASS_DECL_ACME text_reader
{
public:


   const char * m_psz;


   text_reader() {}
   text_reader(const char * psz) : m_psz(psz) { }
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


   text_reader & operator >>(i8 & i)
   {

      i = *m_psz++;

      return *this;

   }




   text_reader & operator >>(i16 & sh)
   {

      read_integer(sh, m_psz);

      return *this;

   }


   text_reader & operator >>(u16 & u)
   {

      read_natural(u, m_psz);

      return *this;

   }


   text_reader & operator >>(i32 & i)
   {

      read_integer(i, m_psz);

      return *this;

   }


   text_reader & operator >>(u32 & u)
   {

      read_natural(u, m_psz);

      return *this;

   }


   text_reader & operator >>(i64 & i)
   {

      read_integer(i, m_psz);

      return *this;

   }


   text_reader & operator >>(u64 & u)
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


   text_reader & operator >>(property_set & set)
   {

      set.parse_network_payload(m_psz);

      return *this;

   }


   static string read_line(const char *& psz)
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


   static const_ansi_range read_word(const char *& psz)
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
   void read_natural(TYPE & t, const char *& psz)
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
   void read_integer(TYPE & t, const char *& psz)
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
   void read_float(TYPE & t, const char *& psz)
   {

      skip_whitespace(psz);

      auto pszStart = psz;

      t = (TYPE)strtod(psz, (char **) & psz);

      if (psz == pszStart)
      {

         throw parsing_exception("cannot text_reader::read_float from \"" + ellipsis(pszStart, 32) + "\"");

      }

   }


   static void skip_whitespace(const char *& psz)
   {

      while (unicode_is_whitespace(*psz))
      {

         psz++;

      }

   }


   static void paired_trim(const_ansi_range & block, const ::ansi_character * pszBeg, const ::ansi_character * pszEnd)
   {

      const ::ansi_character * pszBegChar = pszBeg;
      const ::ansi_character * pszEndChar = pszEnd;

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


   static string ellipsis(const char * psz, strsize maximum_length)
   {

      if (maximum_length < 3)
      {

         throw ::exception(error_bad_argument);

      }

      auto pszStart = psz;

      strsize i = 0;

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

         memcpy(pszBuffer, pszStart, maximum_length - 3);

         strcpy(pszBuffer + maximum_length - 3, "...");

      }
      else
      {

         memcpy(pszBuffer, pszStart, i);

      }

      str.release_buffer(i);

      return ::transfer(str);

   }

};



