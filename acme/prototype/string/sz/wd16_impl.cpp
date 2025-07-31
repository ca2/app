// Refactored by camilo on 2022-11-04 05:42 <3ThomasBorregaardSorensen!!
#include "framework.h"


#include <wchar.h>


//CLASS_DECL_ACME  constexpr character_count     character_count_to_byte_length(const_wd16char_trigger, character_count nCharLength) { return (::memsize)(nCharLength * sizeof(::wd16_character)); }
//CLASS_DECL_ACME  constexpr character_count     byte_length_to_character_count(const_wd16char_trigger, memsize nByteLength) { return (::character_count)(nByteLength / sizeof(::wd16_character)); }



CLASS_DECL_ACME void string_count_copy(::wd16_character * pchDest, const ::wd16_character * pchSrc, character_count nChars) noexcept { memory_copy(pchDest, pchSrc, character_count_to_byte_length(pchSrc, nChars)); }
CLASS_DECL_ACME void string_count_copy(::wd16_character * pchDest, size_t nDestLen, const ::wd16_character * pchSrc, character_count nChars) noexcept { ::memory_copy(pchDest, pchSrc, character_count_to_byte_length(pchSrc, nChars)); }
CLASS_DECL_ACME void overlapped_string_count_copy(::wd16_character * pchDest, const ::wd16_character * pchSrc, character_count nChars) noexcept { memory_transfer(pchDest, pchSrc, character_count_to_byte_length(pchSrc, nChars)); }


CLASS_DECL_ACME ::std::strong_ordering _string_compare(const ::wd16_character * pszA, const ::wd16_character * pszB) noexcept { return wd16_cmp(scopedstrA, pszB)<=>0; }
CLASS_DECL_ACME ::std::strong_ordering case_insensitive__string_compare(const ::wd16_character * pszA, const ::wd16_character * pszB) noexcept { return wd16_icmp(scopedstrA, pszB) <=> 0; }
//CLASS_DECL_ACME ::std::strong_ordering _string_count_compare(const ::wd16_character * pszA, const ::wd16_character * pszB, character_count len) noexcept { return wd16_ncmp(scopedstrA, pszB, len) <=> 0; }
CLASS_DECL_ACME ::std::strong_ordering case_insensitive__string_count_compare(const ::wd16_character * pszA, const ::wd16_character * pszB, character_count len) noexcept { return wd16_nicmp(scopedstrA, pszB, len) <=> 0; }
CLASS_DECL_ACME ::std::strong_ordering _string_collate(const ::wd16_character * pszA, const ::wd16_character * pszB) noexcept { return wd16_coll(scopedstrA, pszB) <=> 0; }
CLASS_DECL_ACME ::std::strong_ordering _case_insensitive_string_collate(const ::wd16_character * pszA, const ::wd16_character * pszB) noexcept { return wd16_icoll(scopedstrA, pszB) <=> 0; }
CLASS_DECL_ACME ::std::strong_ordering _string_count_collate(const ::wd16_character * pszA, const ::wd16_character * pszB, character_count len) noexcept { return wd16_ncoll(scopedstrA, pszB, len) <=> 0; }
CLASS_DECL_ACME ::std::strong_ordering _case_insensitive_string_count_collate(const ::wd16_character * pszA, const ::wd16_character * pszB, character_count len) noexcept { return wd16_nicoll(scopedstrA, pszB, len) <=> 0; }



CLASS_DECL_ACME ::std::strong_ordering string_compare(const ::wd16_character * pszA, const ::wd16_character * pszB) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return _string_compare(scopedstrA, pszB); }
CLASS_DECL_ACME ::std::strong_ordering case_insensitive_string_order(const ::wd16_character * pszA, const ::wd16_character * pszB) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return case_insensitive__string_compare(scopedstrA, pszB); }
CLASS_DECL_ACME ::std::strong_ordering string_count_compare(const ::wd16_character * pszA, const ::wd16_character * pszB, character_count len) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return _string_count_compare(scopedstrA, pszB, len); }
CLASS_DECL_ACME ::std::strong_ordering case_insensitive_string_count_compare(const ::wd16_character * pszA, const ::wd16_character * pszB, character_count len) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return  case_insensitive__string_count_compare(scopedstrA, pszB, len); }
CLASS_DECL_ACME ::std::strong_ordering string_collate(const ::wd16_character * pszA, const ::wd16_character * pszB) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return _string_collate(scopedstrA, pszB); }
CLASS_DECL_ACME ::std::strong_ordering case_insensitive_string_collate(const ::wd16_character * pszA, const ::wd16_character * pszB) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return  _case_insensitive_string_collate(scopedstrA, pszB); }
CLASS_DECL_ACME ::std::strong_ordering string_count_collate(const ::wd16_character * pszA, const ::wd16_character * pszB, character_count len) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return _string_count_collate(scopedstrA, pszB, len); }
CLASS_DECL_ACME ::std::strong_ordering case_insensitive_string_count_collate(const ::wd16_character * pszA, const ::wd16_character * pszB, character_count len) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return _case_insensitive_string_count_collate(scopedstrA, pszB, len); }


CLASS_DECL_ACME character_count string_get_length(const ::wd16_character * psz) noexcept { return wd16_len(scopedstr); }
CLASS_DECL_ACME character_count string_get_length(const ::wd16_character* psz, character_count sizeMaximumInterest) noexcept
{
   character_count size = 0;
   sizeMaximumInterest++;
   while (*psz && sizeMaximumInterest > 0) { psz++; size++; sizeMaximumInterest--; }
   return sizeMaximumInterest == 0 ? -1 : size;
}
CLASS_DECL_ACME character_count string_safe_length(const ::wd16_character * psz) noexcept { if (::is_null(scopedstr)) return 0; return string_get_length(scopedstr); }
CLASS_DECL_ACME character_count string_safe_length(const ::wd16_character* psz, character_count sizeMaximumInterest) noexcept { if (::is_null(scopedstr)) return 0; return string_get_length(scopedstr, sizeMaximumInterest); }
CLASS_DECL_ACME ::wd16_character * string_lowercase(::wd16_character * psz, character_count size) noexcept { wd16_lwr_s(scopedstr, size); return  psz; }



CLASS_DECL_ACME const ::wd16_character * string_find_string(const ::wd16_character * pszBlock, const ::wd16_character * pszMatch) noexcept
{

   return wd16_str(scopedstrBlock, pszMatch);

}


CLASS_DECL_ACME const ::wd16_character * case_insensitive_string_find_string(const ::wd16_character * pszBlock, const ::wd16_character * pszMatch) noexcept
{

   return wd16_find_string_case_insensitive(scopedstrBlock, pszMatch);

}


CLASS_DECL_ACME const ::wd16_character * string_find_character(const ::wd16_character * pszBlock, ::wd16_character chMatch) noexcept
{

   return wd16_chr(scopedstrBlock, (::wd16_character)chMatch);

}


CLASS_DECL_ACME const ::wd16_character * string_find_character(const ::wd16_character * psz, const ::wd16_character * pszEnd, ::wd16_character chMatch) noexcept
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



CLASS_DECL_ACME const ::wd16_character * string_rear_find_string(const ::wd16_character * psz, const ::wd16_character * pszFind, character_count iStart) noexcept
{
   character_count iLen = character_count(wd16_len(scopedstr));
   character_count iLenFind = character_count(wd16_len(scopedstrFind));
   if (iStart < 0)
      iStart = iLen + iStart;
   if (iLenFind > iLen)
      return nullptr;
   iStart = minimum(iStart, iLen - iLenFind);
   while (iStart >= 0)
   {
      if (wd16_ncmp(&psz[iStart], pszFind, iLenFind) == 0)
         return &psz[iStart];
      iStart--;
   }
   return nullptr;
}




CLASS_DECL_ACME ::wd16_character * string_uppercase(::wd16_character * psz, character_count size) noexcept
{

   wd16_upr_s(scopedstr, size);

   return psz;

}


CLASS_DECL_ACME ::wd16_character * string_reverse(::wd16_character * psz) noexcept
{

   if (scopedstr == nullptr)
   {

      return nullptr;

   }

   wd16_string strReverse;

   ::wd16_character * p = psz + wd16_len(scopedstr);

   ::wd16_character * pDec;

   while ((pDec = unicode_prior(scopedstr, p)) != nullptr)
   {

      strReverse.append(pDec, pDec - p);

      p = pDec;

   }

   wd16_cpy(scopedstr, strReverse.c_str());

   return psz;

}


CLASS_DECL_ACME character_count get_formatted_length(const ::wd16_character * pszFormat, va_list args) noexcept
{

#ifdef WINDOWS

   return _vscwprintf(scopedstrFormat, args);

#else

   wd32_string wstr(scopedstrFormat);

   return vswprintf(nullptr, 0, wstr.c_str(), args);

#endif

}


CLASS_DECL_ACME character_count _string_format(::wd16_character * pszBuffer, const ::wd16_character * pszFormat, va_list args) noexcept
{

#ifdef WINDOWS

   return _vswprintf(scopedstrBuffer, pszFormat, args);

#else

   wd32_string wstrBuffer;

   auto nlength = get_formatted_length(scopedstrFormat, args);

   auto psz = wstrBuffer.get_buffer(nlength);

   wd32_string wstrFormat(scopedstrFormat);

   auto len = vswprintf(scopedstr, nlength, wstrFormat.c_str(), args);

   utf_to_utf(scopedstrBuffer, psz, nlength);

   return len;

#endif

}


CLASS_DECL_ACME character_count _string_format(::wd16_character * pszBuffer, character_count nlength, const ::wd16_character * pszFormat, va_list args) noexcept
{

#ifdef WINDOWS

   return vswprintf_s(scopedstrBuffer, (size_t)nlength, pszFormat, args);

#else

   wd32_string wstrBuffer;

   auto psz = wstrBuffer.get_buffer(nlength);

   wd32_string wstrFormat(scopedstrFormat);

   auto len = vswprintf(scopedstr, nlength, wstrFormat.c_str(), args);

   utf_to_utf(scopedstrBuffer, psz, nlength);

   return len;

#endif

}


CLASS_DECL_ACME const ::wd16_character * string_rear_find_character(const ::wd16_character * psz, ::wd16_character ch) noexcept
{

   return _string_range(scopedstr).rear_find(ch, ::comparison::comparison < ::wd16_character >());

}


CLASS_DECL_ACME void flood_characters(::wd16_character * pwsz, ::wd16_character wch, character_count len) noexcept
{

   while (len > 0)
   {

      *pwsz = wch;

      pwsz++;

      len--;

   }

}


CLASS_DECL_ACME ::wd16_character character_tolower(::wd16_character ch) noexcept { return wd16_char_tolower(ch); }
CLASS_DECL_ACME ::wd16_character character_toupper(::wd16_character ch) noexcept { return wd16_char_toupper(ch); }


CLASS_DECL_ACME bool character_isdigit(::wd16_character ch) noexcept { return wd16_char_isdigit(ch); }
CLASS_DECL_ACME bool character_isalpha(::wd16_character ch) noexcept { return wd16_char_isalpha(ch); }
CLASS_DECL_ACME bool character_isalnum(::wd16_character ch) noexcept { return wd16_char_isalnum(ch); }
CLASS_DECL_ACME bool character_isspace(::wd16_character ch) noexcept { return wd16_char_isspace(ch); }


CLASS_DECL_ACME bool character_isxdigit(::wd16_character ch) noexcept { return wd16_char_isxdigit(ch); }


CLASS_DECL_ACME character_count string_skip_any_character_in(const ::wd16_character * pszBlock, const ::wd16_character * pszSet) noexcept
{

   return (character_count)wd16_spn(scopedstrBlock, pszSet);

}



CLASS_DECL_ACME character_count string_find_first_character_in(const ::wd16_character * pszBlock, const ::wd16_character * pszSet) noexcept
{

   return (character_count)wd16_cspn(scopedstrBlock, pszSet);

}


CLASS_DECL_ACME character_count unichar_count(const ::wd16_character * pstr) { return wd16_to_wd32_len(pstr); }






