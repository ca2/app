#pragma once



CLASS_DECL_ACME string i64toa_dup(i64 i, i32 iBase);
CLASS_DECL_ACME string i64toa_dup(i64 i);

CLASS_DECL_ACME string ui64toa_dup(i64 i, i32 iBase);
CLASS_DECL_ACME string ui64toa_dup(i64 i);




inline string ansi_string_from_i64(i64 i, int iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);
inline char * ansi_concatenate_i64(char * psz, i64 i, int iBase = 10, enum_digit_case edigitcase = e_digit_case_lower);





inline void wide_from_i64_base(::wide_character * sz, i64 i, i32 iBase, enum_digit_case edigitcase = e_digit_case_lower);
inline void wide_from_u64_base(::wide_character * sz, u64 i, i32 iBase, enum_digit_case edigitcase = e_digit_case_lower);


inline string ansi_string_from_i64(i64 i, int iBase, enum_digit_case edigitcase)
{
   char sz[32];
//#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID) || defined(FREEBSD)
   ansi_from_i64(sz, i, iBase, edigitcase);
//#else
//   _i64toa(i, sz, 10);
//#endif
   return string(sz);
}

inline char * ansi_concatenate_i64(char * psz, i64 i, int iBase, enum_digit_case edigitcase)
{
//#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID) || defined(FREEBSD)
   ansi_from_i64(psz + strlen(psz), i, iBase, edigitcase);
//#else
//   _i64toa(i, psz + strlen(psz), 10);
//#endif
   return psz;
}


inline string ansi_string_from_i32(i32 i, int iBase, enum_digit_case edigitcase)
{
   char sz[16];
//#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID) || defined(FREEBSD)
   ansi_from_i64(sz, i, iBase, edigitcase);
//#else
  // _itoa(i, sz, 10);
//#endif
   return string(sz);
}

//inline ::wide_character * wide_concatenate_i64(::wide_character * pwsz, i64 i)
//{
//#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID) || defined(FREEBSD)
//   wide_from_i64_base(wide_last_char(pwsz), i, 10);
//#else
//   _i64tow(i, wide_last_char(pwsz), 10);
//#endif
//   return pwsz;
//}
//
//inline ::wide_character * wide_concatenate_u64(::wide_character * pwsz, u64 u)
//{
//#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)  || defined(FREEBSD)
//   wide_from_u64_base(wide_last_char(pwsz), u, 10);
//#else
//   _ui64tow(u, wide_last_char(pwsz), 10);
//#endif
//   return pwsz;
//}

