// Created by camilo on 2023-02-02 02:28 <3ThomasBorregaardSorensen!!
#pragma once


/// <summary>
/// 
/// </summary>
/// <param name="psz"></param>
/// <param name="size"></param>
/// <param name="u"></param>
/// <param name="base"></param>
/// <returns>greater than 0 missing characters to represent the number or lesser than 0 unused characters to represent the n</returns>
inline int utoa_base(char* psz, size_t size, unsigned long long u, int base);

/// <summary>
/// 
/// </summary>
/// <param name="psz"></param>
/// <param name="size"></param>
/// <param name="u"></param>
/// <param name="base"></param>
/// <returns>greater than 0 missing characters to represent the number or lesser than 0 unused characters to represent the n</returns>
inline int itoa_base(char* psz, size_t size, long long i, int base);


constexpr character_count _utoa_base(char* psz, character_count size, unsigned long long u, int base)
{

   while (true)
   {

      int digit = (u % base);

      u /= base;

      if (!u)
      {

         break;

      }

      if (psz && size > 0)
      {

         *psz = __digit(digit);

      }

      size--;

   }

   return -size;

}


inline character_count utoa_base(char* psz, character_count size, unsigned long long u, int base)
{

   if (base < 2 || base > 36)
   {

      throw error_bad_argument;

      return -1;

   }

   auto res = _utoa_base(psz, size - 1, u, base);

   if (psz)
   {

      psz[minimum(size - 1, size - 1 + res)] = '\0';

   }

   return res;

}


constexpr character_count _itoa_base(char* psz, character_count size, long long i, int base)
{

   while (true)
   {

      int digit = -(i % base);

      i /= base;

      if (!i)
      {

         break;

      }

      if (size > 0)
      {

         *psz = __digit(digit);

      }

      size--;

   }

   return -size;

}


inline character_count itoa_base(char* psz, character_count size, long long i, int base)
{

   if (base < 2 || base > 36)
   {

      throw_exception(error_bad_argument);

      return -1;

   }

   if (i < 0)
   {

      *psz++ = '-';

      size--;

   }
   else
   {

      i = -i;

   }

   auto res = _itoa_base(psz, size - 1, i, base);

   if (psz)
   {

      psz[minimum(size - 1, size - 1 + res)] = '\0';

   }

   return res;

}


template < primitive_integral INTEGRAL >
inline INTEGRAL& _consume(INTEGRAL& i, ::ansi_range& range, int iBase = 10)
{

   i = 0;

   auto end = minimum(range.end(), range.begin() + maximum_digits<INTEGRAL>(iBase));

   while (range.begin() < end)
   {

      auto digit = range.defer_consume_digit(iBase);

      if (digit < 0)
      {

         throw "_string parsing error _consume";

      }

      i = digit + i * iBase;

   }

   return i;

}


template < primitive_unsigned UNSIGNED >
inline UNSIGNED & consume(UNSIGNED& u, ::ansi_range& range, int iBase = 10)
{

   return _consume(u, range, iBase);

}


template < primitive_signed SIGNED >
inline SIGNED & consume(SIGNED & s, ::ansi_range& range, int iBase = 10)
{

   bool bNegative = range.begins_eat('-');

   _consume(s, range, iBase);

   if(bNegative) s = -s;

   return s;

}


template < primitive_integral INTEGRAL >
INTEGRAL consume_integral(::ansi_range& range, int iBase = 10)
{

   INTEGRAL integral;

   consume(integral, range, iBase);

   return integral;

}


template < typename BASE_RANGE >
inline long long consume_long_long(::string_range < BASE_RANGE > & range , int iBase = 10) { return consume_integral < long long >(range, iBase); }
template < typename BASE_RANGE >
inline int consume_int(::string_range < BASE_RANGE > & range , int iBase = 10) { return consume_integral < int >(range, iBase); }
template < typename BASE_RANGE >
inline short consume_short(::string_range < BASE_RANGE > & range , int iBase = 10) { return consume_integral < short >(range, iBase); }
template < typename BASE_RANGE >
inline char consume_char(::string_range < BASE_RANGE > & range, int iBase = 10) { return consume_integral < char >(range, iBase); }


template < typename BASE_RANGE >
inline unsigned long long consume_unsigned_long_long(::string_range < BASE_RANGE >& range, int iBase = 10) { return consume_integral < unsigned long long >(range, iBase); }
template < typename BASE_RANGE >
inline unsigned int consume_unsigned_int(::string_range < BASE_RANGE >& range, int iBase = 10) { return consume_integral < unsigned int >(range, iBase); }
template < typename BASE_RANGE >
inline unsigned short consume_unsigned_short(::string_range < BASE_RANGE >& range, int iBase = 10) { return consume_integral < unsigned short >(range, iBase); }
template < typename BASE_RANGE >
inline unsigned char consume_unsigned_char(::string_range < BASE_RANGE >& range, int iBase = 10) { return consume_integral < unsigned char >(range, iBase); }

template < typename BASE_RANGE >
inline long consume_long(::string_range < BASE_RANGE >& range, int iBase = 10) { return consume_integral < long >(range, iBase); }
template < typename BASE_RANGE >
inline unsigned long consume_unsigned_long(::string_range < BASE_RANGE >& range, int iBase = 10) { return consume_integral < unsigned long >(range, iBase); }
template < typename BASE_RANGE >
inline size_t consume_size_t(::string_range < BASE_RANGE >& range, int iBase = 10) { return consume_integral < size_t >(range, iBase); }


inline long long as_long_long(const ::scoped_string& scopedstr, int iBase = 10) { auto r = scopedstr(); return consume_long_long(r, iBase); }
inline int as_int(const ::scoped_string& scopedstr, int iBase = 10) { auto r = scopedstr(); return consume_int(r, iBase); }
inline int as_short(const ::scoped_string& scopedstr, int iBase = 10) { auto r = scopedstr(); return consume_short(r, iBase); }
inline char as_char(const ::scoped_string& scopedstr, int iBase = 10) { auto r = scopedstr(); return consume_char(r, iBase); }


inline unsigned long long as_unsigned_long_long(const ::scoped_string& scopedstr, int iBase = 10) { auto r = scopedstr(); return consume_unsigned_long_long(r, iBase); }
inline unsigned int as_unsigned_int(const ::scoped_string& scopedstr, int iBase = 10) { auto r = scopedstr(); return consume_unsigned_int(r, iBase); }
inline unsigned int as_unsigned_short(const ::scoped_string& scopedstr, int iBase = 10) { auto r = scopedstr(); return consume_unsigned_short(r, iBase); }
inline unsigned char as_unsigned_char(const ::scoped_string& scopedstr, int iBase = 10) { auto r = scopedstr(); return consume_unsigned_char(r, iBase); }


inline long as_long(const ::scoped_string& scopedstr, int iBase = 10) { auto r = scopedstr(); return consume_long(r, iBase); }
inline unsigned long as_unsigned_long(const ::scoped_string& scopedstr, int iBase = 10) { auto r = scopedstr(); return consume_unsigned_long(r, iBase); }
inline size_t as_size_t(const ::scoped_string& scopedstr, int iBase = 10) { auto r = scopedstr(); return consume_size_t(r, iBase); }

//inline int as_int(const ::scoped_string & scopedstr, int iBase = 10)
//{
//
//   auto i = as_long_long(scopedstr, iBase);
//
//   if (i < INT_MIN || i > INT_MAX)
//   {
//
//      throw_exception(error_overflow);
//
//   }
//
//   return (int)i;
//
//}
//
//
//inline short as_short(const ::scoped_string & scopedstr, int iBase = 10)
//{
//
//   auto i = as_long_long(scopedstr, iBase);
//
//   if (i < SHRT_MIN || i > SHRT_MAX)
//   {
//
//      throw_exception(error_overflow);
//
//   }
//
//   return (short)i;
//
//}
//
//
//inline char as_char(const ::scoped_string & scopedstr, int iBase = 10)
//{
//
//   auto i = as_long_long(scopedstr, iBase);
//
//   if (i < CHAR_MIN || i > CHAR_MAX)
//   {
//
//      throw_exception(error_overflow);
//
//   }
//
//   return (char)i;
//
//}
//
//
//inline long as_long(const ::scoped_string & scopedstr, int iBase = 10)
//{
//
//   auto i = as_long_long(scopedstr, iBase);
//
//   if (i < LONG_MIN || i > LONG_MAX)
//   {
//
//      throw_exception(error_overflow);
//
//   }
//
//   return (long)i;
//
//}
//
//
//
//inline unsigned long long as_unsigned_long_long(const ::scoped_string & scopedstr, int iBase = 10)
//{
//
//   const_char_pointer pszEnd = nullptr;
//
//   return ansi_to_unsigned_long_long(scopedstr, &pszEnd, iBase);
//
//}
//
//
//inline unsigned int as_unsigned_int(const ::scoped_string & scopedstr, int iBase = 10)
//{
//
//   auto u = as_unsigned_long_long(scopedstr, iBase);
//
//   if (u > UINT_MAX)
//   {
//
//      throw_exception(error_overflow);
//
//   }
//
//   return (unsigned int)u;
//
//}
//
//
//inline unsigned short as_unsigned_short(const ::scoped_string & scopedstr, int iBase = 10)
//{
//
//   auto u = as_unsigned_long_long(scopedstr, iBase);
//
//   if (u > USHRT_MAX)
//   {
//
//      throw_exception(error_overflow);
//
//   }
//
//   return (unsigned short)u;
//
//}
//
//
//inline unsigned char as_unsigned_char(const ::scoped_string & scopedstr, int iBase = 10)
//{
//
//   auto u = as_unsigned_long_long(scopedstr, iBase);
//
//   if (u > UCHAR_MAX)
//   {
//
//      throw_exception(error_overflow);
//
//   }
//
//   return (unsigned char)u;
//
//}
//
//
//inline unsigned long as_unsigned_long(const ::scoped_string & scopedstr, int iBase = 10)
//{
//
//   auto u = as_unsigned_long_long(scopedstr, iBase);
//
//   if (u > ULONG_MAX)
//   {
//
//      throw_exception(error_overflow);
//
//   }
//
//   return (unsigned long)u;
//
//}
//
//
//inline size_t as_size_t(const ::scoped_string & scopedstr, int iBase = 10)
//{
//
//   auto u = as_unsigned_long_long(scopedstr, iBase);
//
//   if (u > SIZE_MAX)
//   {
//
//      throw_exception(error_overflow);
//
//   }
//
//   return (size_t)u;
//
//}



//inline double as_double(const ::scoped_string & scopedstr)
//{
//
//
//   return (size_t)u;
//
//}
//


template < primitive_integral INTEGRAL >
inline void from_string(INTEGRAL & i, const ::scoped_string & scopedstr, int iBase = 10)
{

   auto r = scopedstr();
   
   if(r.case_insensitive_equals("FALSE") ||
      r.case_insensitive_equals("OFF") ||
      r.case_insensitive_equals("NO"))
   {
      
      i = 0;
      
   }
   else if(r.case_insensitive_equals("TRUE") ||
      r.case_insensitive_equals("ON") ||
      r.case_insensitive_equals("YES"))
   {
      
      i = 1;
      
   }
   else
   {
      
      consume(i, r, iBase);
      
   }
   
}


template < primitive_floating FLOATING >
inline void from_string(FLOATING& f, const ::scoped_string& scopedstr)
{

   ::string str(scopedstr);

   f = (FLOATING) strtod(str.c_str(), nullptr);

}




//inline void fromString(const ::scoped_string& scopedstr, long& dst)
//{
//   dst = ::as_long(scopedstr);
//}
//
//inline void fromString(const ::scoped_string& scopedstr, size_t& dst)
//{
//   dst = ::as_size_t(scopedstr);
//}
//
//inline void fromString(const ::scoped_string& scopedstr, float& dst)
//{
//   dst = ::as_float(scopedstr);
//}
//
//inline void fromString(const ::scoped_string& scopedstr, ::nano2d::color& dst)
//{
//   dst = stringToColor(scopedstr);
//}


