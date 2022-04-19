#pragma once


namespace str
{


   template < typename TYPE_TARGET, typename TYPE_SOURCE >
   inline strsize utf_to_utf_length(const TYPE_TARGET *, const TYPE_SOURCE * psource, strsize srclen)
   {

      throw ::interface_only();

      return 0;

   }


   template <  >
   inline strsize utf_to_utf_length(const ansichar *, const ansichar * psource, strsize srclen)
   {

      return srclen;

   }


   template <  >
   inline strsize utf_to_utf_length(const wd16char *, const wd16char * psource, strsize srclen)
   {

      return srclen;

   }


   template <  >
   inline strsize utf_to_utf_length(const wd16char *, const wd32char * psource, strsize srclen)
   {

      return wd32_to_wd16_len(psource, srclen);

   }

   template <  >
   inline strsize utf_to_utf_length(const wd32char *, const wd32char * psource, strsize srclen)
   {

      return srclen;

   }


   template <  >
   inline strsize utf_to_utf_length(const wd32char *, const wd16char * psource, strsize srclen)
   {

      return wd16_to_wd32_len(psource, srclen);

   }


   template <  >
   inline strsize utf_to_utf_length(const ansichar *, const wd16char * psource, strsize srclen)
   {

      return wd16_to_ansi_len(psource, srclen);

   }


   template <  >
   inline strsize utf_to_utf_length(const wd16char *, const ansichar * psource, strsize srclen)
   {

      return ansi_to_wd16_len(psource, srclen);

   }



   template <  >
   inline strsize utf_to_utf_length(const ansichar *, const wd32char * psource, strsize srclen)
   {

      return wd32_to_ansi_len(psource, srclen);

   }


   template <  >
   inline strsize utf_to_utf_length(const wd32char *, const ansichar * psource, strsize srclen)
   {

      return ansi_to_wd32_len(psource, srclen);

   }

   template < typename TYPE_TARGET, typename TYPE_SOURCE >
   inline strsize utf_to_utf_length(const TYPE_TARGET *, const TYPE_SOURCE * psource)
   {

      throw ::interface_only();

      return 0;

   }


   template <  >
   inline strsize utf_to_utf_length(const ansichar *, const ansichar * psource)
   {

      return strlen(psource);

   }


   template <  >
   inline strsize utf_to_utf_length(const wd16char *, const wd16char * psource)
   {

      return wd16_len(psource);

   }


   template <  >
   inline strsize utf_to_utf_length(const wd16char*, const wd32char* psource)
   {

      return wd32_to_wd16_len(psource);

   }


   template <  >
   inline strsize utf_to_utf_length(const wd32char *, const wd32char * psource)
   {

      return wd32_len(psource);

   }

   template <  >
   inline strsize utf_to_utf_length(const wd32char *, const wd16char * psource)
   {

      return wd16_to_wd32_len(psource);

   }

   template <  >
   inline strsize utf_to_utf_length(const ansichar *, const wd16char * psource)
   {

      return wd16_to_ansi_len(psource);

   }


   template <  >
   inline strsize utf_to_utf_length(const ansichar *, const wd32char * psource)
   {

      return wd32_to_ansi_len(psource);

   }


   template <  >
   inline strsize utf_to_utf_length(const wd16char *, const ansichar * psource)
   {

      return ansi_to_wd16_len(psource);

   }


   template <  >
   inline strsize utf_to_utf_length(const wd32char *, const ansichar * psource)
   {

      return ansi_to_wd32_len(psource);

   }


   template < typename TYPE_TARGET, typename TYPE_SOURCE >
   inline void utf_to_utf(TYPE_TARGET * ptarget, const TYPE_SOURCE * psource, strsize srclen)
   {

      throw ::interface_only();

   }


   inline void utf_to_utf(string & str, const wd16char * psource, strsize srclen)
   {

      char * psz = nullptr;

      auto dstlen = utf_to_utf_length(psz, psource, srclen);

      psz = str.get_string_buffer(dstlen);

      utf_to_utf(psz, psource, srclen);

      psz[dstlen]='\0';

   }


   template <  >
   inline void utf_to_utf(ansichar * ptarget, const ansichar * psource, strsize srclen)
   {

      overlap_safe_ansincpy(ptarget, psource, srclen);

   }


   template <  >
   inline void utf_to_utf(wd16char * ptarget, const wd16char * psource, strsize srclen)
   {

      overlap_safe_w16ncpy(ptarget, psource, srclen);

   }


   template <  >
   inline void utf_to_utf(wd16char* ptarget, const wd32char* psource, strsize srclen)
   {

      wd32_to_wd16(ptarget, psource, srclen);

   }


   template <  >
   inline void utf_to_utf(wd32char * ptarget, const wd32char * psource, strsize srclen)
   {

      overlap_safe_w32ncpy(ptarget, psource, srclen);

   }


   template <  >
   inline void utf_to_utf(wd32char * ptarget, const wd16char * psource, strsize srclen)
   {

      wd16_to_wd32(ptarget, psource, srclen);

   }


   template <  >
   inline void utf_to_utf(ansichar * ptarget, const wd16char * psource, strsize srclen)
   {

      wd16_to_ansi(ptarget, psource, srclen);

   }


   template <  >
   inline void utf_to_utf(ansichar * ptarget, const wd32char * psource, strsize srclen)
   {

      wd32_to_ansi(ptarget, psource, srclen);

   }


   template <  >
   inline void utf_to_utf(wd16char * ptarget, const ansichar * psource, strsize srclen)
   {

      ansi_to_wd16(ptarget, psource, srclen);

   }


   template <  >
   inline void utf_to_utf(wd32char * ptarget, const ansichar * psource, strsize srclen)
   {

      ansi_to_wd32(ptarget, psource, srclen);

   }


   template < typename TYPE_TARGET, typename TYPE_SOURCE >
   inline void utf_to_utf(TYPE_TARGET * ptarget, const TYPE_SOURCE * psource)
   {

      throw ::interface_only();

   }


   template <  >
   inline void utf_to_utf(ansichar * ptarget, const ansichar * psource)
   {

      strcpy(ptarget, psource);

   }


   template <  >
   inline void utf_to_utf(wd16char * ptarget, const wd16char * psource)
   {

      wd16_cpy(ptarget, psource);

   }


   template <  >
   inline void utf_to_utf(wd32char * ptarget, const wd16char * psource)
   {

      wd16_to_wd32(ptarget, psource);

   }


   template <  >
   inline void utf_to_utf(wd32char * ptarget, const wd32char * psource)
   {

      wd32_cpy(ptarget, psource);

   }


   template <  >
   inline void utf_to_utf(wd16char* ptarget, const wd32char* psource)
   {

      wd32_to_wd16(ptarget, psource);

   }


   template <  >
   inline void utf_to_utf(ansichar * ptarget, const wd16char * psource)
   {

      wd16_to_ansi(ptarget, psource);

   }


   template <  >
   inline void utf_to_utf(ansichar * ptarget, const wd32char * psource)
   {

      wd32_to_ansi(ptarget, psource);

   }


   template <  >
   inline void utf_to_utf(wd16char * ptarget, const ansichar * psource)
   {

      ansi_to_wd16(ptarget, psource);

   }


   template <  >
   inline void utf_to_utf(wd32char * ptarget, const ansichar * psource)
   {

      ansi_to_wd32(ptarget, psource);

   }


   inline i32 uni_index(const ansichar *& pszChar, strsize * psrclen) { return ::__uni_index(pszChar, psrclen); }
   inline i32 uni_index(const wd16char *& pszChar, strsize * psrclen) { return ::__uni_index(pszChar, psrclen); }
   inline i32 uni_index(const wd32char *& pszChar, strsize * psrclen) { return ::__uni_index(pszChar, psrclen); }


   inline const ansichar * windows_bbqbunc(const ansistring &) { return "\\\\?\\UNC"; }
   inline const ansichar * windows_bbqb(const ansistring &) { return "\\\\?\\"; }
   inline const ansichar * windows_bb(const ansistring &) { return "\\\\"; }

   inline const widechar * windows_bbqbunc(const widestring &) { return L"\\\\?\\UNC"; }
   inline const widechar * windows_bbqb(const widestring &) { return L"\\\\?\\"; }
   inline const widechar * windows_bb(const widestring &) { return L"\\\\"; }

   inline const ansichar * unichar_inc(const ansichar * psz) { return utf8_inc(psz); }
   inline const wd16char * unichar_inc(const wd16char * psz) { return utf16_inc(psz); }
   inline const wd32char * unichar_inc(const wd32char * psz) { return utf32_inc(psz); }


   inline strsize unichar_count(const ansichar * pstr) { return ansi_to_wd32_len(pstr); }
   inline strsize unichar_count(const wd16char * pstr) { return wd16_to_wd32_len(pstr); }
   inline strsize unichar_count(const wd32char * pstr) { return __wd32len(pstr); }


   inline strsize copy_string_len(wd16char * pszDst, const ansichar * pszSrc, strsize srclen) { return utf_to_utf_length(pszDst, pszSrc, srclen); }
   inline strsize copy_string_len(wd32char * pszDst, const ansichar * pszSrc, strsize srclen) { return utf_to_utf_length(pszDst, pszSrc, srclen); }
   inline strsize copy_string_len(ansichar * pszDst, const wd16char * pszSrc, strsize srclen) { return utf_to_utf_length(pszDst, pszSrc, srclen); }
   inline strsize copy_string_len(ansichar * pszDst, const wd32char * pszSrc, strsize srclen) { return utf_to_utf_length(pszDst, pszSrc, srclen); }


   inline void copy_string(wd16char * pszDst, const ansichar * pszSrc, strsize srclen) { utf_to_utf(pszDst, pszSrc, srclen); }
   inline void copy_string(wd32char * pszDst, const ansichar * pszSrc, strsize srclen) { utf_to_utf(pszDst, pszSrc, srclen); }
   inline void copy_string(ansichar * pszDst, const wd16char * pszSrc, strsize srclen) { utf_to_utf(pszDst, pszSrc, srclen); }
   inline void copy_string(ansichar * pszDst, const wd32char * pszSrc, strsize srclen) { utf_to_utf(pszDst, pszSrc, srclen); }


   template < typename TYPE_CHAR >
   inline string_base < TYPE_CHAR > & assign(string_base < TYPE_CHAR > & strDst, const string_base < TYPE_CHAR > & strSrc)
   {

      strDst.assign_natural_pointer(strSrc);

      return strDst;

   }


   template < typename TYPE_CHAR >
   inline string_base < TYPE_CHAR > & assign(string_base < TYPE_CHAR > & strDst, const natural_string_base < TYPE_CHAR > & strSrc)
   {

      strDst.assign_natural_pointer(strSrc);

      return strDst;

   }


   template < typename TYPE_CHAR1 >
   inline string_base < TYPE_CHAR1 >& assign(string_base < TYPE_CHAR1 >& strDst, const TYPE_CHAR1* pszSrc, strsize srclen)
   {

      if (srclen < 0)
      {

         srclen = ::str::string_get_length(pszSrc) + srclen + 1;

      }

      auto dstlen = utf_to_utf_length(strDst.m_pdata, pszSrc, srclen);

      if (dstlen <= 0)
      {

         strDst.Empty();

      }
      else
      {
         
         if (strDst.metadata()->contains_data(pszSrc))
         {

            if (strDst.metadata()->natural_is_shared())
            {

               strDst.fork_string(dstlen);

            }

         }
         else
         {

            strDst.get_string_buffer(dstlen);

         }

         ::str::utf_to_utf(strDst.m_pdata, pszSrc, dstlen);

         strDst.release_string_buffer(dstlen);

      }

      return strDst;

   }


   template < typename TYPE_CHAR1, typename TYPE_CHAR2 >
   inline string_base < TYPE_CHAR1 > & assign(string_base < TYPE_CHAR1 > & strDst, const TYPE_CHAR2 * pszSrc, strsize srclen)
   {

      if (srclen < 0)
      {

         srclen = ::str::string_get_length(pszSrc) + srclen + 1;

      }

      auto dstlen = utf_to_utf_length(strDst.m_pdata, pszSrc, srclen);

      if (dstlen <= 0)
      {

         strDst.Empty();

      }
      else
      {

         auto pszDst = strDst.get_string_buffer(dstlen);

         ::str::utf_to_utf(pszDst, pszSrc, srclen);

         strDst.release_string_buffer(dstlen);

      }

      return strDst;

   }


   template < typename TYPE_CHAR1, typename TYPE_CHAR2 >
   inline string_base < TYPE_CHAR1 > & assign(string_base < TYPE_CHAR1 > & strDst, const TYPE_CHAR2 * pszSrc)
   {

      auto dstlen = utf_to_utf_length(strDst.m_pdata, pszSrc);

      if (dstlen <= 0)
      {

         strDst.Empty();

      }
      else
      {

         auto pszDst = strDst.get_string_buffer(dstlen);

         ::str::utf_to_utf(pszDst, pszSrc);

         strDst.release_string_buffer(dstlen);

      }

      return strDst;

   }

   template < typename TYPE_CHAR >
   inline string_base < TYPE_CHAR > & assign(string_base < TYPE_CHAR > & ansistrSrc, const TYPE_CHAR * pszSrc)
   {

      return assign(ansistrSrc, pszSrc, ::str::string_safe_length(pszSrc));

   }


   inline wd16string & assign(wd16string & wstrDst, const ansistring & strSrc)
   {

      auto dstlen = copy_string_len(wstrDst.m_pdata, strSrc.m_pdata, strSrc.get_length());

      if (dstlen <= 0)
      {

         wstrDst.Empty();

      }
      else
      {

         auto pch = wstrDst.get_string_buffer(dstlen);

         copy_string(pch, strSrc.m_pdata, strSrc.get_length());

         wstrDst.release_string_buffer();

      }

      return wstrDst;

   }


   inline wd32string& assign(wd32string& wstrDst, const ansistring& strSrc)
   {

      auto dstlen = copy_string_len(wstrDst.m_pdata, strSrc.m_pdata, strSrc.get_length());

      if (dstlen <= 0)
      {

         wstrDst.Empty();

      }
      else
      {

         auto pch = wstrDst.get_string_buffer(dstlen);

         copy_string(pch, strSrc.m_pdata, strSrc.get_length());

         wstrDst.release_string_buffer();

      }

      return wstrDst;

   }


   inline wd16string & assign(wd16string & wstrDst, const natural_ansistring & strSrc)
   {

      auto srclen = ::str::string_safe_length(strSrc.m_pdata);

      auto len = copy_string_len(wstrDst.m_pdata, strSrc.m_pdata, srclen);

      auto pch = wstrDst.get_string_buffer(len);

      copy_string(pch, strSrc.m_pdata, srclen);

      return wstrDst;

   }


   inline wd32string& assign(wd32string& wstrDst, const natural_ansistring& strSrc)
   {

      auto srclen = ::str::string_safe_length(strSrc.m_pdata);

      auto len = copy_string_len(wstrDst.m_pdata, strSrc.m_pdata, srclen);

      auto pch = wstrDst.get_string_buffer(len);

      copy_string(pch, strSrc.m_pdata, srclen);

      return wstrDst;

   }



   inline ansistring & assign(ansistring & ansistrSrc, const wd16string & widestrSrc)
   {

      auto len = copy_string_len(ansistrSrc.m_pdata, widestrSrc.m_pdata, widestrSrc.get_length());

      auto pch = ansistrSrc.get_string_buffer(len);

      copy_string(pch, widestrSrc.m_pdata, widestrSrc.get_length());

      return ansistrSrc;

   }

   inline ansistring& assign(ansistring& ansistrSrc, const wd32string& widestrSrc)
   {

      auto len = copy_string_len(ansistrSrc.m_pdata, widestrSrc.m_pdata, widestrSrc.get_length());

      auto pch = ansistrSrc.get_string_buffer(len);

      copy_string(pch, widestrSrc.m_pdata, widestrSrc.get_length());

      return ansistrSrc;

   }

   inline ansistring & assign(ansistring & ansistrSrc, const natural_wd16string & widestrSrc)
   {

      auto srclen = ::str::string_safe_length(widestrSrc.m_pdata);

      auto len = copy_string_len(ansistrSrc.m_pdata, widestrSrc.m_pdata, srclen);

      auto pch = ansistrSrc.get_string_buffer(len);

      copy_string(pch, widestrSrc.m_pdata, srclen);

      return ansistrSrc;

   }

   inline ansistring& assign(ansistring& ansistrSrc, const natural_wd32string& widestrSrc)
   {

      auto srclen = ::str::string_safe_length(widestrSrc.m_pdata);

      auto len = copy_string_len(ansistrSrc.m_pdata, widestrSrc.m_pdata, srclen);

      auto pch = ansistrSrc.get_string_buffer(len);

      copy_string(pch, widestrSrc.m_pdata, srclen);

      return ansistrSrc;

   }


   inline ansistring & assign(ansistring & ansistrDst, const atom & atom)
   {

      ansistrDst.assign(atom.to_string());

      return ansistrDst;

   }


   inline wd16string & assign(wd16string & widestrDst, const atom & atom)
   {

      widestrDst.assign(atom.to_string());

      return widestrDst;

   }

   inline wd32string& assign(wd32string& widestrDst, const atom& atom)
   {

      widestrDst.assign(atom.to_string());

      return widestrDst;

   }


   inline ansistring & assign(ansistring & ansistrDst, ansichar ansich)
   {

      ansistrDst.assign(&ansich, 1);

      return ansistrDst;

   }


   inline wd16string & assign(wd16string & widestrDst, ansichar ansich)
   {

      widestrDst.assign(&ansich, 1);

      return widestrDst;

   }

   inline wd32string& assign(wd32string& widestrDst, ansichar ansich)
   {

      widestrDst.assign(&ansich, 1);

      return widestrDst;

   }

   inline ansistring & assign(ansistring & ansistrDst, wd16char widech)
   {

      ansistrDst.assign(&widech, 1);

      return ansistrDst;

   }


   inline wd16string & assign(wd16string & widestrDst, wd16char widech)
   {

      widestrDst.assign(&widech, 1);

      return widestrDst;

   }

   inline wd32string& assign(wd32string& widestrDst, wd16char widech)
   {

      widestrDst.assign(&widech, 1);

      return widestrDst;

   }

   inline ansistring & assign(ansistring & ansistrDst, wd32char widech)
   {

      ansistrDst.assign(&widech, 1);

      return ansistrDst;

   }


   inline wd16string & assign(wd16string & widestrDst, wd32char widech)
   {

      widestrDst.assign(&widech, 1);

      return widestrDst;

   }

   inline wd32string& assign(wd32string& widestrDst, wd32char widech)
   {

      widestrDst.assign(&widech, 1);

      return widestrDst;

   }


   inline ansistring & assign(ansistring & ansistrDst, const ::payload & payload)
   {

      ansistrDst.assign(payload);

      return ansistrDst;

   }


   inline wd16string & assign(wd16string & widestrDst, const property & property)
   {

      widestrDst.assign(property.string());

      return widestrDst;

   }


   inline wd32string& assign(wd32string& widestrDst, const property& property)
   {

      widestrDst.assign(property.string());

      return widestrDst;

   }


   inline ansistring & assign(ansistring & ansistrDst, const property & property)
   {

      ansistrDst.assign(property.string());

      return ansistrDst;

   }


   inline wd16string & assign(wd16string & widestrDst, const ::payload & payload)
   {

      widestrDst.assign(payload.string());

      return widestrDst;

   }


   inline wd32string& assign(wd32string& widestrDst, const ::payload & payload)
   {

      widestrDst.assign(payload.string());

      return widestrDst;

   }

   inline ansistring & assign(ansistring & strDst, const wd16char * psrcsz)
   {

      auto srclen = ::str::string_safe_length(psrcsz);

      auto dstlen = utf_to_utf_length(strDst.m_pdata, psrcsz, srclen);

      auto pdstsz = strDst.get_string_buffer(dstlen);

      utf_to_utf(pdstsz, psrcsz, srclen);

      strDst.metadata()->set_length(dstlen);

      return strDst;

   }


   inline ansistring& assign(ansistring& strDst, const wd32char* psrcsz)
   {

      auto srclen = ::str::string_safe_length(psrcsz);

      auto dstlen = utf_to_utf_length(strDst.m_pdata, psrcsz, srclen);

      auto pdstsz = strDst.get_string_buffer(dstlen);

      utf_to_utf(pdstsz, psrcsz, srclen);

      strDst.metadata()->set_length(dstlen);

      return strDst;

   }

   inline wd16string & assign(wd16string & strDst, const ansichar * psrcsz)
   {

      auto srclen = ::str::string_safe_length(psrcsz);

      auto dstlen = utf_to_utf_length(strDst.m_pdata, psrcsz, srclen);

      auto pwidesz = strDst.get_string_buffer(dstlen);

      utf_to_utf(pwidesz, psrcsz, srclen);

      return strDst;

   }


   inline wd16string& assign(wd16string& strDst, const wd16char * psrcsz)
   {

      auto srclen = ::str::string_safe_length(psrcsz);

      auto dstlen = utf_to_utf_length(strDst.m_pdata, psrcsz, srclen);

      auto pwidesz = strDst.get_string_buffer(dstlen);

      utf_to_utf(pwidesz, psrcsz, srclen);

      return strDst;

   }


   inline wd16string& assign(wd16string& strDst, const wd32char* psrcsz)
   {

      auto srclen = ::str::string_safe_length(psrcsz);

      auto dstlen = utf_to_utf_length(strDst.m_pdata, psrcsz, srclen);

      auto pwidesz = strDst.get_string_buffer(dstlen);

      utf_to_utf(pwidesz, psrcsz, srclen);

      return strDst;

   }


   inline wd32string & assign(wd32string & strDst, const ansichar * psrcsz)
   {

      auto srclen = ::str::string_safe_length(psrcsz);

      auto dstlen = utf_to_utf_length(strDst.m_pdata, psrcsz, srclen);

      auto pwidesz = strDst.get_string_buffer(dstlen);

      utf_to_utf(pwidesz, psrcsz, srclen);

      return strDst;

   }


   inline wd32string& assign(wd32string& strDst, const wd16char* psrcsz)
   {

      auto srclen = ::str::string_safe_length(psrcsz);

      auto dstlen = utf_to_utf_length(strDst.m_pdata, psrcsz, srclen);

      auto pwidesz = strDst.get_string_buffer(dstlen);

      utf_to_utf(pwidesz, psrcsz, srclen);

      return strDst;

   }


   inline wd32string& assign(wd32string& strDst, const wd32char* psrcsz)
   {

      auto srclen = ::str::string_safe_length(psrcsz);

      auto dstlen = utf_to_utf_length(strDst.m_pdata, psrcsz, srclen);

      auto pwidesz = strDst.get_string_buffer(dstlen);

      utf_to_utf(pwidesz, psrcsz, srclen);

      return strDst;

   }


   inline ansistring & assign(ansistring & ansistrDst, const type & type)
   {

      ansistrDst.assign(type.m_strName);

      return ansistrDst;

   }


   inline wd16string & assign(wd16string & widestrDst, const type & type)
   {

      widestrDst.assign(type.m_strName);

      return widestrDst;

   }


   inline wd32string& assign(wd32string& widestrDst, const type& type)
   {

      widestrDst.assign(type.m_strName);

      return widestrDst;

   }


} // namespace str



