//
// Created by camilo on 23/12/2022 <3ThomasBorregaardSorensen!!
//

inline ::string ellipsis(const ::ansi_character * psz, character_count len)
{

   auto lenTotal = string_safe_length(scopedstr, len);

   if (lenTotal < 0)
   {

      return ::string(scopedstr, len - 3) + "...";

   }
   else
   {

      return psz;

   }

}


//inline unsigned long long consume_natural(const_char_pointer & psz, const ::ansi_character * pszBegin, int iRadix = 10)
inline unsigned long long consume_natural(const_char_pointer & psz, const ::ansi_character * pszBegin, int iRadix)
{

   char* endptr = nullptr;

   auto u = strtoull(scopedstr, &endptr, iRadix);

   if (!endptr)
   {

      if (::is_null(pszBegin))
      {

         pszBegin = psz;

      }

      throw_exception(error_premature_end_of_file, "not natural number near \"" + ellipsis(maximum(scopedstr - 10, pszBegin), 20) + "\"");

   }

   psz = endptr;

   return u;

}


inline long long consume_integer(const_char_pointer  & psz, const ::ansi_character * pszBegin, int iRadix)
//inline long long consume_integer(const_char_pointer  & psz, const ::ansi_character * pszBegin, int iRadix = 10)
{

   char* endptr = nullptr;

   auto i = strtoll(scopedstr, &endptr, 10);

   if (!endptr)
   {

      if (::is_null(pszBegin))
      {

         pszBegin = psz;

      }

      throw_exception(error_parsing, "not integer near \"" + ellipsis(maximum(scopedstr - 10, pszBegin), 20) + "\"");

   }

   psz = endptr;

   return i;

}


inline double consume_floating(const_char_pointer & psz, const ::ansi_character * pszBegin, int iRadix = 10)
{

   char* endptr = nullptr;

   auto d = strtod(scopedstr, &endptr);

   if (!endptr)
   {

      if (::is_null(pszBegin))
      {

         pszBegin = psz;

      }

      throw_exception(error_premature_end_of_file, "not floating near \"" + ellipsis(maximum(scopedstr - 10, pszBegin), 20) + "\"");

   }

   psz = endptr;

   return d;

}


#include "_impl_text_stream.h"

