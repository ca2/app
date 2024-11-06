#pragma once


#include <string.h>

CLASS_DECL_ACME string i64toa_dup(huge_integer i, int iBase);
CLASS_DECL_ACME string i64toa_dup(huge_integer i);

CLASS_DECL_ACME string ui64toa_dup(huge_integer i, int iBase);
CLASS_DECL_ACME string ui64toa_dup(huge_integer i);

template < primitive_integer INTEGER >
::string string_from(INTEGER i, int iBase = 10)
{

   return i64toa_dup(i, iBase);

}

inline string ansi_string_from_huge_integer(huge_integer i, int iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);
inline char * ansi_concatenate_huge_integer(char * psz, huge_integer i, int iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);





inline void wide_from_huge_integer_base(::wide_character * sz, huge_integer i, int iBase, enum_digit_case edigitcase = e_digit_case_lower);
inline void wide_from_u64_base(::wide_character * sz, huge_natural i, int iBase, enum_digit_case edigitcase = e_digit_case_lower);


inline string ansi_string_from_huge_integer(huge_integer i, int iBase, enum_digit_case edigitcase)
{
   char sz[32];
//#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID) || defined(FREEBSD) || defined(OPENBSD)
   ansi_from_huge_integer(sz, i, iBase, edigitcase);
//#else
//   _huge_integertoa(i, sz, 10);
//#endif
   return string(sz);
}

inline char * ansi_concatenate_huge_integer(char * psz, huge_integer i, int iBase, enum_digit_case edigitcase)
{
//#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID) || defined(FREEBSD) || defined(OPENBSD)
   ansi_from_huge_integer(psz + strlen(psz), i, iBase, edigitcase);
//#else
//   _huge_integertoa(i, psz + strlen(psz), 10);
//#endif
   return psz;
}


inline string ansi_string_from_i(int i, int iBase, enum_digit_case edigitcase)
{
   char sz[16];
//#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID) || defined(FREEBSD) || defined(OPENBSD)
   ansi_from_huge_integer(sz, i, iBase, edigitcase);
//#else
  // _itoa(i, sz, 10);
//#endif
   return string(sz);
}

//inline ::wide_character * wide_concatenate_huge_integer(::wide_character * pwsz, huge_integer i)
//{
//#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID) || defined(FREEBSD) || defined(OPENBSD)
//   wide_from_huge_integer_base(wide_last_char(pwsz), i, 10);
//#else
//   _huge_integertow(i, wide_last_char(pwsz), 10);
//#endif
//   return pwsz;
//}
//
//inline ::wide_character * wide_concatenate_huge_natural(::wide_character * pwsz, huge_natural u)
//{
//#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)  || defined(FREEBSD) || defined(OPENBSD)
//   wide_from_u64_base(wide_last_char(pwsz), u, 10);
//#else
//   _ui64tow(u, wide_last_char(pwsz), 10);
//#endif
//   return pwsz;
//}

