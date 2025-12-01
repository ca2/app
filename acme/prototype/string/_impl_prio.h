#pragma once


CLASS_DECL_ACME long long strtoi(const ::scoped_string & scopedstr);
CLASS_DECL_ACME long long strtoi(const ::wide_character * psz);


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
inline unsigned int _gen_GetConversionACP()
{

   //return CP_UTF8;
   return CodePageUtf8;

}
#endif


class fixed_alloc_array;
////
////
////template < >
////inline ::hash32 as_hash32 < const ansi_string & >(const ansi_string & ansistr)
////{
////
////   return as_hash32 < const_char_pointer >(ansistr.c_str());
////
////}
////
////
////template < >
////inline ::hash32 as_hash32 < const wide_string & >(const wide_string & widestr)
////{
////
////   return as_hash32 < const ::wide_character * >(widestr.c_str());
////
////}
////
////
////template < >
////inline ::hash32 as_hash32 < ansi_string >(ansi_string ansistr)
////{
////
////   return as_hash32 < const ansi_string & >(ansistr);
////
////}
////
////
////template < >
////inline ::hash32 as_hash32 < wide_string >(wide_string widestr)
////{
////
////   return as_hash32 < const wide_string & >(widestr);
////
////}


inline const_char_pointer FormatArgument(const string & value) noexcept { return value.c_str(); }


//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > operator +(const string_base < TYPE_CHAR > & str1, const string_base < TYPE_CHAR > & str2)
//{
//
//   string_base < TYPE_CHAR > str;
//
//   return string_concatenate(str, str1, str1.length(), str2, str2.length());
//
//}



//template < prototype_atom ATOM >
//inline ::string operator +(const ::scoped_string & scopedstr, const ATOM & atom) { return string(scopedstr) + string(atom); }
//
//
//template < prototype_payload PAYLOAD >
//inline ::string operator +(const ::scoped_string & scopedstr, const PAYLOAD & payload) { return string(scopedstr) + string(payload); }

//
//template < prototype_character CHARACTER, prototype_character CHARACTER2 >
//inline ::string_base < CHARACTER2 > operator +(const CHARACTER * pszLeft, const ::string_base < CHARACTER2 > & strRight)
//{
//
//   ::wstring strLeft(scopedstrLeft);
//
//   return strLeft + strRight;
//
//}




//template < prototype_character CHARACTER, prototype_character CHARACTER2 >
//inline ::string_base < CHARACTER2 > operator +(const CHARACTER chLeft, const ::string_base < CHARACTER2 > & strRight)
//{
//
//   ::string_base < CHARACTER2 > strLeft(&chLeft, 1);
//
//   return strLeft + strRight;
//
//}


//#include "__c_wd16_impl.h"



