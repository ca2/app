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

         auto psource = psz;

         auto ptarget = p;

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

   i = (i8)atoi(psz);

}


inline void from_string(i16 & i, const ansichar * psz)
{

   i = (i16)atoi(psz);

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

   u = (u8)ansi_to_u32(psz, nullptr, 10);

}


inline void from_string(u16 & u, const ansichar * psz)
{

   u = (u16)ansi_to_u32(psz, nullptr, 10);

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

inline void from_string(long & l, i32 iBase, const ansichar * psz)
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


inline void from_string(ansichar & ch, const ansichar * psz)
{

   ch = *psz;

}


inline void from_string(widechar & wch, const ansichar * psz)
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


//template < typename FILE >
//inline ::string __string(const ::string_stream & strstream);


//template < typename FILE >
//inline ::string __string(const ::text_stream < FILE > & strstream);


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
inline string string_from_int(const T & t)
{

   return __string((::i64)t);

}


template < typename T >
inline string string_from_u(const T & t)
{

   return __string((::u64)t);

}


CLASS_DECL_ACME void to_string(string & str, const float & f);


CLASS_DECL_ACME void to_string(string & str, const double & d);



inline strsize str::utf8_dec_len(const ansichar * pszBeg, const ansichar * psz)
{

   const ansichar * pszDec = unicode_prior(pszBeg, psz);

   if (pszDec == nullptr)
   {

      return -1;

   }

   return psz - pszDec;

}


inline  strsize str::utf8_inc_len(const ansichar * psz)
{

   return get_utf8_char_length(psz);

}


inline bool str::namespaced(const ansichar * psz, const ansichar * pszNamespace, const ansichar * pszSeparator)
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


inline bool str::begins_ci_skip(const char *& psz, const char * pszPrefix)
{

   auto length = strlen(pszPrefix);

   if (strnicmp(psz, pszPrefix, length) != 0)
   {

      return false;

   }

   psz += length;

   return true;

}


inline const ansichar * str::windows_bbqbunc(const ansistring &) { return "\\\\?\\UNC"; }
inline const ansichar * str::windows_bbqb(const ansistring &) { return "\\\\?\\"; }
inline const ansichar * str::windows_bb(const ansistring &) { return "\\\\"; }

inline const widechar * str::windows_bbqbunc(const widestring &) { return L"\\\\?\\UNC"; }
inline const widechar * str::windows_bbqb(const widestring &) { return L"\\\\?\\"; }
inline const widechar * str::windows_bb(const widestring &) { return L"\\\\"; }


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



