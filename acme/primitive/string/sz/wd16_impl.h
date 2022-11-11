// Refactored by camilo on 2022-11-04 05:42 <3ThomasBorregaardSorensen!!
#pragma once


inline  constexpr strsize     char_length_to_byte_length(const_wd16char_trigger, strsize nCharLength) { return (::memsize)(nCharLength * sizeof(wd16char)); }
inline  constexpr strsize     byte_length_to_char_length(const_wd16char_trigger, memsize nByteLength) { return (::strsize)(nByteLength / sizeof(wd16char)); }



inline void copy_chars(wd16char * pchDest, const wd16char * pchSrc, strsize nChars) noexcept { memcpy_dup(pchDest, pchSrc, char_length_to_byte_length(pchSrc, nChars)); }
inline void copy_chars(wd16char * pchDest, size_t nDestLen, const wd16char * pchSrc, strsize nChars) noexcept { ::memcpy_dup(pchDest, pchSrc, char_length_to_byte_length(pchSrc, nChars)); }
inline void copy_chars_overlapped(wd16char * pchDest, const wd16char * pchSrc, strsize nChars) noexcept { memmove(pchDest, pchSrc, char_length_to_byte_length(pchSrc, nChars)); }



inline i32 string_compare(const wd16char * pszA, const wd16char * pszB) noexcept { return wd16_cmp(pszA, pszB); }
inline i32 string_compare_ci(const wd16char * pszA, const wd16char * pszB) noexcept { return wd16_icmp(pszA, pszB); }
inline i32 string_count_compare(const wd16char * pszA, const wd16char * pszB, strsize len) noexcept { return wd16_ncmp(pszA, pszB, len); }
inline i32 string_count_compare_ci(const wd16char * pszA, const wd16char * pszB, strsize len) noexcept { return wd16_nicmp(pszA, pszB, len); }
inline i32 string_collate(const wd16char * pszA, const wd16char * pszB) noexcept { return wd16_coll(pszA, pszB); }
inline i32 string_collate_ci(const wd16char * pszA, const wd16char * pszB) noexcept { return wd16_icoll(pszA, pszB); }
inline i32 string_n_collate(const wd16char * pszA, const wd16char * pszB, strsize len) noexcept { return wd16_ncoll(pszA, pszB, len); }
inline i32 string_n_collate_ci(const wd16char * pszA, const wd16char * pszB, strsize len) noexcept { return wd16_nicoll(pszA, pszB, len); }
inline strsize string_get_length(const wd16char * psz) noexcept { return wd16_len(psz); }
inline strsize string_safe_length(const wd16char * psz) noexcept { if (::is_null(psz)) return 0; return string_get_length(psz); }
inline wd16char * string_lowercase(wd16char * psz, strsize size) noexcept { wd16_lwr_s(psz, size); return  psz; }



inline const wd16char * string_find_string(const wd16char * pszBlock, const wd16char * pszMatch) noexcept
{

   return wd16_str(pszBlock, pszMatch);

}


inline const wd16char * string_find_string_ci(const wd16char * pszBlock, const wd16char * pszMatch) noexcept
{

   return wd16_find_string_case_insensitive(pszBlock, pszMatch);

}


inline const wd16char * string_find_char(const wd16char * pszBlock, wd16char chMatch) noexcept
{

   return wd16_chr(pszBlock, (wd16char)chMatch);

}



inline const wd16char * string_find_string_reverse(const wd16char * psz, const wd16char * pszFind, strsize iStart) noexcept
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




inline wd16char * string_uppercase(wd16char * psz, strsize size) noexcept
{

   wd16_upr_s(psz, size);

   return psz;

}


inline wd16char * string_reverse(wd16char * psz) noexcept
{

   if (psz == nullptr)
   {

      return nullptr;

   }

   wd16string strReverse;

   wd16char * p = psz + wd16_len(psz);

   wd16char * pDec;

   while ((pDec = unicode_prior(psz, p)) != nullptr)
   {

      strReverse.append(pDec, pDec - p);

      p = pDec;

   }

   wd16_cpy(psz, strReverse);

   return psz;

}


inline strsize get_formatted_length(const wd16char * pszFormat, va_list args) noexcept
{

#ifdef WINDOWS

   return _vscwprintf(pszFormat, args);

#else

   wd32string wstr(pszFormat);

   return vswprintf(nullptr, 0, wstr, args);

#endif

}


inline strsize string_format(wd16char * pszBuffer, const wd16char * pszFormat, va_list args) noexcept
{

#ifdef WINDOWS

   return _vswprintf(pszBuffer, pszFormat, args);

#else

   wd32string wstrBuffer;

   auto nlength = get_formatted_length(pszFormat, args);

   auto psz = wstrBuffer.get_string_buffer(nlength);

   wd32string wstrFormat(pszFormat);

   auto len = vswprintf(psz, nlength, wstrFormat, args);

   utf_to_utf(pszBuffer, psz, nlength);

   return len;

#endif

}


inline strsize string_format(wd16char * pszBuffer, strsize nlength, const wd16char * pszFormat, va_list args) noexcept
{

#ifdef WINDOWS

   return vswprintf_s(pszBuffer, (size_t)nlength, pszFormat, args);

#else

   wd32string wstrBuffer;

   auto psz = wstrBuffer.get_string_buffer(nlength);

   wd32string wstrFormat(pszFormat);

   auto len = vswprintf(psz, nlength, wstrFormat, args);

   utf_to_utf(pszBuffer, psz, nlength);

   return len;

#endif

}




inline const wd16char * string_find_char_reverse(const wd16char * psz, wd16char ch, strsize iStart) noexcept
{


   const wd16char * p;

   if (iStart < 0)
   {

      p = psz + string_safe_length(psz) - iStart;

   }
   else
   {

      p = psz + minimum(iStart, string_safe_length(psz) - 1);

   }

   while (p >= psz)
   {

      if (*p == ch)
      {

         return p;

      }

      p--;

   }

   return nullptr;

}


inline void flood_characters(wd16char * pwsz, wd16char wch, strsize len) noexcept
{

   while (len > 0)
   {

      *pwsz = wch;

      pwsz++;

      len--;

   }

}


inline wd16char character_tolower(wd16char ch) noexcept { return wd16_char_tolower(ch); }
inline wd16char character_toupper(wd16char ch) noexcept { return wd16_char_toupper(ch); }


inline bool character_isdigit(wd16char ch) noexcept { return wd16_char_isdigit(ch); }
inline bool character_isalpha(wd16char ch) noexcept { return wd16_char_isalpha(ch); }
inline bool character_isalnum(wd16char ch) noexcept { return wd16_char_isalnum(ch); }
inline bool character_isspace(wd16char ch) noexcept { return wd16_char_isspace(ch); }


inline strsize string_span_including(const wd16char * pszBlock, const wd16char * pszSet) noexcept
{

   return (strsize)wd16_spn(pszBlock, pszSet);

}



inline strsize string_span_excluding(const wd16char * pszBlock, const wd16char * pszSet) noexcept
{

   return (strsize)wd16_cspn(pszBlock, pszSet);

}


inline strsize unichar_count(const wd16char * pstr) { return wd16_to_wd32_len(pstr); }






