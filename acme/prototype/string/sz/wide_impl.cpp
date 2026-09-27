// Refactored by camilo on 2022-11-04 05:42 <3ThomasBorregaardSorensen!!
#include "platform.h"
#include "_template.h"
#include <wchar.h>
//CLASS_DECL_ACME  constexpr character_count     character_count_to_byte_length(const_widechar_trigger, character_count nCharLength) { return (::memsize)(nCharLength * sizeof(::wide_character)); }
//CLASS_DECL_ACME  constexpr character_count     byte_length_to_character_count(const_widechar_trigger, memsize nByteLength) { return (::character_count)(nByteLength / sizeof(::wide_character)); }


CLASS_DECL_ACME void string_count_copy(::wide_character * pchDest, const ::wide_character * pchSrc, character_count nChars) noexcept { memory_copy(pchDest, pchSrc, character_count_to_byte_length(pchSrc, nChars)); }
CLASS_DECL_ACME void string_count_copy(::wide_character * pchDest, size_t nDestLen, const ::wide_character * pchSrc, character_count nChars) noexcept { ::memory_copy(pchDest, pchSrc, character_count_to_byte_length(pchSrc, nChars)); }
CLASS_DECL_ACME void overlapped_string_count_copy(::wide_character * pchDest, const ::wide_character * pchSrc, character_count nChars) noexcept { memory_transfer(pchDest, pchSrc, character_count_to_byte_length(pchSrc, nChars)); }


CLASS_DECL_ACME ::i32 _string_compare(const ::wide_character * pszA, const ::wide_character * pszB) noexcept { return wide_cmp(pszA, pszB); }
CLASS_DECL_ACME ::i32 case_insensitive__string_compare(const ::wide_character * pszA, const ::wide_character * pszB) noexcept { return wide_icmp(pszA, pszB); }
CLASS_DECL_ACME ::i32 case_insensitive__string_count_compare(const ::wide_character * pszA, const ::wide_character * pszB, character_count len) noexcept { return wide_nicmp(pszA, pszB, len); }
CLASS_DECL_ACME  ::std::strong_ordering _string_collate(const ::wide_character * pszA, const ::wide_character * pszB) noexcept { return wide_coll(pszA, pszB) <=> 0; }
CLASS_DECL_ACME ::std::strong_ordering _case_insensitive_string_collate(const ::wide_character * pszA, const ::wide_character * pszB) noexcept { return wide_icoll(pszA, pszB) <=> 0; }
CLASS_DECL_ACME ::std::strong_ordering _string_count_collate(const ::wide_character * pszA, const ::wide_character * pszB, character_count len) noexcept { return wide_ncoll(pszA, pszB, len) <=> 0; }
CLASS_DECL_ACME ::std::strong_ordering _case_insensitive_string_count_collate(const ::wide_character * pszA, const ::wide_character * pszB, character_count len) noexcept { return wide_nicoll(pszA, pszB, len) <=> 0; }




CLASS_DECL_ACME ::i32 string_compare(const ::wide_character * pszA, const ::wide_character * pszB) noexcept { ::i32 ordering = 0; if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return _string_compare(pszA, pszB); }
CLASS_DECL_ACME ::i32 case_insensitive_string_compare(const ::wide_character * pszA, const ::wide_character * pszB) noexcept { ::i32 ordering = 0; if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return case_insensitive__string_compare(pszA, pszB); }
CLASS_DECL_ACME ::i32 string_count_compare(const ::wide_character * pszA, const ::wide_character * pszB, character_count len) noexcept { ::i32 ordering = 0; if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return _string_count_compare(pszA, pszB, len); }
CLASS_DECL_ACME ::i32 case_insensitive_string_count_compare(const ::wide_character * pszA, const ::wide_character * pszB, character_count len) noexcept { ::i32 ordering = 0; if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return  case_insensitive__string_count_compare(pszA, pszB, len); }
CLASS_DECL_ACME ::std::strong_ordering string_collate(const ::wide_character * pszA, const ::wide_character * pszB) noexcept { ::std::strong_ordering ordering(1<=>1); if (string_order_prefix(ordering, pszA, pszB)) return ordering; return _string_collate(pszA, pszB); }
CLASS_DECL_ACME ::std::strong_ordering case_insensitive_string_collate(const ::wide_character * pszA, const ::wide_character * pszB) noexcept { ::std::strong_ordering ordering(1<=>1); if (string_order_prefix(ordering, pszA, pszB)) return ordering; return  _case_insensitive_string_collate(pszA, pszB); }
CLASS_DECL_ACME ::std::strong_ordering string_count_collate(const ::wide_character * pszA, const ::wide_character * pszB, character_count len) noexcept { ::std::strong_ordering ordering(1<=>1); if (string_order_prefix(ordering, pszA, pszB)) return ordering; return _string_count_collate(pszA, pszB, len); }
CLASS_DECL_ACME ::std::strong_ordering case_insensitive_string_count_collate(const ::wide_character * pszA, const ::wide_character * pszB, character_count len) noexcept { ::std::strong_ordering ordering(1<=>1); if (string_order_prefix(ordering, pszA, pszB)) return ordering; return _case_insensitive_string_count_collate(pszA, pszB, len); }


CLASS_DECL_ACME character_count string_get_length(const ::wide_character * psz) noexcept { return wide_len(psz); }
// CLASS_DECL_ACME character_count string_get_length(const ::wide_character* psz, character_count sizeMaximumInterest) noexcept
// {
//    character_count size = 0;
//    sizeMaximumInterest++;
//    while (*psz && sizeMaximumInterest > 0) { psz++; size++; sizeMaximumInterest--; }
//    return sizeMaximumInterest == 0 ? -1 : size;
// }


CLASS_DECL_ACME character_count string_get_length2(const ::wide_character* psz, character_count lengthMax) noexcept 
{ 

   return _string_get_length2(psz, lengthMax);
   
   // character_count size = 0;

   // while (lengthMax > 0 && *psz) 
   // { 
      
   //    psz++; 
      
   //    size++; 
      
   //    lengthMax--; 
   
   // }

   // return size;

}


CLASS_DECL_ACME character_count string_safe_length(const ::wide_character * psz) noexcept { if (::is_null(psz)) return 0; return string_get_length(psz); }
CLASS_DECL_ACME character_count string_safe_length2(const ::wide_character* psz, character_count sizeMaximumInterest) noexcept 
{
    if (::is_null(psz)) return 0; return string_get_length2(psz, sizeMaximumInterest); 
   
}
CLASS_DECL_ACME ::wide_character * string_lowercase(::wide_character * psz, character_count size) noexcept { wide_lwr_s(psz, size); return  psz; }





CLASS_DECL_ACME const ::wide_character * string_find_string(const ::wide_character * pszBlock, const ::wide_character * pszMatch) noexcept
{

   return wide_str(pszBlock, pszMatch);

}


CLASS_DECL_ACME const ::wide_character * case_insensitive_string_find_string(const ::wide_character * pszBlock, const ::wide_character * pszMatch) noexcept
{

   return wide_find_string_case_insensitive(pszBlock, pszMatch);

}


CLASS_DECL_ACME const ::wide_character * string_find_character(const ::wide_character * pszBlock, ::wide_character chMatch) noexcept
{

   return wide_chr(pszBlock, (::wide_character)chMatch);

}


CLASS_DECL_ACME const ::wide_character * string_find_character(const ::wide_character * psz, const ::wide_character * pszEnd, ::wide_character chMatch) noexcept
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


CLASS_DECL_ACME const ::wide_character * string_rear_find_string(const ::wide_character * psz, const ::wide_character * pszFind, character_count iStart) noexcept
{
   character_count iLen = character_count(wide_len(psz));
   character_count iLenFind = character_count(wide_len(pszFind));
   if (iStart < 0)
      iStart = iLen + iStart;
   if (iLenFind > iLen)
      return nullptr;
   iStart = minimum(iStart, iLen - iLenFind);
   while (iStart >= 0)
   {
      if (wide_ncmp(&psz[iStart], pszFind, iLenFind) == 0)
         return &psz[iStart];
      iStart--;
   }
   return nullptr;
}




CLASS_DECL_ACME ::wide_character * string_uppercase(::wide_character * psz, character_count size) noexcept
{

   wide_upr_s(psz, size);

   return psz;

}


CLASS_DECL_ACME ::wide_character * string_reverse(::wide_character * psz) noexcept
{

   if (psz == nullptr)
   {

      return nullptr;

   }

   ::wide_character * p1 = psz;

   ::wide_character * p2 = psz + (wide_len(psz) - 1);

   while (p2 > p1)
   {

      __swap(*p1, *p2);

      p1++;

      p2--;

   }

   return psz;

}


CLASS_DECL_ACME character_count  get_formatted_length(const ::wide_character * pszFormat, va_list args) noexcept
{

#ifdef WINDOWS

   wstring wstr(pszFormat);

   return _vscwprintf(wstr.c_str(), args);

#else

   wide_string wstr(pszFormat);

   wide_character dummy;

   return vswprintf(&dummy, 0, pszFormat, args);

#endif

}


CLASS_DECL_ACME character_count _string_format(::wide_character * pszBuffer, const ::wide_character * pszFormat, va_list args) noexcept
{

#ifdef WINDOWS

   va_list argsLength;

   va_copy(argsLength, args);

   auto nlength = _vscwprintf(pszFormat, argsLength);

   va_end(argsLength);

   if (nlength < 0)
   {

      return nlength;

   }

   return _vswprintf(pszBuffer, pszFormat, args);

#else

   return vswprintf(pszBuffer, get_formatted_length(pszFormat, args), pszFormat, args);

#endif

}


CLASS_DECL_ACME character_count _string_format(::wide_character * pszBuffer, character_count nlength, const ::wide_character * pszFormat, va_list args) noexcept
{

#ifdef WINDOWS

   return vswprintf_s(pszBuffer, (size_t)nlength, pszFormat, args);

#else

   return vswprintf(pszBuffer, nlength, pszFormat, args);

#endif

}


CLASS_DECL_ACME const ::wide_character * string_rear_find_character(const ::wide_character * psz, ::wide_character ch) noexcept
{

   return _string_range(psz).rear_find(ch, ::comparison::comparison < ::wide_character >());

}


CLASS_DECL_ACME void  flood_characters(::wide_character * pwsz, ::wide_character wch, character_count len) noexcept
{

   while (len > 0)
   {

      *pwsz = wch;

      pwsz++;

      len--;

   }

}





CLASS_DECL_ACME ::wide_character character_tolower(::wide_character ch) noexcept { return wide_char_tolower(ch); }
CLASS_DECL_ACME ::wide_character character_toupper(::wide_character ch) noexcept { return wide_char_toupper(ch); }


CLASS_DECL_ACME bool character_isdigit(::wide_character ch) noexcept { return wide_char_isdigit(ch); }
CLASS_DECL_ACME bool character_isalpha(::wide_character ch) noexcept { return wide_char_isalpha(ch); }
CLASS_DECL_ACME bool character_isalnum(::wide_character ch) noexcept { return wide_char_isalnum(ch); }
CLASS_DECL_ACME bool character_isspace(::wide_character ch) noexcept { return wide_char_isspace(ch); }


CLASS_DECL_ACME bool character_isxdigit(::wide_character ch) noexcept { return wide_char_isxdigit(ch); }



CLASS_DECL_ACME character_count  string_skip_any_character_in(const ::wide_character * pszBlock, const ::wide_character * pszSet) noexcept
{

   return (character_count)wide_spn(pszBlock, pszSet);

}



CLASS_DECL_ACME character_count  string_find_first_character_in(const ::wide_character * pszBlock, const ::wide_character * pszSet) noexcept
{

   return (character_count)wide_cspn(pszBlock, pszSet);

}



CLASS_DECL_ACME character_count unichar_count(const ::wide_character * pstr) { return __widelen(pstr); }


