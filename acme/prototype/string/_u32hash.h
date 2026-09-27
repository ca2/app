#pragma once


#include "acme/prototype/prototype/hash32.h"


//inline ::hash32 character_array_as_hash32(
//   const ::ansi_character * p,
//   ::character_count c)
//{
//
//   if (::is_null(p) || c <= 0)
//   {
//
//      return { 0 };
//
//   }
//
//   ::u32 uHash = 2166136261u;
//
//   for (::character_count i = 0; i < c; ++i)
//   {
//
//      uHash ^= (::u8)p[i];
//
//      uHash *= 16777619u;
//
//   }
//
//   // Final avalanche
//
//   uHash ^= uHash >> 16;
//   uHash *= 0x85ebca6bu;
//   uHash ^= uHash >> 13;
//   uHash *= 0xc2b2ae35u;
//   uHash ^= uHash >> 16;
//
//   return { uHash };
//
//}
//
//
//inline ::hash32 character_array_as_hash32(
//   const ::wd16_character * p,
//   ::character_count c)
//{
//
//   if (::is_null(p) || c <= 0)
//   {
//
//      return { 0 };
//
//   }
//
//   ::u32 uHash = 2166136261u;
//
//   for (::character_count i = 0; i < c; ++i)
//   {
//
//      ::u16 u = (::u16)p[i];
//
//      uHash ^= (::u8)(u);
//      uHash *= 16777619u;
//
//      uHash ^= (::u8)(u >> 8);
//      uHash *= 16777619u;
//
//   }
//
//   uHash ^= uHash >> 16;
//   uHash *= 0x85ebca6bu;
//   uHash ^= uHash >> 13;
//   uHash *= 0xc2b2ae35u;
//   uHash ^= uHash >> 16;
//
//   return { uHash };
//
//}
//
//
//inline ::hash32 character_array_as_hash32(
//   const ::wd32_character * p,
//   ::character_count c)
//{
//
//   if (::is_null(p) || c <= 0)
//   {
//
//      return { 0 };
//
//   }
//
//   ::u32 uHash = 2166136261u;
//
//   for (::character_count i = 0; i < c; ++i)
//   {
//
//      ::u32 u = (::u32)p[i];
//
//      uHash ^= (::u8)(u);
//      uHash *= 16777619u;
//
//      uHash ^= (::u8)(u >> 8);
//      uHash *= 16777619u;
//
//      uHash ^= (::u8)(u >> 16);
//      uHash *= 16777619u;
//
//      uHash ^= (::u8)(u >> 24);
//      uHash *= 16777619u;
//
//   }
//
//   uHash ^= uHash >> 16;
//   uHash *= 0x85ebca6bu;
//   uHash ^= uHash >> 13;
//   uHash *= 0xc2b2ae35u;
//   uHash ^= uHash >> 16;
//
//   return { uHash };
//
//}
//
//
//template < >
//inline ::hash32 as_hash32 < const ::ansi_character * >(const ::ansi_character * const & p)
//{
//
//   auto psz = p;
//
//   if (::is_null(psz) || *psz == 0)
//   {
//
//      return { 0 };
//
//   }
//
//   ::u32 uHash = 2166136261u;
//
//   while (*psz)
//   {
//
//      uHash ^= (::u8)*psz;
//
//      uHash *= 16777619u;
//
//      ++psz;
//
//   }
//
//   uHash ^= uHash >> 16;
//   uHash *= 0x85ebca6bu;
//   uHash ^= uHash >> 13;
//   uHash *= 0xc2b2ae35u;
//   uHash ^= uHash >> 16;
//
//   return { uHash };
//
//}
//
//
//template < >
//inline ::hash32 as_hash32 < const ::wd16_character * >(const ::wd16_character * const & p)
//{
//
//   auto psz = p;
//
//   if (::is_null(psz) || *psz == 0)
//   {
//
//      return { 0 };
//
//   }
//
//   ::u32 uHash = 2166136261u;
//
//   while (*psz)
//   {
//
//      ::u16 u = (::u16)*psz;
//
//      uHash ^= (::u8)u;
//      uHash *= 16777619u;
//
//      uHash ^= (::u8)(u >> 8);
//      uHash *= 16777619u;
//
//      ++psz;
//
//   }
//
//   uHash ^= uHash >> 16;
//   uHash *= 0x85ebca6bu;
//   uHash ^= uHash >> 13;
//   uHash *= 0xc2b2ae35u;
//   uHash ^= uHash >> 16;
//
//   return { uHash };
//
//}
//
//
//template < >
//inline ::hash32 as_hash32 < const ::wd32_character * >(const ::wd32_character * const & p)
//{
//
//   auto psz = p;
//
//   if (::is_null(psz) || *psz == 0)
//   {
//
//      return { 0 };
//
//   }
//
//   ::u32 uHash = 2166136261u;
//
//   while (*psz)
//   {
//
//      ::u32 u = (::u32)*psz;
//
//      uHash ^= (::u8)u;
//      uHash *= 16777619u;
//
//      uHash ^= (::u8)(u >> 8);
//      uHash *= 16777619u;
//
//      uHash ^= (::u8)(u >> 16);
//      uHash *= 16777619u;
//
//      uHash ^= (::u8)(u >> 24);
//      uHash *= 16777619u;
//
//      ++psz;
//
//   }
//
//   uHash ^= uHash >> 16;
//   uHash *= 0x85ebca6bu;
//   uHash ^= uHash >> 13;
//   uHash *= 0xc2b2ae35u;
//   uHash ^= uHash >> 16;
//
//   return { uHash };
//
//}
//
//
////
////template < >
////inline ::hash32 as_hash32 < const ::wd16_character * >(const ::wd16_character * const & p)
////{
////
////   auto psz = p;
////
////   if (::is_null(psz) || *psz == 0)
////   {
////
////      return { 0 };
////
////   }
////
////   ::u32 uHash = 0;
////
////   character_count i = 1;
////
////   for (; psz[i]; i++)
////   {
////
////      if (i % 2 == 1)
////      {
////
////         uHash = (uHash << 5) + ((::u32*)psz)[i >> 1];
////
////      }
////
////   }
////
////   psz += i;
////
////   i %= 2;
////
////   if (i > 0)
////   {
////
////      while (i-- >= 0) uHash = (uHash << 5) + *(--psz);
////
////   }
////
////   return { uHash };
////
////}
////
////
////template < >
////inline ::hash32 as_hash32 < const ::wd32_character * >(const ::wd32_character * const & p)
////{
////
////   auto psz = p;
////
////   if (::is_null(psz) || *psz == 0)
////   {
////
////      return { 0 };
////
////   }
////
////   ::u32 uHash = 0;
////
////   for (; *psz; psz++)
////   {
////
////      uHash = (uHash << 5) + *psz;
////
////   }
////
////   return { uHash };
////
////}
////
////
////


#pragma once


#include "acme/prototype/prototype/hash32.h"


namespace character_hash32
{


   inline void hash_byte(::u32 & uHash, ::u8 u)
   {

      uHash ^= u;
      uHash *= 16777619u;

   }


   inline void hash_character(::u32 & uHash, ::ansi_character ch)
   {

      hash_byte(uHash, (::u8)ch);

   }


   inline void hash_character(::u32 & uHash, ::wd16_character ch)
   {

      ::u16 u = (::u16)ch;

      hash_byte(uHash, (::u8)u);
      hash_byte(uHash, (::u8)(u >> 8));

   }


   inline void hash_character(::u32 & uHash, ::wd32_character ch)
   {

      ::u32 u = (::u32)ch;

      hash_byte(uHash, (::u8)u);
      hash_byte(uHash, (::u8)(u >> 8));
      hash_byte(uHash, (::u8)(u >> 16));
      hash_byte(uHash, (::u8)(u >> 24));

   }


   inline void hash_character(::u32 & uHash, ::wide_character ch)
   {

      //
      // wchar_t / wide_character is generally:
      //
      // Windows       : 16 bits
      // Linux / Unix  : 32 bits
      //
      // Do not assume either representation.
      //

      if constexpr (sizeof(::wide_character) == 2)
      {

         ::u16 u = (::u16)ch;

         hash_byte(uHash, (::u8)u);
         hash_byte(uHash, (::u8)(u >> 8));

      }
      else if constexpr (sizeof(::wide_character) == 4)
      {

         ::u32 u = (::u32)ch;

         hash_byte(uHash, (::u8)u);
         hash_byte(uHash, (::u8)(u >> 8));
         hash_byte(uHash, (::u8)(u >> 16));
         hash_byte(uHash, (::u8)(u >> 24));

      }
      else
      {

         //
         // Extremely unusual wchar_t size.
         //
         // Hash its representation one byte at a time through
         // shifts rather than depending on host byte order.
         //

         using unsigned_wide =
            decltype((::wide_character)0 + (::u64)0);

         auto u = (unsigned_wide)ch;

         for (::memsize i = 0; i < sizeof(::wide_character); ++i)
         {

            hash_byte(uHash, (::u8)(u >> (i * 8)));

         }

      }

   }


   inline ::hash32 finish(::u32 uHash)
   {

      // Final avalanche

      uHash ^= uHash >> 16;
      uHash *= 0x85ebca6bu;
      uHash ^= uHash >> 13;
      uHash *= 0xc2b2ae35u;
      uHash ^= uHash >> 16;

      return { uHash };

   }


   template < typename CHARACTER >
   inline ::hash32 array(
      const CHARACTER * p,
      ::character_count c)
   {

      if (::is_null(p) || c <= 0)
      {

         return { 0 };

      }

      ::u32 uHash = 2166136261u;

      for (::character_count i = 0; i < c; ++i)
      {

         hash_character(uHash, p[i]);

      }

      return finish(uHash);

   }


   template < typename CHARACTER >
   inline ::hash32 zero_terminated(
      const CHARACTER * psz)
   {

      if (::is_null(psz) || *psz == 0)
      {

         return { 0 };

      }

      ::u32 uHash = 2166136261u;

      while (*psz)
      {

         hash_character(uHash, *psz);

         ++psz;

      }

      return finish(uHash);

   }


} // namespace character_hash32



inline ::hash32 character_array_as_hash32(
   const ::ansi_character * p,
   ::character_count c)
{

   return ::character_hash32::array(p, c);

}


inline ::hash32 character_array_as_hash32(
   const ::wd16_character * p,
   ::character_count c)
{

   return ::character_hash32::array(p, c);

}


inline ::hash32 character_array_as_hash32(
   const ::wd32_character * p,
   ::character_count c)
{

   return ::character_hash32::array(p, c);

}


inline ::hash32 character_array_as_hash32(
   const ::wide_character * p,
   ::character_count c)
{

   return ::character_hash32::array(p, c);

}



template < >
inline ::hash32 as_hash32 < const ::ansi_character * >(
   const ::ansi_character * const & p)
{

   return ::character_hash32::zero_terminated(p);

}


template < >
inline ::hash32 as_hash32 < const ::wd16_character * >(
   const ::wd16_character * const & p)
{

   return ::character_hash32::zero_terminated(p);

}


template < >
inline ::hash32 as_hash32 < const ::wd32_character * >(
   const ::wd32_character * const & p)
{

   return ::character_hash32::zero_terminated(p);

}


template < >
inline ::hash32 as_hash32 < const ::wide_character * >(
   const ::wide_character * const & p)
{

   return ::character_hash32::zero_terminated(p);

}
