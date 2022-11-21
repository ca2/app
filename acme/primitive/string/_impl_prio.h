#pragma once


CLASS_DECL_ACME i64 strtoi(const char * psz);
CLASS_DECL_ACME i64 strtoi(const widechar * psz);


namespace file
{

   
   class str;


} // namespace file


#if defined(__APPLE)

#define noexcept

#endif


template <typename T>
inline T FormatArgument(T value) noexcept
{

   return value;

}


#ifdef WINDOWS
inline ::u32 _gen_GetConversionACP()
{

   //return CP_UTF8;
   return CodePageUtf8;

}
#endif


class fixed_alloc_array;


template < >
inline uptr u32_hash < const ansistring & >(const ansistring & ansistr)
{

   return u32_hash < const ansichar * >(ansistr.c_str());

}


template < >
inline uptr u32_hash < const widestring & >(const widestring & widestr)
{

   return u32_hash < const widechar * >(widestr.c_str());

}


template < >
inline uptr u32_hash < ansistring >(ansistring ansistr)
{

   return u32_hash < const ansistring & >(ansistr);

}


template < >
inline uptr u32_hash < widestring >(widestring widestr)
{

   return u32_hash < const widestring & >(widestr);

}


inline const char * FormatArgument(const string & value) noexcept { return value.c_str(); }


//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > operator+(const string_base < TYPE_CHAR > & str1, const string_base < TYPE_CHAR > & str2)
//{
//
//   string_base < TYPE_CHAR > str;
//
//   return string_concatenate(str, str1, str1.get_length(), str2, str2.get_length());
//
//}



//template < primitive_atom ATOM >
//inline ::string operator+(const char * psz, const ATOM & atom) { return string(psz) + string(atom); }
//
//
//template < primitive_payload PAYLOAD >
//inline ::string operator+(const char * psz, const PAYLOAD & payload) { return string(psz) + string(payload); }

//
//template < primitive_character CHARACTER, primitive_character CHARACTER2 >
//inline ::string_base < CHARACTER2 > operator +(const CHARACTER * pszLeft, const ::string_base < CHARACTER2 > & strRight)
//{
//
//   ::wstring strLeft(pszLeft);
//
//   return strLeft + strRight;
//
//}




//template < primitive_character CHARACTER, primitive_character CHARACTER2 >
//inline ::string_base < CHARACTER2 > operator +(const CHARACTER chLeft, const ::string_base < CHARACTER2 > & strRight)
//{
//
//   ::string_base < CHARACTER2 > strLeft(&chLeft, 1);
//
//   return strLeft + strRight;
//
//}


#include "__c_wd16_impl.h"



