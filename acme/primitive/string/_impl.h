#pragma once


#include "_string_range_impl.h"
#include "_impl_string_base.h"

#include "c/_impl.h"
#include "sz/_impl.h"

#include "unicode_impl.h"


#include "_u32hash.h"
#include "_conv.h"
#include "hex.h"


CLASS_DECL_ACME i64 strtoi(const ::scoped_string & scopedstr);
CLASS_DECL_ACME i64 strtoi(const ::wide_character * psz);


namespace file
{


   class str;


} // namespace file


#if defined(__APPLE)

#define noexcept

#endif

//
//template <typename T>
//inline T FormatArgument(T value) noexcept
//{
//
//   return value;
//
//}
//
//
//#ifdef WINDOWS
//inline ::u32 _gen_GetConversionACP()
//{
//
//   //return CP_UTF8;
//   return CodePageUtf8;
//
//}
//#endif


class fixed_alloc_array;


template < >
inline ::u32hash u32_hash < const ansi_string & >(const ansi_string & ansistr)
{

   return u32_hash(ansistr.c_str());

}


template < >
inline ::u32hash u32_hash < const wide_string & >(const wide_string & widestr)
{

   return u32_hash(widestr.c_str());

}


//inline const char * FormatArgument(const string & value) noexcept { return value.c_str(); }


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


template < primitive_integral INTEGRAL >
inline inline_number_string as_string(INTEGRAL i, int radix, enum_digit_case edigitcase)
{

   inline_number_string numberstring;

   __tosz(i, numberstring.m_end, radix, edigitcase);

   return numberstring;

}


// template < primitive_integral SIGNED >
// inline inline_number_string as_string(SIGNED i, int radix, enum_digit_case edigitcase)
// {

//   inline_number_string numberstring;

//   __tosz(i, numberstring.m_end, radix, edigitcase);

//   return numberstring;

// }


//   inline_number_string numberstring;

//   __i64toansi(i, numberstring, iRadix, edigitcase, numberstring.m_iLength);

//   return numberstring;

// }


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


template < >
inline ::u32hash u32_hash < scoped_ansi_string >(scoped_ansi_string scopedstr) {

   return _scoped_string_u32_hash((::scoped_string_base<const ::ansi_character *>) scopedstr);

}


template < >
inline ::u32hash u32_hash < scoped_wd16_string >(scoped_wd16_string scopedstr) {

   return _scoped_string_u32_hash((::scoped_string_base<const ::wd16_character *>) scopedstr);

}


template < >
inline ::u32hash u32_hash < scoped_wd32_string >(scoped_wd32_string scopedstr) {

   return _scoped_string_u32_hash((::scoped_string_base<const ::wd32_character *>) scopedstr);

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
inline bool const_string_range < ITERATOR_TYPE > ::operator==(const ::ansi_string &str) const
{

   return this->equals(string_base(str));

}

template < typename ITERATOR_TYPE >
inline bool const_string_range < ITERATOR_TYPE > ::operator==(const ::wd16_string &str) const { return this->equals(string_base(str)); }

template < typename ITERATOR_TYPE >
inline bool const_string_range < ITERATOR_TYPE > ::operator==(const ::wd32_string &str) const { return this->equals(string_base(str)); }



template<typename ITERATOR_TYPE>
::count string_range < ITERATOR_TYPE>::consume(bool(*character_is_function)(CHARACTER character), strsize minimum_count)
{

   auto c = this->begins_count(character_is_function);

   if (c < minimum_count)
   {

      throw_parsing_exception("didn't reached minimum count of characters meet character_is_function requirements");

   }

   this->begin() += c;

   return c;

}


// Convert the string_base < ITERATOR_TYPE > to lowercase
template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > const_string_range < ITERATOR_TYPE > ::lowered() const
{

   string_base < ITERATOR_TYPE > str(*this);

   str.make_lower();

   return str;

}



template < typename ITERATOR_TYPE >
::string_base < ITERATOR_TYPE > string_range < ITERATOR_TYPE > ::consume_quoted_value()
{

   string_base < ITERATOR_TYPE > str;

   auto & range = *this;

   auto pszStart = this->m_begin;

   if (*pszStart != '\"' && *pszStart != '\'')
   {

      throw_parsing_exception("Quote character is required here");

      return str;

   }

   char quoting_character = *this->m_begin;

   this->m_begin++;

   const typename ::string_range < ITERATOR_TYPE>::CHARACTER * pszValueStart = this->m_begin;

   while (*this->m_begin != quoting_character)
   {

   skip:

      unicode_increment(this->m_begin);

      if (this->is_empty() || *this->m_begin == '\0')
      {

         throw_parsing_exception("Quote character is required here, premature end");

         return str;

      }

      if (*this->m_begin == '\\')
      {

         unicode_increment(this->m_begin);

         if (this->is_empty())
         {

            throw_parsing_exception("Quote character is required here, premature end");

            return str;

         }

         goto skip;

      }

   }

   str.assign(pszValueStart, this->m_begin - pszValueStart);

   this->m_begin++;

   auto p = str.get_string_buffer();

   auto pend = p + str.length();

   while (*p)
   {

      if (*p == '\\')
      {

         if (p[1] == '\\')
         {

            memmove(p, p + 1, pend - p);
         }
         else if (p[1] == '\"')
         {

            memmove(p, p + 1, pend - p);

         }

      }

      p++;

   }

   str.release_string_buffer();

   return str;

}


template < typename ITERATOR_TYPE >
::string_base < ITERATOR_TYPE > string_range < ITERATOR_TYPE > ::consume_token_until_any_character_in(const SCOPED_STRING & scopedstrCharacters, bool bReturnSeparator, bool bSkipAnyCharactersIn)
{
          
   auto p1 = this->find_first_character_in(scopedstrCharacters);
          
   if(!p1)
   {
      
      auto range = (*this)();
             
      this->m_begin = this->m_end;
      
      return range;
             
   }
   
   if(bSkipAnyCharactersIn)
   {
      
      auto p2 = (*this)(p1).skip_any_character_in(scopedstrCharacters);
      
      if(bReturnSeparator)
      {
         
         auto range = string_range < ITERATOR_TYPE >(this->m_begin, p2);
         
         this->m_begin = p2;
         
         return range;
         
      }
         
      auto range = string_range < ITERATOR_TYPE >(this->m_begin, p1);
      
      this->m_begin = p2;
      
      return range;
      
   }
      
   if(bReturnSeparator)
   {
      
      auto range = string_range < ITERATOR_TYPE >(this->m_begin, p1 + 1);
      
      this->m_begin = p1 + 1;
      
      return range;
      
   }
      
   auto range = string_range < ITERATOR_TYPE >(this->m_begin, p1);
   
   this->m_begin = p1 + 1;
   
   return range;

}

//
//template < >
//inline ::u32hash u32_hash < const ansi_string & >(const ansi_string & ansistr)
//{
//
//   return u32_hash < const ::ansi_character * >(ansistr.c_str());
//
//}
//
//
//template < >
//inline ::u32hash u32_hash < const wide_string & >(const wide_string & widestr)
//{
//
//   return u32_hash < const ::wide_character * >(widestr.c_str());
//
//}


template < >
inline ::u32hash u32_hash < ansi_string >(ansi_string ansistr)
{

   return u32_hash < const ansi_string & >(ansistr);

}


template < >
inline ::u32hash u32_hash < wide_string >(wide_string widestr)
{

   return u32_hash < const wide_string & >(widestr);

}




template < typename ITERATOR_TYPE >
void string_range < ITERATOR_TYPE >::consume(const char * pszToConsume)
{

   while(*pszToConsume)
   {
      
      if (*this->m_begin != *pszToConsume)
      {

         throw_parsing_exception("Name does not match expected");

      }

      this->m_begin++;

      pszToConsume++;

   }

}


template < typename ITERATOR_TYPE >
bool string_range < ITERATOR_TYPE >::begins_consume(const ::scoped_string & scopedstr)
{

   if (!this->begins(scopedstr))
   {

      return false;

   }

   this->m_begin += scopedstr.size();

   return true;

}


template < typename ITERATOR_TYPE >
bool string_range < ITERATOR_TYPE >::case_insensitive_begins_eat(const ::scoped_string & scopedstr)
{

   if (!this->case_insensitive_begins(scopedstr))
   {

      return false;

   }

   this->m_begin += scopedstr.size();

   return true;

}


template < typename ITERATOR_TYPE >
bool string_range < ITERATOR_TYPE >::case_insensitive_ends_eat(const ::scoped_string & scopedstr)
{

   if (!this->case_insensitive_ends(scopedstr))
   {

      return false;

   }

   this->m_end -= scopedstr.size();

   return true;

}


//
//template < typename ITERATOR_TYPE >
//void string_base < ITERATOR_TYPE >::consume(const ::ansi_character * psz)
//{
//
//   for (idx = 0; idx < len; idx++)
//   {
//      if (ra[idx] != psz[idx])
//      {
//         throw ::parsing_exception("Name does not match expected");
//         break;
//      }
//   }
//
//   pszParse += len;
//
//}


template < typename ITERATOR_TYPE >
void string_range < ITERATOR_TYPE >::consume(const ::scoped_string & scopedstr)
{

   auto rangeToConsume = scopedstr();

   while(rangeToConsume.has_char())
   {

      if(this->is_empty() || (*this->m_begin != *rangeToConsume.m_begin))
      {

         throw_parsing_exception("Name does not match expected");

         break;

      }

      rangeToConsume.m_begin++;

      this->m_begin++;

   }

}


//template < typename ITERATOR_TYPE >
//void string_range < ITERATOR_TYPE >::consume_spaces(::count iMinimumCount)
//{
//
//   i32 i = 0;
//
//   while (unicode_is_whitespace(this->m_begin))
//   {
//
//      unicode_increment(this->m_begin);
//
//      i++;
//
//   }
//
//   if (i < iMinimumCount)
//   {
//
//      throw ::parsing_exception("At least "+ ::as_string(iMinimumCount) + " space(s) is(are) required. Found " + ::as_string(i) + " whitespace(s).");
//
//   }
//
//}


//u64 str::consume_natural(u64 uMax, u64 uMin)
//{
//
//   auto u = consume_natural(this->m_begin, uMax, uMin);
//
//   return u;
//
//}


template < typename ITERATOR_TYPE >
u64 string_range < ITERATOR_TYPE >::consume_natural(u64 uMax, u64 uMin)
{

   if (uMax < uMin)
   {

      throw ::exception(error_bad_argument, "maximum should be greater than minimum");

   }

   auto pszStart = this->m_begin;

   i32 i = 0;

   u64 u;

   while (unicode_is_digit(this->m_begin))
   {

      unicode_increment(this->m_begin);

      i++;

   }

   if (this->m_begin == pszStart)
   {

      throw_parsing_exception("empty natural found");

   }

   u = ::as_u32({ pszStart, this->m_begin - pszStart });

   if (u < uMin)
   {

      throw_parsing_exception("natural less than minimum");

   }
   else if (u > uMax)
   {

      throw_parsing_exception("natural greater than maximum");

   }

   return u;

}

//
//template < typename ITERATOR_TYPE >
//void string_base < ITERATOR_TYPE >::consume_spaces(::count iMinimumCount)
//{
//
//   i32 i = 0;
//
//   while (unicode_is_whitespace(this->m_begin))
//   {
//
//      unicode_increment(this->m_begin);
//
//      if (this->m_begin > this->m_end)
//      {
//
//         throw ::parsing_exception("premature end");
//
//         break;
//
//      }
//
//      i++;
//
//   }
//
//   if (i < iMinimumCount)
//   {
//
//      throw ::parsing_exception("At least " + ::as_string(iMinimumCount) + " space(s) is(are) required");
//
//   }
//
//}


//template < typename ITERATOR_TYPE >
//::string_base < ITERATOR_TYPE > string_range < ITERATOR_TYPE >::consume_non_spaces(const ::ansi_character *& psz)
//{
//
//   return consume_non_spaces(psz, psz + strlen(psz));
//
//}
//


template < typename ITERATOR_TYPE >
::string_base < ITERATOR_TYPE > string_range < ITERATOR_TYPE >::consume_non_spaces()
{

   auto pszStart = this->m_begin;

   while (!unicode_is_whitespace(this->m_begin))
   {
      
      unicode_increment(this->m_begin);

      if (this->is_empty())
      {

         break;

      }

   }

   return { pszStart, this->m_begin - pszStart };

}


template < typename ITERATOR_TYPE >
::string_base < ITERATOR_TYPE > string_range < ITERATOR_TYPE >::consume_hex()
{
   
   auto pszStart = this->m_begin;

   while (this->is_empty())
   {

      ::i32 len;
      
      i64 i = unicode_index_length(this->m_begin, len);

      if ((i >= '0' && i <= '9') || (i >= 'a' && i <= 'f') || (i >= 'A' && i <= 'F'))
      {

         this->m_begin += len;

      }
      else
      {

         break;
      
      }

   }

   if (this->m_begin == pszStart)
   {

      throw_parsing_exception("no hex consumed");
      
      return "";

   }
   
   return { pszStart, this->m_begin - pszStart };

}


template < typename ITERATOR_TYPE >
::string_base < ITERATOR_TYPE > string_range < ITERATOR_TYPE >::consume_nc_name()
{
   
   auto pszStart = this->m_begin;
   
   if (this->is_empty() || !unicode_is_letter(this->m_begin))
   {

      throw_parsing_exception("NCName required here");

      return "";

   }
   
   do
   {

      unicode_increment(this->m_begin);

   } while(this->has_char() &&
           (unicode_is_letter_or_digit(this->m_begin)
            || *this->m_begin == '_' || *this->m_begin == '-'));
   
   return { pszStart, this->m_begin - pszStart };

}


//string consume_quoted_value(const char * & pszParse)
//{

//   ::str::utf8_char utf8char;

//   auto psz = pszParse;
//   utf8char.parse(psz); // quote character
//   if(utf8char.m_chLen != 1)
//   {
//      throw ::parsing_exception("Quote character is required here");
//      return "";
//   }
//   char strUtf8Char = utf8char.m_sz[0];
//   if(strUtf8Char != '\"' && strUtf8Char != '\\')
//   {
//      throw ::parsing_exception("Quote character is required here");
//      return "";
//   }
//   int iPos = utf8char.m_chLen;
//   string str;
//   int iPosStart = iPos;
//   while(true)
//   {
//      iPos += utf8char.parse(&psz[iPos]);
//      if(utf8char.m_chLen <= 0)
//      {
//         throw ::parsing_exception("Quote character is required here, premature end");
//         return "";
//      }
//      if(utf8char.m_chLen == 1 && utf8char.m_sz[0] == strUtf8Char)
//         break;

//   }
//   str = string(&psz[iPosStart], iPos - iPosStart - 1);
//   pszParse = &psz[iPos];
//   return str;
//}




//template < typename ITERATOR_TYPE >
// void string_base < ITERATOR_TYPE >::no_escape_consume_quoted_value(char ** ppsz, strsize & iBufferSize)
//{
//
//   const ::ansi_character * pszStart = this->m_begin;
//
//   if (*pszStart != '\"' && *pszStart != '\\')
//   {
//
//      throw ::parsing_exception("Quote character is required here");
//
//      return;
//
//   }
//
//   char quoting_character = *this->m_begin;
//
//   this->m_begin++;
//
//   const ::ansi_character * pszValueStart = this->m_begin;
//
//   while (*this->m_begin != quoting_character)
//   {
//
//      unicode_increment(this->m_begin);
//
//      if (this->is_empty())
//      {
//
//         throw ::parsing_exception("Quote character is required here, premature end");
//
//         return;
//
//      }
//
//   }
//
//   strsize iNewBufferSize = this->m_begin - pszValueStart;
//
//   if (iNewBufferSize > iBufferSize)
//   {
//
//      *ppsz = (char *)memory_allocate(iNewBufferSize + 1);
//
//   }
//
//   ansi_count_copy(*ppsz, pszValueStart, iNewBufferSize);
//
//   (*ppsz)[iNewBufferSize] = '\0';
//
//   iBufferSize = iNewBufferSize;
//
//   this->m_begin++;
//
//}


template < typename ITERATOR_TYPE >
::string_base < ITERATOR_TYPE > string_range < ITERATOR_TYPE >::no_escape_consume_quoted_value()
{

   const ::ansi_character * pszStart = this->m_begin;

   no_escape_skip_quoted_value();

   return { pszStart + 1, this->m_begin - pszStart - 2 };

}


template < typename ITERATOR_TYPE >
void string_range < ITERATOR_TYPE >::no_escape_skip_quoted_value()
{

   if (*this->m_begin != '\"' && *this->m_begin != '\\')
   {

      throw_parsing_exception("Quote character is required here");

      return;

   }

   char quoting_character = *this->m_begin;

   this->m_begin++;

   while (*this->m_begin != quoting_character)
   {

      unicode_increment(this->m_begin);

      if (this->is_empty())
      {

         throw_parsing_exception("Quote character is required here, premature end");

         return;

      }

   }

   this->m_begin++;

}


template < typename ITERATOR_TYPE >
::string_base < ITERATOR_TYPE > string_range < ITERATOR_TYPE >::consume_quoted_value_ex()
{

   string str;

   this->_consume_quoted_value_ex<true>(&str);

   return str;

}


template < typename ITERATOR_TYPE >
void string_range < ITERATOR_TYPE >::skip_quoted_value_ex()
{
   
   this->_consume_quoted_value_ex<false>(nullptr);

}


template < typename ITERATOR_TYPE >
::string_base < ITERATOR_TYPE > string_range < ITERATOR_TYPE >::consume_spaced_value()
{

   this->consume_spaces(0);

   if (this->is_empty())
   {

      return {};

   }

   auto pszStart = this->m_begin;

   while (this->has_char() && !ansi_char_isspace(*this->m_begin))
   {
      
      this->m_begin++;

   }

   if (this->m_begin == pszStart)
   {

      throw_parsing_exception("No spaced value to consumer");

   }

   return { pszStart, this->m_begin - pszStart };

}


//template < typename ITERATOR_TYPE >
//::string_base < ITERATOR_TYPE > string_range < ITERATOR_TYPE >::consume_spaced_value(const char *& psz)
//{
//
//   string str(psz);
//
//   strsize iOldLen = str.length();
//
//   string strResult = consume_spaced_value(str);
//
//   psz += iOldLen - str.length();
//
//   return strResult;
//
//}

//template < typename ITERATOR_TYPE >
//::string_base < ITERATOR_TYPE > string_range < ITERATOR_TYPE >::consume_spaced_value(const char *& psz, const ::ansi_character * pszEnd)
//{
//
//   string str(psz, pszEnd - psz);
//
//   strsize iOldLen = str.length();
//
//   string strResult = consume_spaced_value(str);
//
//   psz += iOldLen - str.length();
//
//   return strResult;
//
//}


template < typename ITERATOR_TYPE >
::string_base < ITERATOR_TYPE > string_range < ITERATOR_TYPE >::consume_command_line_argument()
{

   this->consume_spaces(0);

   if (*this->m_begin == '\"' || *this->m_begin == '\'')
   {

      return this->consume_quoted_value();

   }
   else
   {

      return this->consume_spaced_value();

   }

}


template < typename ITERATOR_TYPE >
void string_range < ITERATOR_TYPE >::consume_until_any_character_in(const ::scoped_string & scopedstr)
{

   this->m_begin = this->find_first_character_in(scopedstr);

   if (not_found(this->m_begin))
   {

      throw_parsing_exception("Not found any character in \"" + scopedstr + "\"");

   }

}


//template < typename ITERATOR_TYPE >
//::string_base < ITERATOR_TYPE > string_range < ITERATOR_TYPE >::consume_command_line_argument(const char *& psz)
//{
//
//   string str(psz);
//
//   strsize iOldLen = str.length();
//
//   string strResult = consume_command_line_argument(str);
//
//   psz += iOldLen - str.length();
//
//   return strResult;
//
//}
//
//template < typename ITERATOR_TYPE >
//::string_base < ITERATOR_TYPE > string_range < ITERATOR_TYPE >::consume_command_line_argument(const char *& psz, const ::ansi_character * pszEnd)
//{
//
//   string str(psz, pszEnd - psz);
//
//   strsize iOldLen = str.length();
//
//   string strResult = consume_command_line_argument(str);
//
//   psz += iOldLen - str.length();
//
//   return strResult;
//
//}


template < typename ITERATOR_TYPE >
::string_base < ITERATOR_TYPE > string_range < ITERATOR_TYPE >::consume_c_quoted_value()
{

   auto pszStart = this->m_begin;

   if (*this->m_begin != '\"' && *this->m_begin != '\\')
   {

      throw_parsing_exception("Quote character is required here");

      return "";

   }

   auto quoting_character = this->consume_utf8_char();

   STRING_RANGE rangeCurrentChar;

   STRING_BASE str;

   STRING_RANGE rangePreviousChar;

   while (this->has_char())
   {

//      unicode_increment(this->m_begin);

      rangePreviousChar = rangeCurrentChar;

      rangeCurrentChar = this->consume_utf8_char();

      //string str = utf8_to_unicode(qc2);

      if (rangeCurrentChar.is_empty())
      {

         throw_parsing_exception("Quote character is required here, premature end");

         return "";

      }

      if (rangePreviousChar == "\\")
      {

         str += rangeCurrentChar;

         rangeCurrentChar.m_begin = nullptr;
         rangeCurrentChar.m_end = nullptr;

      }
      else if (rangeCurrentChar == "\\")
      {

      }
      else
      {

         if (rangeCurrentChar == quoting_character)
         {

            break;

         }

         str += rangeCurrentChar;

      }

   }

   this->consume_utf8_char();
   //unicode_increment(this->m_begin);

   return str;

}


template < typename ITERATOR_TYPE >
template < bool bWriteOutput >
void string_range < ITERATOR_TYPE >::_consume_quoted_value_ex(string * pstrOut)
{

   char quoting_character = *this->m_begin;

   if (quoting_character != '\"' && quoting_character != '\'')
   {

      throw_parsing_exception("Quote character is required here, premature end");

      return;

   }

   this->m_begin++;

   const ::ansi_character * pszNext = this->m_begin;

   while (true)
   {

      pszNext = unicode_next(this->m_begin);

      if (pszNext > this->m_end)
      {

         throw_parsing_exception("Quote character is required here, premature end");

         if (bWriteOutput)
         {

            *pstrOut = "";

         }
         
      }

      if (*this->m_begin == '\0')
      {

         throw_parsing_exception("Quote character is required here, premature end");

         if (bWriteOutput)
         {

            *pstrOut = "";

         }

      }
      else if (*this->m_begin == quoting_character)
      {

         this->m_begin++;

         break;

      }
      else if (*this->m_begin == '\\')
      {

         this->m_begin = pszNext;

         pszNext = unicode_next(this->m_begin);

         if (pszNext > this->m_end)
         {

            throw_parsing_exception("Quote character is required here, premature end");

            if (bWriteOutput)
            {

               *pstrOut = "";

            }

         }

         if (*this->m_begin == 'n')
         {
            
            if (bWriteOutput)
            {

               pstrOut->append_character('\n');

            }

         }
         else if (*this->m_begin == 't')
         {
            
            if (bWriteOutput)
            {

               pstrOut->append_character('\t');

            }

         }
         else if (*this->m_begin == 'r')
         {

            if (bWriteOutput)
            {

               pstrOut->append_character('\r');

            }

         }
         else if (*this->m_begin == 'u')
         {

            this->m_begin++;

            u16 u16a[2];

            u16a[0] = ::hex::parse_u16_exc(*this);

            if (utf16_is_1st_surrogate(u16a[0]))
            {

               if (*this->m_begin != '\\')
               {

                  throw_parsing_exception("expect back slash here (for low surrogate)");

               }

               this->m_begin++;

               if (*this->m_begin != 'u' && *this->m_begin != 'U')
               {

                  throw_parsing_exception("expect 'u' character here (for low surrogate)");

               }

               this->m_begin++;

               u16a[1] = ::hex::parse_u16_exc(*this);

               if (!utf16_is_2nd_surrogate(u16a[1]))
               {

                  throw_parsing_exception("expect low surrogate");

               }
               else
               {

                  if (bWriteOutput)
                  {

                     ::wd32_character uni = (::wd32_character)decode_utf16_pair(u16a);
                  
                     string strUtf8 = wd32_to_ansi_str(&uni, 1);

                     pstrOut->append(strUtf8);

                  }

               }

            }
            else
            {

               if (bWriteOutput)
               {

                  ::wd32_character uni = u16a[0];
                  
                  string strUtf8 = wd32_to_ansi_str(&uni, 1);

                  pstrOut->append(strUtf8);

               }

            }
            
            pszNext = this->m_begin;

         }
         else if (*this->m_begin == '\"')
         {

            if (bWriteOutput)
            {

               pstrOut->append_character('\"');

            }

         }
         else
         {

            if (bWriteOutput)
            {

               pstrOut->append(this->m_begin, pszNext - this->m_begin);
             
            }

         }

      }
      else
      {

         if (bWriteOutput)
         {

            pstrOut->append(this->m_begin, pszNext - this->m_begin);

         }

      }

      this->m_begin = pszNext;

   }

}


template < typename ITERATOR_TYPE >
bool const_string_range < ITERATOR_TYPE >::xml_is_comment() const
{

   return this->size() > 3 && this->m_begin[0] == '<' && this->m_begin[1] == '!' && this->m_begin[2] == '-';

}


template < typename ITERATOR_TYPE >
::string_base < ITERATOR_TYPE > string_range < ITERATOR_TYPE >::xml_consume_comment()
{

   this->consume("<!--");

   auto pszStart = this->m_begin;

   while (this->m_begin[0] != '-' || this->m_begin[1] != '-' || this->m_begin[2] != '>')
   {

      if (this->is_empty() || *this->m_begin == '\0')
      {

         break;

      }

      unicode_increment(this->m_begin);

   }

   this->m_begin += 3;

   return { pszStart, this->m_begin - pszStart - 3 };

}

constexpr u32 decode_utf16_pair(u16 * units)
{
   u32 code;
   ASSERT(utf16_is_1st_surrogate(units[0]));
   ASSERT(utf16_is_2nd_surrogate(units[1]));
   code = 0x10000;
   code += (units[0] & 0x03FF) << 10;
   code += (units[1] & 0x03FF);
   return code;
}



//========================================================
// Name   : _tcsechr
// Desc   : similar with strchr with escape process
// Param  : escape - will be escape character
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
template < typename ITERATOR_TYPE >
void string_range < ITERATOR_TYPE >::escape_skip_to_character(i32 ch, i32 escape)
{

  while (this->has_char() && *this->m_begin)
  {

     if (escape != 0 && *this->m_begin == escape)
        this->m_begin++;
     else
        if (*this->m_begin == ch)
           return;
     this->m_begin++;
  }
  //return pch;
}


//========================================================
  // Name   : _tcsepbrk
  // Desc   : similar with ansi_scan with escape process
  // Param  : escape - will be escape character
  // Return :
  //--------------------------------------------------------
  // Coder    Date                      Desc
  // bro      2002-10-29
  //========================================================
//========================================================
  // Name   : _tcsepbrk
  // Desc   : similar with ansi_scan with escape process
  // Param  : escape - will be escape character
  // Return :
  //--------------------------------------------------------
  // Coder    Date                      Desc
  // bro      2002-10-29
  //========================================================
template < typename ITERATOR_TYPE >
void string_range < ITERATOR_TYPE >::escape_skip_to_first_character_in(const char * chset, i32 escape)
{
  
  const char * prev_escape = nullptr;

  while (this->has_char() && *this->m_begin)
  {
     
     if (escape != 0 && *this->m_begin == escape && prev_escape == nullptr)
     {

        prev_escape = this->m_begin;

     }
     else
     {
        
        prev_escape = nullptr;

        if (strchr(chset, *this->m_begin))
        {
           return;

        }

     }

     this->m_begin++;

  }
  
}
//========================================================
// Name   : _tcsenicmp
// Desc   : similar with ansi_count_compare_ci with escape process
// Param  : escape - will be escape character
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
 template < typename ITERATOR_TYPE >
::std::strong_ordering const_string_range < ITERATOR_TYPE >::escape_case_insensitive_count_order(const ::scoped_string & scopedstr, i32 escape) const
{

  auto rangeCompare = scopedstr();

  ::std::strong_ordering order = ::std::strong_ordering::equal;

  const char * prev_escape = nullptr;

  auto r = (*this)();

  while (r.has_char() && *r.m_begin && rangeCompare.has_char())
  {
     
     if (escape != 0 && *r.m_begin == escape && prev_escape == nullptr)
     {

        prev_escape = r.m_begin;

     }
     else
     {

        prev_escape = nullptr;

        order = tolower(*r.m_begin) <=> tolower(*rangeCompare.m_begin);

        if (order != 0)
        {

           break;

        }

        rangeCompare.m_begin++;

     }

     r.m_begin++;

  }

  return order;

}


//========================================================
// Name   : _tcsenistr
// Desc   : similar with _tcsistr with escape process
// Param  : escape - will be escape character
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
template < typename ITERATOR_TYPE >
void string_range < ITERATOR_TYPE >::escape_case_insensitive_skip_to(const ::scoped_string & scopedstr, i32 escape)
{
  
  const char * prev_escape = nullptr;
   
  while (this->has_char() && *this->m_begin)
  {

     if (escape != 0 && *this->m_begin == escape && prev_escape == nullptr)
     {

        prev_escape = this->m_begin;

     }
     else
     {
        
        prev_escape = nullptr;
        
        if (this->escape_case_insensitive_count_order(scopedstr, escape) == 0)
        {

           return;

        }

     }
     
     this->m_begin++;

  }
  
}




//========================================================
// Name   : _tcsecpy
// Desc   : similar with _tcscpy with escape process
// Param  : escape - will be escape character
// Return :
//--------------------------------------------------------
// Coder    Date                      Desc
// bro      2002-10-29
//========================================================
template < typename ITERATOR_TYPE >
void mutable_string_range < ITERATOR_TYPE >::escape_copy(char escape, const ::const_ansi_range & rangeSource)
{

   auto pTarget = this->m_begin;

   auto pSource = this->m_begin;

   bool bEscaping = false;

   while(pSource < rangeSource.m_end && pTarget < this->m_end)
   {

      if(bEscaping)
      {

         bEscaping = false;

         *pTarget++ = *pSource;

      }
      else if(*pSource == escape)
      {

         bEscaping = true;

      }
      else
      {

         *pTarget++ = *pSource;

      }

      pSource++;

   }

   *pTarget = '\0';

   this->m_end = pTarget;

}


template < typename ITERATOR_TYPE >
typename const_string_range < ITERATOR_TYPE >::THIS_RANGE const_string_range < ITERATOR_TYPE >::get_utf8_char() const
{

   auto pszStart = this->m_begin;

   auto pszNext = unicode_next(pszStart);

   return { pszStart, minimum(pszNext, this->m_end) };

}



template < typename ITERATOR_TYPE >
typename string_range < ITERATOR_TYPE >::THIS_RANGE string_range < ITERATOR_TYPE >::consume_utf8_char()
{

   auto pszStart = this->m_begin;

   this->m_begin = unicode_next(pszStart);

   return { pszStart, minimum(this->m_begin, this->m_end) };

}
