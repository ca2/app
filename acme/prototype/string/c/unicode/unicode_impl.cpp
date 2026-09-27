// Created from _unicode by camilo on 2022-11-07 09:23 <3ThomasBorregaardSorensen!!
#include "platform.h"
#include <string.h>
//
// wide_character support
//
// wide_character is wchar_t and therefore it is a distinct C++ type from
// wd16_character (char16_t) and wd32_character (char32_t), even when they
// happen to have the same size.
//
// Do not reinterpret_cast wide_character * to wd16_character * or
// wd32_character *.
//
// Instead, treat:
//
// sizeof(wide_character) == 2 : UTF-16
// sizeof(wide_character) == 4 : UTF-32
//


namespace unicode_wide_detail
{


   template < typename CHARACTER >
   constexpr int utf_unit_size()
   {

      static_assert(
         sizeof(CHARACTER) == 1
         || sizeof(CHARACTER) == 2
         || sizeof(CHARACTER) == 4);

      return (int) sizeof(CHARACTER);

   }


   template < typename CHARACTER >
   character_count string_length(const CHARACTER * psz)
   {

      auto p = psz;

      while (*p)
      {

         ++p;

      }

      return p - psz;

   }


   template < typename CHARACTER >
   character_count normalize_source_length(
      const CHARACTER * psource,
      character_count srclen)
   {

      if (srclen >= 0)
      {

         return srclen;

      }

      //
      // Maintains the semantics suggested by the old
      // _utf_to_utf_length implementation:
      //
      //    string_length(psource) + srclen + 1
      //
      // Therefore:
      //
      //    -1 -> complete zero-terminated string
      //    -2 -> complete string except last character
      //    ...
      //

      auto len = string_length(psource);

      auto n = len + srclen + 1;

      return n > 0 ? n : 0;

   }


   template < typename CHARACTER >
   ::u32 decode(
      const CHARACTER * & p,
      const CHARACTER * end)
   {

      if constexpr (sizeof(CHARACTER) == 1)
      {

         //
         // UTF-8
         //

         if (p >= end)
         {

            return 0;

         }

         auto b0 = (::u8) *p++;

         if (b0 < 0x80)
         {

            return b0;

         }

         if ((b0 & 0xe0) == 0xc0)
         {

            if (p >= end)
            {

               return 0xfffd;

            }

            auto b1 = (::u8) *p++;

            if ((b1 & 0xc0) != 0x80)
            {

               return 0xfffd;

            }

            auto u =
               ((::u32)(b0 & 0x1f) << 6)
               | (::u32)(b1 & 0x3f);

            if (u < 0x80)
            {

               return 0xfffd;

            }

            return u;

         }

         if ((b0 & 0xf0) == 0xe0)
         {

            if (end - p < 2)
            {

               p = end;

               return 0xfffd;

            }

            auto b1 = (::u8) *p++;
            auto b2 = (::u8) *p++;

            if ((b1 & 0xc0) != 0x80
               || (b2 & 0xc0) != 0x80)
            {

               return 0xfffd;

            }

            auto u =
               ((::u32)(b0 & 0x0f) << 12)
               | ((::u32)(b1 & 0x3f) << 6)
               | (::u32)(b2 & 0x3f);

            if (u < 0x800)
            {

               return 0xfffd;

            }

            if (u >= 0xd800 && u <= 0xdfff)
            {

               return 0xfffd;

            }

            return u;

         }

         if ((b0 & 0xf8) == 0xf0)
         {

            if (end - p < 3)
            {

               p = end;

               return 0xfffd;

            }

            auto b1 = (::u8) *p++;
            auto b2 = (::u8) *p++;
            auto b3 = (::u8) *p++;

            if ((b1 & 0xc0) != 0x80
               || (b2 & 0xc0) != 0x80
               || (b3 & 0xc0) != 0x80)
            {

               return 0xfffd;

            }

            auto u =
               ((::u32)(b0 & 0x07) << 18)
               | ((::u32)(b1 & 0x3f) << 12)
               | ((::u32)(b2 & 0x3f) << 6)
               | (::u32)(b3 & 0x3f);

            if (u < 0x10000 || u > 0x10ffff)
            {

               return 0xfffd;

            }

            return u;

         }

         return 0xfffd;

      }
      else if constexpr (sizeof(CHARACTER) == 2)
      {

         //
         // UTF-16
         //

         if (p >= end)
         {

            return 0;

         }

         ::u32 u0 = (::u16) *p++;

         if (u0 >= 0xd800 && u0 <= 0xdbff)
         {

            if (p >= end)
            {

               return 0xfffd;

            }

            ::u32 u1 = (::u16) *p;

            if (u1 < 0xdc00 || u1 > 0xdfff)
            {

               return 0xfffd;

            }

            ++p;

            return
               0x10000
               + ((u0 - 0xd800) << 10)
               + (u1 - 0xdc00);

         }

         if (u0 >= 0xdc00 && u0 <= 0xdfff)
         {

            return 0xfffd;

         }

         return u0;

      }
      else
      {

         //
         // UTF-32
         //

         if (p >= end)
         {

            return 0;

         }

         ::u32 u = (::u32) *p++;

         if (u > 0x10ffff)
         {

            return 0xfffd;

         }

         if (u >= 0xd800 && u <= 0xdfff)
         {

            return 0xfffd;

         }

         return u;

      }

   }


   template < typename CHARACTER >
   character_count encoded_length(::u32 u)
   {

      if constexpr (sizeof(CHARACTER) == 1)
      {

         if (u <= 0x7f)
         {

            return 1;

         }

         if (u <= 0x7ff)
         {

            return 2;

         }

         if (u <= 0xffff)
         {

            return 3;

         }

         return 4;

      }
      else if constexpr (sizeof(CHARACTER) == 2)
      {

         return u <= 0xffff ? 1 : 2;

      }
      else
      {

         return 1;

      }

   }


   template < typename CHARACTER >
   CHARACTER * encode(
      CHARACTER * ptarget,
      ::u32 u)
   {

      if (u > 0x10ffff
         || (u >= 0xd800 && u <= 0xdfff))
      {

         u = 0xfffd;

      }

      if constexpr (sizeof(CHARACTER) == 1)
      {

         if (u <= 0x7f)
         {

            *ptarget++ = (CHARACTER) u;

         }
         else if (u <= 0x7ff)
         {

            *ptarget++ = (CHARACTER) (0xc0 | (u >> 6));
            *ptarget++ = (CHARACTER) (0x80 | (u & 0x3f));

         }
         else if (u <= 0xffff)
         {

            *ptarget++ = (CHARACTER) (0xe0 | (u >> 12));
            *ptarget++ = (CHARACTER) (0x80 | ((u >> 6) & 0x3f));
            *ptarget++ = (CHARACTER) (0x80 | (u & 0x3f));

         }
         else
         {

            *ptarget++ = (CHARACTER) (0xf0 | (u >> 18));
            *ptarget++ = (CHARACTER) (0x80 | ((u >> 12) & 0x3f));
            *ptarget++ = (CHARACTER) (0x80 | ((u >> 6) & 0x3f));
            *ptarget++ = (CHARACTER) (0x80 | (u & 0x3f));

         }

      }
      else if constexpr (sizeof(CHARACTER) == 2)
      {

         if (u <= 0xffff)
         {

            *ptarget++ = (CHARACTER) u;

         }
         else
         {

            u -= 0x10000;

            *ptarget++ =
               (CHARACTER) (0xd800 + (u >> 10));

            *ptarget++ =
               (CHARACTER) (0xdc00 + (u & 0x3ff));

         }

      }
      else
      {

         *ptarget++ = (CHARACTER) u;

      }

      return ptarget;

   }


   template <
      typename TARGET_CHARACTER,
      typename SOURCE_CHARACTER >
   character_count utf_length(
      const SOURCE_CHARACTER * psource,
      character_count srclen)
   {

      srclen =
         normalize_source_length(
            psource,
            srclen);

      auto p = psource;
      auto end = psource + srclen;

      character_count targetlen = 0;

      while (p < end)
      {

         auto u = decode(p, end);

         targetlen +=
            encoded_length < TARGET_CHARACTER >(u);

      }

      return targetlen;

   }


   template <
      typename TARGET_CHARACTER,
      typename SOURCE_CHARACTER >
   character_count utf_length2(
      const SOURCE_CHARACTER * psource,
      character_count & srclen)
   {

      srclen =
         normalize_source_length(
            psource,
            srclen);

      return utf_length < TARGET_CHARACTER >(
         psource,
         srclen);

   }


   template <
      typename TARGET_CHARACTER,
      typename SOURCE_CHARACTER >
   character_count utf_length(
      const SOURCE_CHARACTER * psource)
   {

      return utf_length < TARGET_CHARACTER >(
         psource,
         string_length(psource));

   }


   template <
      typename TARGET_CHARACTER,
      typename SOURCE_CHARACTER >
   void utf_convert(
      TARGET_CHARACTER * ptarget,
      const SOURCE_CHARACTER * psource,
      character_count srclen)
   {

      srclen =
         normalize_source_length(
            psource,
            srclen);

      auto p = psource;
      auto end = psource + srclen;

      while (p < end)
      {

         auto u = decode(p, end);

         ptarget = encode(ptarget, u);

      }

   }


   template <
      typename TARGET_CHARACTER,
      typename SOURCE_CHARACTER >
   void utf_convert(
      TARGET_CHARACTER * ptarget,
      const SOURCE_CHARACTER * psource)
   {

      auto srclen = string_length(psource);

      utf_convert(
         ptarget,
         psource,
         srclen);

      //
      // Zero-terminated overloads produce a zero-terminated
      // destination string.
      //

      auto targetlen =
         utf_length < TARGET_CHARACTER >(
            psource,
            srclen);

      ptarget[targetlen] = (TARGET_CHARACTER) 0;

   }


} // namespace unicode_wide_detail


namespace unicode_non_wide_detail
{


   template < typename TARGET_CHARACTER, typename SOURCE_CHARACTER >
   character_count utf_length(
      const SOURCE_CHARACTER * psource,
      character_count srclen)
   {

      if constexpr (std::same_as < TARGET_CHARACTER, SOURCE_CHARACTER >)
      {

         return ::unicode_wide_detail::normalize_source_length(psource, srclen);

      }
      else
      {

         return ::unicode_wide_detail::utf_length < TARGET_CHARACTER >(psource, srclen);

      }

   }


   template < typename TARGET_CHARACTER, typename SOURCE_CHARACTER >
   character_count utf_length2(
      const SOURCE_CHARACTER * psource,
      character_count & srclen)
   {

      srclen = ::unicode_wide_detail::normalize_source_length(psource, srclen);

      return utf_length < TARGET_CHARACTER >(psource, srclen);

   }


   template < typename TARGET_CHARACTER, typename SOURCE_CHARACTER >
   void utf_convert(
      TARGET_CHARACTER * ptarget,
      const SOURCE_CHARACTER * psource,
      character_count srclen)
   {

      srclen = ::unicode_wide_detail::normalize_source_length(psource, srclen);

      if constexpr (std::same_as < TARGET_CHARACTER, SOURCE_CHARACTER >)
      {

         memmove(ptarget, psource, srclen * sizeof(TARGET_CHARACTER));

      }
      else
      {

         ::unicode_wide_detail::utf_convert(ptarget, psource, srclen);

      }

   }


   template < typename TARGET_CHARACTER, typename SOURCE_CHARACTER >
   void utf_convert(
      TARGET_CHARACTER * ptarget,
      const SOURCE_CHARACTER * psource)
   {

      if constexpr (std::same_as < TARGET_CHARACTER, SOURCE_CHARACTER >)
      {

         auto srclen = ::unicode_wide_detail::string_length(psource);

         memmove(ptarget, psource, (srclen + 1) * sizeof(TARGET_CHARACTER));

      }
      else
      {

         ::unicode_wide_detail::utf_convert(ptarget, psource);

      }

   }


} // namespace unicode_non_wide_detail


#define DEFINE_NON_WIDE_UTF_PAIR(TARGET_CHARACTER, SOURCE_CHARACTER) \
   CLASS_DECL_ACME character_count utf_to_utf_length1( \
      const TARGET_CHARACTER *, \
      const SOURCE_CHARACTER * psource, \
      character_count srclen) \
   { \
      return ::unicode_non_wide_detail::utf_length < TARGET_CHARACTER >(psource, srclen); \
   } \
   CLASS_DECL_ACME character_count utf_to_utf_length2( \
      const TARGET_CHARACTER *, \
      const SOURCE_CHARACTER * psource, \
      character_count & srclen) \
   { \
      return ::unicode_non_wide_detail::utf_length2 < TARGET_CHARACTER >(psource, srclen); \
   } \
   CLASS_DECL_ACME character_count utf_to_utf_length( \
      const TARGET_CHARACTER *, \
      const SOURCE_CHARACTER * psource) \
   { \
      return ::unicode_non_wide_detail::utf_length < TARGET_CHARACTER >(psource, -1); \
   } \
   CLASS_DECL_ACME void utf_to_utf( \
      TARGET_CHARACTER * ptarget, \
      const SOURCE_CHARACTER * psource, \
      character_count srclen) \
   { \
      ::unicode_non_wide_detail::utf_convert(ptarget, psource, srclen); \
   } \
   CLASS_DECL_ACME void utf_to_utf( \
      TARGET_CHARACTER * ptarget, \
      const SOURCE_CHARACTER * psource) \
   { \
      ::unicode_non_wide_detail::utf_convert(ptarget, psource); \
   }


DEFINE_NON_WIDE_UTF_PAIR(::ansi_character, ::ansi_character)
DEFINE_NON_WIDE_UTF_PAIR(::ansi_character, ::wd16_character)
DEFINE_NON_WIDE_UTF_PAIR(::ansi_character, ::wd32_character)
DEFINE_NON_WIDE_UTF_PAIR(::wd16_character, ::ansi_character)
DEFINE_NON_WIDE_UTF_PAIR(::wd16_character, ::wd16_character)
DEFINE_NON_WIDE_UTF_PAIR(::wd16_character, ::wd32_character)
DEFINE_NON_WIDE_UTF_PAIR(::wd32_character, ::ansi_character)
DEFINE_NON_WIDE_UTF_PAIR(::wd32_character, ::wd16_character)
DEFINE_NON_WIDE_UTF_PAIR(::wd32_character, ::wd32_character)


#undef DEFINE_NON_WIDE_UTF_PAIR



//
// utf_to_utf_length1
//


// 10 wide wide
CLASS_DECL_ACME character_count utf_to_utf_length1(
   const ::wide_character *,
   const ::wide_character * psource,
   character_count srclen)
{

   //
   // Same encoding. Do not unnecessarily decode/re-encode.
   //

   return ::unicode_wide_detail::normalize_source_length(
      psource,
      srclen);

}


// 11 wide ::i8
CLASS_DECL_ACME character_count utf_to_utf_length1(
   const ::wide_character *,
   const_char_pointer psource,
   character_count srclen)
{

   return ::unicode_wide_detail::utf_length < ::wide_character >(
      psource,
      srclen);

}


// 12 ::i8 wide
CLASS_DECL_ACME character_count utf_to_utf_length1(
   const_char_pointer,
   const ::wide_character * psource,
   character_count srclen)
{

   return ::unicode_wide_detail::utf_length < ::ansi_character >(
      psource,
      srclen);

}


// 13 wide wd16
CLASS_DECL_ACME character_count utf_to_utf_length1(
   const ::wide_character *,
   const ::wd16_character * psource,
   character_count srclen)
{

   return ::unicode_wide_detail::utf_length < ::wide_character >(
      psource,
      srclen);

}


// 14 wd16 wide
CLASS_DECL_ACME character_count utf_to_utf_length1(
   const ::wd16_character *,
   const ::wide_character * psource,
   character_count srclen)
{

   return ::unicode_wide_detail::utf_length < ::wd16_character >(
      psource,
      srclen);

}


// 15 wide wd32
CLASS_DECL_ACME character_count utf_to_utf_length1(
   const ::wide_character *,
   const ::wd32_character * psource,
   character_count srclen)
{

   return ::unicode_wide_detail::utf_length < ::wide_character >(
      psource,
      srclen);

}


// 16 wd32 wide
CLASS_DECL_ACME character_count utf_to_utf_length1(
   const ::wd32_character *,
   const ::wide_character * psource,
   character_count srclen)
{

   return ::unicode_wide_detail::utf_length < ::wd32_character >(
      psource,
      srclen);

}



//
// utf_to_utf_length2
//


// 10 wide wide
CLASS_DECL_ACME character_count utf_to_utf_length2(
   const ::wide_character *,
   const ::wide_character * psource,
   character_count & srclen)
{

   srclen =
      ::unicode_wide_detail::normalize_source_length(
         psource,
         srclen);

   return srclen;

}


// 11 wide ::i8
CLASS_DECL_ACME character_count utf_to_utf_length2(
   const ::wide_character *,
   const_char_pointer psource,
   character_count & srclen)
{

   return ::unicode_wide_detail::utf_length2 < ::wide_character >(
      psource,
      srclen);

}


// 12 ::i8 wide
CLASS_DECL_ACME character_count utf_to_utf_length2(
   const_char_pointer,
   const ::wide_character * psource,
   character_count & srclen)
{

   return ::unicode_wide_detail::utf_length2 < ::ansi_character >(
      psource,
      srclen);

}


// 13 wide wd16
CLASS_DECL_ACME character_count utf_to_utf_length2(
   const ::wide_character *,
   const ::wd16_character * psource,
   character_count & srclen)
{

   return ::unicode_wide_detail::utf_length2 < ::wide_character >(
      psource,
      srclen);

}


// 14 wd16 wide
CLASS_DECL_ACME character_count utf_to_utf_length2(
   const ::wd16_character *,
   const ::wide_character * psource,
   character_count & srclen)
{

   return ::unicode_wide_detail::utf_length2 < ::wd16_character >(
      psource,
      srclen);

}


// 15 wide wd32
CLASS_DECL_ACME character_count utf_to_utf_length2(
   const ::wide_character *,
   const ::wd32_character * psource,
   character_count & srclen)
{

   return ::unicode_wide_detail::utf_length2 < ::wide_character >(
      psource,
      srclen);

}


// 16 wd32 wide
CLASS_DECL_ACME character_count utf_to_utf_length2(
   const ::wd32_character *,
   const ::wide_character * psource,
   character_count & srclen)
{

   return ::unicode_wide_detail::utf_length2 < ::wd32_character >(
      psource,
      srclen);

}



//
// utf_to_utf_length - zero terminated
//


CLASS_DECL_ACME character_count utf_to_utf_length(
   const ::wide_character *,
   const ::wide_character * psource)
{

   return wide_len(psource);

}


CLASS_DECL_ACME character_count utf_to_utf_length(
   const ::wide_character *,
   const_char_pointer psource)
{

   return ::unicode_wide_detail::utf_length < ::wide_character >(
      psource);

}


CLASS_DECL_ACME character_count utf_to_utf_length(
   const_char_pointer,
   const ::wide_character * psource)
{

   return ::unicode_wide_detail::utf_length < ::ansi_character >(
      psource);

}


CLASS_DECL_ACME character_count utf_to_utf_length(
   const ::wide_character *,
   const ::wd16_character * psource)
{

   return ::unicode_wide_detail::utf_length < ::wide_character >(
      psource);

}


CLASS_DECL_ACME character_count utf_to_utf_length(
   const ::wd16_character *,
   const ::wide_character * psource)
{

   return ::unicode_wide_detail::utf_length < ::wd16_character >(
      psource);

}


CLASS_DECL_ACME character_count utf_to_utf_length(
   const ::wide_character *,
   const ::wd32_character * psource)
{

   return ::unicode_wide_detail::utf_length < ::wide_character >(
      psource);

}


CLASS_DECL_ACME character_count utf_to_utf_length(
   const ::wd32_character *,
   const ::wide_character * psource)
{

   return ::unicode_wide_detail::utf_length < ::wd32_character >(
      psource);

}



//
// utf_to_utf - explicit source length
//


CLASS_DECL_ACME void utf_to_utf(
   ::wide_character * ptarget,
   const ::wide_character * psource,
   character_count srclen)
{

   overlap_safe_widencpy(
      ptarget,
      psource,
      srclen);

}


CLASS_DECL_ACME void utf_to_utf(
   ::wide_character * ptarget,
   const_char_pointer psource,
   character_count srclen)
{

   ::unicode_wide_detail::utf_convert(
      ptarget,
      psource,
      srclen);

}


CLASS_DECL_ACME void utf_to_utf(
   ::ansi_character * ptarget,
   const ::wide_character * psource,
   character_count srclen)
{

   ::unicode_wide_detail::utf_convert(
      ptarget,
      psource,
      srclen);

}


CLASS_DECL_ACME void utf_to_utf(
   ::wide_character * ptarget,
   const ::wd16_character * psource,
   character_count srclen)
{

   ::unicode_wide_detail::utf_convert(
      ptarget,
      psource,
      srclen);

}


CLASS_DECL_ACME void utf_to_utf(
   ::wd16_character * ptarget,
   const ::wide_character * psource,
   character_count srclen)
{

   ::unicode_wide_detail::utf_convert(
      ptarget,
      psource,
      srclen);

}


CLASS_DECL_ACME void utf_to_utf(
   ::wide_character * ptarget,
   const ::wd32_character * psource,
   character_count srclen)
{

   ::unicode_wide_detail::utf_convert(
      ptarget,
      psource,
      srclen);

}


CLASS_DECL_ACME void utf_to_utf(
   ::wd32_character * ptarget,
   const ::wide_character * psource,
   character_count srclen)
{

   ::unicode_wide_detail::utf_convert(
      ptarget,
      psource,
      srclen);

}



//
// utf_to_utf - zero terminated
//


CLASS_DECL_ACME void utf_to_utf(
   ::wide_character * ptarget,
   const ::wide_character * psource)
{

   wide_cpy(ptarget, psource);

}


CLASS_DECL_ACME void utf_to_utf(
   ::wide_character * ptarget,
   const_char_pointer psource)
{

   ::unicode_wide_detail::utf_convert(
      ptarget,
      psource);

}


CLASS_DECL_ACME void utf_to_utf(
   ::ansi_character * ptarget,
   const ::wide_character * psource)
{

   ::unicode_wide_detail::utf_convert(
      ptarget,
      psource);

}


CLASS_DECL_ACME void utf_to_utf(
   ::wide_character * ptarget,
   const ::wd16_character * psource)
{

   ::unicode_wide_detail::utf_convert(
      ptarget,
      psource);

}


CLASS_DECL_ACME void utf_to_utf(
   ::wd16_character * ptarget,
   const ::wide_character * psource)
{

   ::unicode_wide_detail::utf_convert(
      ptarget,
      psource);

}


CLASS_DECL_ACME void utf_to_utf(
   ::wide_character * ptarget,
   const ::wd32_character * psource)
{

   ::unicode_wide_detail::utf_convert(
      ptarget,
      psource);

}


CLASS_DECL_ACME void utf_to_utf(
   ::wd32_character * ptarget,
   const ::wide_character * psource)
{

   ::unicode_wide_detail::utf_convert(
      ptarget,
      psource);

}


CLASS_DECL_ACME ::i32 unicode_index(
   const ::wide_character * psz)
{

   ::i32 len;

   return unicode_index_length(psz, len);

}


CLASS_DECL_ACME bool unicode_is_whitespace(
   const ::wide_character * psz)
{

   return unicode_is_whitespace(unicode_index(psz));

}


CLASS_DECL_ACME ::i32 unicode_len(
   const ::wide_character * psz)
{

   ::i32 len;

   unicode_index_length(psz, len);

   return len;

}
