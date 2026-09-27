//
// Created by camilo on 9/26/2026. <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
//
#pragma once


inline ::i32 unicode_index_length(
   const ::wide_character * psz,
   ::i32 & len)
{

   if constexpr (sizeof(::wide_character) == 2)
   {

      //
      // wide_character is UTF-16.
      //

      auto uFirst = (::u32)(::u16)psz[0];

      if (uFirst >= 0xd800 && uFirst <= 0xdbff)
      {

         auto uSecond = (::u32)(::u16)psz[1];

         if (uSecond >= 0xdc00 && uSecond <= 0xdfff)
         {

            len = 2;

            return (::i32)(
               0x10000
               + ((uFirst - 0xd800) << 10)
               + (uSecond - 0xdc00));

         }

         //
         // Invalid high surrogate.
         //
         // If your existing wd16 implementation uses another
         // convention here, mirror that convention instead.
         //

         len = 1;

         return (::i32)0xfffd;

      }

      if (uFirst >= 0xdc00 && uFirst <= 0xdfff)
      {

         //
         // Isolated low surrogate.
         //

         len = 1;

         return (::i32)0xfffd;

      }

      len = 1;

      return (::i32)uFirst;

   }
   else if constexpr (sizeof(::wide_character) == 4)
   {

      //
      // wide_character is UTF-32.
      //

      auto u = (::u32)psz[0];

      len = 1;

      if (u > 0x10ffff)
      {

         return (::i32)0xfffd;

      }

      if (u >= 0xd800 && u <= 0xdfff)
      {

         return (::i32)0xfffd;

      }

      return (::i32)u;

   }
   else
   {

      static_assert(
         sizeof(::wide_character) == 2
         || sizeof(::wide_character) == 4,
         "Unsupported wide_character size");

      len = 0;

      return -1;

   }

}