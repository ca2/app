// Refactored by camilo on 2022-11-04 05:42 <3ThomasBorregaardSørensen!!
#pragma once


//inline  constexpr strsize     character_count_to_byte_length(const_wd16char_trigger, strsize nCharLength) { return (::memsize)(nCharLength * sizeof(::wd16_character)); }
//inline  constexpr strsize     byte_length_to_character_count(const_wd16char_trigger, memsize nByteLength) { return (::strsize)(nByteLength / sizeof(::wd16_character)); }



inline void string_count_copy(::wd16_character * pchDest, const ::wd16_character * pchSrc, strsize nChars) noexcept { memcpy_dup(pchDest, pchSrc, character_count_to_byte_length(pchSrc, nChars)); }
inline void string_count_copy(::wd16_character * pchDest, size_t nDestLen, const ::wd16_character * pchSrc, strsize nChars) noexcept { ::memcpy_dup(pchDest, pchSrc, character_count_to_byte_length(pchSrc, nChars)); }
inline void overlapped_string_count_copy(::wd16_character * pchDest, const ::wd16_character * pchSrc, strsize nChars) noexcept { memmove(pchDest, pchSrc, character_count_to_byte_length(pchSrc, nChars)); }


inline ::std::strong_ordering _string_compare(const ::wd16_character * pszA, const ::wd16_character * pszB) noexcept { return wd16_cmp(pszA, pszB)<=>0; }
inline ::std::strong_ordering _string_compare_ci(const ::wd16_character * pszA, const ::wd16_character * pszB) noexcept { return wd16_icmp(pszA, pszB) <=> 0; }
inline ::std::strong_ordering _string_count_compare(const ::wd16_character * pszA, const ::wd16_character * pszB, strsize len) noexcept { return wd16_ncmp(pszA, pszB, len) <=> 0; }
inline ::std::strong_ordering _string_count_compare_ci(const ::wd16_character * pszA, const ::wd16_character * pszB, strsize len) noexcept { return wd16_nicmp(pszA, pszB, len) <=> 0; }
inline ::std::strong_ordering _string_collate(const ::wd16_character * pszA, const ::wd16_character * pszB) noexcept { return wd16_coll(pszA, pszB) <=> 0; }
inline ::std::strong_ordering _case_insensitive_string_collate(const ::wd16_character * pszA, const ::wd16_character * pszB) noexcept { return wd16_icoll(pszA, pszB) <=> 0; }
inline ::std::strong_ordering _string_count_collate(const ::wd16_character * pszA, const ::wd16_character * pszB, strsize len) noexcept { return wd16_ncoll(pszA, pszB, len) <=> 0; }
inline ::std::strong_ordering _case_insensitive_string_count_collate(const ::wd16_character * pszA, const ::wd16_character * pszB, strsize len) noexcept { return wd16_nicoll(pszA, pszB, len) <=> 0; }



inline ::std::strong_ordering string_compare(const ::wd16_character * pszA, const ::wd16_character * pszB) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return _string_compare(pszA, pszB); }
inline ::std::strong_ordering case_insensitive_string_order(const ::wd16_character * pszA, const ::wd16_character * pszB) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return _string_compare_ci(pszA, pszB); }
inline ::std::strong_ordering string_count_compare(const ::wd16_character * pszA, const ::wd16_character * pszB, strsize len) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return _string_count_compare(pszA, pszB, len); }
inline ::std::strong_ordering string_count_compare_ci(const ::wd16_character * pszA, const ::wd16_character * pszB, strsize len) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return  _string_count_compare_ci(pszA, pszB, len); }
inline ::std::strong_ordering string_collate(const ::wd16_character * pszA, const ::wd16_character * pszB) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return _string_collate(pszA, pszB); }
inline ::std::strong_ordering case_insensitive_string_collate(const ::wd16_character * pszA, const ::wd16_character * pszB) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return  _case_insensitive_string_collate(pszA, pszB); }
inline ::std::strong_ordering string_count_collate(const ::wd16_character * pszA, const ::wd16_character * pszB, strsize len) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return _string_count_collate(pszA, pszB, len); }
inline ::std::strong_ordering case_insensitive_string_count_collate(const ::wd16_character * pszA, const ::wd16_character * pszB, strsize len) noexcept { ::std::strong_ordering ordering(::std::strong_ordering::less); if (string_compare_prefix(ordering, pszA, pszB)) return ordering; return _case_insensitive_string_count_collate(pszA, pszB, len); }


inline strsize string_get_length(const ::wd16_character * psz) noexcept { return wd16_len(psz); }
inline strsize string_get_length(const ::wd16_character* psz, strsize sizeMaximumInterest) noexcept
{
   strsize size = 0;
   sizeMaximumInterest++;
   while (*psz && sizeMaximumInterest > 0) { psz++; size++; sizeMaximumInterest--; }
   return sizeMaximumInterest == 0 ? -1 : size;
}
inline strsize string_safe_length(const ::wd16_character * psz) noexcept { if (::is_null(psz)) return 0; return string_get_length(psz); }
inline strsize string_safe_length(const ::wd16_character* psz, strsize sizeMaximumInterest) noexcept { if (::is_null(psz)) return 0; return string_get_length(psz, sizeMaximumInterest); }
inline ::wd16_character * string_lowercase(::wd16_character * psz, strsize size) noexcept { wd16_lwr_s(psz, size); return  psz; }



inline const ::wd16_character * string_find_string(const ::wd16_character * pszBlock, const ::wd16_character * pszMatch) noexcept
{

   return wd16_str(pszBlock, pszMatch);

}


inline const ::wd16_character * string_find_string_ci(const ::wd16_character * pszBlock, const ::wd16_character * pszMatch) noexcept
{

   return wd16_find_string_case_insensitive(pszBlock, pszMatch);

}


inline const ::wd16_character * string_find_chararacter(const ::wd16_character * pszBlock, ::wd16_character chMatch) noexcept
{

   return wd16_chr(pszBlock, (::wd16_character)chMatch);

}



inline const ::wd16_character * string_rear_find_string(const ::wd16_character * psz, const ::wd16_character * pszFind, strsize iStart) noexcept
{
   strsize iLen = strsize(wd16_len(psz));
   strsize iLenFind = strsize(wd16_len(pszFind));
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




inline ::wd16_character * string_uppercase(::wd16_character * psz, strsize size) noexcept
{

   wd16_upr_s(psz, size);

   return psz;

}


inline ::wd16_character * string_reverse(::wd16_character * psz) noexcept
{

   if (psz == nullptr)
   {

      return nullptr;

   }

   wd16_string strReverse;

   ::wd16_character * p = psz + wd16_len(psz);

   ::wd16_character * pDec;

   while ((pDec = unicode_prior(psz, p)) != nullptr)
   {

      strReverse.append(pDec, pDec - p);

      p = pDec;

   }

   wd16_cpy(psz, strReverse.c_str());

   return psz;

}


inline strsize get_formatted_length(const ::wd16_character * pszFormat, va_list args) noexcept
{

#ifdef WINDOWS

   return _vscwprintf(pszFormat, args);

#else

   wd32_string wstr(pszFormat);

   return vswprintf(nullptr, 0, wstr.c_str(), args);

#endif

}


inline strsize _string_format(::wd16_character * pszBuffer, const ::wd16_character * pszFormat, va_list args) noexcept
{

#ifdef WINDOWS

   return _vswprintf(pszBuffer, pszFormat, args);

#else

   wd32_string wstrBuffer;

   auto nlength = get_formatted_length(pszFormat, args);

   auto psz = wstrBuffer.get_string_buffer(nlength);

   wd32_string wstrFormat(pszFormat);

   auto len = vswprintf(psz, nlength, wstrFormat.c_str(), args);

   utf_to_utf(pszBuffer, psz, nlength);

   return len;

#endif

}


inline strsize _string_format(::wd16_character * pszBuffer, strsize nlength, const ::wd16_character * pszFormat, va_list args) noexcept
{

#ifdef WINDOWS

   return vswprintf_s(pszBuffer, (size_t)nlength, pszFormat, args);

#else

   wd32_string wstrBuffer;

   auto psz = wstrBuffer.get_string_buffer(nlength);

   wd32_string wstrFormat(pszFormat);

   auto len = vswprintf(psz, nlength, wstrFormat.c_str(), args);

   utf_to_utf(pszBuffer, psz, nlength);

   return len;

#endif

}


inline const ::wd16_character * string_rear_find_character(const ::wd16_character * psz, ::wd16_character ch) noexcept
{

   return _string_range(psz).rear_find(ch, ::comparison::comparison < ::wd16_character >());

}


inline void flood_characters(::wd16_character * pwsz, ::wd16_character wch, strsize len) noexcept
{

   while (len > 0)
   {

      *pwsz = wch;

      pwsz++;

      len--;

   }

}


inline ::wd16_character character_tolower(::wd16_character ch) noexcept { return wd16_char_tolower(ch); }
inline ::wd16_character character_toupper(::wd16_character ch) noexcept { return wd16_char_toupper(ch); }


inline bool character_isdigit(::wd16_character ch) noexcept { return wd16_char_isdigit(ch); }
inline bool character_isalpha(::wd16_character ch) noexcept { return wd16_char_isalpha(ch); }
inline bool character_isalnum(::wd16_character ch) noexcept { return wd16_char_isalnum(ch); }
inline bool character_isspace(::wd16_character ch) noexcept { return wd16_char_isspace(ch); }


inline strsize string_skip_any_character_in(const ::wd16_character * pszBlock, const ::wd16_character * pszSet) noexcept
{

   return (strsize)wd16_spn(pszBlock, pszSet);

}



inline strsize string_find_first_character_in(const ::wd16_character * pszBlock, const ::wd16_character * pszSet) noexcept
{

   return (strsize)wd16_cspn(pszBlock, pszSet);

}


inline strsize unichar_count(const ::wd16_character * pstr) { return wd16_to_wd32_len(pstr); }






