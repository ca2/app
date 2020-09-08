#pragma once


template < >
inline uptr uptr_hash < const char * >(const char * psz)
{

   if (::is_null(psz) || *psz == 0)
   {

      return 0;

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

   return uHash;

}


template < >
inline uptr uptr_hash < const u16 * >(const u16 * psz)
{

   if (::is_null(psz) || *psz == 0)
   {

      return 0;

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

   return uHash;

}


template<>
inline uptr uptr_hash < const u32 * >(const u32 * psz)
{

   if (::is_null(psz) || *psz == 0)
   {

      return 0;

   }

   u32 uHash = 0;

   for (; *psz; psz++)
   {

      uHash = (uHash << 5) + *psz;

   }

   return uHash;

}


//template<>
//inline u64 uptr_hash < const char* >(const char* psz)
//{
//
//   if (::is_null(psz) || *psz == 0)
//   {
//
//      return 0;
//
//   }
//
//   u32 uHash = 0;
//
//   strsize i = 1;
//
//   for (; psz[i]; i++)
//   {
//
//      if (i % 8 == 7)
//      {
//
//         uHash = (uHash << 5) + ((u32*)psz)[i >> 3];
//
//      }
//
//   }
//
//   psz += i;
//
//   i %= 8;
//
//   if (i > 0)
//   {
//
//      while (i-- >= 0) uHash = (uHash << 5) + *(--psz);
//
//   }
//
//   return uHash;
//
//}


//template<>
//inline u64 uptr_hash < const u16 * >(const u16 * psz)
//{
//
//   if (::is_null(psz) || *psz == 0)
//   {
//
//      return 0;
//
//   }
//
//   u32 uHash = 0;
//
//   strsize i = 1;
//
//   for (; psz[i]; i++)
//   {
//
//      if (i % 4 == 3)
//      {
//
//         uHash = (uHash << 5) + ((u32*)psz)[i >> 2];
//
//      }
//
//   }
//
//   psz += i;
//
//   i %= 4;
//
//   if (i > 0)
//   {
//
//      while (i-- >= 0) uHash = (uHash << 5) + *(--psz);
//
//   }
//
//   return uHash;
//
//}


//template<>
//inline u64 uptr_hash < const u32 * >(const u32 * psz)
//{
//
//   if (::is_null(psz) || *psz == 0)
//   {
//
//      return 0;
//
//   }
//
//   u32 uHash = 0;
//
//   strsize i = 1;
//
//   for (; psz[i]; i++)
//   {
//
//      if (i % 2 == 1)
//      {
//
//         uHash = (uHash << 5) + ((u32*)psz)[i >> 1];
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
//   return uHash;
//
//}


template < >
inline uptr uptr_hash < const wchar_t * >(const wchar_t * psz)
{

#if WCHAR_T_SIZE == 16

    return uptr_hash((const u16 *) psz);

#else

    return uptr_hash((const u32 *) psz);

#endif

}

//
//#if !defined(LINUX)
//
//template<>
//inline uptr uptr_hash < const unichar * > (const unichar* key)
//{
//
//#if WCHAR_T_SIZE == 16
//
//    return uptr_hash((const u16 *) psz);
//
//#else
//
//    return uptr_hash((const u32 *) psz);
//
//#endif
//
//}
//
//#endif



