#pragma once


template < typename CHAR_TYPE >
inline string_base < CHAR_TYPE > str::repeat(const CHAR_TYPE * psz, strsize c)
{

   auto itemLen = string_safe_length(psz);

   auto itemByteCount = itemLen * sizeof(CHAR_TYPE);

   auto len = itemLen * c;

   string str;

   if (len > 0)
   {

      auto p = str.get_string_buffer(len);

      while (c > 0)
      {

         memcpy(p, psz, itemByteCount);

         p += itemLen;

         c--;

      }

      str.release_string_buffer(len);

   }

   return str;

}


inline i32 compare_ignore_case(const char * left, const char * right, size_t len)
{

   if (len)
   {

#if defined(WIN32) || defined(WIN64)

      return _strnicmp(left, right, len);

#elif defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

      return ansi_count_compare_ci(left, right, len);

#else

      return strncasecmp(left, right, len);

#endif

   }
   else
   {

#if defined(WIN32) || defined(WIN64)

      return _stricmp(left, right);

#elif defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

      return ansi_compare_ci(left, right);

#else

      return strcasecmp(left, right);

#endif

   }

}


inline bool equal_ignore_case(const char * left, const char * right, size_t len)
{

   return compare_ignore_case(left, right, len) == 0;

}


inline CLASS_DECL_ACME bool trimmed_is_empty(const char * psz)
{

   while (true)
   {

      if (*psz == '\0')
      {

         break;

      }

      if (!isspace(*psz))
      {

         return false;

      }

      psz++;

   }

   return true;

}



inline i32 compare_ignore_case(const string & left, const string & right, size_t len)
{

   if (len)
   {

#if defined(WIN32) || defined(WIN64)

      return _strnicmp(left.c_str(), right.c_str(), len);

#elif defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

      return ansi_count_compare_ci(left.c_str(), right.c_str(), len);

#else

      return strncasecmp(left.c_str(), right.c_str(), len);

#endif

   }
   else
   {

#if defined(WIN32) || defined(WIN64)

      return _stricmp(left.c_str(), right.c_str());

#elif defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

      return ansi_compare_ci(left.c_str(), right.c_str());

#else

      return strcasecmp(left.c_str(), right.c_str());

#endif

   }

}


inline bool equal_ignore_case(const string & left, const string & right, size_t len)
{

   return compare_ignore_case(left, right, len) == 0;

}


inline i32 compare_ignore_case(const char * left, const string & right, size_t len)
{

   if (len)
   {

#if defined(WIN32) || defined(WIN64)

      return _strnicmp(left, right.c_str(), len);

#elif defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

      return ansi_count_compare_ci(left, right.c_str(), len);

#else

      return strncasecmp(left, right.c_str(), len);

#endif

   }
   else
   {

#if defined(WIN32) || defined(WIN64)

      return _stricmp(left, right.c_str());

#elif defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

      return ansi_compare_ci(left, right.c_str());

#else

      return strcasecmp(left, right.c_str());

#endif

   }

}


   inline bool equal_ignore_case(const char * left, const string & right, size_t len)
   {

      return compare_ignore_case(left, right, len) == 0;

   }


   inline i32 compare_ignore_case(const string & left, const char * right, size_t len)
   {

      if (len)
      {

#if defined(WIN32) || defined(WIN64)

         return _strnicmp(left.c_str(), right, len);

#elif defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

         return ansi_count_compare_ci(left.c_str(), right, len);

#else

         return strncasecmp(left.c_str(), right, len);

#endif

      }
      else
      {

#if defined(WIN32) || defined(WIN64)

         return _stricmp(left.c_str(), right);

#elif defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

         return ansi_compare_ci(left.c_str(), right);

#else

         return strcasecmp(left.c_str(), right);

#endif

      }

   }


   inline bool equal_ignore_case(const string & left, const char * right, size_t len)
   {

      return compare_ignore_case(left, right, len) == 0;

   }





inline void from_string(i8 & i, const ansichar * psz)
{

   i = (i8) atoi(psz);

}


inline void from_string(i16 & i, const ansichar * psz)
{

   i = (i16) atoi(psz);

}


inline void from_string(i32 & i, const ansichar * psz)
{

   i = atoi(psz);

}


inline void from_string(i64 & i, const ansichar * psz)
{

   i = atoll(psz);

}


inline void from_string(i32 & i, i32 iBase, const ansichar * psz)
{

   i = ansi_to_i32(psz, nullptr, iBase);

}


inline void from_string(i64 & i, i32 iBase, const ansichar * psz)
{

   i = ansi_to_i64(psz, nullptr, iBase);

}


inline void from_string(u8 & u, const ansichar * psz)
{

   u = (u8) ansi_to_u32(psz, nullptr, 10);

}


inline void from_string(u16 & u, const ansichar * psz)
{

   u = (u16) ansi_to_u32(psz, nullptr, 10);

}


inline void from_string(u32 & u, const ansichar * psz)
{

   u = ansi_to_u32(psz, nullptr, 10);

}


inline void from_string(u64 & u, const ansichar * psz)
{

   u = ansi_to_u64(psz, nullptr, 10);

}


inline void from_string(u32 & u, i32 iBase, const ansichar * psz)
{

   u = ansi_to_u32(psz, nullptr, iBase);

}


inline void from_string(u64 & u, i32 iBase, const ansichar * psz)
{

   u = ansi_to_u64(psz, nullptr, iBase);

}


#if defined(__APPLE__) || defined(ANDROID) || defined(RASPBIAN)
inline void from_string(long & l, const ansichar * psz)
{

l = ansi_to_i64(psz, nullptr, 10);

}
#elif defined(WINDOWS)
inline void from_string(long & l, const ansichar * psz)
{

   l = ansi_to_i32(psz, nullptr, 10);

}
#endif


#if defined(__APPLE__) || defined(ANDROID) || defined(RASPBIAN)

inline void from_string(long  & l, i32 iBase, const ansichar * psz)
{

l = ansi_to_i64(psz, nullptr, iBase);

}
#elif defined(WINDOWS)
inline void from_string(long & l, i32 iBase, const ansichar * psz)
{

   l = ansi_to_i32(psz, nullptr, 10);

}
#endif


inline void from_string(i32 & i, const wd16char * psz)
{

   i = wd16_to_i32(psz);

}


inline void from_string(i64 & i, const wd16char * psz)
{

   i = wd16_to_i64(psz);

}


inline void from_string(i32 & i, const wd32char * psz)
{

   i = wd32_to_i32(psz);

}


inline void from_string(i64 & i, const wd32char * psz)
{

   i = wd32_to_i64(psz);

}


inline void from_string(i32 & i, i32 iBase, const widechar * psz)
{

   i = wide_to_i32(psz, nullptr, iBase);

}


inline void from_string(i64 & i, i32 iBase, const widechar * psz)
{

   i = wide_to_i64(psz, nullptr, iBase);

}


inline void from_string(u32 & u, const widechar * psz)
{

   u = wide_to_u32(psz, nullptr, 10);

}


inline void from_string(u64 & u, const widechar * psz)
{

   u = wide_to_u64(psz, nullptr, 10);

}


inline void from_string(u32 & u, i32 iBase, const widechar * psz)
{

   u = wide_to_u32(psz, nullptr, iBase);

}


inline void from_string(u64 & u, i32 iBase, const widechar * psz)
{

   u = wide_to_u64(psz, nullptr, iBase);

}


inline void from_string(float & f, const ansichar * psz)
{

   f = strtof(psz, nullptr);

}


inline void from_string(double & d, const ansichar * psz)
{

   d = strtod(psz, nullptr);

}


inline void from_string(ansichar * sz, const ansichar * psz)
{

   strcpy(sz, psz);

}


inline void from_string(ansichar & ch, const ansichar* psz)
{

   ch = *psz;

}


inline void from_string(widechar & wch, const ansichar* psz)
{

   str().utf_to_utf(&wch, psz, utf8_inc(psz) - psz);

}


inline void from_string(wd16char * sz, const ansichar * psz)
{

   str().utf_to_utf(sz, psz);

}


inline void from_string(wd32char * sz, const ansichar * psz)
{

   str().utf_to_utf(sz, psz);

}


template < size_t n >
inline void from_string(ansichar sz[n], const ansichar * psz)
{

   if (strlen(psz) >= n)
   {

      throw ::exception(error_would_reach_buffer_limit);

   }

   strcpy(sz, psz);

}


template < size_t n >
inline void from_string(wd16char sz[n], const ansichar * psz)
{

   if (str().utf_to_utf_length(sz, psz) >= n)
   {

      throw ::exception(error_would_reach_buffer_limit);

   }

   str().utf_to_utf(sz, psz);

}


template < size_t n >
inline void from_string(wd32char sz[n], const ansichar * psz)
{

   if (str().utf_to_utf_length(sz, psz) >= n)
   {

      throw ::exception(error_would_reach_buffer_limit);

   }

   str().utf_to_utf(sz, psz);

}


inline void from_string(::atom & atom, const ansichar * psz)
{

   atom = psz;

}


inline void from_string(::element & element, const ansichar * psz)
{

   payload_stream stream;

   stream.m_ppayload->parse_network_payload(psz);

   element.exchange(stream);

}


template < typename TYPE >
inline void to_string(string & str, const TYPE & t)
{

   str = t.get_string();

}



//inline void to_string(string & str, const element & t)
//{

//   auto len = t.sz_len();

//   auto psz = str.get_string_buffer(len);

//   t.to_sz(psz, len);

//   str.release_string_buffer(len);

//}


//#ifdef _UWP
//
//
//   inline void to_string(string& str, Platform::String ^ strSource)
//   {
//
//      str = strSource->Begin();
//
//   }
//
//#endif

inline void to_string(string & str, const element & o)
{

   auto len = o.sz_len();

   auto psz = str.get_string_buffer(len);

   o.to_sz(psz, len);

   str.release_string_buffer();

}


//inline void to_string(string & str, const element & o)
//{

//   o.to_string(str);

//}


inline void to_string(string & str, const ::atom & atom)
{

   atom.to_string(str);

}


inline void to_string(string & str, const ::wd16string & wd16str)
{

   str = wd16str;

}


inline void to_string(string & str, const ::wd32string & wd32str)
{

   str = wd32str;

}


CLASS_DECL_ACME void to_string(string & str, const ::string_stream & strstream);


CLASS_DECL_ACME void to_string(string & str, const ::text_stream & strstream);


inline string _001Concatenate(const ::string & str1, const ::string & strMid, const ::string & str2)
{

   if (str1.is_empty())
   {

      if (str2.is_empty())
      {

         return "";

      }
      else
      {

         return str2;

      }

   }
   else if (str2.is_empty())
   {

      return str1;

   }
   else
   {

      return str1 + strMid + str2;

   }

}





template < typename T >
inline string string_from_int(const T& t)
{

   string str;

   to_string(str, (i64)t);

   return str;

}


template < typename T >
inline string string_from_u(const T& t)
{

   string str;

   to_string(str, (u64)t);

   return str;

}


//
//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR >::string_base(const string_base & strSrc)
//{
//
//   POINTER::operator =(strSrc);
//
//}
//
//
//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR >::string_base(const ansichar * pszSrc)
//   : string_base(pszSrc, string_safe_length(pszSrc))
//{
//
//}


//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR >::string_base(const ansichar* pch,strsize strsize)
//{
//
//   if (::is_null(pch))
//   {
//
//      if(strsize != 0)
//      {
//
//         throw ::exception(error_bad_argument);
//
//      }
//
//      natural_release();
//
//   }
//   else
//   {
//
//      auto pNew = create_meta_data(char_length_to_byte_length(strsize + 1));
//
//      if (pNew == nullptr)
//      {
//
//         throw no_memory();
//
//      }
//
//      POINTER::operator=(pNew);
//
//      memcpy(pNew->m_pdata, pch, pNew->memsize());
//
//      set_length(strsize);
//
//   }
//
//}

// besides returning a element (and const does not really impedes changing), do not machine a string_base (or string) directly,
// there may be multiple instances of a string (all referencing the same pointer).
//template < typename TYPE_CHAR >
//inline const ansichar & string_base < TYPE_CHAR >::operator [](index iChar ) const
//{
//
//   return m_psz[iChar];
//
//}
//
//template < typename TYPE_CHAR >
//inline ansichar string_base < TYPE_CHAR >::get_at(strsize iChar ) const
//{
//
//   return m_psz[iChar];
//
//}

//template < typename TYPE_CHAR >
//inline void string_base < TYPE_CHAR >::set_at(strsize iChar,ansichar ch )
//{
//
//   if((iChar < 0) || (iChar >= get_length()))
//   {
//
//      throw ::exception(error_bad_argument);
//
//   }
//
//   strsize nLength = get_length();
//
//   ansichar * pszBuffer = get_string_buffer();
//
//   pszBuffer[iChar] = ch;
//
//   release_string_buffer( nLength );
//
//}
//

//template < typename TYPE_CHAR >
//inline void string_base < TYPE_CHAR >::set_string(const ansichar * pszSrc,strsize nLength )
//{
//
//   if( nLength == 0 )
//   {
//
//      Empty();
//
//   }
//   else
//   {
//
//      // It is possible that pszSrc points to a locationd inside of our
//      // buffer.  GetBuffer() might machine m_psz if (1) the buffer
//      // is shared or (2) the buffer is too small to hold the new
//      // string.  We detect this aliasing, and modify pszSrc to point_i32
//      // into the newly allocated buffer instead.
//      if(pszSrc == nullptr)
//      {
//
//         throw ::exception(error_bad_argument);
//
//      }
//
//      uptr nOldLength = (uptr) get_length();
//
//      uptr nOffset = (uptr) (pszSrc - m_psz);
//
//      // If 0 <= nOffset <= nOldLength, then pszSrc points into our
//      // buffer
//      auto pszBuffer = get_string_buffer( nLength );
//
//      if( nOffset <= nOldLength )
//      {
//
//#if _SECURE_TEMPLATE
//
//         CopyCharsOverlapped( pszBuffer, nLength,
//                              pszBuffer+nOffset, nLength );
//
//#else
//
//         CopyCharsOverlapped( pszBuffer, pszBuffer+nOffset, nLength );
//
//#endif
//
//      }
//      else
//      {
//
//#if _SECURE_TEMPLATE
//
//         CopyChars( pszBuffer, nLength, pszSrc, nLength );
//
//#else
//         CopyChars( pszBuffer, pszSrc, nLength );
//
//#endif
//
//      }
//
//      release_string_buffer( nLength );
//
//   }
//
//}

//template < typename TYPE_CHAR >
//inline void string_file < TYPE_CHAR >::set_length(strsize nLength )
//{
//
//   ASSERT(nLength >= 0);
//
//   ASSERT(nLength <= m_nBufferLength);
//
//   if(nLength < 0)
//   {
//
//      throw ::exception(error_bad_argument);
//
//   }
//
//   m_nLength = nLength;
//
//}
//
//
//template < typename TYPE_CHAR >
//inline void string_base < TYPE_CHAR >::release_string_buffer(strsize nNewLength )
//{
//
//   ASSERT(nNewLength >= 0);
//
//   this->metadata()->set_length(nNewLength);
//
//}


template < typename TYPE_CHAR >
inline void string_base < TYPE_CHAR >::truncate(strsize nNewLength)
{

   if (nNewLength >= this->length())
   {

      return;

   }

   if(nNewLength <= 0)
   {

      Empty();

   }

   get_string_buffer(nNewLength);

   release_string_buffer(nNewLength);

}


template < typename TYPE_CHAR >
inline void string_base < TYPE_CHAR >::set_at(strsize iChar, CHAR_TYPE ch)
{

   auto p = this->metadata();

   if (p->natural_is_shared() || iChar >= p->length())
   {

      fork_string(maximum(p->length(), iChar + 1));

   }

   this->m_pdata[iChar] = ch;

}


#ifdef WINDOWS
#if OSBIT == 64
typedef ::u64* int_ptr_atomic;
#elif OSBIT == 32
typedef unsigned int* int_ptr_atomic;
#else
#error "What is OSBIT?"
#endif
#else
#ifdef ANDROID
typedef int* int_ptr_atomic;
#elif defined(RASPBIAN)
typedef ::u64* int_ptr_atomic;
#elif defined(LINUX)
typedef ::u64* int_ptr_atomic;
#elif defined(__APPLE__)
typedef ::u64* int_ptr_atomic;
#else
typedef iptr int_ptr_atomic;
#endif
#endif





template < >
inline void std_string_assign(string& t, const ansichar* psz)
{
   t.assign(psz);
}

template < >
inline void std_string_assign(string& t, const widechar* psz)
{
   t = unicode_to_utf8(psz);
}

template < >
inline void std_string_bassign(string& t, const u8* psz, strsize nsize)
{
   t = (const ansichar*)string((const ansichar*)psz, minimum(nsize, strlen_s_dup((const ansichar*)psz, nsize)));
}

template < >
inline void std_string_assign(string& t, const string* pstr)
{
   t = *pstr;
}

template < >
inline void std_string_assign(string& t, const wstring* pwstr)
{
   t = unicode_to_utf8(*pwstr);
}

//template < >
//inline void std_string_assign(string & t,const bstring * pbstr)
//{
//   t = string((const ansichar *)pbstr->get_data(),minimum(pbstr->get_length(),strlen_s_dup((const ansichar *)pbstr->get_data(),pbstr->get_length())));
//}

//template < >
//inline void std_string_assign(string & t,const ansichar * psz)
//{
//   t.assign(psz);
//}


//template < >
//inline void std_string_assign(string & t,const widechar * psz)
//{
//
//   t.assign(psz);
//
//}


template < >
inline void std_string_bassign(wstring& t, const u8* psz, strsize nsize)
{
   t = utf8_to_unicode(string((const ansichar*)psz, minimum(nsize, strlen_s_dup((const ansichar*)psz, nsize))));
}

template < >
inline void std_string_assign(wstring& t, const string* pstr)
{
   t = utf8_to_unicode(*pstr);
}

//template < >
//inline void std_string_assign(wstring & t,const string * pstr)
//{
//   t = utf8_to_unicode(*pstr);
//}

template < >
inline void std_string_assign(wstring& t, const wstring* pwstr)
{
   t = *pwstr;
}

//template < >
//inline void std_string_assign(wstring & t,const bstring * pbstr)
//{
//   t = utf8_to_unicode(string((const ansichar *)pbstr->get_data(),minimum(pbstr->get_length(),strlen_s_dup((const ansichar *)pbstr->get_data(),pbstr->get_length()))));
//}


//template < >
//inline void std_string_assign(bstring & t,const ansichar * psz)
//{
//   t.assign(psz);
//}
//
//template < >
//inline void std_string_assign(bstring & t,const widechar * psz)
//{
//   t.assign(unicode_to_utf8(psz));
//}
//
//template < >
//inline void std_string_bassign(bstring & t,const u8 * psz,strsize nsize)
//{
//   t.assign(string((const ansichar *)psz,minimum(nsize,strlen_s_dup((const ansichar *)psz,nsize))));
//}
//
//template < >
//inline void std_string_assign(bstring & t,const string * pstr)
//{
//   t = (const ansichar *) *pstr;
//}
//
//template < >
//inline void std_string_assign(bstring & t,const wstring * pwstr)
//{
//   t = (const ansichar *) unicode_to_utf8(*pwstr);
//}
//
//template < >
//inline void std_string_assign(bstring & t,const bstring * pbstr)
//{
//   t = *pbstr;
//}
//





















// namespace str
// {


   //inline void from(string & str, const wstring & wstr)
   //{

   //   unicode_to_utf8(str, wstr, wstr.get_length());

   //}


//inline string::string(const istring & istr) :
//   string_base(istr.m_str)
//{
//
//}


inline void to_string(string& str, const i16& i)
{

   str = i64toa_dup(i);

}


inline void to_string(string& str, const u16& u)
{

   str = ui64toa_dup(u);

}


inline void to_string(string& str, const i32& i)
{

   str = i64toa_dup(i);

}


inline void to_string(string& str, const u32& u)
{

   str = ui64toa_dup(u);

}


inline void to_string(string& str, const i64& i)
{

   str = i64toa_dup(i);

}


inline void to_string(string& str, const u64& u)
{

   str = ui64toa_dup(u, 10);

}


/// 
//#if !defined(WINDOWS) && !defined(LINUX) && !defined(FREEBSD)
//
//
//inline void to_string(string& str, const unsigned long & ul)
//{
//
//   str = ui64toa_dup(ul, 10);
//
//}
//
//#endif


CLASS_DECL_ACME void to_string(string& str, const float & f);


CLASS_DECL_ACME void to_string(string& str, const double & d);

//
//#if defined(ANDROID) || defined(RASPBIAN)
//
//inline void to_string(string& str, const long int& i)
//{
//
//   str = i64toa_dup(i);
//
//}
//
//#endif



//#ifdef WINDOWS
//
//
//inline void to_string(string & str, const long & l)
//{
//
//   str = i64toa_dup(l);
//
//}
//
//
//
////inline void to_string(string & str, const unsigned long &ul)
////{
////
////   str = ui64toa_dup(ul);
////
////}
//
//
//#elif defined(__APPLE__)
//
//
//inline void to_string(string& str, const long& l)
//{
//
//   str = i64toa_dup(l);
//
//}
//
//
//#endif


//} // namespace str


//#if defined(_UWP) && defined(__cplusplus_winrt)
//
//
//inline string & string::operator = (String ^ & str)
//{
//
//
//   return operator = (begin(str));
//
//
//}
//
//
//#endif

//
//
//inline bool string_format::defer_get_additional_argument(const ansichar * & s)
//{
//
//   throw ::exception(::exception("missing argument value"));
//
//}
//
//
//template < typename T, typename... Args>
//inline void string_format::defer_get_additional_argument(const ansichar * & s, const T & value, Args... args)
//{
//
//   if(m_estate == e_state_initial || m_estate == state_parse_precision || m_estate == state_parse_length)
//   {
//
//      if(!parse(s))
//      {
//
//         str::format_type(this, value);
//
//         m_estate = e_state_initial;
//
//         format(s, args...);
//
//         return;
//
//      }
//
//   }
//
//   if(m_estate == state_waiting_width)
//   {
//
//      throw ::exception(::exception("width should plain i32"));
//
//   }
//   else if(m_estate == state_waiting_precision)
//   {
//
//      throw ::exception(::exception("width should plain i32"));
//
//   }
//
//   defer_get_additional_argument(s, args...);
//
//}
//

// namespace str
// {

//=======
//>>>>>>> origin/basis
inline string string_from_strdup(const ansichar* psz)
{

   if (psz == nullptr)
   {

      return "";

   }

   string str;

   try
   {

      str = psz;

   }
   catch (...)
   {

   }

   try
   {

      ::free((void*)psz);

   }
   catch (...)
   {

   }

   return str;

}

//
//namespace str
//{
//

   inline strsize str::utf8_dec_len(const ansichar* pszBeg, const ansichar* psz)
   {

      const ansichar* pszDec = str::uni_dec(pszBeg, psz);

      if (pszDec == nullptr)
      {

         return -1;

      }

      return psz - pszDec;

   }


   inline  strsize str::utf8_inc_len(const ansichar* psz)
   {

      return get_utf8_char_length(psz);

   }


   inline bool str::namespaced(const ansichar * psz, const ansichar * pszNamespace, const ansichar* pszSeparator)
   {

      if (::is_null(psz) || ::is_null(pszNamespace) || *psz == '\0' || *pszNamespace == '\0')
      {

         return false;

      }

      if (strcmp(psz, pszNamespace) == 0)
      {

         return true;

      }

      if (str::begins(psz, string(pszNamespace) + pszSeparator))
      {

         return true;

      }

      return false;

   }


   inline bool str::begins_ci_skip(const char*& psz, const char* pszPrefix)
   {

      auto length = strlen(pszPrefix);

      if (strnicmp(psz, pszPrefix, length) != 0)
      {

         return false;

      }

      psz += length;

      return true;

   }


   /// Returns:
   /// end of line, and;
   /// next line or null if no next line
   inline struct ::end_of_line_and_next_line str::end_of_line_and_next_line(const char* psz)
   {

      struct ::end_of_line_and_next_line pair;

      pair.end_of_line = strpbrk(psz, "\r\n\0");

      pair.next_line = pair.end_of_line;

      if (!*pair.next_line  )
      {

         pair.next_line   = nullptr;

      }
      else if (*pair.next_line   == '\r')
      {

         pair.next_line  ++;

         if (*pair.next_line   == '\r')
         {

            pair.next_line  ++;

         }

      }
      else if (*pair.next_line   == '\n')
      {

         pair.next_line  ++;

      }
      else
      {

         throw ::exception(error_failed);

      }

      return pair;

   }
//
//
//} // namespace str
//

template < typename TYPE_CHAR >
inline bool string_base < TYPE_CHAR >::equals(const CHAR_TYPE* psz) const
{

   return compare(psz) == 0;

}


template < typename TYPE_CHAR >
inline bool string_base < TYPE_CHAR >::equals_ci(const CHAR_TYPE* psz) const
{

   return compare_ci(psz) == 0;

}


//// find the first occurrence of character 'ch', starting at strsize 'iStart'
//inline strsize string::find(ansichar ch) const RELEASENOTHROW
//{
//
//   const ansichar * psz = strchr(m_psz, ch);
//
//   return psz == nullptr ? -1 : psz - m_psz;
//
//}
//

//// find the first occurrence of character 'ch', starting at strsize 'iStart'
//inline strsize string::find(ansichar ch, strsize iStart) const RELEASENOTHROW
//{
//
//   const ansichar * psz = strchr(&m_psz[iStart], ch);
//
//   return psz == nullptr ? -1 : psz - m_psz;
//
//}


int get_mem_free_available_kb();


template < typename TYPE_CHAR >
inline void string_meta_data < TYPE_CHAR > ::set_length(::strsize strsize)
{

   if (this->natural_is_shared())
   {

      throw ::exception(error_wrong_state, "invalid state");

   }

   auto strsizeStorage = this->memsize_in_chars();

   if (strsize >= strsizeStorage)
   {

      throw ::exception(error_bad_argument);

   }

   this->m_datasize = strsize;

   this->get_data()[strsize] = (TYPE_CHAR)0;

   this->get_data()[strsizeStorage - 1] = (TYPE_CHAR)0;

}



inline int str::get_utf8_char_length(const char * psz)
{

   int len = ch_uni_len(*psz);
   if (len == 0) return 0;
   if (*psz++ == 0)
   {
      return -1;
   }
   if (len == 1) return 1;
   if (*psz++ == 0)
   {
      return -1;
   }
   if (len == 2) return 2;
   if (*psz++ == 0)
   {
      return -1;
   }
   if (len == 3) return 3;
   if (*psz++ == 0)
   {
      return -1;
   }
   if (len == 4) return 4;
   if (*psz++ == 0)
   {
      return -1;
   }
   if (len == 5) return 5;
   if (*psz++ == 0)
   {
      return -1;
   }
   if (len == 6) return 6;

   {
      return -1;
   }
   return -1;
}







