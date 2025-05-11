#include "framework.h"
#include "_str.h"

#include "acme/exception/parsing.h"

#include <string.h>


CLASS_DECL_ACME int compare_ignore_case(const char * left, const char * right, size_t len);


CLASS_DECL_ACME bool equal_ignore_case(const char * left, const char * right, size_t len)
{

   return compare_ignore_case(left, right, len) == 0;

}


CLASS_DECL_ACME bool str::trimmed_is_empty(const ::scoped_string & scopedstr)
{

   const char * psz = scopedstr.c_str();

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



CLASS_DECL_ACME int compare_ignore_case(const string & left, const string & right, size_t len);


CLASS_DECL_ACME bool equal_ignore_case(const string & left, const string & right, size_t len)
{

   return compare_ignore_case(left, right, len) == 0;

}


CLASS_DECL_ACME int compare_ignore_case(const char * left, const string & right, size_t len);


CLASS_DECL_ACME bool equal_ignore_case(const char * left, const string & right, size_t len)
{

   return compare_ignore_case(left, right, len) == 0;

}


CLASS_DECL_ACME int compare_ignore_case(const string & left, const char * right, size_t len);


CLASS_DECL_ACME bool equal_ignore_case(const string & left, const char * right, size_t len)
{

   return compare_ignore_case(left, right, len) == 0;

}





//CLASS_DECL_ACME void from_string(char & i, const ::ansi_character * psz)
//{
//
//   i = (char)atoi(psz);
//
//}


CLASS_DECL_ACME void from_string(short & i, const ::ansi_character * psz)
{

   i = (short)atoi(psz);

}


CLASS_DECL_ACME void from_string(int & i, const ::ansi_character * psz)
{

   i = atoi(psz);

}


CLASS_DECL_ACME void from_string(long long & i, const ::ansi_character * psz)
{

   i = atoll(psz);

}


CLASS_DECL_ACME void from_string(int & i, int iBase, const ::ansi_character * psz)
{

   i = ansi_to_int(psz, nullptr, iBase);

}


CLASS_DECL_ACME void from_string(long long & i, int iBase, const ::ansi_character * psz)
{

   i = ansi_to_long_long(psz, nullptr, iBase);

}


CLASS_DECL_ACME void from_string(unsigned char & u, const ::ansi_character * psz)
{

   u = (unsigned char)ansi_to_unsigned_int(psz, nullptr, 10);

}


CLASS_DECL_ACME void from_string(unsigned short & u, const ::ansi_character * psz)
{

   u = (unsigned short)ansi_to_unsigned_int(psz, nullptr, 10);

}


CLASS_DECL_ACME void from_string(unsigned int & u, const ::ansi_character * psz)
{

   u = ansi_to_unsigned_int(psz, nullptr, 10);

}


CLASS_DECL_ACME void from_string(unsigned long long & u, const ::ansi_character * psz)
{

   u = ansi_to_unsigned_long_long(psz, nullptr, 10);

}


CLASS_DECL_ACME void from_string(unsigned int & u, int iBase, const ::ansi_character * psz)
{

   u = ansi_to_unsigned_int(psz, nullptr, iBase);

}


CLASS_DECL_ACME void from_string(unsigned long long & u, int iBase, const ::ansi_character * psz)
{

   u = ansi_to_unsigned_long_long(psz, nullptr, iBase);

}


#if defined(__APPLE__) || defined(__ANDROID__) || defined(RASPBERRYPIOS)
CLASS_DECL_ACME void from_string(long & l, const ::ansi_character * psz)
{

   l = ansi_to_long_long(psz, nullptr, 10);

}
#elif defined(WINDOWS)
CLASS_DECL_ACME void from_string(long & l, const ::ansi_character * psz)
{

   l = ansi_to_int(psz, nullptr, 10);

}
#endif


#if defined(__APPLE__) || defined(__ANDROID__) || defined(RASPBERRYPIOS)

CLASS_DECL_ACME void from_string(long & l, int iBase, const ::ansi_character * psz)
{

   l = ansi_to_long_long(psz, nullptr, iBase);

}
#elif defined(WINDOWS)
CLASS_DECL_ACME void from_string(long & l, int iBase, const ::ansi_character * psz)
{

   l = ansi_to_int(psz, nullptr, 10);

}
#endif


CLASS_DECL_ACME void from_string(int & i, const ::wd16_character * psz)
{

   i = wd16_to_int(psz);

}


CLASS_DECL_ACME void from_string(long long & i, const ::wd16_character * psz)
{

   i = wd16_to_long_long(psz);

}


CLASS_DECL_ACME void from_string(int & i, const ::wd32_character * psz)
{

   i = wd32_to_int(psz);

}


CLASS_DECL_ACME void from_string(long long & i, const ::wd32_character * psz)
{

   i = wd32_to_long_long(psz);

}


CLASS_DECL_ACME void from_string(float & f, const ::ansi_character * psz)
{

   f = strtof(psz, nullptr);

}


CLASS_DECL_ACME void from_string(double & d, const ::ansi_character * psz)
{

   d = strtod(psz, nullptr);

}


CLASS_DECL_ACME void from_string(::ansi_character * sz, const ::ansi_character * psz)
{

   strcpy(sz, psz);

}


CLASS_DECL_ACME void from_string(::ansi_character & ansich, const ::ansi_character * psz)
{

   ansich = *psz;

}


CLASS_DECL_ACME void from_string(::wide_character & wch, const ::ansi_character * psz)
{

   utf_to_utf(&wch, psz, unicode_next(psz) - psz);

}


CLASS_DECL_ACME void from_string(::wd16_character * sz, const ::ansi_character * psz)
{

   utf_to_utf(sz, psz);

}


CLASS_DECL_ACME void from_string(::wd32_character * sz, const ::ansi_character * psz)
{

   utf_to_utf(sz, psz);

}


template < size_t n >
CLASS_DECL_ACME void from_string(::ansi_character sz[n], const ::ansi_character * psz)
{

   if (strlen(psz) >= n)
   {

      throw_exception(error_would_reach_buffer_limit);

   }

   strcpy(sz, psz);

}


template < size_t n >
CLASS_DECL_ACME void from_string(::wd16_character sz[n], const ::ansi_character * psz)
{

   if (utf_to_utf_length(sz, psz) >= n)
   {

      throw_exception(error_would_reach_buffer_limit);

   }

   utf_to_utf(sz, psz);

}


template < size_t n >
CLASS_DECL_ACME void from_string(::wd32_character sz[n], const ::ansi_character * psz)
{

   if (utf_to_utf_length(sz, psz) >= n)
   {

      throw_exception(error_would_reach_buffer_limit);

   }

   utf_to_utf(sz, psz);

}


//// template < typename FILE >
//CLASS_DECL_ACME ::string as_string(const ::string_stream & strstream);


//// template < typename FILE >
//CLASS_DECL_ACME ::string as_string(const ::text_stream < FILE > & strstream);


CLASS_DECL_ACME string _001Concatenate(const ::string & str1, const ::string & strMid, const ::string & str2)
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
CLASS_DECL_ACME string string_from_int(const T & t)
{

   return as_string((long long)t);

}


template < typename T >
CLASS_DECL_ACME string string_from_u(const T & t)
{

   return as_string((unsigned long long)t);

}


CLASS_DECL_ACME void to_string(string & str, const float & f);


CLASS_DECL_ACME void to_string(string & str, const double & d);





CLASS_DECL_ACME bool str::namespaced(const ::ansi_character * psz, const ::ansi_character * pszNamespace, const ::ansi_character * pszSeparator)
{

   if (::is_null(psz) || ::is_null(pszNamespace) || *psz == '\0' || *pszNamespace == '\0')
   {

      return false;

   }

   if (strcmp(psz, pszNamespace) == 0)
   {

      return true;

   }

   if (::string(psz).begins(::string(pszNamespace) + pszSeparator))
   {

      return true;

   }

   return false;

}


//CLASS_DECL_ACME bool str::begins_ci_skip(const char *& psz, const ::scoped_string & scopedstrPrefix)
//{
//
//   auto length = scopedstrPrefix.size();
//
//   if (ansi_nicmp(psz, scopedstrPrefix.c_str(), length) != 0)
//   {
//
//      return false;
//
//   }
//
//   psz += length;
//
//   return true;
//
//}


// CLASS_DECL_ACME const ::ansi_character * str::windows_bbqbunc(const ansi_string &) { return "\\\\?\\UNC"; }
// CLASS_DECL_ACME const ::ansi_character * str::windows_bbqb(const ansi_string &) { return "\\\\?\\"; }
// CLASS_DECL_ACME const ::ansi_character * str::windows_bb(const ansi_string &) { return "\\\\"; }

// CLASS_DECL_ACME const ::wide_character * str::windows_bbqbunc(const wide_string &) { return L"\\\\?\\UNC"; }
// CLASS_DECL_ACME const ::wide_character * str::windows_bbqb(const wide_string &) { return L"\\\\?\\"; }
// CLASS_DECL_ACME const ::wide_character * str::windows_bb(const wide_string &) { return L"\\\\"; }


///// Returns:
///// end of line, and;
///// next line or null if no next line
//CLASS_DECL_ACME struct ::end_of_line_and_next_line str::end_of_line_and_next_line(const ::scoped_string & scopedstr)
//{
//
//   struct ::end_of_line_and_next_line pair;
//
//   pair.end_of_line = scopedstr.find_first_character_in("\r\n\0");
//
//   pair.next_line = pair.end_of_line;
//
//   if (!*pair.next_line)
//   {
//
//      pair.next_line = nullptr;
//
//   }
//   else if (*pair.next_line == '\r')
//   {
//
//      pair.next_line++;
//
//      if (*pair.next_line == '\r')
//      {
//
//         pair.next_line++;
//
//      }
//
//   }
//   else if (*pair.next_line == '\n')
//   {
//
//      pair.next_line++;
//
//   }
//   else
//   {
//
//      throw_exception(error_failed);
//
//   }
//
//   return pair;
//
//}






