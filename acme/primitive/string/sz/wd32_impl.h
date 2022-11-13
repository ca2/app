// Refactored by camilo on 2022-11-04 05:42 <3ThomasBorregaardSorensen!!
#pragma once


inline  constexpr strsize     char_length_to_byte_length(const_wd32char_trigger, strsize nCharLength) { return (::memsize)(nCharLength * sizeof(wd32char)); }
inline  constexpr strsize     byte_length_to_char_length(const_wd32char_trigger, memsize nByteLength) { return (::strsize)(nByteLength / sizeof(wd32char)); }


inline void copy_chars(wd32char * pchDest, const wd32char * pchSrc, strsize nChars) noexcept { memcpy_dup(pchDest, pchSrc, char_length_to_byte_length(pchSrc, nChars)); }
inline void copy_chars(wd32char * pchDest, size_t nDestLen, const wd32char * pchSrc, strsize nChars) noexcept { ::memcpy_dup(pchDest, pchSrc, char_length_to_byte_length(pchSrc, nChars)); }
inline void copy_chars_overlapped(wd32char * pchDest, const wd32char * pchSrc, strsize nChars) noexcept { memmove(pchDest, pchSrc, char_length_to_byte_length(pchSrc, nChars)); }






inline i32 string_compare(const wd32char * pszA, const wd32char * pszB) noexcept { return wd32_cmp(pszA, pszB); }
inline i32 string_compare_ci(const wd32char * pszA, const wd32char * pszB) noexcept { return wd32_icmp(pszA, pszB); }
inline i32 string_count_compare(const wd32char * pszA, const wd32char * pszB, strsize len) noexcept { return wd32_ncmp(pszA, pszB, len); }
inline i32 string_count_compare_ci(const wd32char * pszA, const wd32char * pszB, strsize len) noexcept { return wd32_nicmp(pszA, pszB, len); }
inline i32 string_collate(const wd32char * pszA, const wd32char * pszB) noexcept { return wd32_coll(pszA, pszB); }
inline i32 string_collate_ci(const wd32char * pszA, const wd32char * pszB) noexcept { return wd32_icoll(pszA, pszB); }
inline i32 string_n_collate(const wd32char * pszA, const wd32char * pszB, strsize len) noexcept { return wd32_ncoll(pszA, pszB, len); }
inline i32 string_n_collate_ci(const wd32char * pszA, const wd32char * pszB, strsize len) noexcept { return wd32_nicoll(pszA, pszB, len); }
inline strsize string_get_length(const wd32char * psz) noexcept { return wd32_len(psz); }
inline strsize string_get_length(const wd32char* psz, strsize sizeMaximumInterest) noexcept
{
   strsize size = 0;
   sizeMaximumInterest++;
   while (*psz && sizeMaximumInterest > 0) { psz++; size++; sizeMaximumInterest--; }
   return sizeMaximumInterest == 0 ? -1 : size;
}
inline strsize string_safe_length(const wd32char * psz) noexcept { if (::is_null(psz)) return 0; return string_get_length(psz); }
inline strsize string_safe_length(const wd32char* psz, strsize sizeMaximumInterest) noexcept { if (::is_null(psz)) return 0; return string_get_length(psz, sizeMaximumInterest); }
inline wd32char * string_lowercase(wd32char * psz, strsize size) noexcept { wd32_lwr_s(psz, size); return  psz; }





inline const wd32char * string_find_string(const wd32char * pszBlock, const wd32char * pszMatch) noexcept
{

   return wd32_str(pszBlock, pszMatch);

}


inline const wd32char * string_find_string_ci(const wd32char * pszBlock, const wd32char * pszMatch) noexcept
{

   return wd32_find_string_case_insensitive(pszBlock, pszMatch);

}


inline const wd32char * string_find_char(const wd32char * pszBlock, wd32char chMatch) noexcept
{

   return wd32_chr(pszBlock, (wd32char)chMatch);

}



inline const wd32char * string_find_string_reverse(const wd32char * psz, const wd32char * pszFind, strsize iStart) noexcept
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




inline wd32char * string_uppercase(wd32char * psz, strsize size) noexcept
{

   wd32_upr_s(psz, size);

   return psz;

}


inline wd32char * string_reverse(wd32char * psz) noexcept
{

   if (psz == nullptr)
   {

      return nullptr;

   }

   wd32char * p1 = psz;

   wd32char * p2 = psz + (wd32_len(psz) - 1);

   while (p2 > p1)
   {

      __swap(*p1, *p2);

      p1++;

      p2--;

   }

   return psz;

}


inline strsize  get_formatted_length(const wd32char * pszFormat, va_list args) noexcept
{

#ifdef WINDOWS

   wstring wstr(pszFormat);

   return _vscwprintf(wstr, args);

#else

   return vswprintf(nullptr, 0, pszFormat, args);

#endif

}


inline strsize  string_format(wd32char * pszBuffer, const wd32char * pszFormat, va_list args) noexcept
{

#ifdef WINDOWS

   throw_todo();

   return -1;

#else

   return vswprintf(pszBuffer, get_formatted_length(pszFormat, args), pszFormat, args);

#endif

}


inline strsize  string_format(wd32char * pszBuffer, strsize nlength, const wd32char * pszFormat, va_list args) noexcept
{

#ifdef WINDOWS
   throw_todo();
   //return vswprintf_s(pszBuffer, (size_t)nlength, pszFormat, args);
   return 0;

#else

   return vswprintf(pszBuffer, nlength, pszFormat, args);

#endif

}


inline const wd32char * string_find_char_reverse(const wd32char * psz, wd32char ch, strsize iStart) noexcept
{


   const wd32char * p;

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


inline void  flood_characters(wd32char * pwsz, wd32char wch, strsize len) noexcept
{

   while (len > 0)
   {

      *pwsz = wch;

      pwsz++;

      len--;

   }

}





inline wd32char character_tolower(wd32char ch) noexcept { return wd32_char_tolower(ch); }
inline wd32char character_toupper(wd32char ch) noexcept { return wd32_char_toupper(ch); }


inline bool character_isdigit(wd32char ch) noexcept { return wd32_char_isdigit(ch); }
inline bool character_isalpha(wd32char ch) noexcept { return wd32_char_isalpha(ch); }
inline bool character_isalnum(wd32char ch) noexcept { return wd32_char_isalnum(ch); }
inline bool character_isspace(wd32char ch) noexcept { return wd32_char_isspace(ch); }



inline strsize  string_span_including(const wd32char * pszBlock, const wd32char * pszSet) noexcept
{

   return (strsize)wd32_spn(pszBlock, pszSet);

}



inline strsize  string_span_excluding(const wd32char * pszBlock, const wd32char * pszSet) noexcept
{

   return (strsize)wd32_cspn(pszBlock, pszSet);

}



inline strsize unichar_count(const wd32char * pstr) { return __wd32len(pstr); }


