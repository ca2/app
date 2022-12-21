#pragma once


#include "_u32hash.h"
#include "_conv.h"


CLASS_DECL_ACME i64 strtoi(const ::scoped_string & scopedstr);
CLASS_DECL_ACME i64 strtoi(const ::wide_character * psz);


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
inline u32hash u32_hash < const ansi_string & >(const ansi_string & ansistr)
{

   return u32_hash < const ::ansi_character * >(ansistr.c_str());

}


template < >
inline u32hash u32_hash < const wide_string & >(const wide_string & widestr)
{

   return u32_hash < const ::wide_character * >(widestr.c_str());

}


template < >
inline u32hash u32_hash < ansi_string >(ansi_string ansistr)
{

   return u32_hash < const ansi_string & >(ansistr);

}


template < >
inline u32hash u32_hash < wide_string >(wide_string widestr)
{

   return u32_hash < const wide_string & >(widestr);

}


inline const char * FormatArgument(const string & value) noexcept { return value.c_str(); }


//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR > operator+(const string_base < TYPE_CHAR > & str1, const string_base < TYPE_CHAR > & str2)
//{
//
//   string_base < TYPE_CHAR > str;
//
//   return string_concatenate(str, str1, str1.length(), str2, str2.length());
//
//}



//template < primitive_character CHARACTER, primitive_character CHARACTER2 >
//inline ::string_base < CHARACTER2 > operator +(const CHARACTER * pszLeft, const ::string_base < CHARACTER2 > & strRight)
//{
//
//   ::wstring strLeft(pszLeft);
//
//   return strLeft + strRight;
//
//}
//
//
//
//
//template < primitive_character CHARACTER, primitive_character CHARACTER2 >
//inline ::string_base < CHARACTER2 > operator +(const CHARACTER chLeft, const ::string_base < CHARACTER2 > & strRight)
//{
//
//   ::string_base < CHARACTER2 > strLeft(&chLeft, 1);
//
//   return strLeft + strRight;
//
//}


//#include "__c_wd16_impl.h"


#include "_string_base_impl.h"


template < typename CHAR_TYPE1, typename CHAR_TYPE2 >
void copy(::string_base < CHAR_TYPE1 >& str1, const ::string_base < CHAR_TYPE2 >& str2)
{

	str1 = str2;

}


template < typename CHAR_TYPE1, primitive_character CHARACTER, std::size_t N >
void copy(::string_base < CHAR_TYPE1 >& str1, const CHARACTER sz[N])
{

	str1 = sz;

}


template < typename CHAR_TYPE1, primitive_character CHARACTER >
void copy(::string_base < CHAR_TYPE1 >& str1, const CHARACTER* psz)
{

	str1 = psz;

}





template < primitive_string STRING, primitive_integral INTEGRAL >
inline STRING& copy(STRING& string, const INTEGRAL& number)
{

	string.append_format("%lld", (::i64)number);

	return string;

}


template < primitive_signed SIGNED, primitive_string STRING >
inline void copy(SIGNED& s, const STRING& string)
{

	s = (SIGNED)string_to_signed(string);

}


template < primitive_natural NATURAL, primitive_string STRING >
inline void copy(NATURAL& n, const STRING& string)
{

	n = (NATURAL)string_to_natural(string);

}


template < primitive_floating FLOATING, primitive_string STRING >
inline void copy(FLOATING& f, const STRING& string)
{

	f = (FLOATING)string_to_floating(string);

}


template < primitive_string STRING, primitive_floating FLOATING >
inline STRING& copy(STRING& string, const FLOATING& number)
{

	string.format("%f", (::f64)number);

	return string;

}









//template < typename TYPE >
//inline ::string as_string(const TYPE& t)
//{
//
//	::string str;
//
//	::copy(str, t);
//
//	return ::move(str);
//
//}


template < primitive_number NUMBER >
inline string as_string(NUMBER number, const ::ansi_character * pszFormat)
{

   ::string str;

   str.format(pszFormat, number);

   return ::move(str);

}


template < primitive_unsigned UNSIGNED >
inline inline_number_string as_string(UNSIGNED u, int radix = 10, enum_digit_case edigitcase = e_digit_case_lower)
{

   inline_number_string numberstring;

   __utosz(u, numberstring.m_end, radix, edigitcase);

   return numberstring;

}


template < primitive_signed SIGNED >
inline inline_number_string as_string(SIGNED i, int radix = 10, enum_digit_case edigitcase = e_digit_case_lower)
{

   inline_number_string numberstring;

   __itosz(i, numberstring.m_end, radix, edigitcase);

   return numberstring;

}


//   inline_number_string numberstring;
//
//   __i64toansi(i, numberstring, iRadix, edigitcase, numberstring.m_iLength);
//
//   return numberstring;
//
//}


template < primitive_floating FLOATING, int len >
inline ::string as_string(FLOATING f, const ::ansi_character * pszFormat = "%f")
{

   ::string str;

   str.format(pszFormat, f);

   return str;

}



