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
inline int utoa_base(char* psz, size_t size, ::u64 u, int base);

/// <summary>
/// 
/// </summary>
/// <param name="psz"></param>
/// <param name="size"></param>
/// <param name="u"></param>
/// <param name="base"></param>
/// <returns>greater than 0 missing characters to represent the number or lesser than 0 unused characters to represent the n</returns>
inline int itoa_base(char* psz, size_t size, ::i64 i, int base);


constexpr strsize _utoa_base(char* psz, strsize size, ::u64 u, int base)
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


inline strsize utoa_base(char* psz, strsize size, ::u64 u, int base)
{

   if (base < 2 || base > 36)
   {

      throw exception(error_bad_argument);

      return -1;

   }

   auto res = _utoa_base(psz, size - 1, u, base);

   if (psz)
   {

      psz[minimum(size - 1, size - 1 + res)] = '\0';

   }

   return res;

}


constexpr strsize _itoa_base(char* psz, strsize size, ::i64 i, int base)
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


inline strsize itoa_base(char* psz, strsize size, ::i64 i, int base)
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

         throw ::exception(::error_parsing);

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


inline ::i64 consume_i64(::ansi_range& range , int iBase = 10) { return consume_integral < ::i64 >(range, iBase); }
inline ::i32 consume_i32(::ansi_range& range , int iBase = 10) { return consume_integral < ::i32 >(range, iBase); }
inline ::i16 consume_i16(::ansi_range& range , int iBase = 10) { return consume_integral < ::i16 >(range, iBase); }
inline ::i8 consume_i8(::ansi_range& range, int iBase = 10) { return consume_integral < ::i8 >(range, iBase); }


inline ::u64 consume_u64(::ansi_range& range, int iBase = 10) { return consume_integral < ::u64 >(range, iBase); }
inline ::u32 consume_u32(::ansi_range& range, int iBase = 10) { return consume_integral < ::u32 >(range, iBase); }
inline ::u16 consume_u16(::ansi_range& range, int iBase = 10) { return consume_integral < ::u16 >(range, iBase); }
inline ::u8 consume_u8(::ansi_range& range, int iBase = 10) { return consume_integral < ::u8 >(range, iBase); }


inline long consume_long(::ansi_range& range, int iBase = 10) { return consume_integral < long >(range, iBase); }
inline unsigned long consume_unsigned_long(::ansi_range& range, int iBase = 10) { return consume_integral < unsigned long >(range, iBase); }
inline size_t consume_size_t(::ansi_range& range, int iBase = 10) { return consume_integral < size_t >(range, iBase); }


inline ::i64 as_i64(const ::scoped_string& scopedstr, int iBase = 10) { auto r = scopedstr(); return consume_i64(r, iBase); }
inline ::i32 as_i32(const ::scoped_string& scopedstr, int iBase = 10) { auto r = scopedstr(); return consume_i32(r, iBase); }
inline ::i32 as_i16(const ::scoped_string& scopedstr, int iBase = 10) { auto r = scopedstr(); return consume_i16(r, iBase); }
inline ::i8 as_i8(const ::scoped_string& scopedstr, int iBase = 10) { auto r = scopedstr(); return consume_i8(r, iBase); }


inline ::u64 as_u64(const ::scoped_string& scopedstr, int iBase = 10) { auto r = scopedstr(); return consume_u64(r, iBase); }
inline ::u32 as_u32(const ::scoped_string& scopedstr, int iBase = 10) { auto r = scopedstr(); return consume_u32(r, iBase); }
inline ::u32 as_u16(const ::scoped_string& scopedstr, int iBase = 10) { auto r = scopedstr(); return consume_u16(r, iBase); }
inline ::u8 as_u8(const ::scoped_string& scopedstr, int iBase = 10) { auto r = scopedstr(); return consume_u8(r, iBase); }


inline long as_long(const ::scoped_string& scopedstr, int iBase = 10) { auto r = scopedstr(); return consume_long(r, iBase); }
inline unsigned long as_unsigned_long(const ::scoped_string& scopedstr, int iBase = 10) { auto r = scopedstr(); return consume_unsigned_long(r, iBase); }
inline size_t as_size_t(const ::scoped_string& scopedstr, int iBase = 10) { auto r = scopedstr(); return consume_size_t(r, iBase); }

//inline ::i32 as_i32(const ::scoped_string & scopedstr, int iBase = 10)
//{
//
//   auto i = as_i64(psz, iBase);
//
//   if (i < INT_MIN || i > INT_MAX)
//   {
//
//      throw_exception(error_overflow);
//
//   }
//
//   return (::i32)i;
//
//}
//
//
//inline ::i16 as_i16(const ::scoped_string & scopedstr, int iBase = 10)
//{
//
//   auto i = as_i64(psz, iBase);
//
//   if (i < SHRT_MIN || i > SHRT_MAX)
//   {
//
//      throw_exception(error_overflow);
//
//   }
//
//   return (::i16)i;
//
//}
//
//
//inline ::i8 as_i8(const ::scoped_string & scopedstr, int iBase = 10)
//{
//
//   auto i = as_i64(psz, iBase);
//
//   if (i < CHAR_MIN || i > CHAR_MAX)
//   {
//
//      throw_exception(error_overflow);
//
//   }
//
//   return (::i8)i;
//
//}
//
//
//inline long as_long(const ::scoped_string & scopedstr, int iBase = 10)
//{
//
//   auto i = as_i64(psz, iBase);
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
//inline ::u64 as_u64(const ::scoped_string & scopedstr, int iBase = 10)
//{
//
//   const ::scoped_string & scopedstrEnd = nullptr;
//
//   return ansi_to_u64(psz, &pszEnd, iBase);
//
//}
//
//
//inline ::u32 as_u32(const ::scoped_string & scopedstr, int iBase = 10)
//{
//
//   auto u = as_u64(psz, iBase);
//
//   if (u > UINT_MAX)
//   {
//
//      throw_exception(error_overflow);
//
//   }
//
//   return (::u32)u;
//
//}
//
//
//inline ::u16 as_u16(const ::scoped_string & scopedstr, int iBase = 10)
//{
//
//   auto u = as_u64(psz, iBase);
//
//   if (u > USHRT_MAX)
//   {
//
//      throw_exception(error_overflow);
//
//   }
//
//   return (::u16)u;
//
//}
//
//
//inline ::u8 as_u8(const ::scoped_string & scopedstr, int iBase = 10)
//{
//
//   auto u = as_u64(psz, iBase);
//
//   if (u > UCHAR_MAX)
//   {
//
//      throw_exception(error_overflow);
//
//   }
//
//   return (::u8)u;
//
//}
//
//
//inline unsigned long as_unsigned_long(const ::scoped_string & scopedstr, int iBase = 10)
//{
//
//   auto u = as_u64(psz, iBase);
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
//   auto u = as_u64(psz, iBase);
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



//inline ::f64 as_f64(const ::scoped_string & scopedstr)
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
//   dst = ::as_f32(scopedstr);
//}
//
//inline void fromString(const ::scoped_string& scopedstr, ::nano2d::color& dst)
//{
//   dst = stringToColor(scopedstr);
//}


