#pragma once


#include <string.h>

CLASS_DECL_ACME string i64toa_dup(::i64 i, ::i32 iBase);
CLASS_DECL_ACME string i64toa_dup(::i64 i);

CLASS_DECL_ACME string ui64toa_dup(::i64 i, ::i32 iBase);
CLASS_DECL_ACME string ui64toa_dup(::i64 i);

template < prototype_integer INTEGER >
::string string_from(INTEGER i, ::i32 iBase = 10)
{

   return i64toa_dup(i, iBase);

}

inline string ansi_string_from_long_long(::i64 i, ::i32 iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);
inline char_pointer ansi_concatenate_long_long(char_pointer psz, ::i64 i, ::i32 iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);





inline void wide_from_i64_base(::wide_character * sz, ::i64 i, ::i32 iBase, enum_digit_case edigitcase = e_digit_case_lower);
inline void wide_from_u64_base(::wide_character * sz, ::u64 i, ::i32 iBase, enum_digit_case edigitcase = e_digit_case_lower);


inline string ansi_string_from_long_long(::i64 i, ::i32 iBase, enum_digit_case edigitcase)
{
   ::i8 sz[32];
//#if defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__) || defined(FREEBSD) || defined(OPENBSD)
   ansi_from_long_long(sz, i, iBase, edigitcase);
//#else
//   _long_longtoa(i, sz, 10);
//#endif
   return string(sz);
}

inline char_pointer ansi_concatenate_long_long(char_pointer psz, ::i64 i, ::i32 iBase, enum_digit_case edigitcase)
{
//#if defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__) || defined(FREEBSD) || defined(OPENBSD)
   ansi_from_long_long(psz + strlen(psz), i, iBase, edigitcase);
//#else
//   _long_longtoa(i, psz + strlen(scopedstr), 10);
//#endif
   return psz;
}


inline string ansi_string_from_i(::i32 i, ::i32 iBase, enum_digit_case edigitcase)
{
   ::i8 sz[16];
//#if defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__) || defined(FREEBSD) || defined(OPENBSD)
   ansi_from_long_long(sz, i, iBase, edigitcase);
//#else
  // _itoa(i, sz, 10);
//#endif
   return string(sz);
}

//inline ::wide_character * wide_concatenate_long_long(::wide_character * pwsz, ::i64 i)
//{
//#if defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__) || defined(FREEBSD) || defined(OPENBSD)
//   wide_from_i64_base(wide_last_char(pwsz), i, 10);
//#else
//   _long_longtow(i, wide_last_char(pwsz), 10);
//#endif
//   return pwsz;
//}
//
//inline ::wide_character * wide_concatenate_unsigned_long_long(::wide_character * pwsz, ::u64 u)
//{
//#if defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__)  || defined(FREEBSD) || defined(OPENBSD)
//   wide_from_u64_base(wide_last_char(pwsz), u, 10);
//#else
//   _ui64tow(u, wide_last_char(pwsz), 10);
//#endif
//   return pwsz;
//}

