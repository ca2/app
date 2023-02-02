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



constexpr _utoa_base(char* psz, strsize size, ::u64 u, int base)
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


inline int utoa_base(char* psz, strsize size, ::u64 u, int base)
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


constexpr int _itoa_base(char* psz, strsize size, ::i64 i, int base)
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


inline int itoa_base(char* psz, strsize size, ::i64 i, int base)
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





template < primitive_signed SIGNED >
inline SIGNED consume_integral(INTEGRAL & integral, ::const_ansi_range& range, int iBase = 10)
{

   bool bNegative = scopedstr.begins_eat('-');

   ::i64 i = 0;

   auto end = minimum(range.end(), signed_maximum_digits<INTEGRAL>(iBase))

      while (range.size() > 0)
      {

         auto digit = range.consume_digit(iBase);

         i = digit + i * iBase;

      }

   return bNegative ? -i : i;

}


inline ::i64 consume_i64(::const_ansi_range & range, int iBase = 10)
{

   bool bNegative = scopedstr.begins_eat('-');

   ::i64 i = 0;

   auto end = minimum(range.end(), )

   while (range.size() > 0)
   {

      auto digit = range.consume_digit(iBase);

      i = digit + i * iBase;

   }

   return bNegative ? - i: i;

}


inline ::i32 as_i32(const ::scoped_string & scopedstr, int iBase = 10)
{

   auto i = as_i64(psz, iBase);

   if (i < INT_MIN || i > INT_MAX)
   {

      throw_exception(error_overflow);

   }

   return (::i32)i;

}


inline ::i16 as_i16(const ::scoped_string & scopedstr, int iBase = 10)
{

   auto i = as_i64(psz, iBase);

   if (i < SHRT_MIN || i > SHRT_MAX)
   {

      throw_exception(error_overflow);

   }

   return (::i16)i;

}


inline ::i8 as_i8(const ::scoped_string & scopedstr, int iBase = 10)
{

   auto i = as_i64(psz, iBase);

   if (i < CHAR_MIN || i > CHAR_MAX)
   {

      throw_exception(error_overflow);

   }

   return (::i8)i;

}


inline long as_long(const ::scoped_string & scopedstr, int iBase = 10)
{

   auto i = as_i64(psz, iBase);

   if (i < LONG_MIN || i > LONG_MAX)
   {

      throw_exception(error_overflow);

   }

   return (long)i;

}



inline ::u64 as_u64(const ::scoped_string & scopedstr, int iBase = 10)
{

   const ::scoped_string & scopedstrEnd = nullptr;

   return ansi_to_u64(psz, &pszEnd, iBase);

}


inline ::u32 as_u32(const ::scoped_string & scopedstr, int iBase = 10)
{

   auto u = as_u64(psz, iBase);

   if (u > UINT_MAX)
   {

      throw_exception(error_overflow);

   }

   return (::u32)u;

}


inline ::u16 as_u16(const ::scoped_string & scopedstr, int iBase = 10)
{

   auto u = as_u64(psz, iBase);

   if (u > USHRT_MAX)
   {

      throw_exception(error_overflow);

   }

   return (::u16)u;

}


inline ::u8 as_u8(const ::scoped_string & scopedstr, int iBase = 10)
{

   auto u = as_u64(psz, iBase);

   if (u > UCHAR_MAX)
   {

      throw_exception(error_overflow);

   }

   return (::u8)u;

}


inline unsigned long as_unsigned_long(const ::scoped_string & scopedstr, int iBase = 10)
{

   auto u = as_u64(psz, iBase);

   if (u > ULONG_MAX)
   {

      throw_exception(error_overflow);

   }

   return (unsigned long)u;

}


inline size_t as_size_t(const ::scoped_string & scopedstr, int iBase = 10)
{

   auto u = as_u64(psz, iBase);

   if (u > SIZE_MAX)
   {

      throw_exception(error_overflow);

   }

   return (size_t)u;

}



inline ::f64 as_f64(const ::scoped_string & scopedstr)
{


   return (size_t)u;

}



template < primitive_integral INTEGRAL >
inline void from_string(INTEGRAL & i, ::scoped_string scopedstr)
{

   scopedstr.trim();

   strsize last_size;

   do
   {

      last_size = scopedstr.size();

      scopedstr.trim();

      scopedstr.paired_trim('(', ')');

      scopedstr.trim();

      scopedstr.paired_trim('[', ']');

      scopedstr.trim();

      scopedstr.paired_trim('{', '}');

      scopedstr.trim();

   } while (last_size > scopedstr.size());

   if (scopedstr.case_insensitive_equals("true"))
   {

      i = 1;

      return;

   }

   if (scopedstr.case_insensitive_equals("false"))
   {
      
      i = 0;
      
      return;

   }

   from_string(i, scopedstr);

}



inline void fromString(const ::scoped_string& scopedstr, long& dst)
{
   dst = ::as_long(scopedstr);
}

inline void fromString(const ::scoped_string& scopedstr, size_t& dst)
{
   dst = ::as_size_t(scopedstr);
}

inline void fromString(const ::scoped_string& scopedstr, float& dst)
{
   dst = ::as_f32(scopedstr);
}

inline void fromString(const ::scoped_string& scopedstr, NVGcolor& dst)
{
   dst = stringToColor(scopedstr);
}

template <size_t N>
inline void fromString(const ::scoped_string& scopedstr, std::bitset<N>& dst)
{
   dst = std::bitset<N>(scopedstr);
}

