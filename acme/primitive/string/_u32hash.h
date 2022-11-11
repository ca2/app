#pragma once


#include "acme/primitive/primitive/_u32hash.h"


template < >
inline u32hash u32_hash < const ansichar * >(const ansichar * psz)
{

   if (::is_null(psz) || *psz == 0)
   {

      return { 0 };

   }

   u32 uHash = 0;

   strsize i = 1;

   for(; psz[i]; i++)
   {

      if (i % 4 == 3)
      {

         uHash = (uHash << 5) + ((u32*)psz)[i>>2];

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
inline u32hash u32_hash < const wd16char * >(const wd16char * psz)
{

   if (::is_null(psz) || *psz == 0)
   {

      return { 0 };

   }

   u32 uHash = 0;

   strsize i = 1;

   for (; psz[i]; i++)
   {

      if (i % 2 == 1)
      {

         uHash = (uHash << 5) + ((u32*)psz)[i >> 1];

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


template<>
inline u32hash u32_hash < const wd32char * >(const wd32char * psz)
{

   if (::is_null(psz) || *psz == 0)
   {

      return { 0 };

   }

   u32 uHash = 0;

   for (; *psz; psz++)
   {

      uHash = (uHash << 5) + *psz;

   }

   return { uHash };

}



//template < >
//inline uhash u32_hash < const wchar_t * >(const wchar_t * psz)
//{
//
//#if WCHAR_T_SIZE == 16
//
//    return u32_hash((const wd16char *) psz);
//
//#else
//
//    return u32_hash((const wd32char *) psz);
//
//#endif
//
//}




