#pragma once


namespace str
{


   inline  constexpr auto     char_length_to_byte_length(const_wd32char_trigger, strsize nCharLength) { return (::memsize) (nCharLength * sizeof(wd32char)); }
   inline  constexpr auto     byte_length_to_char_length(const_wd32char_trigger, memsize nByteLength) { return (::strsize) (nByteLength / sizeof(wd32char)); }


   inline i32 string_compare(const wd32char * pszA, const wd32char * pszB) noexcept { return wd32_cmp(pszA, pszB); }
   inline i32 string_compare_ci(const wd32char * pszA, const wd32char * pszB) noexcept { return wd32_icmp(pszA, pszB); }
   inline i32  string_n_compare(const wd32char * pszA, const wd32char * pszB, strsize len) noexcept { return wd32_ncmp(pszA, pszB, len); }
   inline i32  string_n_compare_ci(const wd32char * pszA, const wd32char * pszB, strsize len) noexcept { return wd32_nicmp(pszA, pszB, len); }
   inline i32 string_collate(const wd32char * pszA, const wd32char * pszB) noexcept { return wd32_coll(pszA, pszB); }
   inline i32 string_collate_ci(const wd32char * pszA, const wd32char * pszB) noexcept { return wd32_icoll(pszA, pszB); }
   inline i32  string_n_collate(const wd32char * pszA, const wd32char * pszB, strsize len) noexcept { return wd32_ncoll(pszA, pszB, len); }
   inline i32  string_n_collate_ci(const wd32char * pszA, const wd32char * pszB, strsize len) noexcept { return wd32_nicoll(pszA, pszB, len); }
   inline strsize string_get_length(const wd32char * psz) noexcept { return wd32_len(psz); }
   inline strsize string_safe_length(const wd32char * psz) noexcept { if (::is_null(psz)) return 0; return string_get_length(psz); }
   inline void copy_chars(wd32char * pchDest, const wd32char * pchSrc, strsize nChars) noexcept { memcpy_dup(pchDest, pchSrc, char_length_to_byte_length(pchSrc, nChars)); }
   inline void copy_chars(wd32char * pchDest, size_t nDestLen, const wd32char * pchSrc, strsize nChars) noexcept { ::memcpy_dup(pchDest, pchSrc, char_length_to_byte_length(pchSrc, nChars)); }
   inline void copy_chars_overlapped(wd32char * pchDest, const wd32char * pchSrc, strsize nChars) noexcept { memmove(pchDest, pchSrc, char_length_to_byte_length(pchSrc, nChars)); }
   inline wd32char * string_lowercase(wd32char * psz, strsize size) noexcept { wd32_lwr_s(psz, size); return  psz; }





   wd32char * char_next(const wd32char * psz) noexcept
   {

      return const_cast<wd32char *>(::uni_inc(psz));

   }

   inline bool isalpha(wd32char ch) noexcept { return wd32_char_is_alphabetic(ch); }
   inline bool isdigit(wd32char ch) noexcept { return wd32_char_is_digit(ch); }
   inline bool isspace(wd32char ch) noexcept { return wd32_char_is_space(ch); }

   inline wd32char tolower(wd32char ch) noexcept { return wd32_char_lowered(ch); }
   inline wd32char toupper(wd32char ch) noexcept { return wd32_char_uppered(ch); }


   //
   //
   //
   //i32  char_traits::string_collate(const wd32char * pszA,const wd32char * pszB) noexcept
   //{
   //   return strcmp(reinterpret_cast<const  wd32char*>(pszA),reinterpret_cast<const  wd32char*>(pszB));
   //}
   //
   //i32  char_traits::string_collate_ci(const wd32char * pszA,const wd32char * pszB) noexcept
   //{
   //   return ansi_compare_ci(reinterpret_cast<const  wd32char*>(pszA),reinterpret_cast<const  wd32char*>(pszB));
   //}
   //


   const wd32char * string_find_string(const wd32char * pszBlock, const wd32char * pszMatch) noexcept
   {

      return wd32_str(pszBlock, pszMatch);

   }


   const wd32char * string_find_string_ci(const wd32char * pszBlock, const wd32char * pszMatch) noexcept
   {

      return wd32_find_string_case_insensitive(pszBlock, pszMatch);

   }


   inline const wd32char * string_find_char(const wd32char * pszBlock, wd32char chMatch) noexcept
   {

      return wd32_chr(pszBlock, (wd32char)chMatch);

   }


   //
   ///*
   //strsize  char_traits::string_compare(const wd32char * pszA,const wd32char * pszB ) noexcept
   //{
   //return _mbscmp( reinterpret_cast< const uchar* >( pszA ), reinterpret_cast< const uchar* >( pszB ) );
   //}
   //
   //strsize  char_traits::string_compare_ci(const wd32char * pszA,const wd32char * pszB ) noexcept
   //{
   //return _mbsicmp( reinterpret_cast< const uchar* >( pszA ), reinterpret_cast< const uchar* >( pszB ) );
   //}
   //
   //strsize  char_traits::string_collate(const wd32char * pszA,const wd32char * pszB ) noexcept
   //{
   //return _mbscoll( reinterpret_cast< const uchar* >( pszA ), reinterpret_cast< const uchar* >( pszB ) );
   //}
   //
   //strsize  char_traits::string_collate_ci(const wd32char * pszA,const wd32char * pszB ) noexcept
   //{
   //return _mbsicoll( reinterpret_cast< const uchar* >( pszA ), reinterpret_cast< const uchar* >( pszB ) );
   //}
   //
   //const wd32char *  char_traits::string_find_string(const wd32char * pszBlock,const wd32char * pszMatch ) noexcept
   //{
   //return reinterpret_cast< const wd32char * >( _mbsstr( reinterpret_cast< const uchar* >( pszBlock ),
   //reinterpret_cast< const uchar* >( pszMatch ) ) );
   //}
   //
   //wd32char *  char_traits::string_find_string(wd32char * pszBlock,const wd32char * pszMatch ) noexcept
   //{
   //return( const_cast< wd32char * >( string_find_string( const_cast< const wd32char * >( pszBlock ), pszMatch ) ) );
   //}
   //
   //const wd32char *  char_traits::string_find_char(const wd32char * pszBlock,wd32char chMatch ) noexcept
   //{
   //return reinterpret_cast< const wd32char * >( _mbschr( reinterpret_cast< const uchar* >( pszBlock ), (uchar)chMatch ) );
   //}
   //*/




   inline const wd32char * string_find_string_reverse(const wd32char * psz, const wd32char * pszFind, strsize iStart) noexcept
   {
      strsize iLen = strsize(wd32_len(psz));
      strsize iLenFind = strsize(wd32_len(pszFind));
      if (iStart < 0)
         iStart = iLen + iStart;
      if (iLenFind > iLen)
         return nullptr;
      iStart = min(iStart, iLen - iLenFind);
      while (iStart >= 0)
      {
         if (wd32_ncmp(&psz[iStart], pszFind, iLenFind) == 0)
            return &psz[iStart];
         iStart--;
      }
      return nullptr;
   }


   const wd32char * string_scan_set(const wd32char * pszBlock, const wd32char * pszMatch) noexcept
   {

      if (pszMatch == nullptr || pszBlock == nullptr || *pszBlock == '\0')
         return nullptr;

      return wd32_scan(pszBlock, pszMatch);

   }


   strsize string_span_including(const wd32char * pszBlock, const wd32char * pszSet) noexcept
   {

      return (strsize)wd32_spn(pszBlock, pszSet);

   }



   strsize string_span_excluding(const wd32char * pszBlock, const wd32char * pszSet) noexcept
   {

      return (strsize)wd32_cspn(pszBlock, pszSet);

   }


   //#ifdef WINDOWS
   //_INSECURE_DEPRECATE("You must pass an output size_i32 to char_traits::string_uppercase")
   //#endif
   //wd32char *  char_traits::string_uppercase(wd32char * psz) noexcept
   //{
   //#pragma warning (push)
   //#pragma warning(disable : 4996)
   //   if(psz == nullptr)
   //      return nullptr;
   //   wd32char * point = psz;
   //   string strFinal;
   //   while(*point_i32)
   //   {
   //      strFinal += ::str::ch::to_upper_case(point);
   //      point = (wd32char *) ::str::utf8_inc(point);
   //   }
   //   strcpy(point_i32,strFinal);
   //   return psz;
   //
   //
   //   //   return reinterpret_cast< wd32char * >(( reinterpret_cast< uchar* >( psz ) ) );
   //#pragma warning (pop)
   //}
   //
   //#if defined(WINDOWS)
   //_INSECURE_DEPRECATE("You must pass an output size_i32 to char_traits::string_lowercase")
   //#endif
   //wd32char *  char_traits::string_lowercase(wd32char * psz) noexcept
   //{
   //#pragma warning (push)
   //#pragma warning(disable : 4996)
   //   if(psz == nullptr)
   //      return nullptr;
   //   wd32char * point = psz;
   //   string strFinal;
   //   while(*point_i32)
   //   {
   //      strFinal += ::str::ch::to_lower_case(point);
   //      point = (wd32char *) ::str::utf8_inc(point);
   //   }
   //   strcpy(point_i32,strFinal);
   //   return psz;
   //
   //   //   return reinterpret_cast< wd32char * >( _mbslwr( reinterpret_cast< uchar* >( psz ) ) );
   //#pragma warning (pop)
   //}
   //
   inline wd32char * string_uppercase(wd32char * psz, strsize size) noexcept
   {

      wd32_upr_s(psz, size);

      return psz;

   }


   wd32char * string_reverse(wd32char * psz) noexcept
   {

      if (psz == nullptr)
      {

         return nullptr;

      }

      wd32char * p1 = psz;

      wd32char * p2 = psz + (wd32_len(psz) - 1);

      while (p2 > p1)
      {

         swap(*p1, *p2);

         p1++;

         p2--;

      }

      return psz;

   }


   inline strsize get_formatted_length(const wd32char * pszFormat, va_list args) noexcept
   {

#ifdef WINDOWS

      wstring wstr(pszFormat);

      return _vscwprintf(wstr, args);

#else

      return vswprintf(nullptr, 0, pszFormat, args);

#endif

   }


   strsize string_format(wd32char * pszBuffer, const wd32char * pszFormat, va_list args) noexcept
   {

#ifdef WINDOWS

      throw_todo();

#else

      return vswprintf(pszBuffer, get_formatted_length(pszFormat, args), pszFormat, args);

#endif

   }

   strsize string_format(wd32char * pszBuffer, strsize nlength, const wd32char * pszFormat, va_list args) noexcept
   {

#ifdef WINDOWS
      throw_todo();
      //return vswprintf_s(pszBuffer, (size_t)nlength, pszFormat, args);
      return 0;

#else

      return vswprintf(pszBuffer, nlength, pszFormat, args);

#endif

   }


   //strsize  char_traits::get_char_length(const wd32char * pszSrc) noexcept
   //{
   //   // Returns required buffer length in XCHARs
   //   return strsize(strlen(pszSrc));
   //}
   //
   //strsize  char_traits::get_char_length(const wd32char * pszSrc,strsize nLength) noexcept
   //{
   //   (void)pszSrc;
   //   // Returns required buffer length in XCHARs
   //   return nLength;
   //}
   //
   //strsize  char_traits::get_char_length(const wd32char * pszSource) noexcept
   //{
   //   // Returns required buffer length in XCHARs
   //   return ::WideCharToMultiByte2(_gen_GetConversionACP(),0,pszSource,-1,nullptr,0,nullptr,nullptr) - 1;
   //}
   //
   //strsize  char_traits::get_char_length(const wd32char * pszSource,strsize nLength) noexcept
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
   //void  char_traits::ConvertTochar(wd32char * pszDest,strsize nDestLength,const wd32char * pszSrc,strsize nSrcLength) noexcept
   //{
   //   if(nSrcLength == -1) { nSrcLength=1 + get_char_length(pszSrc); }
   //   // nLen is in XCHARs
   //   ::acme::memcpy_s(pszDest,(size_t) (nDestLength*sizeof(wd32char)), pszSrc,(size_t) (nSrcLength*sizeof(wd32char)));
   //}
   //
   //void  char_traits::ConvertTochar(wd32char * pszDest, strsize nDestLength, const wd32char * pszSrc, strsize nSrcLength) noexcept
   //{
   //   // nLen is in XCHARs
   //   ::WideCharToMultiByte2(CP_UTF8,0,pszSrc, (i32) nSrcLength,pszDest,(i32)nDestLength,nullptr,nullptr);
   //}
   //
   //
   //void  char_traits::ConvertTochar(wd32char * pszDest,strsize nDestLength,const wd32char * pszSrc,strsize nSrcLength) noexcept
   //{
   //
   //   //if(nDestLength >= 0)
   //   //{
   //   //   __throw(::exception::exception("I am wasting this branching (if(nDestLength >= 0) to tell you that nDestLength should be negative so the buffer is already correct size... or you like incorrect size_i32? Go to Facebook and click in Like for Community \"I Like incorrect size_i32!!\", there should exist such community... there are so many things in the multi bramas... The hardware will check again if you didn't dirtied any other process... (only another process, though)... and you're probably be fired or even not be hired if incorrect size_i32"));
   //   //}
   //
   //   wd32_to_ansi(pszDest,pszSrc,nSrcLength);
   //
   //}
   //
   //void char_traits::ConvertToOem(wd32char* pstrString) RELEASENOTHROW
   //{
   //#ifdef WINDOWS_DESKTOP
   //   bool fSuccess=::CharToOemA(pstrString,pstrString) != 0;
   //   // old version can't report error
   //   ASSERT(fSuccess);
   //#endif
   //}
   //
   //void char_traits::ConvertToAnsi(wd32char* pstrString) RELEASENOTHROW
   //{
   //#ifdef WINDOWS_DESKTOP
   //   bool fSuccess=::OemToCharA(pstrString,pstrString) != 0;
   //   // old version can't report error
   //   ASSERT(fSuccess);
   //#endif
   //}



   //void char_traits::ConvertToAnsi(wd32char* pstrString, strsize size)
   //{
   //
   //#ifdef WINDOWS_DESKTOP
   //
   //   if(size > UINT_MAX)
   //   {
   //      // API only allows u32 size_i32
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
   //void char_traits::ConvertToOem(wd32char* pstrString, strsize size)
   //{
   //
   //#ifdef WINDOWS_DESKTOP
   //
   //   if(size > UINT_MAX)
   //   {
   //      // API only allows u32 size_i32
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

   inline const wd32char * string_find_char_reverse(const wd32char * psz, wd32char ch, strsize iStart) noexcept
   {


      const wd32char * p;

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


   inline void flood_characters(wd32char * pwsz, wd32char wch, strsize len) noexcept
   {

      while (len > 0)
      {

         *pwsz = wch;

         pwsz++;

         len--;

      }

   }

} // namespace str


