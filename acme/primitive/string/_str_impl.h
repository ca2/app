#pragma once


//#include "__string.h"

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

         auto psource = psz;
         
         auto ptarget = psz;
         
         auto copyLength = itemLen;
         
         while (copyLength > 0)
         {

            *ptarget++ = *psource++;

            copyLength--;

         }

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


inline bool str::trimmed_is_empty(const ::string & str)
{

   const char * psz = str.c_str();

   while (true)
   {

      if (*psz == '\0')
      {

         break;

      }

      if (!character_isspace(*psz))
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


//inline void from_string(i32 & i, i32 iBase, const widechar * psz)
//{
//
//   i = wide_to_i32(psz, nullptr, iBase);
//
//}
//
//
//inline void from_string(i64 & i, i32 iBase, const widechar * psz)
//{
//
//   i = wide_to_i64(psz, nullptr, iBase);
//
//}
//
//
//inline void from_string(u32 & u, const widechar * psz)
//{
//
//   u = wide_to_u32(psz, nullptr, 10);
//
//}
//
//
//inline void from_string(u64 & u, const widechar * psz)
//{
//
//   u = wide_to_u64(psz, nullptr, 10);
//
//}
//
//
//inline void from_string(u32 & u, i32 iBase, const widechar * psz)
//{
//
//   u = wide_to_u32(psz, nullptr, iBase);
//
//}
//
//
//inline void from_string(u64 & u, i32 iBase, const widechar * psz)
//{
//
//   u = wide_to_u64(psz, nullptr, iBase);
//
//}


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

   utf_to_utf(&wch, psz, unicode_next(psz) - psz);

}


inline void from_string(wd16char * sz, const ansichar * psz)
{

   utf_to_utf(sz, psz);

}


inline void from_string(wd32char * sz, const ansichar * psz)
{

   utf_to_utf(sz, psz);

}


template < size_t n >
inline void from_string(ansichar sz[n], const ansichar * psz)
{

   if (strlen(psz) >= n)
   {

      throw_exception(error_would_reach_buffer_limit);

   }

   strcpy(sz, psz);

}


template < size_t n >
inline void from_string(wd16char sz[n], const ansichar * psz)
{

   if (utf_to_utf_length(sz, psz) >= n)
   {

      throw_exception(error_would_reach_buffer_limit);

   }

   utf_to_utf(sz, psz);

}


template < size_t n >
inline void from_string(wd32char sz[n], const ansichar * psz)
{

   if (utf_to_utf_length(sz, psz) >= n)
   {

      throw_exception(error_would_reach_buffer_limit);

   }

   utf_to_utf(sz, psz);

}



//inline void from_string(::element & element, const ansichar * psz)
//{
//
//   payload_stream stream;
//
//   stream.m_ppayload->parse_network_payload(psz);
//
//   element.exchange(stream);
//
//}
//

//template < typename TYPE >
//inline ::string __string(const TYPE & t)
//{
//
//   str = t.get_string();
//
//}



//inline ::string __string(const element & t)
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




//inline ::string __string(const element & o)
//{

//   o.to_string(str);

//}


//inline ::string __string(const ::atom & atom)
//{
//
//   atom.to_string(str);
//
//}


//inline ::string __string(const ::wd16string & wd16str)
//{
//
//   str = wd16str;
//
//}
//
//
//inline ::string __string(const ::wd32string & wd32str)
//{
//
//   str = wd32str;
//
//}




CLASS_DECL_ACME ::string __string(const ::string_stream & strstream);


CLASS_DECL_ACME ::string __string(const ::text_stream & strstream);


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

   return __string((::i64)t);

}


template < typename T >
inline string string_from_u(const T& t)
{

   return __string((::u64)t);

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
//         throw_exception(error_bad_argument);
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
//      throw_exception(error_bad_argument);
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
//      // is shared or (2) the buffer is too small to hold the memory_new
//      // string.  We detect this aliasing, and modify pszSrc to point_i32
//      // into the newly allocated buffer instead.
//      if(pszSrc == nullptr)
//      {
//
//         throw_exception(error_bad_argument);
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
//inline void string_buffer < TYPE_CHAR >::set_length(strsize nLength )
//{
//
//   ASSERT(nLength >= 0);
//
//   ASSERT(nLength <= m_nBufferLength);
//
//   if(nLength < 0)
//   {
//
//      throw_exception(error_bad_argument);
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


//template < >
//inline void std_string_bassign(wstring& t, const u8* psz, strsize nsize)
//{
//   t = utf8_to_unicode(string((const ansichar*)psz, minimum(nsize, strlen_s_dup((const ansichar*)psz, nsize))));
//}
//
//template < >
//inline void std_string_assign(wstring& t, const string* pstr)
//{
//   t = utf8_to_unicode(*pstr);
//}

//template < >
//inline void std_string_assign(wstring & t,const string * pstr)
//{
//   t = utf8_to_unicode(*pstr);
//}

//template < >
//inline void std_string_assign(wstring& t, const wstring* pwstr)
//{
//   t = *pwstr;
//}

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
//inline ::string __string(const long & l)
//{
//
//   str = i64toa_dup(l);
//
//}
//
//
//
////inline ::string __string(const unsigned long &ul)
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
//   throw_exception(::exception("missing argument value"));
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
//      throw_exception(::exception("width should plain i32"));
//
//   }
//   else if(m_estate == state_waiting_precision)
//   {
//
//      throw_exception(::exception("width should plain i32"));
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

//
//namespace str
//{
//

   inline strsize str::utf8_dec_len(const ansichar* pszBeg, const ansichar* psz)
   {

      const ansichar* pszDec = unicode_prior(pszBeg, psz);

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

      if (string_begins(psz, string(pszNamespace) + pszSeparator))
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


//
//
//} // namespace str
//





//template < const_c_string TOPIC_STRING, const_c_string PREFIX_STRING >
//inline bool str::begins(const TOPIC_STRING & topic_string, const PREFIX_STRING & prefix_string)
//{
//
//   using topic_type = typename base_const_c_string < TOPIC_STRING >::type;
//
//   using prefix_type = typename base_const_c_string < PREFIX_STRING >::type;
//
//   static_assert(::std::same_as < topic_type, prefix_type >);
//
//   auto prefix = (prefix_type)prefix_string;
//
//   auto prefix_length = string_safe_length(prefix);
//
//   if (prefix_length <= 0)
//   {
//
//      return true;
//
//   }
//
//   auto topic = (topic_type)topic_string;
//
//   auto topic_length = string_safe_length(topic);
//
//   if (topic_length < prefix_length)
//   {
//
//      return false;
//
//   }
//
//   return !string_count_compare(topic, prefix, prefix_length);
//
//}


//template < const_c_string TOPIC_STRING, const_c_string PREFIX_STRING >
//inline bool str::begins_ci(const TOPIC_STRING & topic_string, const PREFIX_STRING & prefix_string)
//{
//
//   using topic_type = typename base_const_c_string < TOPIC_STRING >::type;
//
//   using prefix_type = typename base_const_c_string < PREFIX_STRING >::type;
//
//   static_assert(::std::same_as < topic_type, prefix_type >);
//
//   auto prefix = (prefix_type)prefix_string;
//
//   auto prefix_length = string_safe_length(prefix);
//
//   if (prefix_length <= 0)
//   {
//
//      return true;
//
//   }
//
//   auto topic = (topic_type)topic_string;
//
//   auto topic_length = string_safe_length(topic);
//
//   if (topic_length < prefix_length)
//   {
//
//      return false;
//
//   }
//
//   return !string_count_compare_ci(topic, prefix, prefix_length);
//
//}


//   template < typename TYPE, typename PREFIX >
//   inline bool begins_ci(const TYPE & str, const PREFIX & strPrefix)
//   {
//
//      return !str::string_count_compare_ci(str, strPrefix, string_safe_length(strPrefix));
//
//   }


//template < typename TYPE, typename FED, typename PREFIX >
//inline bool str::begins_ci(const TYPE & str, FED & strFed, const PREFIX & strPrefix)
//{
//
//   if (!begins_ci(str, strPrefix))
//   {
//
//      return false;
//
//   }
//
//   strFed = strPrefix;
//
//   return true;
//
//}
//
//template < typename TYPE, typename PREFIX >
//inline bool str::begins_eat(TYPE & str, const PREFIX & strPrefix)
//{
//
//   auto len = string_safe_length(strPrefix);
//
//   if (string_count_compare(str, strPrefix, len))
//   {
//
//      return false;
//
//   }
//
//   str = str.c_str() + len;
//
//   return true;
//
//}


//template < typename TYPE, typename PREFIX >
//inline bool str::begins_eat_ci(TYPE & str, const PREFIX & strPrefix)
//{
//
//   auto len = string_safe_length(strPrefix);
//
//   if (string_count_compare_ci(str, strPrefix, len))
//   {
//
//      return false;
//
//   }
//
//   str = &str[len];
//
//   return true;
//
//}
//
//
//
//
//
//template < const_c_string TOPIC_STRING, const_c_string SUFFIX_STRING >
//inline bool str::ends(const TOPIC_STRING & topic_string, const SUFFIX_STRING & suffix_string)
//{
//
//   using topic_type = typename base_const_c_string < TOPIC_STRING >::type;
//
//   using suffix_type = typename base_const_c_string < SUFFIX_STRING >::type;
//
//   static_assert(::std::same_as < topic_type, suffix_type >);
//
//   auto suffix = (suffix_type)suffix_string;
//
//   auto suffix_length = string_safe_length(suffix);
//
//   if (suffix_length <= 0)
//   {
//
//      return true;
//
//   }
//
//   auto topic = (topic_type)topic_string;
//
//   auto topic_length = string_safe_length(topic);
//
//   if (topic_length < suffix_length)
//   {
//
//      return false;
//
//   }
//
//   auto end_index = (topic_length - suffix_length);
//
//   auto end = topic + end_index;
//
//   return !string_count_compare(end, suffix, suffix_length);
//
//}
//
//
//template < const_c_string TOPIC_STRING, const_c_string SUFFIX_STRING >
//inline bool str::ends_ci(const TOPIC_STRING & topic_string, const SUFFIX_STRING & suffix_string)
//{
//
//   using topic_type = typename base_const_c_string < TOPIC_STRING >::type;
//
//   using suffix_type = typename base_const_c_string < SUFFIX_STRING >::type;
//
//   static_assert(::std::same_as < topic_type, suffix_type >);
//
//   auto suffix = (suffix_type)suffix_string;
//
//   auto suffix_length = string_safe_length(suffix);
//
//   if (suffix_length <= 0)
//   {
//
//      return true;
//
//   }
//
//   auto topic = (topic_type)topic_string;
//
//   auto topic_length = string_safe_length(topic);
//
//   if (topic_length < suffix_length)
//   {
//
//      return false;
//
//   }
//
//   auto end_index = (topic_length - suffix_length);
//
//   auto end = topic + end_index;
//
//   return !string_count_compare_ci(end, suffix, suffix_length);
//
//}
//
//
//
//template < typename TYPE, typename SUFFIX >
//inline bool str::ends_eat(TYPE & str, const SUFFIX & strSuffix)
//{
//
//   auto len = string_safe_length(strSuffix);
//
//   auto end = string_safe_length(str) - len;
//
//   if (string_count_compare(&str[end], strSuffix, len))
//   {
//
//      return false;
//
//   }
//
//   str.truncate(end);
//
//   return true;
//
//}
//
//
//template < typename TYPE, typename SUFFIX >
//inline bool str::ends_eat_ci(TYPE & str, const SUFFIX & strSuffix)
//{
//
//   auto len = string_safe_length(strSuffix);
//
//   auto end = string_safe_length(str) - len;
//
//   if (string_count_compare_ci(&str[end], strSuffix, len))
//   {
//
//      return false;
//
//   }
//
//   str.truncate(end);
//
//   return true;
//
//}
//

//} // namespace str
//
//






//namespace str
//{
//

//   template < typename TYPE_TARGET, typename TYPE_SOURCE >
//   inline strsize str::utf_to_utf_length(const TYPE_TARGET *, const TYPE_SOURCE * psource, strsize srclen)
//   {
//
//      throw ::interface_only();
//
//      return 0;
//
//   }


//   template <  >



inline const ansichar * str::windows_bbqbunc(const ansistring &) { return "\\\\?\\UNC"; }
inline const ansichar * str::windows_bbqb(const ansistring &) { return "\\\\?\\"; }
inline const ansichar * str::windows_bb(const ansistring &) { return "\\\\"; }

inline const widechar * str::windows_bbqbunc(const widestring &) { return L"\\\\?\\UNC"; }
inline const widechar * str::windows_bbqb(const widestring &) { return L"\\\\?\\"; }
inline const widechar * str::windows_bb(const widestring &) { return L"\\\\"; }



inline strsize str::copy_string_len(wd16char * pszDst, const ansichar * pszSrc, strsize srclen) { return utf_to_utf_length(pszDst, pszSrc, srclen); }
inline strsize str::copy_string_len(wd32char * pszDst, const ansichar * pszSrc, strsize srclen) { return utf_to_utf_length(pszDst, pszSrc, srclen); }
inline strsize str::copy_string_len(ansichar * pszDst, const wd16char * pszSrc, strsize srclen) { return utf_to_utf_length(pszDst, pszSrc, srclen); }
inline strsize str::copy_string_len(ansichar * pszDst, const wd32char * pszSrc, strsize srclen) { return utf_to_utf_length(pszDst, pszSrc, srclen); }


inline void str::copy_string(wd16char * pszDst, const ansichar * pszSrc, strsize srclen) { utf_to_utf(pszDst, pszSrc, srclen); }
inline void str::copy_string(wd32char * pszDst, const ansichar * pszSrc, strsize srclen) { utf_to_utf(pszDst, pszSrc, srclen); }
inline void str::copy_string(ansichar * pszDst, const wd16char * pszSrc, strsize srclen) { utf_to_utf(pszDst, pszSrc, srclen); }
inline void str::copy_string(ansichar * pszDst, const wd32char * pszSrc, strsize srclen) { utf_to_utf(pszDst, pszSrc, srclen); }


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > & str::assign(string_base < TYPE_CHAR > & strDst, const string_base < TYPE_CHAR > & strSrc)
{

   strDst.assign_natural_pointer(strSrc);

   return strDst;

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > & str::assign(string_base < TYPE_CHAR > & strDst, const string_natural_pointer < TYPE_CHAR > & strSrc)
{

   strDst.assign_natural_pointer(strSrc);

   return strDst;

}


template < typename TYPE_CHAR1 >
inline string_base < TYPE_CHAR1 > & str::assign(string_base < TYPE_CHAR1 > & strDst, const TYPE_CHAR1 * pszSrc, strsize srclen)
{

   if (srclen < 0)
   {

      srclen = string_get_length(pszSrc) + srclen + 1;

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

      utf_to_utf(strDst.m_pdata, pszSrc, dstlen);

      strDst.release_string_buffer(dstlen);

   }

   return strDst;

}


template < typename TYPE_CHAR1, typename TYPE_CHAR2 >
inline string_base < TYPE_CHAR1 > & str::assign(string_base < TYPE_CHAR1 > & strDst, const TYPE_CHAR2 * pszSrc, strsize srclen)
{

   if (srclen < 0)
   {

      srclen = string_get_length(pszSrc) + srclen + 1;

   }

   auto dstlen = utf_to_utf_length(strDst.m_pdata, pszSrc, srclen);

   if (dstlen <= 0)
   {

      strDst.Empty();

   }
   else
   {

      auto pszDst = strDst.get_string_buffer(dstlen);

      utf_to_utf(pszDst, pszSrc, srclen);

      strDst.release_string_buffer(dstlen);

   }

   return strDst;

}


template < typename TYPE_CHAR1, typename TYPE_CHAR2 >
inline string_base < TYPE_CHAR1 > & str::assign(string_base < TYPE_CHAR1 > & strDst, const TYPE_CHAR2 * pszSrc)
{

   auto dstlen = utf_to_utf_length(strDst.m_pdata, pszSrc);

   if (dstlen <= 0)
   {

      strDst.Empty();

   }
   else
   {

      auto pszDst = strDst.get_string_buffer(dstlen);

      utf_to_utf(pszDst, pszSrc);

      strDst.release_string_buffer(dstlen);

   }

   return strDst;

}


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > & str::assign(string_base < TYPE_CHAR > & ansistrSrc, const TYPE_CHAR * pszSrc)
{

   return assign(ansistrSrc, pszSrc, string_safe_length(pszSrc));

}


//inline wd16string & str::assign(wd16string & wstrDst, const ansistring & strSrc)
//{
//
//   auto dstlen = copy_string_len(wstrDst.m_pdata, strSrc.m_pdata, strSrc.get_length());
//
//   if (dstlen <= 0)
//   {
//
//      wstrDst.Empty();
//
//   }
//   else
//   {
//
//      auto pch = wstrDst.get_string_buffer(dstlen);
//
//      copy_string(pch, strSrc.m_pdata, strSrc.get_length());
//
//      wstrDst.release_string_buffer();
//
//   }
//
//   return wstrDst;
//
//}
//
//
//inline wd32string & str::assign(wd32string & wstrDst, const ansistring & strSrc)
//{
//
//   auto dstlen = copy_string_len(wstrDst.m_pdata, strSrc.m_pdata, strSrc.get_length());
//
//   if (dstlen <= 0)
//   {
//
//      wstrDst.Empty();
//
//   }
//   else
//   {
//
//      auto pch = wstrDst.get_string_buffer(dstlen);
//
//      copy_string(pch, strSrc.m_pdata, strSrc.get_length());
//
//      wstrDst.release_string_buffer();
//
//   }
//
//   return wstrDst;
//
//}


//inline wd16string & str::assign(wd16string & wstrDst, const natural_ansistring & strSrc)
//{
//
//   auto srclen = string_safe_length(strSrc.m_pdata);
//
//   auto len = copy_string_len(wstrDst.m_pdata, strSrc.m_pdata, srclen);
//
//   auto pch = wstrDst.get_string_buffer(len);
//
//   copy_string(pch, strSrc.m_pdata, srclen);
//
//   return wstrDst;
//
//}
//
//
//inline wd32string & str::assign(wd32string & wstrDst, const natural_ansistring & strSrc)
//{
//
//   auto srclen = string_safe_length(strSrc.m_pdata);
//
//   auto len = copy_string_len(wstrDst.m_pdata, strSrc.m_pdata, srclen);
//
//   auto pch = wstrDst.get_string_buffer(len);
//
//   copy_string(pch, strSrc.m_pdata, srclen);
//
//   return wstrDst;
//
//}
//
//
//
//inline ansistring & str::assign(ansistring & ansistrSrc, const wd16string & widestrSrc)
//{
//
//   auto len = copy_string_len(ansistrSrc.m_pdata, widestrSrc.m_pdata, widestrSrc.get_length());
//
//   auto pch = ansistrSrc.get_string_buffer(len);
//
//   copy_string(pch, widestrSrc.m_pdata, widestrSrc.get_length());
//
//   return ansistrSrc;
//
//}
//
//inline ansistring & str::assign(ansistring & ansistrSrc, const wd32string & widestrSrc)
//{
//
//   auto len = copy_string_len(ansistrSrc.m_pdata, widestrSrc.m_pdata, widestrSrc.get_length());
//
//   auto pch = ansistrSrc.get_string_buffer(len);
//
//   copy_string(pch, widestrSrc.m_pdata, widestrSrc.get_length());
//
//   return ansistrSrc;
//
//}
//
//
//inline ansistring & str::assign(ansistring & ansistrSrc, const natural_wd16string & widestrSrc)
//{
//
//   auto srclen = string_safe_length(widestrSrc.m_pdata);
//
//   auto len = copy_string_len(ansistrSrc.m_pdata, widestrSrc.m_pdata, srclen);
//
//   auto pch = ansistrSrc.get_string_buffer(len);
//
//   copy_string(pch, widestrSrc.m_pdata, srclen);
//
//   return ansistrSrc;
//
//}
//
//inline ansistring & str::assign(ansistring & ansistrSrc, const natural_wd32string & widestrSrc)
//{
//
//   auto srclen = string_safe_length(widestrSrc.m_pdata);
//
//   auto len = copy_string_len(ansistrSrc.m_pdata, widestrSrc.m_pdata, srclen);
//
//   auto pch = ansistrSrc.get_string_buffer(len);
//
//   copy_string(pch, widestrSrc.m_pdata, srclen);
//
//   return ansistrSrc;
//
//}



//
//inline ansistring & str::assign(ansistring & ansistrDst, ansichar ansich)
//{
//
//   ansistrDst.assign(&ansich, 1);
//
//   return ansistrDst;
//
//}
//
//
//inline wd16string & str::assign(wd16string & widestrDst, ansichar ansich)
//{
//
//   widestrDst.assign(&ansich, 1);
//
//   return widestrDst;
//
//}
//
//inline wd32string & str::assign(wd32string & widestrDst, ansichar ansich)
//{
//
//   widestrDst.assign(&ansich, 1);
//
//   return widestrDst;
//
//}
//
//inline ansistring & str::assign(ansistring & ansistrDst, wd16char widech)
//{
//
//   ansistrDst.assign(&widech, 1);
//
//   return ansistrDst;
//
//}
//
//
//inline wd16string & str::assign(wd16string & widestrDst, wd16char widech)
//{
//
//   widestrDst.assign(&widech, 1);
//
//   return widestrDst;
//
//}
//
//inline wd32string & str::assign(wd32string & widestrDst, wd16char widech)
//{
//
//   widestrDst.assign(&widech, 1);
//
//   return widestrDst;
//
//}
//
//inline ansistring & str::assign(ansistring & ansistrDst, wd32char widech)
//{
//
//   ansistrDst.assign(&widech, 1);
//
//   return ansistrDst;
//
//}
//
//
//inline wd16string & str::assign(wd16string & widestrDst, wd32char widech)
//{
//
//   widestrDst.assign(&widech, 1);
//
//   return widestrDst;
//
//}
//
//inline wd32string & str::assign(wd32string & widestrDst, wd32char widech)
//{
//
//   widestrDst.assign(&widech, 1);
//
//   return widestrDst;
//
//}
//
//
//
//inline ansistring & str::assign(ansistring & strDst, const wd16char * psrcsz)
//{
//
//   auto srclen = string_safe_length(psrcsz);
//
//   auto dstlen = utf_to_utf_length(strDst.m_pdata, psrcsz, srclen);
//
//   auto pdstsz = strDst.get_string_buffer(dstlen);
//
//   utf_to_utf(pdstsz, psrcsz, srclen);
//
//   strDst.metadata()->set_length(dstlen);
//
//   return strDst;
//
//}
//
//
//inline ansistring & str::assign(ansistring & strDst, const wd32char * psrcsz)
//{
//
//   auto srclen = string_safe_length(psrcsz);
//
//   auto dstlen = utf_to_utf_length(strDst.m_pdata, psrcsz, srclen);
//
//   auto pdstsz = strDst.get_string_buffer(dstlen);
//
//   utf_to_utf(pdstsz, psrcsz, srclen);
//
//   strDst.metadata()->set_length(dstlen);
//
//   return strDst;
//
//}
//
//inline wd16string & str::assign(wd16string & strDst, const ansichar * psrcsz)
//{
//
//   auto srclen = string_safe_length(psrcsz);
//
//   auto dstlen = utf_to_utf_length(strDst.m_pdata, psrcsz, srclen);
//
//   auto pwidesz = strDst.get_string_buffer(dstlen);
//
//   utf_to_utf(pwidesz, psrcsz, srclen);
//
//   return strDst;
//
//}
//
//
//inline wd16string & str::assign(wd16string & strDst, const wd16char * psrcsz)
//{
//
//   auto srclen = string_safe_length(psrcsz);
//
//   auto dstlen = utf_to_utf_length(strDst.m_pdata, psrcsz, srclen);
//
//   auto pwidesz = strDst.get_string_buffer(dstlen);
//
//   utf_to_utf(pwidesz, psrcsz, srclen);
//
//   return strDst;
//
//}
//
//
//inline wd16string & str::assign(wd16string & strDst, const wd32char * psrcsz)
//{
//
//   auto srclen = string_safe_length(psrcsz);
//
//   auto dstlen = utf_to_utf_length(strDst.m_pdata, psrcsz, srclen);
//
//   auto pwidesz = strDst.get_string_buffer(dstlen);
//
//   utf_to_utf(pwidesz, psrcsz, srclen);
//
//   return strDst;
//
//}
//
//
//inline wd32string & str::assign(wd32string & strDst, const ansichar * psrcsz)
//{
//
//   auto srclen = string_safe_length(psrcsz);
//
//   auto dstlen = utf_to_utf_length(strDst.m_pdata, psrcsz, srclen);
//
//   auto pwidesz = strDst.get_string_buffer(dstlen);
//
//   utf_to_utf(pwidesz, psrcsz, srclen);
//
//   return strDst;
//
//}
//
//
//inline wd32string & str::assign(wd32string & strDst, const wd16char * psrcsz)
//{
//
//   auto srclen = string_safe_length(psrcsz);
//
//   auto dstlen = utf_to_utf_length(strDst.m_pdata, psrcsz, srclen);
//
//   auto pwidesz = strDst.get_string_buffer(dstlen);
//
//   utf_to_utf(pwidesz, psrcsz, srclen);
//
//   return strDst;
//
//}
//
//
//inline wd32string & str::assign(wd32string & strDst, const wd32char * psrcsz)
//{
//
//   auto srclen = string_safe_length(psrcsz);
//
//   auto dstlen = utf_to_utf_length(strDst.m_pdata, psrcsz, srclen);
//
//   auto pwidesz = strDst.get_string_buffer(dstlen);
//
//   utf_to_utf(pwidesz, psrcsz, srclen);
//
//   return strDst;
//
//}
//
//
//
////
////} // namespace str
////
//





/// Returns:
/// end of line, and;
/// next line or null if no next line
inline struct ::end_of_line_and_next_line str::end_of_line_and_next_line(const char * psz)
{

   struct ::end_of_line_and_next_line pair;

   pair.end_of_line = strpbrk(psz, "\r\n\0");

   pair.next_line = pair.end_of_line;

   if (!*pair.next_line)
   {

      pair.next_line = nullptr;

   }
   else if (*pair.next_line == '\r')
   {

      pair.next_line++;

      if (*pair.next_line == '\r')
      {

         pair.next_line++;

      }

   }
   else if (*pair.next_line == '\n')
   {

      pair.next_line++;

   }
   else
   {

      throw_exception(error_failed);

   }

   return pair;

}












