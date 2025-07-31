// Refactored by camilo on 2022-11-04 05:42 <3ThomasBorregaardSorensen!!
#include "framework.h"

#include <wchar.h>
//CLASS_DECL_ACME  constexpr character_count     character_count_to_byte_length(const_wd32char_trigger, character_count nCharLength) { return (::memsize)(nCharLength * sizeof(::wd32_character)); }
//CLASS_DECL_ACME  constexpr character_count     byte_length_to_character_count(const_wd32char_trigger, memsize nByteLength) { return (::character_count)(nByteLength / sizeof(::wd32_character)); }


CLASS_DECL_ACME void string_count_copy(::wd32_character * pchDest, const ::wd32_character * pchSrc, character_count nChars) noexcept { memory_copy(pchDest, pchSrc, character_count_to_byte_length(pchSrc, nChars)); }
CLASS_DECL_ACME void string_count_copy(::wd32_character * pchDest, size_t nDestLen, const ::wd32_character * pchSrc, character_count nChars) noexcept { ::memory_copy(pchDest, pchSrc, character_count_to_byte_length(pchSrc, nChars)); }
CLASS_DECL_ACME void overlapped_string_count_copy(::wd32_character * pchDest, const ::wd32_character * pchSrc, character_count nChars) noexcept { memory_transfer(pchDest, pchSrc, character_count_to_byte_length(pchSrc, nChars)); }


CLASS_DECL_ACME ::std::strong_ordering _string_compare(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept { return wd32_cmp(scopedstrA, pszB)<=>0; }
CLASS_DECL_ACME ::std::strong_ordering case_insensitive__string_compare(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept { return wd32_icmp(scopedstrA, pszB) <=> 0; }
//CLASS_DECL_ACME ::std::strong_ordering _string_count_compare(const ::wd32_character * pszA, const ::wd32_character * pszB, character_count len) noexcept { return wd32_ncmp(scopedstrA, pszB, len) <=> 0; }
CLASS_DECL_ACME ::std::strong_ordering case_insensitive__string_count_compare(const ::wd32_character * pszA, const ::wd32_character * pszB, character_count len) noexcept { return wd32_nicmp(scopedstrA, pszB, len) <=> 0; }
CLASS_DECL_ACME ::std::strong_ordering _string_collate(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept { return wd32_coll(scopedstrA, pszB) <=> 0; }
CLASS_DECL_ACME ::std::strong_ordering _case_insensitive_string_collate(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept { return wd32_icoll(scopedstrA, pszB) <=> 0; }
CLASS_DECL_ACME ::std::strong_ordering _string_count_collate(const ::wd32_character * pszA, const ::wd32_character * pszB, character_count len) noexcept { return wd32_ncoll(scopedstrA, pszB, len) <=> 0; }
CLASS_DECL_ACME ::std::strong_ordering _case_insensitive_string_count_collate(const ::wd32_character * pszA, const ::wd32_character * pszB, character_count len) noexcept { return wd32_nicoll(scopedstrA, pszB, len) <=> 0; }




CLASS_DECL_ACME ::std::strong_ordering string_compare(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return _string_compare(scopedstrA, pszB); }
CLASS_DECL_ACME ::std::strong_ordering case_insensitive_string_order(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return case_insensitive__string_compare(scopedstrA, pszB); }
CLASS_DECL_ACME ::std::strong_ordering string_count_compare(const ::wd32_character * pszA, const ::wd32_character * pszB, character_count len) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return _string_count_compare(scopedstrA, pszB, len); }
CLASS_DECL_ACME ::std::strong_ordering case_insensitive_string_count_compare(const ::wd32_character * pszA, const ::wd32_character * pszB, character_count len) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return  case_insensitive__string_count_compare(scopedstrA, pszB, len); }
CLASS_DECL_ACME ::std::strong_ordering string_collate(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return _string_collate(scopedstrA, pszB); }
CLASS_DECL_ACME ::std::strong_ordering case_insensitive_string_collate(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return  _case_insensitive_string_collate(scopedstrA, pszB); }
CLASS_DECL_ACME ::std::strong_ordering string_count_collate(const ::wd32_character * pszA, const ::wd32_character * pszB, character_count len) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return _string_count_collate(scopedstrA, pszB, len); }
CLASS_DECL_ACME ::std::strong_ordering case_insensitive_string_count_collate(const ::wd32_character * pszA, const ::wd32_character * pszB, character_count len) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return _case_insensitive_string_count_collate(scopedstrA, pszB, len); }


CLASS_DECL_ACME character_count string_get_length(const ::wd32_character * psz) noexcept { return wd32_len(scopedstr); }
CLASS_DECL_ACME character_count string_get_length(const ::wd32_character* psz, character_count sizeMaximumInterest) noexcept
{
   character_count size = 0;
   sizeMaximumInterest++;
   while (*psz && sizeMaximumInterest > 0) { psz++; size++; sizeMaximumInterest--; }
   return sizeMaximumInterest == 0 ? -1 : size;
}
CLASS_DECL_ACME character_count string_safe_length(const ::wd32_character * psz) noexcept { if (::is_null(scopedstr)) return 0; return string_get_length(scopedstr); }
CLASS_DECL_ACME character_count string_safe_length(const ::wd32_character* psz, character_count sizeMaximumInterest) noexcept { if (::is_null(scopedstr)) return 0; return string_get_length(scopedstr, sizeMaximumInterest); }
CLASS_DECL_ACME ::wd32_character * string_lowercase(::wd32_character * psz, character_count size) noexcept { wd32_lwr_s(scopedstr, size); return  psz; }





CLASS_DECL_ACME const ::wd32_character * string_find_string(const ::wd32_character * pszBlock, const ::wd32_character * pszMatch) noexcept
{

   return wd32_str(scopedstrBlock, pszMatch);

}


CLASS_DECL_ACME const ::wd32_character * case_insensitive_string_find_string(const ::wd32_character * pszBlock, const ::wd32_character * pszMatch) noexcept
{

   return wd32_find_string_case_insensitive(scopedstrBlock, pszMatch);

}


CLASS_DECL_ACME const ::wd32_character * string_find_character(const ::wd32_character * pszBlock, ::wd32_character chMatch) noexcept
{

   return wd32_chr(scopedstrBlock, (::wd32_character)chMatch);

}


CLASS_DECL_ACME const ::wd32_character * string_find_character(const ::wd32_character * psz, const ::wd32_character * pszEnd, ::wd32_character chMatch) noexcept
{
   
   while(scopedstr < pszEnd)
   {
      
      if(*psz == chMatch)
      {
       
         return psz;
         
      }
      
      psz++;
      
   }

   return nullptr;

}


CLASS_DECL_ACME const ::wd32_character * string_rear_find_string(const ::wd32_character * psz, const ::wd32_character * pszFind, character_count iStart) noexcept
{
   character_count iLen = character_count(wd32_len(scopedstr));
   character_count iLenFind = character_count(wd32_len(scopedstrFind));
   if (iStart < 0)
      iStart = iLen + iStart;
   if (iLenFind > iLen)
      return nullptr;
   iStart = minimum(iStart, iLen - iLenFind);
   while (iStart >= 0)
   {
      if (wd32_ncmp(&psz[iStart], pszFind, iLenFind) == 0)
         return &psz[iStart];
      iStart--;
   }
   return nullptr;
}




CLASS_DECL_ACME ::wd32_character * string_uppercase(::wd32_character * psz, character_count size) noexcept
{

   wd32_upr_s(scopedstr, size);

   return psz;

}


CLASS_DECL_ACME ::wd32_character * string_reverse(::wd32_character * psz) noexcept
{

   if (scopedstr == nullptr)
   {

      return nullptr;

   }

   ::wd32_character * p1 = psz;

   ::wd32_character * p2 = psz + (wd32_len(scopedstr) - 1);

   while (p2 > p1)
   {

      __swap(*p1, *p2);

      p1++;

      p2--;

   }

   return psz;

}


CLASS_DECL_ACME character_count  get_formatted_length(const ::wd32_character * pszFormat, va_list args) noexcept
{

#ifdef WINDOWS

   wstring wstr(scopedstrFormat);

   return _vscwprintf(wstr.c_str(), args);

#else

   wd32_string wstr(scopedstrFormat);

   return vswprintf(nullptr, 0, pszFormat, args);

#endif

}


CLASS_DECL_ACME character_count _string_format(::wd32_character * pszBuffer, const ::wd32_character * pszFormat, va_list args) noexcept
{

#ifdef WINDOWS

   throw_todo();

   return -1;

#else

   return vswprintf(scopedstrBuffer, get_formatted_length(scopedstrFormat, args), pszFormat, args);

#endif

}


CLASS_DECL_ACME character_count wd32tring_format(::wd32_character * pszBuffer, character_count nlength, const ::wd32_character * pszFormat, va_list args) noexcept
{

#ifdef WINDOWS
   throw_todo();
   //return vswprintf_s(scopedstrBuffer, (size_t)nlength, pszFormat, args);
   return 0;

#else

   return vswprintf(scopedstrBuffer, nlength, pszFormat, args);

#endif

}


CLASS_DECL_ACME const ::wd32_character * string_rear_find_character(const ::wd32_character * psz, ::wd32_character ch) noexcept
{

   return _string_range(scopedstr).rear_find(ch, ::comparison::comparison < ::wd32_character >());

}


CLASS_DECL_ACME void  flood_characters(::wd32_character * pwsz, ::wd32_character wch, character_count len) noexcept
{

   while (len > 0)
   {

      *pwsz = wch;

      pwsz++;

      len--;

   }

}





CLASS_DECL_ACME ::wd32_character character_tolower(::wd32_character ch) noexcept { return wd32_char_tolower(ch); }
CLASS_DECL_ACME ::wd32_character character_toupper(::wd32_character ch) noexcept { return wd32_char_toupper(ch); }


CLASS_DECL_ACME bool character_isdigit(::wd32_character ch) noexcept { return wd32_char_isdigit(ch); }
CLASS_DECL_ACME bool character_isalpha(::wd32_character ch) noexcept { return wd32_char_isalpha(ch); }
CLASS_DECL_ACME bool character_isalnum(::wd32_character ch) noexcept { return wd32_char_isalnum(ch); }
CLASS_DECL_ACME bool character_isspace(::wd32_character ch) noexcept { return wd32_char_isspace(ch); }


CLASS_DECL_ACME bool character_isxdigit(::wd32_character ch) noexcept { return wd32_char_isxdigit(ch); }



CLASS_DECL_ACME character_count  string_skip_any_character_in(const ::wd32_character * pszBlock, const ::wd32_character * pszSet) noexcept
{

   return (character_count)wd32_spn(scopedstrBlock, pszSet);

}



CLASS_DECL_ACME character_count  string_find_first_character_in(const ::wd32_character * pszBlock, const ::wd32_character * pszSet) noexcept
{

   return (character_count)wd32_cspn(scopedstrBlock, pszSet);

}



CLASS_DECL_ACME character_count unichar_count(const ::wd32_character * pstr) { return __wd32len(pstr); }


