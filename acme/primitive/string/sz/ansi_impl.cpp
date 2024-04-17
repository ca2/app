// Refactored by camilo on 2022-11-04 05:43 <3ThomasBorregaardSorensen!!
#include "framework.h"

#include <string.h>
#include <stdio.h>
// CLASS_DECL_ACME  constexpr strsize     character_count_to_byte_length(const_ansichar_trigger, strsize nCharLength) { return (::memsize)((nCharLength) * sizeof(::ansi_character)); }
// CLASS_DECL_ACME  constexpr strsize     byte_length_to_character_count(const_ansichar_trigger, memsize nByteLength) { return (::strsize)((nByteLength / sizeof(::ansi_character))); }
// CLASS_DECL_ACME  constexpr strsize     null_terminated_character_count_to_byte_length(const_ansichar_trigger, strsize nCharLength) { return (::memsize)((nCharLength + 1) * sizeof(::ansi_character)); }
// CLASS_DECL_ACME  constexpr strsize     null_terminated_byte_length_to_character_count(const_ansichar_trigger, memsize nByteLength) { return (::strsize)((nByteLength / sizeof(::ansi_character)) - 1); }



CLASS_DECL_ACME void string_count_copy(::ansi_character * pchDest, const ::ansi_character * pchSrc, strsize nChars) noexcept { memory_copy(pchDest, pchSrc, character_count_to_byte_length(pchSrc, nChars)); }
CLASS_DECL_ACME void string_count_copy(::ansi_character * pchDest, size_t nDestLen, const ::ansi_character * pchSrc, strsize nChars) noexcept { ::memory_copy(pchDest, pchSrc, character_count_to_byte_length(pchSrc, nChars)); }
CLASS_DECL_ACME void overlapped_string_count_copy(::ansi_character * pchDest, const ::ansi_character * pchSrc, strsize nChars) noexcept { memory_transfer(pchDest, pchSrc, character_count_to_byte_length(pchSrc, nChars)); }


CLASS_DECL_ACME ::std::strong_ordering as_strong_ordering(int i)
{

   return i <=> 0;

}


CLASS_DECL_ACME ::std::strong_ordering _string_compare(const ::ansi_character * pszA, const ::ansi_character * pszB) noexcept { return ansi_cmp(pszA, pszB)<=>0; }
CLASS_DECL_ACME ::std::strong_ordering _string_compare_ci(const ::ansi_character * pszA, const ::ansi_character * pszB) noexcept { return ansi_icmp(pszA, pszB) <=> 0; }
CLASS_DECL_ACME ::std::strong_ordering _string_count_compare(const ::ansi_character * pszA, const ::ansi_character * pszB, strsize len) noexcept { return ansi_ncmp(pszA, pszB, len) <=> 0; }
CLASS_DECL_ACME ::std::strong_ordering _string_count_compare_ci(const ::ansi_character * pszA, const ::ansi_character * pszB, strsize len) noexcept { return ansi_nicmp(pszA, pszB, len) <=> 0; }
CLASS_DECL_ACME ::std::strong_ordering _string_collate(const ::ansi_character * pszA, const ::ansi_character * pszB) noexcept { return ansi_coll(pszA, pszB) <=> 0; }
CLASS_DECL_ACME ::std::strong_ordering _case_insensitive_string_collate(const ::ansi_character * pszA, const ::ansi_character * pszB) noexcept { return ansi_icoll(pszA, pszB) <=> 0; }
CLASS_DECL_ACME ::std::strong_ordering _string_count_collate(const ::ansi_character * pszA, const ::ansi_character * pszB, strsize len) noexcept { return ansi_ncoll(pszA, pszB, len) <=> 0; }
CLASS_DECL_ACME ::std::strong_ordering _case_insensitive_string_count_collate(const ::ansi_character * pszA, const ::ansi_character * pszB, strsize len) noexcept { return ansi_nicoll(pszA, pszB, len) <=> 0; }


CLASS_DECL_ACME ::std::strong_ordering string_compare(const ::ansi_character * pszA, const ::ansi_character * pszB) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return _string_compare(pszA, pszB); }
CLASS_DECL_ACME ::std::strong_ordering case_insensitive_string_order(const ::ansi_character * pszA, const ::ansi_character * pszB) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return _string_compare_ci(pszA, pszB); }
CLASS_DECL_ACME ::std::strong_ordering string_count_compare(const ::ansi_character * pszA, const ::ansi_character * pszB, strsize len) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return _string_count_compare(pszA, pszB, len); }
CLASS_DECL_ACME ::std::strong_ordering string_count_compare_ci(const ::ansi_character * pszA, const ::ansi_character * pszB, strsize len) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return  _string_count_compare_ci(pszA, pszB, len); }
CLASS_DECL_ACME ::std::strong_ordering string_collate(const ::ansi_character * pszA, const ::ansi_character * pszB) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return _string_collate(pszA, pszB); }
CLASS_DECL_ACME ::std::strong_ordering case_insensitive_string_collate(const ::ansi_character * pszA, const ::ansi_character * pszB) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return  _case_insensitive_string_collate(pszA, pszB); }
CLASS_DECL_ACME ::std::strong_ordering string_count_collate(const ::ansi_character * pszA, const ::ansi_character * pszB, strsize len) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return _string_count_collate(pszA, pszB, len); }
CLASS_DECL_ACME ::std::strong_ordering case_insensitive_string_count_collate(const ::ansi_character * pszA, const ::ansi_character * pszB, strsize len) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return _case_insensitive_string_count_collate(pszA, pszB, len); }


// defined at block
// CLASS_DECL_ACME strsize string_get_length(const ::ansi_character* psz) noexcept { return strlen(psz); }
CLASS_DECL_ACME strsize string_get_length(const ::ansi_character* psz, strsize sizeMaximumInterest) noexcept 
{ 
   strsize size = 0;
   sizeMaximumInterest++;
   while (*psz && sizeMaximumInterest > 0) { psz++; size++; sizeMaximumInterest--; }
   return sizeMaximumInterest == 0 ? -1 : size;
}
CLASS_DECL_ACME strsize string_safe_length(const ::ansi_character* psz, strsize sizeMaximumInterest) noexcept { if (::is_null(psz)) return 0; return string_get_length(psz, sizeMaximumInterest); }
// defined at block
//CLASS_DECL_ACME strsize string_safe_length(const ::ansi_character* psz) noexcept { if (::is_null(psz)) return 0; return string_get_length(psz); }
CLASS_DECL_ACME ::ansi_character * string_lowercase(::ansi_character * psz, strsize size) noexcept { ansi_lwr_s(psz, size); return  psz; }




CLASS_DECL_ACME const ::ansi_character * string_find_string(const ::ansi_character * pszBlock, const ::ansi_character * pszMatch) noexcept
{

   return ansi_find_string(pszBlock, pszMatch);

}


CLASS_DECL_ACME const ::ansi_character * string_find_string_ci(const ::ansi_character * pszBlock, const ::ansi_character * pszMatch) noexcept
{

   return ansi_find_string_ci(pszBlock, pszMatch);

}


CLASS_DECL_ACME const ::ansi_character * string_find_character(const ::ansi_character * pszBlock, ::ansi_character chMatch) noexcept
{

   return strchr(pszBlock, (::ansi_character)chMatch);

}


CLASS_DECL_ACME const ::ansi_character * string_find_character(const ::ansi_character * psz, const ::ansi_character * pszEnd, ::ansi_character chMatch) noexcept
{
   
   while(psz < pszEnd)
   {
      
      if(*psz == chMatch)
      {
       
         return psz;
         
      }
      
      psz++;
      
   }

   return nullptr;

}


CLASS_DECL_ACME const ::ansi_character * string_rear_find_string(const ::ansi_character * psz, const ::ansi_character * pszFind, strsize iStart) noexcept
{

   strsize iLen = strsize(strlen(psz));

   strsize iLenFind = strsize(strlen(pszFind));

   if (iStart < 0)
   {

      iStart = iLen + iStart;

   }

   if (iLenFind > iLen)
   {

      return nullptr;

   }

   iStart = minimum(iStart, iLen - iLenFind);

   while (iStart >= 0)
   {

      if (ansi_count_compare(&psz[iStart], pszFind, iLenFind) == 0)
      {

         return &psz[iStart];

      }

      iStart--;

   }

   return nullptr;

}




CLASS_DECL_ACME ::ansi_character * string_uppercase(::ansi_character * psz, strsize size) noexcept
{

   ansi_upr_s(psz, size);

   return psz;

}


CLASS_DECL_ACME ::ansi_character * string_reverse(::ansi_character * psz) noexcept
{

   if (psz == nullptr)
   {

      return nullptr;

   }

   string strReverse;

   ::ansi_character * p = psz + strlen(psz);

   ::ansi_character * pDec;

   while ((pDec = (::ansi_character *)unicode_decrement(psz, p)) != nullptr)
   {

      strReverse.append(pDec, pDec - p);

      p = pDec;

   }

#ifdef __GNUC__

   // To avoid GCC's:
   // /usr/include/x86_64-linux-gnu/bits/string_fortified.h:79:33: warning: argument 1 null where non-null expected
   // "GCC checks for non null but doesn't check for non null enoughieyr better than MSVC or Apple-CLANG"
   // gcc (Ubuntu 12.2.0-17ubuntu1) 12.2.0
   // Copyright (C) 2022 Free Software Foundation, Inc.
   //      This is free software; see the source for copying conditions.  There is
   // NO WARranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

   ::string strHolderBackup;

   auto pszHolderBackup = strHolderBackup.get_buffer(strReverse.length());

   strcpy(psz ? psz : pszHolderBackup, strReverse.c_str());

   strHolderBackup.release_buffer();

#else

   strcpy(psz, strReverse.c_str());

#endif

   return psz;

}



CLASS_DECL_ACME strsize  get_formatted_length(const ::ansi_character * pszFormat, va_list args) noexcept
{

#ifdef WINDOWS

   return _vscprintf(pszFormat, args);

#else

   return vsnprintf(nullptr, 0, pszFormat, args);

#endif

}


CLASS_DECL_ACME strsize _string_format(::ansi_character * pszBuffer, strsize nlength, const ::ansi_character * pszFormat, va_list args) noexcept
{

#ifdef WINDOWS

   return vsprintf_s(pszBuffer, (size_t)nlength, pszFormat, args);

#else

   return vsnprintf(pszBuffer, nlength, pszFormat, args);

#endif

}


CLASS_DECL_ACME const ::ansi_character * _string_rear_find_character(const ::ansi_character * psz, ::ansi_character ch) noexcept
{

   return _string_range(psz).rear_find(ch, ::comparison::comparison < ::ansi_character >());

}


CLASS_DECL_ACME void flood_characters(::ansi_character * psz, ::ansi_character ch, strsize len) noexcept
{

   ::memory_set(psz, ch, len);

}


CLASS_DECL_ACME ::ansi_character character_tolower(::ansi_character ch) noexcept { return ansi_char_tolower(ch); }
CLASS_DECL_ACME ::ansi_character character_toupper(::ansi_character ch) noexcept { return ansi_char_toupper(ch); }


CLASS_DECL_ACME bool character_isdigit(::ansi_character ch) noexcept { return ansi_char_isdigit(ch); }
CLASS_DECL_ACME bool character_isalpha(::ansi_character ch) noexcept { return ansi_char_isalpha(ch); }
CLASS_DECL_ACME bool character_isalnum(::ansi_character ch) noexcept { return ansi_char_isalnum(ch); }
CLASS_DECL_ACME bool character_isspace(::ansi_character ch) noexcept { return ansi_char_isspace(ch); }
CLASS_DECL_ACME bool character_isupper(::ansi_character ch) noexcept { return ch >= 'A' && ch <= 'Z'; }


CLASS_DECL_ACME bool character_isxdigit(::ansi_character ch) noexcept { return ansi_char_isxdigit(ch); }


// From STRSPN(3) - Linux Programmer's Manual
// The strspn() function calculates the length(in bytes) of the initial
// segment of s which consists entirely of bytes in accept.
// The strcspn() function calculates the length of the initial segment
// of s which consists entirely of bytes not in reject.

CLASS_DECL_ACME strsize string_skip_any_character_in(const ::ansi_character * pszBlock, const ::ansi_character * pszSet) noexcept
{

   return (strsize)strspn(pszBlock, pszSet);

}


CLASS_DECL_ACME strsize string_find_first_character_in(const ::ansi_character * pszBlock, const ::ansi_character * pszSet) noexcept
{

   return (strsize)strcspn(pszBlock, pszSet);

}


CLASS_DECL_ACME strsize unichar_count(const ::ansi_character * pstr) { return ansi_to_wd32_len(pstr); }


