﻿// Refactored by camilo on 2022-11-04 05:42 <3ThomasBorregaardSørensen!!
#pragma once


//inline  constexpr strsize     character_count_to_byte_length(const_wd32char_trigger, strsize nCharLength) { return (::memsize)(nCharLength * sizeof(::wd32_character)); }
//inline  constexpr strsize     byte_length_to_character_count(const_wd32char_trigger, memsize nByteLength) { return (::strsize)(nByteLength / sizeof(::wd32_character)); }


inline void string_count_copy(::wd32_character * pchDest, const ::wd32_character * pchSrc, strsize nChars) noexcept { memory_copy(pchDest, pchSrc, character_count_to_byte_length(pchSrc, nChars)); }
inline void string_count_copy(::wd32_character * pchDest, size_t nDestLen, const ::wd32_character * pchSrc, strsize nChars) noexcept { ::memory_copy(pchDest, pchSrc, character_count_to_byte_length(pchSrc, nChars)); }
inline void overlapped_string_count_copy(::wd32_character * pchDest, const ::wd32_character * pchSrc, strsize nChars) noexcept { memmove(pchDest, pchSrc, character_count_to_byte_length(pchSrc, nChars)); }


inline ::std::strong_ordering _string_compare(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept { return wd32_cmp(pszA, pszB)<=>0; }
inline ::std::strong_ordering _string_compare_ci(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept { return wd32_icmp(pszA, pszB) <=> 0; }
inline ::std::strong_ordering _string_count_compare(const ::wd32_character * pszA, const ::wd32_character * pszB, strsize len) noexcept { return wd32_ncmp(pszA, pszB, len) <=> 0; }
inline ::std::strong_ordering _string_count_compare_ci(const ::wd32_character * pszA, const ::wd32_character * pszB, strsize len) noexcept { return wd32_nicmp(pszA, pszB, len) <=> 0; }
inline ::std::strong_ordering _string_collate(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept { return wd32_coll(pszA, pszB) <=> 0; }
inline ::std::strong_ordering _case_insensitive_string_collate(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept { return wd32_icoll(pszA, pszB) <=> 0; }
inline ::std::strong_ordering _string_count_collate(const ::wd32_character * pszA, const ::wd32_character * pszB, strsize len) noexcept { return wd32_ncoll(pszA, pszB, len) <=> 0; }
inline ::std::strong_ordering _case_insensitive_string_count_collate(const ::wd32_character * pszA, const ::wd32_character * pszB, strsize len) noexcept { return wd32_nicoll(pszA, pszB, len) <=> 0; }




inline ::std::strong_ordering string_compare(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return _string_compare(pszA, pszB); }
inline ::std::strong_ordering case_insensitive_string_order(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return _string_compare_ci(pszA, pszB); }
inline ::std::strong_ordering string_count_compare(const ::wd32_character * pszA, const ::wd32_character * pszB, strsize len) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return _string_count_compare(pszA, pszB, len); }
inline ::std::strong_ordering string_count_compare_ci(const ::wd32_character * pszA, const ::wd32_character * pszB, strsize len) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return  _string_count_compare_ci(pszA, pszB, len); }
inline ::std::strong_ordering string_collate(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return _string_collate(pszA, pszB); }
inline ::std::strong_ordering case_insensitive_string_collate(const ::wd32_character * pszA, const ::wd32_character * pszB) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return  _case_insensitive_string_collate(pszA, pszB); }
inline ::std::strong_ordering string_count_collate(const ::wd32_character * pszA, const ::wd32_character * pszB, strsize len) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return _string_count_collate(pszA, pszB, len); }
inline ::std::strong_ordering case_insensitive_string_count_collate(const ::wd32_character * pszA, const ::wd32_character * pszB, strsize len) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return _case_insensitive_string_count_collate(pszA, pszB, len); }


inline strsize string_get_length(const ::wd32_character * psz) noexcept { return wd32_len(psz); }
inline strsize string_get_length(const ::wd32_character* psz, strsize sizeMaximumInterest) noexcept
{
   strsize size = 0;
   sizeMaximumInterest++;
   while (*psz && sizeMaximumInterest > 0) { psz++; size++; sizeMaximumInterest--; }
   return sizeMaximumInterest == 0 ? -1 : size;
}
inline strsize string_safe_length(const ::wd32_character * psz) noexcept { if (::is_null(psz)) return 0; return string_get_length(psz); }
inline strsize string_safe_length(const ::wd32_character* psz, strsize sizeMaximumInterest) noexcept { if (::is_null(psz)) return 0; return string_get_length(psz, sizeMaximumInterest); }
inline ::wd32_character * string_lowercase(::wd32_character * psz, strsize size) noexcept { wd32_lwr_s(psz, size); return  psz; }





inline const ::wd32_character * string_find_string(const ::wd32_character * pszBlock, const ::wd32_character * pszMatch) noexcept
{

   return wd32_str(pszBlock, pszMatch);

}


inline const ::wd32_character * string_find_string_ci(const ::wd32_character * pszBlock, const ::wd32_character * pszMatch) noexcept
{

   return wd32_find_string_case_insensitive(pszBlock, pszMatch);

}


inline const ::wd32_character * string_find_character(const ::wd32_character * pszBlock, ::wd32_character chMatch) noexcept
{

   return wd32_chr(pszBlock, (::wd32_character)chMatch);

}



inline const ::wd32_character * string_rear_find_string(const ::wd32_character * psz, const ::wd32_character * pszFind, strsize iStart) noexcept
{
   strsize iLen = strsize(wd32_len(psz));
   strsize iLenFind = strsize(wd32_len(pszFind));
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




inline ::wd32_character * string_uppercase(::wd32_character * psz, strsize size) noexcept
{

   wd32_upr_s(psz, size);

   return psz;

}


inline ::wd32_character * string_reverse(::wd32_character * psz) noexcept
{

   if (psz == nullptr)
   {

      return nullptr;

   }

   ::wd32_character * p1 = psz;

   ::wd32_character * p2 = psz + (wd32_len(psz) - 1);

   while (p2 > p1)
   {

      __swap(*p1, *p2);

      p1++;

      p2--;

   }

   return psz;

}


inline strsize  get_formatted_length(const ::wd32_character * pszFormat, va_list args) noexcept
{

#ifdef WINDOWS

   wstring wstr(pszFormat);

   return _vscwprintf(wstr.c_str(), args);

#else

   return vswprintf(nullptr, 0, pszFormat, args);

#endif

}


inline strsize _string_format(::wd32_character * pszBuffer, const ::wd32_character * pszFormat, va_list args) noexcept
{

#ifdef WINDOWS

   throw_todo();

   return -1;

#else

   return vswprintf(pszBuffer, get_formatted_length(pszFormat, args), pszFormat, args);

#endif

}


inline strsize wd32tring_format(::wd32_character * pszBuffer, strsize nlength, const ::wd32_character * pszFormat, va_list args) noexcept
{

#ifdef WINDOWS
   throw_todo();
   //return vswprintf_s(pszBuffer, (size_t)nlength, pszFormat, args);
   return 0;

#else

   return vswprintf(pszBuffer, nlength, pszFormat, args);

#endif

}


inline const ::wd32_character * string_rear_find_character(const ::wd32_character * psz, ::wd32_character ch) noexcept
{

   return _string_range(psz).rear_find(ch, ::comparison::comparison < ::wd32_character >());

}


inline void  flood_characters(::wd32_character * pwsz, ::wd32_character wch, strsize len) noexcept
{

   while (len > 0)
   {

      *pwsz = wch;

      pwsz++;

      len--;

   }

}





inline ::wd32_character character_tolower(::wd32_character ch) noexcept { return wd32_char_tolower(ch); }
inline ::wd32_character character_toupper(::wd32_character ch) noexcept { return wd32_char_toupper(ch); }


inline bool character_isdigit(::wd32_character ch) noexcept { return wd32_char_isdigit(ch); }
inline bool character_isalpha(::wd32_character ch) noexcept { return wd32_char_isalpha(ch); }
inline bool character_isalnum(::wd32_character ch) noexcept { return wd32_char_isalnum(ch); }
inline bool character_isspace(::wd32_character ch) noexcept { return wd32_char_isspace(ch); }



inline strsize  string_skip_any_character_in(const ::wd32_character * pszBlock, const ::wd32_character * pszSet) noexcept
{

   return (strsize)wd32_spn(pszBlock, pszSet);

}



inline strsize  string_find_first_character_in(const ::wd32_character * pszBlock, const ::wd32_character * pszSet) noexcept
{

   return (strsize)wd32_cspn(pszBlock, pszSet);

}



inline strsize unichar_count(const ::wd32_character * pstr) { return __wd32len(pstr); }


