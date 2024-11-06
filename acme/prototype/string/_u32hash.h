#pragma once


//#include "acme/prototype/prototype/_u32hash.h"


template < >
inline ::u32hash unsigned_int_hash < const ::ansi_character * >(const ::ansi_character * const & p)
{

   auto psz = p;

   if (::is_null(psz) || *psz == 0)
   {

      return { 0 };

   }

   unsigned int uHash = 0;

   character_count i = 1;

   for(; psz[i]; i++)
   {

      if (i % 4 == 3)
      {

         uHash = (uHash << 5) + ((unsigned int*)psz)[i>>2];

      }

   }

   psz += i;

   i %= 4;

   if (i > 0)
   {

      while (i-- >= 0) uHash = (uHash << 5) + *(--psz);

   }

   return { uHash };

}


template < >
inline ::u32hash unsigned_int_hash < const ::wd16_character * >(const ::wd16_character * const & p)
{

   auto psz = p;

   if (::is_null(psz) || *psz == 0)
   {

      return { 0 };

   }

   unsigned int uHash = 0;

   character_count i = 1;

   for (; psz[i]; i++)
   {

      if (i % 2 == 1)
      {

         uHash = (uHash << 5) + ((unsigned int*)psz)[i >> 1];

      }

   }

   psz += i;

   i %= 2;

   if (i > 0)
   {

      while (i-- >= 0) uHash = (uHash << 5) + *(--psz);

   }

   return { uHash };

}


template < >
inline ::u32hash unsigned_int_hash < const ::wd32_character * >(const ::wd32_character * const & p)
{

   auto psz = p;

   if (::is_null(psz) || *psz == 0)
   {

      return { 0 };

   }

   unsigned int uHash = 0;

   for (; *psz; psz++)
   {

      uHash = (uHash << 5) + *psz;

   }

   return { uHash };

}



