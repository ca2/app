// Refactored by camilo on 2022-11-04 05:43 <3ThomasBorregaardSorensen!!
#pragma once



inline  constexpr strsize     char_length_to_byte_length(const_ansichar_trigger, strsize nCharLength) { return (::memsize)(nCharLength * sizeof(ansichar)); }
inline  constexpr strsize     byte_length_to_char_length(const_ansichar_trigger, memsize nByteLength) { return (::strsize)(nByteLength / sizeof(ansichar)); }



inline void copy_chars(ansichar * pchDest, const ansichar * pchSrc, strsize nChars) noexcept { memcpy_dup(pchDest, pchSrc, char_length_to_byte_length(pchSrc, nChars)); }
inline void copy_chars(ansichar * pchDest, size_t nDestLen, const ansichar * pchSrc, strsize nChars) noexcept { ::memcpy_dup(pchDest, pchSrc, char_length_to_byte_length(pchSrc, nChars)); }
inline void copy_chars_overlapped(ansichar * pchDest, const ansichar * pchSrc, strsize nChars) noexcept { memmove(pchDest, pchSrc, char_length_to_byte_length(pchSrc, nChars)); }


inline i32 string_compare(const ansichar * pszA, const ansichar * pszB) noexcept { int i; if (_str_safe_precmp(i, pszA, pszB)) return i; return strcmp(pszA, pszB); }
inline i32 string_compare_ci(const ansichar * pszA, const ansichar * pszB) noexcept { int i; if (_str_safe_precmp(i, pszA, pszB)) return i; return ansi_compare_ci(pszA, pszB); }
inline i32 string_count_compare(const ansichar * pszA, const ansichar * pszB, strsize len) noexcept { int i; if (_str_safe_precmp(i, pszA, pszB)) return i; return  strncmp(pszA, pszB, len); }
inline i32 string_count_compare_ci(const ansichar * pszA, const ansichar * pszB, strsize len) noexcept { int i; if (_str_safe_precmp(i, pszA, pszB)) return i; return  ansi_nicmp(pszA, pszB, len); }
inline i32 string_collate(const ansichar * pszA, const ansichar * pszB) noexcept { int i; if (_str_safe_precmp(i, pszA, pszB)) return i; return  strcoll(pszA, pszB); }
inline i32 string_collate_ci(const ansichar * pszA, const ansichar * pszB) noexcept { int i; if (_str_safe_precmp(i, pszA, pszB)) return i; return  __ansiicoll(pszA, pszB); }
inline i32 string_n_collate(const ansichar * pszA, const ansichar * pszB, strsize len) noexcept { int i; if (_str_safe_precmp(i, pszA, pszB)) return i; return  __ansincoll(pszA, pszB, len); }
inline i32 string_n_collate_ci(const ansichar * pszA, const ansichar * pszB, strsize len) noexcept { int i; if (_str_safe_precmp(i, pszA, pszB)) return i; return  __ansinicoll(pszA, pszB, len); }
inline strsize string_get_length(const ansichar * psz) noexcept { return strlen(psz); }
inline strsize string_get_length(const ansichar* psz, strsize sizeMaximumInterest) noexcept 
{ 
   strsize size = 0;
   sizeMaximumInterest++;
   while (*psz && sizeMaximumInterest > 0) { psz++; size++; sizeMaximumInterest--; }
   return sizeMaximumInterest == 0 ? -1 : size;
}
inline strsize string_safe_length(const ansichar * psz) noexcept { if (::is_null(psz)) return 0; return string_get_length(psz); }
inline strsize string_safe_length(const ansichar* psz, strsize sizeMaximumInterest) noexcept { if (::is_null(psz)) return 0; return string_get_length(psz, sizeMaximumInterest); }
inline ansichar * string_lowercase(ansichar * psz, strsize size) noexcept { ansi_lwr_s(psz, size); return  psz; }




inline const ansichar * string_find_string(const ansichar * pszBlock, const ansichar * pszMatch) noexcept
{

   return ansi_find_string(pszBlock, pszMatch);

}


inline const ansichar * string_find_string_ci(const ansichar * pszBlock, const ansichar * pszMatch) noexcept
{

   return ansi_find_string_ci(pszBlock, pszMatch);

}


inline const ansichar * string_find_char(const ansichar * pszBlock, ansichar chMatch) noexcept
{

   return strchr(pszBlock, (ansichar)chMatch);

}


inline const ansichar * string_find_string_reverse(const ansichar * psz, const ansichar * pszFind, strsize iStart) noexcept
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




inline ansichar * string_uppercase(ansichar * psz, strsize size) noexcept
{

   ansi_upr_s(psz, size);

   return psz;

}


inline ansichar * string_reverse(ansichar * psz) noexcept
{

   if (psz == nullptr)
   {

      return nullptr;

   }

   string strReverse;

   ansichar * p = psz + strlen(psz);

   ansichar * pDec;

   while ((pDec = (ansichar *)unicode_decrement(psz, p)) != nullptr)
   {

      strReverse.append(pDec, pDec - p);

      p = pDec;
   }

   strcpy(psz, strReverse);

   return psz;

}



inline strsize  get_formatted_length(const ansichar * pszFormat, va_list args) noexcept
{

#ifdef WINDOWS

   return _vscprintf(pszFormat, args);

#else

   return vsnprintf(nullptr, 0, pszFormat, args);

#endif

}


inline strsize  string_format(ansichar * pszBuffer, strsize nlength, const ansichar * pszFormat, va_list args) noexcept
{

#ifdef WINDOWS

   return vsprintf_s(pszBuffer, (size_t)nlength, pszFormat, args);

#else

   return vsnprintf(pszBuffer, nlength, pszFormat, args);

#endif

}



inline const ansichar * string_find_char_reverse(const ansichar * psz, ansichar ch, strsize iStart) noexcept
{


   const ansichar * p;

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


inline void  flood_characters(ansichar * psz, ansichar ch, strsize len) noexcept
{

   memset(psz, ch, len);

}


inline ansichar character_tolower(ansichar ch) noexcept { return ansi_char_tolower(ch); }
inline ansichar character_toupper(ansichar ch) noexcept { return ansi_char_toupper(ch); }


inline bool character_isdigit(ansichar ch) noexcept { return ansi_char_isdigit(ch); }
inline bool character_isalpha(ansichar ch) noexcept { return ansi_char_isalpha(ch); }
inline bool character_isalnum(ansichar ch) noexcept { return ansi_char_isalnum(ch); }
inline bool character_isspace(ansichar ch) noexcept { return ansi_char_isspace(ch); }


// From STRSPN(3) - Linux Programmer's Manual
// The strspn() function calculates the length(in bytes) of the initial
// segment of s which consists entirely of bytes in accept.
// The strcspn() function calculates the length of the initial segment
// of s which consists entirely of bytes not in reject.

inline strsize string_span_including(const ansichar * pszBlock, const ansichar * pszSet) noexcept
{

   return (strsize)strspn(pszBlock, pszSet);

}


inline strsize string_span_excluding(const ansichar * pszBlock, const ansichar * pszSet) noexcept
{

   return (strsize)strcspn(pszBlock, pszSet);

}


inline strsize unichar_count(const ansichar * pstr) { return ansi_to_wd32_len(pstr); }


