#pragma once


#include "_string_range_impl.h"
#include "_impl_string_base.h"

#include "c/_impl.h"
#include "sz/_impl.h"

#include "unicode_impl.h"


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


//#include "_string_base_impl.h"


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
//	return ::transfer(str);
//
//}


template < primitive_number NUMBER >
inline string as_string(NUMBER number, const ::ansi_character * pszFormat)
{

   ::string str;

   str.format(pszFormat, number);

   return ::transfer(str);

}


template < primitive_unsigned UNSIGNED >
inline inline_number_string as_string(UNSIGNED u, int radix, enum_digit_case edigitcase)
{

   inline_number_string numberstring;

   __utosz(u, numberstring.m_end, radix, edigitcase);

   return numberstring;

}


template < primitive_signed SIGNED >
inline inline_number_string as_string(SIGNED i, int radix, enum_digit_case edigitcase)
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


template < primitive_floating FLOATING >
inline ::string as_string(FLOATING f, const ::ansi_character * pszFormat)
{

   ::string str;

   str.format(pszFormat, f);

   return str;

}


template < character_range CHARACTER_RANGE >
payload::payload(const CHARACTER_RANGE & range) :
   payload(e_no_initialize)
{

   m_etype = e_type_ansi_range;
   zero(m_all);
   m_str = range;

}


template<>
inline u32hash u32_hash<scoped_ansi_string>(scoped_ansi_string scopedstr) {

   return _scoped_string_u32_hash<::ansi_character>((::scoped_string_base<const ::ansi_character *>) scopedstr);

}


template<>
inline u32hash u32_hash<scoped_wd16_string>(scoped_wd16_string scopedstr) {

   return _scoped_string_u32_hash<::wd16_character>((::scoped_string_base<const ::wd16_character *>) scopedstr);

}


template<>
inline u32hash u32_hash<scoped_wd32_string>(scoped_wd32_string scopedstr) {

   return _scoped_string_u32_hash<::wd32_character>((::scoped_string_base<const ::wd32_character *>) scopedstr);

}


template < strsize n >
inline bool atom::operator == (const ::ansi_character (&cha)[n]) const
{

   return *this == ::scoped_string(cha);

}


template < strsize n >
inline ::std::strong_ordering atom::operator <=> (const ::ansi_character (&cha)[n]) const
{

   return *this <=> ::scoped_string(cha);

}


namespace file
{


    inline path::path(const ::scoped_string & scopedstr, enum_path epath, int iDir, bool bNormalizePath, i64 iSize) :
            path(::ansi_string(scopedstr), epath, iDir, bNormalizePath, iSize)
    {


    }


    inline path& path::operator /= (const ::scoped_string & scopedstr)
    {

       return *this = (*this / scopedstr);

    }


    inline path path::operator * (const ::scoped_string & scopedstr) const { return operator * (::file::path(scopedstr)); }


    inline path& path::operator *= (const ::scoped_string & scopedstr) { return operator *= (::file::path(scopedstr)); }


    inline bool path::operator == (const ::scoped_string & scopedstr) const
    {

       return operator == (string(scopedstr));

    }


    inline bool path::operator != (const ::scoped_string & scopedstr) const
    {

       return operator != (string(scopedstr));

    }




} // namespace file






template < typename TYPE, enum_type m_etypeContainer >
inline void implode(const numeric_array < TYPE, m_etypeContainer > & a, string & str, const ::scoped_string & scopedstrSeparator, ::index start, ::count count)
{
   
   if(start < 0)
   {
      start += a.get_size();
   }
   ::index last;
   if(count < 0)
   {
      last = a.get_size() + count;
   }
   else
   {
      last = start + count - 1;
   }
   if(start <= last)
   {

      ::index i = start;
      
      ::copy(str, a.element_at(i));

      i++;
      for(; i <= last; i++)
      {
         str += scopedstrSeparator + as_string(a.element_at(i));
      }
   }
   else
   {

      str.empty();

   }


}


template < typename TYPE, enum_type m_etypeContainer >
inline string implode(const numeric_array < TYPE, m_etypeContainer > & a,const ::scoped_string & scopedstrSeparator, ::index start, ::count count)
{
   
   string str;

   implode(a, str, scopedstrSeparator, start, count);

   return str;

}


template < typename TYPE, ::enum_type m_etypeContainer >
string surround_and_implode(const numeric_array < TYPE, m_etypeContainer > & a, const ::scoped_string & scopedstrSeparator, const ::scoped_string & scopedstrPrefix, const ::scoped_string & scopedstrSuffix, ::index iStart, ::count iCount)
{
   string str;
   string strSeparator(scopedstrSeparator);
   string strPrefix(scopedstrPrefix);
   string strSuffix(scopedstrSuffix);
   ::index iEnd;
   if(iStart < 0)
      iStart = a.get_size() + iStart;
   if(iCount < 0)
      iEnd = a.get_size() + iCount;
   else
      iEnd = iStart + iCount - 1;
   if(iStart <= iEnd)
   {
      ::index i = iStart;
      str = strPrefix + as_string(a.element_at(i)) + strSuffix;
      i++;
      for(; i <= iEnd; i++)
      {
         str += strSeparator + strPrefix + as_string(a.element_at(i)) + strSuffix;
      }
   }
   return str;
}


template < typename ITERATOR_TYPE >
inline bool string_range < ITERATOR_TYPE > ::operator==(const ::ansi_string &str) const
{

   return this->equals(string_base(str));

}

template < typename ITERATOR_TYPE >
inline bool string_range < ITERATOR_TYPE > ::operator==(const ::wd16_string &str) const { return this->equals(string_base(str)); }

template < typename ITERATOR_TYPE >
inline bool string_range < ITERATOR_TYPE > ::operator==(const ::wd32_string &str) const { return this->equals(string_base(str)); }


