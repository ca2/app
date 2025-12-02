#pragma once


#include <string.h>

CLASS_DECL_ACME string i64toa_dup(long long i, int iBase);
CLASS_DECL_ACME string i64toa_dup(long long i);

CLASS_DECL_ACME string ui64toa_dup(long long i, int iBase);
CLASS_DECL_ACME string ui64toa_dup(long long i);

template < prototype_integer INTEGER >
::string string_from(INTEGER i, int iBase = 10)
{

   return i64toa_dup(i, iBase);

}

inline string ansi_string_from_long_long(long long i, int iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);
inline char * ansi_concatenate_long_long(char * psz, long long i, int iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);





inline void wide_from_long_long_base(::wide_character * sz, long long i, int iBase, enum_digit_case edigitcase = e_digit_case_lower);
inline void wide_from_u64_base(::wide_character * sz, unsigned long long i, int iBase, enum_digit_case edigitcase = e_digit_case_lower);


inline string ansi_string_from_long_long(long long i, int iBase, enum_digit_case edigitcase)
{
   char sz[32];
//#if defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__) || defined(FREEBSD) || defined(OPENBSD)
   ansi_from_long_long(sz, i, iBase, edigitcase);
//#else
//   _long_longtoa(i, sz, 10);
//#endif
   return string(sz);
}

inline char * ansi_concatenate_long_long(char * psz, long long i, int iBase, enum_digit_case edigitcase)
{
//#if defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__) || defined(FREEBSD) || defined(OPENBSD)
   ansi_from_long_long(psz + strlen(psz), i, iBase, edigitcase);
//#else
//   _long_longtoa(i, psz + strlen(scopedstr), 10);
//#endif
   return psz;
}


inline string ansi_string_from_i(int i, int iBase, enum_digit_case edigitcase)
{
   char sz[16];
//#if defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__) || defined(FREEBSD) || defined(OPENBSD)
   ansi_from_long_long(sz, i, iBase, edigitcase);
//#else
  // _itoa(i, sz, 10);
//#endif
   return string(sz);
}

//inline ::wide_character * wide_concatenate_long_long(::wide_character * pwsz, long long i)
//{
//#if defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__) || defined(FREEBSD) || defined(OPENBSD)
//   wide_from_long_long_base(wide_last_char(pwsz), i, 10);
//#else
//   _long_longtow(i, wide_last_char(pwsz), 10);
//#endif
//   return pwsz;
//}
//
//inline ::wide_character * wide_concatenate_unsigned_long_long(::wide_character * pwsz, unsigned long long u)
//{
//#if defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__)  || defined(FREEBSD) || defined(OPENBSD)
//   wide_from_u64_base(wide_last_char(pwsz), u, 10);
//#else
//   _ui64tow(u, wide_last_char(pwsz), 10);
//#endif
//   return pwsz;
//}

