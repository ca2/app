//
// Created by camilo on 23/12/2022 <3ThomasBorregaardSorensen!!
//

inline ::string ellipsis(const ::ansi_character * psz, character_count len)
{

   auto lenTotal = string_safe_length(psz, len);

   if (lenTotal < 0)
   {

      return ::string(psz, len - 3) + "...";

   }
   else
   {

      return psz;

   }

}


//inline unsigned long long consume_natural(const char*& psz, const ::ansi_character * pszBegin, int iRadix = 10)
inline unsigned long long consume_natural(const char*& psz, const ::ansi_character * pszBegin, int iRadix)
{

   char* endptr = nullptr;

   auto u = strtoull(psz, &endptr, iRadix);

   if (!endptr)
   {

      if (::is_null(pszBegin))
      {

         pszBegin = psz;

      }

      throw_exception(error_premature_end_of_file, "not natural number near \"" + ellipsis(maximum(psz - 10, pszBegin), 20) + "\"");

   }

   psz = endptr;

   return u;

}


inline long long consume_integer(const char * & psz, const ::ansi_character * pszBegin, int iRadix)
//inline long long consume_integer(const char * & psz, const ::ansi_character * pszBegin, int iRadix = 10)
{

   char* endptr = nullptr;

   auto i = strtoll(psz, &endptr, 10);

   if (!endptr)
   {

      if (::is_null(pszBegin))
      {

         pszBegin = psz;

      }

      throw_exception(error_parsing, "not integer near \"" + ellipsis(maximum(psz - 10, pszBegin), 20) + "\"");

   }

   psz = endptr;

   return i;

}


inline double consume_floating(const char*& psz, const ::ansi_character * pszBegin, int iRadix = 10)
{

   char* endptr = nullptr;

   auto d = strtod(psz, &endptr);

   if (!endptr)
   {

      if (::is_null(pszBegin))
      {

         pszBegin = psz;

      }

      throw_exception(error_premature_end_of_file, "not floating near \"" + ellipsis(maximum(psz - 10, pszBegin), 20) + "\"");

   }

   psz = endptr;

   return d;

}


#include "_impl_text_stream.h"

