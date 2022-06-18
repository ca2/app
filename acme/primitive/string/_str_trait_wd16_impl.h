#pragma once



   inline  constexpr strsize     str::char_length_to_byte_length(const_wd16char_trigger, strsize nCharLength) { return (::memsize) (nCharLength * sizeof(wd16char)); }
   inline  constexpr strsize    str::byte_length_to_char_length(const_wd16char_trigger, memsize nByteLength) { return (::strsize) (nByteLength / sizeof(wd16char)); }


   inline i32 str::string_compare(const wd16char * pszA, const wd16char * pszB) noexcept { return wd16_cmp(pszA, pszB); }
   inline i32 str::string_compare_ci(const wd16char * pszA, const wd16char * pszB) noexcept { return wd16_icmp(pszA, pszB); }
   inline i32 str::string_n_compare(const wd16char * pszA, const wd16char * pszB, strsize len) noexcept { return wd16_ncmp(pszA, pszB, len); }
   inline i32 str::string_n_compare_ci(const wd16char * pszA, const wd16char * pszB, strsize len) noexcept { return wd16_nicmp(pszA, pszB, len); }
   inline i32 str::string_collate(const wd16char * pszA, const wd16char * pszB) noexcept { return wd16_coll(pszA, pszB); }
   inline i32 str::string_collate_ci(const wd16char * pszA, const wd16char * pszB) noexcept { return wd16_icoll(pszA, pszB); }
   inline i32 str::string_n_collate(const wd16char * pszA, const wd16char * pszB, strsize len) noexcept { return wd16_ncoll(pszA, pszB, len); }
   inline i32 str::string_n_collate_ci(const wd16char * pszA, const wd16char * pszB, strsize len) noexcept { return wd16_nicoll(pszA, pszB, len); }
   inline strsize str::string_get_length(const wd16char * psz) noexcept { return wd16_len(psz); }
   inline strsize str::string_safe_length(const wd16char * psz) noexcept { if (::is_null(psz)) return 0; return string_get_length(psz); }
   inline void str::copy_chars(wd16char * pchDest, const wd16char * pchSrc, strsize nChars) noexcept { memcpy_dup(pchDest, pchSrc, char_length_to_byte_length(pchSrc, nChars)); }
   inline void str::copy_chars(wd16char * pchDest, size_t nDestLen, const wd16char * pchSrc, strsize nChars) noexcept { ::memcpy_dup(pchDest, pchSrc, char_length_to_byte_length(pchSrc, nChars)); }
   inline void str::copy_chars_overlapped(wd16char * pchDest, const wd16char * pchSrc, strsize nChars) noexcept { memmove(pchDest, pchSrc, char_length_to_byte_length(pchSrc, nChars)); }
   inline wd16char * str::string_lowercase(wd16char * psz, strsize size) noexcept { wd16_lwr_s(psz, size); return  psz; }




   inline bool str::isalpha(wd16char ch) noexcept { return wd16_char_is_alphabetic(ch); }
   inline bool str::isdigit(wd16char ch) noexcept { return wd16_char_is_digit(ch); }
   inline bool str::isspace(wd16char ch) noexcept { return wd16_char_is_space(ch); }

   inline wd16char str::tolower(wd16char ch) noexcept { return wd16_char_lowered(ch); }
   inline wd16char str::toupper(wd16char ch) noexcept { return wd16_char_uppered(ch); }


   //
   //
   //
   //i32  char_traits::string_collate(const wd16char * pszA,const wd16char * pszB) noexcept
   //{
   //   return strcmp(reinterpret_cast<const  wd16char*>(pszA),reinterpret_cast<const  wd16char*>(pszB));
   //}
   //
   //i32  char_traits::string_collate_ci(const wd16char * pszA,const wd16char * pszB) noexcept
   //{
   //   return ansi_compare_ci(reinterpret_cast<const  wd16char*>(pszA),reinterpret_cast<const  wd16char*>(pszB));
   //}
   //


   const wd16char * str::string_find_string(const wd16char * pszBlock, const wd16char * pszMatch) noexcept
   {

      return wd16_str(pszBlock, pszMatch);

   }


   const wd16char * str::string_find_string_ci(const wd16char * pszBlock, const wd16char * pszMatch) noexcept
   {

      return wd16_find_string_case_insensitive(pszBlock, pszMatch);

   }


   inline const wd16char * str::string_find_char(const wd16char * pszBlock, wd16char chMatch) noexcept
   {

      return wd16_chr(pszBlock, (wd16char)chMatch);

   }


   //
   ///*
   //strsize  char_traits::string_compare(const wd16char * pszA,const wd16char * pszB ) noexcept
   //{
   //return _mbscmp( reinterpret_cast< const uchar* >( pszA ), reinterpret_cast< const uchar* >( pszB ) );
   //}
   //
   //strsize  char_traits::string_compare_ci(const wd16char * pszA,const wd16char * pszB ) noexcept
   //{
   //return _mbsicmp( reinterpret_cast< const uchar* >( pszA ), reinterpret_cast< const uchar* >( pszB ) );
   //}
   //
   //strsize  char_traits::string_collate(const wd16char * pszA,const wd16char * pszB ) noexcept
   //{
   //return _mbscoll( reinterpret_cast< const uchar* >( pszA ), reinterpret_cast< const uchar* >( pszB ) );
   //}
   //
   //strsize  char_traits::string_collate_ci(const wd16char * pszA,const wd16char * pszB ) noexcept
   //{
   //return _mbsicoll( reinterpret_cast< const uchar* >( pszA ), reinterpret_cast< const uchar* >( pszB ) );
   //}
   //
   //const wd16char *  char_traits::string_find_string(const wd16char * pszBlock,const wd16char * pszMatch ) noexcept
   //{
   //return reinterpret_cast< const wd16char * >( _mbsstr( reinterpret_cast< const uchar* >( pszBlock ),
   //reinterpret_cast< const uchar* >( pszMatch ) ) );
   //}
   //
   //wd16char *  char_traits::string_find_string(wd16char * pszBlock,const wd16char * pszMatch ) noexcept
   //{
   //return( const_cast< wd16char * >( string_find_string( const_cast< const wd16char * >( pszBlock ), pszMatch ) ) );
   //}
   //
   //const wd16char *  char_traits::string_find_char(const wd16char * pszBlock,wd16char chMatch ) noexcept
   //{
   //return reinterpret_cast< const wd16char * >( _mbschr( reinterpret_cast< const uchar* >( pszBlock ), (uchar)chMatch ) );
   //}
   //*/




   inline const wd16char * str::string_find_string_reverse(const wd16char * psz, const wd16char * pszFind, strsize iStart) noexcept
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


   const wd16char * str::string_scan_set(const wd16char * pszBlock, const wd16char * pszMatch) noexcept
   {

      if (pszMatch == nullptr || pszBlock == nullptr || *pszBlock == '\0')
         return nullptr;

      return wd16_scan(pszBlock, pszMatch);

   }


   strsize str::string_span_including(const wd16char * pszBlock, const wd16char * pszSet) noexcept
   {

      return (strsize)wd16_spn(pszBlock, pszSet);

   }



   strsize str::string_span_excluding(const wd16char * pszBlock, const wd16char * pszSet) noexcept
   {

      return (strsize)wd16_cspn(pszBlock, pszSet);

   }


   //#ifdef WINDOWS
   //_INSECURE_DEPRECATE("You must pass an output size_i32 to char_traits::string_uppercase")
   //#endif
   //wd16char *  char_traits::string_uppercase(wd16char * psz) noexcept
   //{
   //#pragma warning (push)
   //#pragma warning(disable : 4996)
   //   if(psz == nullptr)
   //      return nullptr;
   //   wd16char * pszPos = psz;
   //   string strFinal;
   //   while(*pszPos)
   //   {
   //      strFinal += ::str::ch().to_upper_case(pszPos);
   //      ::str().increment(pszPos);
   //   }
   //   strcpy(pszPos,strFinal);
   //   return psz;
   //
   //
   //   //   return reinterpret_cast< wd16char * >(( reinterpret_cast< uchar* >( psz ) ) );
   //#pragma warning (pop)
   //}
   //
   //#if defined(WINDOWS)
   //_INSECURE_DEPRECATE("You must pass an output size_i32 to char_traits::string_lowercase")
   //#endif
   //wd16char *  char_traits::string_lowercase(wd16char * psz) noexcept
   //{
   //#pragma warning (push)
   //#pragma warning(disable : 4996)
   //   if(psz == nullptr)
   //      return nullptr;
   //   wd16char * pszPos = psz;
   //   string strFinal;
   //   while(*pszPos)
   //   {
   //      strFinal += ::str::ch().to_lower_case(pszPos);
   //      ::str().increment(pszPos);
   //   }
   //   strcpy(pszPos,strFinal);
   //   return psz;
   //
   //   //   return reinterpret_cast< wd16char * >( _mbslwr( reinterpret_cast< uchar* >( psz ) ) );
   //#pragma warning (pop)
   //}
   //
   inline wd16char * str::string_uppercase(wd16char * psz, strsize size) noexcept
   {

      wd16_upr_s(psz, size);

      return psz;

   }


   wd16char * str::string_reverse(wd16char * psz) noexcept
   {

      if (psz == nullptr)
      {

         return nullptr;

      }

      wd16string strReverse;

      wd16char * p = psz + wd16_len(psz);

      wd16char * pDec;

      while ((pDec = prior(psz, p)) != nullptr)
      {

         strReverse.append(pDec, pDec - p);

         p = pDec;

      }

      wd16_cpy(psz, strReverse);

      return psz;

   }


   inline strsize str::get_formatted_length(const wd16char * pszFormat, va_list args) noexcept
   {

#ifdef WINDOWS

      return _vscwprintf(pszFormat, args);

#else

      wd32string wstr(pszFormat);

      return vswprintf(nullptr, 0, wstr, args);

#endif

   }


   strsize str::string_format(wd16char * pszBuffer, const wd16char * pszFormat, va_list args) noexcept
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


   strsize str::string_format(wd16char * pszBuffer, strsize nlength, const wd16char * pszFormat, va_list args) noexcept
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




   inline const wd16char * str::string_find_char_reverse(const wd16char * psz, wd16char ch, strsize iStart) noexcept
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


   inline void str::flood_characters(wd16char * pwsz, wd16char wch, strsize len) noexcept
   {

      while (len > 0)
      {

         *pwsz = wch;

         pwsz++;

         len--;

      }

   }

