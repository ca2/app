#include "framework.h"
#include "_str.h"

#include "acme/exception/parsing.h"

#include <string.h>


CLASS_DECL_ACME int compare_ignore_case(const_char_pointer left, const_char_pointer right, size_t len);


CLASS_DECL_ACME bool equal_ignore_case(const_char_pointer left, const_char_pointer right, size_t len)
{

   return compare_ignore_case(left, right, len) == 0;

}


CLASS_DECL_ACME bool str::trimmed_is_empty(const ::scoped_string & scopedstr)
{

   const_char_pointer psz = scopedstr.c_str();

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


CLASS_DECL_ACME int compare_ignore_case(const_char_pointer left, const string & right, size_t len);


CLASS_DECL_ACME bool equal_ignore_case(const_char_pointer left, const string & right, size_t len)
{

   return compare_ignore_case(left, right, len) == 0;

}


CLASS_DECL_ACME int compare_ignore_case(const string & left, const_char_pointer right, size_t len);


CLASS_DECL_ACME bool equal_ignore_case(const string & left, const_char_pointer right, size_t len)
{

   return compare_ignore_case(left, right, len) == 0;

}





//CLASS_DECL_ACME void from_string(char & i, const_char_pointer psz)
//{
//
//   i = (char)atoi(scopedstr);
//
//}


CLASS_DECL_ACME void from_string(short & i, const_char_pointer psz)
{

   i = (short)atoi(psz);

}


CLASS_DECL_ACME void from_string(int & i, const_char_pointer psz)
{

   i = atoi(psz);

}


CLASS_DECL_ACME void from_string(long long & i, const_char_pointer psz)
{

   i = atoll(psz);

}


CLASS_DECL_ACME void from_string(int & i, int iBase, const_char_pointer psz)
{

   i = ansi_to_int(psz, nullptr, iBase);

}


CLASS_DECL_ACME void from_string(long long & i, int iBase, const_char_pointer psz)
{

   i = ansi_to_long_long(psz, nullptr, iBase);

}


CLASS_DECL_ACME void from_string(unsigned char & u, const_char_pointer psz)
{

   u = (unsigned char)ansi_to_unsigned_int(psz, nullptr, 10);

}


CLASS_DECL_ACME void from_string(unsigned short & u, const_char_pointer psz)
{

   u = (unsigned short)ansi_to_unsigned_int(psz, nullptr, 10);

}


CLASS_DECL_ACME void from_string(unsigned int & u, const_char_pointer psz)
{

   u = ansi_to_unsigned_int(psz, nullptr, 10);

}


CLASS_DECL_ACME void from_string(unsigned long long & u, const_char_pointer psz)
{

   u = ansi_to_unsigned_long_long(psz, nullptr, 10);

}


CLASS_DECL_ACME void from_string(unsigned int & u, int iBase, const_char_pointer psz)
{

   u = ansi_to_unsigned_int(psz, nullptr, iBase);

}


CLASS_DECL_ACME void from_string(unsigned long long & u, int iBase, const_char_pointer psz)
{

   u = ansi_to_unsigned_long_long(psz, nullptr, iBase);

}


#if defined(__APPLE__) || defined(__ANDROID__) || defined(RASPBERRYPIOS)
CLASS_DECL_ACME void from_string(long & l, const_char_pointer psz)
{

   l = ansi_to_long_long(psz, nullptr, 10);

}
#elif defined(WINDOWS)
CLASS_DECL_ACME void from_string(long & l, const_char_pointer psz)
{

   l = ansi_to_int(psz, nullptr, 10);

}
#endif


#if defined(__APPLE__) || defined(__ANDROID__) || defined(RASPBERRYPIOS)

CLASS_DECL_ACME void from_string(long & l, int iBase, const_char_pointer psz)
{

   l = ansi_to_long_long(psz, nullptr, iBase);

}
#elif defined(WINDOWS)
CLASS_DECL_ACME void from_string(long & l, int iBase, const_char_pointer psz)
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


CLASS_DECL_ACME void from_string(float & f, const_char_pointer psz)
{

   f = strtof(psz, nullptr);

}


CLASS_DECL_ACME void from_string(double & d, const_char_pointer psz)
{

   d = strtod(psz, nullptr);

}


CLASS_DECL_ACME void from_string(::ansi_character * sz, const_char_pointer psz)
{

   strcpy(sz, psz);

}


CLASS_DECL_ACME void from_string(::ansi_character & ansich, const_char_pointer psz)
{

   ansich = *psz;

}


CLASS_DECL_ACME void from_string(::wide_character & wch, const_char_pointer psz)
{

   utf_to_utf(&wch, psz, unicode_next(psz) - psz);

}


CLASS_DECL_ACME void from_string(::wd16_character * sz, const_char_pointer psz)
{

   utf_to_utf(sz, psz);

}


CLASS_DECL_ACME void from_string(::wd32_character * sz, const_char_pointer psz)
{

   utf_to_utf(sz, psz);

}


template < size_t n >
CLASS_DECL_ACME void from_string(::ansi_character sz[n], const_char_pointer psz)
{

   if (strlen(psz) >= n)
   {

      throw_exception(error_would_reach_buffer_limit);

   }

   strcpy(sz, psz);

}


template < size_t n >
CLASS_DECL_ACME void from_string(::wd16_character sz[n], const_char_pointer psz)
{

   if (utf_to_utf_length(sz, psz) >= n)
   {

      throw_exception(error_would_reach_buffer_limit);

   }

   utf_to_utf(sz, psz);

}


template < size_t n >
CLASS_DECL_ACME void from_string(::wd32_character sz[n], const_char_pointer psz)
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


CLASS_DECL_ACME string _001Concatenate(const ::scoped_string & scopedstr1, const ::scoped_string & scopedstrMid, const ::scoped_string & scopedstr2)
{

   if (scopedstr1.is_empty())
   {

      if (scopedstr2.is_empty())
      {

         return "";

      }
      else
      {

         return scopedstr2;

      }

   }
   else if (scopedstr2.is_empty())
   {

      return scopedstr1;

   }
   else
   {

      return scopedstr1 + scopedstrMid + scopedstr2;

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





CLASS_DECL_ACME bool str::namespaced(const_char_pointer psz, const_char_pointer pszNamespace, const_char_pointer pszSeparator)
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


//CLASS_DECL_ACME bool str::begins_ci_skip(const_char_pointer &psz, const ::scoped_string & scopedstrPrefix)
//{
//
//   auto length = scopedstrPrefix.size();
//
//   if (ansi_nicmp(scopedstr, scopedstrPrefix.c_str(), length) != 0)
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


// CLASS_DECL_ACME const_char_pointer str::windows_bbqbunc(const ansi_string &) { return "\\\\?\\UNC"; }
// CLASS_DECL_ACME const_char_pointer str::windows_bbqb(const ansi_string &) { return "\\\\?\\"; }
// CLASS_DECL_ACME const_char_pointer str::windows_bb(const ansi_string &) { return "\\\\"; }

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






