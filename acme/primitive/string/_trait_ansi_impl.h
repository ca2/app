#pragma once


namespace str
{


   inline  constexpr auto     char_length_to_byte_length(const_ansichar_trigger, strsize nCharLength) { return (::memsize) (nCharLength * sizeof(ansichar)); }
   inline  constexpr auto     byte_length_to_char_length(const_ansichar_trigger, memsize nByteLength) { return (::strsize) (nByteLength / sizeof(ansichar)); }

   inline bool _str_safe_precmp(int & i, const ansichar* pszA, const ansichar* pszB)
   {

      if (::is_null(pszA))
      {

         if (::is_null(pszB))
         {

            i = 0;

            return true;

         }
         else
         {

            i = -1;

            return true;

         }

      }
      else if (::is_null(pszB))
      {

         i = 1;

         return true;

      }

      return false;

   }

   inline i32 string_compare(const ansichar* pszA, const ansichar* pszB) noexcept { int i; if(_str_safe_precmp(i, pszA, pszB)) return i; return strcmp(pszA, pszB); }
   inline i32 string_compare_ci(const ansichar * pszA, const ansichar * pszB) noexcept { int i; if(_str_safe_precmp(i, pszA, pszB)) return i; return ansi_compare_ci(pszA, pszB); }
   inline i32  string_n_compare(const ansichar * pszA, const ansichar * pszB, strsize len) noexcept { int i; if(_str_safe_precmp(i, pszA, pszB)) return i; return  strncmp(pszA, pszB, len); }
   inline i32  string_n_compare_ci(const ansichar * pszA, const ansichar * pszB, strsize len) noexcept { int i; if(_str_safe_precmp(i, pszA, pszB)) return i; return  ansi_nicmp(pszA, pszB, len); }
   inline i32 string_collate(const ansichar * pszA, const ansichar * pszB) noexcept { int i; if(_str_safe_precmp(i, pszA, pszB)) return i; return  strcoll(pszA, pszB); }
   inline i32 string_collate_ci(const ansichar * pszA, const ansichar * pszB) noexcept { int i; if(_str_safe_precmp(i, pszA, pszB)) return i; return  __ansiicoll(pszA, pszB); }
   inline i32  string_n_collate(const ansichar * pszA, const ansichar * pszB, strsize len) noexcept { int i; if(_str_safe_precmp(i, pszA, pszB)) return i; return  __ansincoll(pszA, pszB, len); }
   inline i32  string_n_collate_ci(const ansichar * pszA, const ansichar * pszB, strsize len) noexcept { int i; if(_str_safe_precmp(i, pszA, pszB)) return i; return  __ansinicoll(pszA, pszB, len); }
   inline strsize string_get_length(const ansichar * psz) noexcept { return strlen(psz); }
   inline strsize string_safe_length(const ansichar * psz) noexcept { if (c_is_null(psz)) return 0; return string_get_length(psz); }
   inline void copy_chars(ansichar * pchDest, const ansichar * pchSrc, strsize nChars) noexcept { memcpy_dup(pchDest, pchSrc, char_length_to_byte_length(pchSrc, nChars)); }
   inline void copy_chars(ansichar * pchDest, size_t nDestLen, const ansichar * pchSrc, strsize nChars) noexcept { ::memcpy_dup(pchDest, pchSrc, char_length_to_byte_length(pchSrc, nChars)); }
   inline void copy_chars_overlapped(ansichar * pchDest, const ansichar * pchSrc, strsize nChars) noexcept { memmove(pchDest, pchSrc, char_length_to_byte_length(pchSrc, nChars)); }
   inline ansichar * string_lowercase(ansichar * psz, strsize size) noexcept { ansi_lwr_s(psz, size); return  psz; }


   ansichar * char_next(const ansichar * psz) noexcept
   {

      return const_cast<ansichar *>(::utf8_inc(psz));

   }


   inline bool isalpha(ansichar ch) noexcept { return ansi_char_is_alphabetic(ch); }
   inline bool isdigit(ansichar ch) noexcept { return ansi_char_is_digit(ch); }
   inline bool isspace(ansichar ch) noexcept { return ansi_char_is_space(ch); }

   inline ansichar tolower(ansichar ch) noexcept { return ansi_char_lowered(ch); }
   inline ansichar toupper(ansichar ch) noexcept { return ansi_char_uppered(ch); }


   const ansichar * string_find_string(const ansichar * pszBlock, const ansichar * pszMatch) noexcept
   {

      return ansi_find_string(pszBlock, pszMatch);

   }


   const ansichar * string_find_string_ci(const ansichar * pszBlock, const ansichar * pszMatch) noexcept
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

      iStart = min(iStart, iLen - iLenFind);

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


   const ansichar * string_scan_set(const ansichar * pszBlock, const ansichar * pszMatch) noexcept
   {

      if (pszMatch == nullptr || pszBlock == nullptr || *pszBlock == '\0')
         return nullptr;

      return ansi_scan(pszBlock, pszMatch);

   }

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


   //#ifdef WINDOWS
   //_INSECURE_DEPRECATE("You must pass an output size to char_traits::string_uppercase")
   //#endif
   //ansichar *  char_traits::string_uppercase(ansichar * psz) noexcept
   //{
   //#pragma warning (push)
   //#pragma warning(disable : 4996)
   //   if(psz == nullptr)
   //      return nullptr;
   //   ansichar * point = psz;
   //   string strFinal;
   //   while(*point)
   //   {
   //      strFinal += ::str::ch::to_upper_case(point);
   //      point = (ansichar *) ::str::utf8_inc(point);
   //   }
   //   strcpy(point,strFinal);
   //   return psz;
   //
   //
   //   //   return reinterpret_cast< ansichar * >(( reinterpret_cast< uchar* >( psz ) ) );
   //#pragma warning (pop)
   //}
   //
   //#if defined(WINDOWS)
   //_INSECURE_DEPRECATE("You must pass an output size to char_traits::string_lowercase")
   //#endif
   //ansichar *  char_traits::string_lowercase(ansichar * psz) noexcept
   //{
   //#pragma warning (push)
   //#pragma warning(disable : 4996)
   //   if(psz == nullptr)
   //      return nullptr;
   //   ansichar * point = psz;
   //   string strFinal;
   //   while(*point)
   //   {
   //      strFinal += ::str::ch::to_lower_case(point);
   //      point = (ansichar *) ::str::utf8_inc(point);
   //   }
   //   strcpy(point,strFinal);
   //   return psz;
   //
   //   //   return reinterpret_cast< ansichar * >( _mbslwr( reinterpret_cast< uchar* >( psz ) ) );
   //#pragma warning (pop)
   //}
   //
   inline ansichar * string_uppercase(ansichar * psz, strsize size) noexcept
   {

      ansi_upr_s(psz, size);

      return psz;

   }


   ansichar * string_reverse(ansichar * psz) noexcept
   {

      if (psz == nullptr)
      {

         return nullptr;

      }

      string strReverse;

      ansichar * p = psz + strlen(psz);

      ansichar * pDec;

      while ((pDec = (ansichar *) ::str::uni_dec(psz, p)) != nullptr)
      {

         strReverse.append(pDec, pDec - p);

         p = pDec;
      }

      strcpy(psz, strReverse);

      return psz;

   }



   inline strsize get_formatted_length(const ansichar * pszFormat, va_list args) noexcept
   {

#ifdef WINDOWS

      return _vscprintf(pszFormat, args);

#else

      return vsnprintf(nullptr, 0, pszFormat, args);

#endif

   }


   inline strsize string_format(ansichar * pszBuffer, const ansichar * pszFormat, va_list args) noexcept
   {

      return vsprintf(pszBuffer, pszFormat, args);

   }


   strsize string_format(ansichar * pszBuffer, strsize nlength, const ansichar * pszFormat, va_list args) noexcept
   {

#ifdef WINDOWS

      return vsprintf_s(pszBuffer, (size_t)nlength, pszFormat, args);

#else

      return vsnprintf(pszBuffer, nlength, pszFormat, args);

#endif

   }


   //strsize  char_traits::get_char_length(const ansichar * pszSrc) noexcept
   //{
   //   // Returns required buffer length in XCHARs
   //   return strsize(strlen(pszSrc));
   //}
   //
   //strsize  char_traits::get_char_length(const ansichar * pszSrc,strsize nLength) noexcept
   //{
   //   (void)pszSrc;
   //   // Returns required buffer length in XCHARs
   //   return nLength;
   //}
   //
   //strsize  char_traits::get_char_length(const unichar * pszSource) noexcept
   //{
   //   // Returns required buffer length in XCHARs
   //   return ::WideCharToMultiByte2(_gen_GetConversionACP(),0,pszSource,-1,nullptr,0,nullptr,nullptr) - 1;
   //}
   //
   //strsize  char_traits::get_char_length(const unichar * pszSource,strsize nLength) noexcept
   //{
   //   // Returns required buffer length in XCHARs
   //   return ::WideCharToMultiByte2(_gen_GetConversionACP(),0,pszSource,(i32)nLength,nullptr,0,nullptr,nullptr);
   //}
   //
   //
   //strsize  char_traits::get_char_length(const wd32char * pszSource) noexcept
   //{
   //   return wd32_to_ansi_len(pszSource);
   //}
   //
   //strsize  char_traits::get_char_length(const wd32char * pszSource,strsize nLength) noexcept
   //{
   //   return wd32_to_ansi_len(pszSource, nLength);
   //}
   //
   //void  char_traits::ConvertTochar(ansichar * pszDest,strsize nDestLength,const ansichar * pszSrc,strsize nSrcLength) noexcept
   //{
   //   if(nSrcLength == -1) { nSrcLength=1 + get_char_length(pszSrc); }
   //   // nLen is in XCHARs
   //   ::acme::memcpy_s(pszDest,(size_t) (nDestLength*sizeof(ansichar)), pszSrc,(size_t) (nSrcLength*sizeof(ansichar)));
   //}
   //
   //void  char_traits::ConvertTochar(ansichar * pszDest, strsize nDestLength, const unichar * pszSrc, strsize nSrcLength) noexcept
   //{
   //   // nLen is in XCHARs
   //   ::WideCharToMultiByte2(CP_UTF8,0,pszSrc, (i32) nSrcLength,pszDest,(i32)nDestLength,nullptr,nullptr);
   //}
   //
   //
   //void  char_traits::ConvertTochar(ansichar * pszDest,strsize nDestLength,const wd32char * pszSrc,strsize nSrcLength) noexcept
   //{
   //
   //   //if(nDestLength >= 0)
   //   //{
   //   //   __throw(::exception::exception("I am wasting this branching (if(nDestLength >= 0) to tell you that nDestLength should be negative so the buffer is already correct size... or you like incorrect size? Go to Facebook and click in Like for Community \"I Like incorrect size!!\", there should exist such community... there are so many things in the multi bramas... The hardware will check again if you didn't dirtied any other process... (only another process, though)... and you're probably be fired or even not be hired if incorrect size"));
   //   //}
   //
   //   wd32_to_ansi(pszDest,pszSrc,nSrcLength);
   //
   //}
   //
   //void char_traits::ConvertToOem(ansichar* pstrString) RELEASENOTHROW
   //{
   //#ifdef WINDOWS_DESKTOP
   //   bool fSuccess=::CharToOemA(pstrString,pstrString) != 0;
   //   // old version can't report error
   //   ASSERT(fSuccess);
   //#endif
   //}
   //
   //void char_traits::ConvertToAnsi(ansichar* pstrString) RELEASENOTHROW
   //{
   //#ifdef WINDOWS_DESKTOP
   //   bool fSuccess=::OemToCharA(pstrString,pstrString) != 0;
   //   // old version can't report error
   //   ASSERT(fSuccess);
   //#endif
   //}
   //

#ifdef WINDOWS


   BSTR AllocSysString(const ansichar * pchData, strsize nDataLength) noexcept
   {

      BSTR bstr = nullptr;

      strsize nLen = utf_to_utf_length(bstr, pchData, nDataLength);

      bstr = ::SysAllocStringLen(nullptr, (::u32)nLen);

      if (bstr != nullptr)
      {

         utf_to_utf(bstr, pchData, nDataLength);

      }

      return bstr;

   }


   // pbstr is [in,out] BSTR string
   bool ReAllocSysString(BSTR * pbstr, const ansichar * pchData, strsize nDataLength) noexcept
   {

      strsize nLen = utf_to_utf_length(pbstr, pchData, nDataLength);

      bool bSuccess = ::SysReAllocStringLen(pbstr, nullptr, (::u32)nLen) != 0;

      if (bSuccess)
      {

         utf_to_utf(*pbstr, pchData, nDataLength);

      }

      return bSuccess;

   }


#endif


   u32 format_message(u32 dwFlags, const void * pSource, u32 dwMessageID, u32 dwLanguageID, ansichar * pszBuffer, u32 nSize, va_list * pArguments) noexcept
   {

#ifdef WINDOWS

      return ::FormatMessageA(dwFlags, pSource, dwMessageID, dwLanguageID, pszBuffer, nSize, pArguments);

#else

      return 0;

#endif

   }


   //u32  char_traits::format_message(u32 dwFlags,const void * pSource,u32 dwMessageID,u32 dwLanguageID,ansichar * pszBuffer,u32 nSize,va_list* pArguments) noexcept
   //{
   //
   //#ifdef WINDOWS
   //
   //   return format_message(dwFlags, pSource, dwMessageID, dwLanguageID, pszBuffer, nSize, pArguments);
   //
   //#else
   //
   //   return 0;
   //
   //#endif
   //
   //}
   //
   //strsize  char_traits::SafeStringLen(const ansichar * psz) noexcept
   //{
   //   // returns length in bytes
   //   return (psz != nullptr) ? strsize(strlen(psz)) : 0;
   //}
   //
   //strsize  char_traits::SafeStringLen(const unichar * psz) noexcept
   //{
   //   // returns length in wchar_ts
   //#ifdef WINDOWS
   //   return (psz != nullptr) ? strsize(wcslen(psz)) : 0;
   //#else
   //   return (psz != nullptr) ? strsize(wide_length(psz)) : 0;
   //#endif
   //}
   //
   //strsize  char_traits::GetCharLen(const unichar* pch) noexcept
   //{
   //   (void)pch;
   //   // returns ansichar length
   //   return 1;
   //}
   //
   //strsize  char_traits::GetCharLen(const ansichar* pch) noexcept
   //{
   //   // returns ansichar length
   //   return  ::str::get_utf8_char(pch).get_length();
   //}


   u32  get_environment_variable(const ansichar * pszVar, ansichar * pszBuffer, u32 dwSize)
   {

#ifdef _UWP

      __throw(todo());

#elif defined(WINDOWS_DESKTOP)

      return ::GetEnvironmentVariableA(pszVar, pszBuffer, dwSize);

#else

      const ansichar * pszEnv = getenv(pszVar);

      if (pszBuffer == nullptr)
      {

         if (pszEnv == nullptr)
         {

            return 0;

         }
         else
         {

            return (u32)strlen(pszEnv);

         }

      }

      return (u32)strlen(ansi_count_copy(pszBuffer, pszEnv, dwSize));

#endif

   }


   //void char_traits::ConvertToAnsi(ansichar* pstrString, strsize size)
   //{
   //
   //#ifdef WINDOWS_DESKTOP
   //
   //   if(size > UINT_MAX)
   //   {
   //      // API only allows u32 size
   //      __throw(invalid_argument_exception());
   //   }
   //   u32 dwSize=static_cast<u32>(size);
   //   bool fSuccess=::OemToCharBuffA(pstrString,pstrString,dwSize) != 0;
   //   if(!fSuccess)
   //   {
   //      __throw(last_error_exception());
   //   }
   //
   //#endif
   //
   //}
   //
   //
   //void char_traits::ConvertToOem(ansichar* pstrString, strsize size)
   //{
   //
   //#ifdef WINDOWS_DESKTOP
   //
   //   if(size > UINT_MAX)
   //   {
   //      // API only allows u32 size
   //      __throw(invalid_argument_exception());
   //   }
   //   u32 dwSize=static_cast<u32>(size);
   //   bool fSuccess=::CharToOemBuffA(pstrString,pstrString,dwSize) != 0;
   //   if(!fSuccess)
   //   {
   //      __throw(last_error_exception());
   //   }
   //
   //#endif
   //
   //}
   //
   //

   inline const ansichar * string_find_char_reverse(const ansichar * psz, ansichar ch, strsize iStart) noexcept
   {


      const ansichar * p;

      if (iStart < 0)
      {

         p = psz + string_safe_length(psz) - iStart;

      }
      else
      {

         p = psz + min(iStart, string_safe_length(psz) - 1);

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


   inline void flood_characters(ansichar * psz, ansichar ch, strsize len) noexcept
   {

      memset(psz, ch, len);

   }


} // namespace str



