#pragma once


#include "acme/prototype/prototype/hash32.h"


inline ::hash32 character_array_as_hash32(
   const ::ansi_character * p,
   ::character_count c)
{

   if (::is_null(p) || c <= 0)
   {

      return { 0 };

   }

   ::u32 uHash = 2166136261u;

   for (::character_count i = 0; i < c; ++i)
   {

      uHash ^= (::u8)p[i];

      uHash *= 16777619u;

   }

   // Final avalanche

   uHash ^= uHash >> 16;
   uHash *= 0x85ebca6bu;
   uHash ^= uHash >> 13;
   uHash *= 0xc2b2ae35u;
   uHash ^= uHash >> 16;

   return { uHash };

}


inline ::hash32 character_array_as_hash32(
   const ::wd16_character * p,
   ::character_count c)
{

   if (::is_null(p) || c <= 0)
   {

      return { 0 };

   }

   ::u32 uHash = 2166136261u;

   for (::character_count i = 0; i < c; ++i)
   {

      ::u16 u = (::u16)p[i];

      uHash ^= (::u8)(u);
      uHash *= 16777619u;

      uHash ^= (::u8)(u >> 8);
      uHash *= 16777619u;

   }

   uHash ^= uHash >> 16;
   uHash *= 0x85ebca6bu;
   uHash ^= uHash >> 13;
   uHash *= 0xc2b2ae35u;
   uHash ^= uHash >> 16;

   return { uHash };

}


inline ::hash32 character_array_as_hash32(
   const ::wd32_character * p,
   ::character_count c)
{

   if (::is_null(p) || c <= 0)
   {

      return { 0 };

   }

   ::u32 uHash = 2166136261u;

   for (::character_count i = 0; i < c; ++i)
   {

      ::u32 u = (::u32)p[i];

      uHash ^= (::u8)(u);
      uHash *= 16777619u;

      uHash ^= (::u8)(u >> 8);
      uHash *= 16777619u;

      uHash ^= (::u8)(u >> 16);
      uHash *= 16777619u;

      uHash ^= (::u8)(u >> 24);
      uHash *= 16777619u;

   }

   uHash ^= uHash >> 16;
   uHash *= 0x85ebca6bu;
   uHash ^= uHash >> 13;
   uHash *= 0xc2b2ae35u;
   uHash ^= uHash >> 16;

   return { uHash };

}


template < >
inline ::hash32 as_hash32 < const ::ansi_character * >(const ::ansi_character * const & p)
{

   auto psz = p;

   if (::is_null(psz) || *psz == 0)
   {

      return { 0 };

   }

   ::u32 uHash = 2166136261u;

   while (*psz)
   {

      uHash ^= (::u8)*psz;

      uHash *= 16777619u;

      ++psz;

   }

   uHash ^= uHash >> 16;
   uHash *= 0x85ebca6bu;
   uHash ^= uHash >> 13;
   uHash *= 0xc2b2ae35u;
   uHash ^= uHash >> 16;

   return { uHash };

}


template < >
inline ::hash32 as_hash32 < const ::wd16_character * >(const ::wd16_character * const & p)
{

   auto psz = p;

   if (::is_null(psz) || *psz == 0)
   {

      return { 0 };

   }

   ::u32 uHash = 2166136261u;

   while (*psz)
   {

      ::u16 u = (::u16)*psz;

      uHash ^= (::u8)u;
      uHash *= 16777619u;

      uHash ^= (::u8)(u >> 8);
      uHash *= 16777619u;

      ++psz;

   }

   uHash ^= uHash >> 16;
   uHash *= 0x85ebca6bu;
   uHash ^= uHash >> 13;
   uHash *= 0xc2b2ae35u;
   uHash ^= uHash >> 16;

   return { uHash };

}


template < >
inline ::hash32 as_hash32 < const ::wd32_character * >(const ::wd32_character * const & p)
{

   auto psz = p;

   if (::is_null(psz) || *psz == 0)
   {

      return { 0 };

   }

   ::u32 uHash = 2166136261u;

   while (*psz)
   {

      ::u32 u = (::u32)*psz;

      uHash ^= (::u8)u;
      uHash *= 16777619u;

      uHash ^= (::u8)(u >> 8);
      uHash *= 16777619u;

      uHash ^= (::u8)(u >> 16);
      uHash *= 16777619u;

      uHash ^= (::u8)(u >> 24);
      uHash *= 16777619u;

      ++psz;

   }

   uHash ^= uHash >> 16;
   uHash *= 0x85ebca6bu;
   uHash ^= uHash >> 13;
   uHash *= 0xc2b2ae35u;
   uHash ^= uHash >> 16;

   return { uHash };

}


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
//   ::u32 uHash = 0;
//
//   character_count i = 1;
//
//   for (; psz[i]; i++)
//   {
//
//      if (i % 2 == 1)
//      {
//
//         uHash = (uHash << 5) + ((::u32*)psz)[i >> 1];
//
//      }
//
//   }
//
//   psz += i;
//
//   i %= 2;
//
//   if (i > 0)
//   {
//
//      while (i-- >= 0) uHash = (uHash << 5) + *(--psz);
//
//   }
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
//   ::u32 uHash = 0;
//
//   for (; *psz; psz++)
//   {
//
//      uHash = (uHash << 5) + *psz;
//
//   }
//
//   return { uHash };
//
//}
//
//
//
